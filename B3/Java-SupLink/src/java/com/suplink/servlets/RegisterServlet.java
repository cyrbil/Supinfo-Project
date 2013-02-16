package com.suplink.servlets;

//<editor-fold defaultstate="collapsed" desc="imports">
import com.mysql.jdbc.exceptions.jdbc4.MySQLIntegrityConstraintViolationException;
import com.suplink.dao.SuplinkDAO;
import com.suplink.dao.UsersDAO;
import com.suplink.entities.Users;
import com.suplink.tools.Mailer;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
//</editor-fold>

@WebServlet(name = "RegisterServlet", urlPatterns = {"/servlets/register"})
public class RegisterServlet extends HttpServlet {
    private final String FORM_MAIL_NAME = "register_mail";
    private final String FORM_PASSWORD_NAME = "register_password";
    private final String FORM_CONFIRM_NAME = "register_comfirm";
    private final String MAIL_SUBJECT = "Welcome to SupLink";
    private final String MAIL_CONTENT = "Welcome to SupLink,\n"
            + "To complete your registration please use this link:\n"
            + "http://localhost:8084/SupLink/mailconfirm/";
    
    
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("/dashboard").forward(req, resp);
    }
    
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        //check if we are already auhentified,
        // if so, redirect to dashboard
        if(request.getSession().getAttribute("user") != null) {
            request.getRequestDispatcher("/dashboard").forward(request, response);
            return;
        }
        
        // look for params
        try {
            boolean error = false;
            String mail = request.getParameter(FORM_MAIL_NAME).toLowerCase().trim();
            // to string is useless, but if param doesn't exist it fires an null exception
            // so we know than param is invalid or inexistant
            String password = request.getParameter(FORM_PASSWORD_NAME).toString();
            String passConfirm = request.getParameter(FORM_CONFIRM_NAME).toString();
            
            InternetAddress emailAddr = null;
            try {
                emailAddr = new InternetAddress(mail, true);
                emailAddr.validate();
            } catch(AddressException ex) { // if email is invalid
                Logger.getLogger(RegisterServlet.class.getName()).log(Level.ALL, "User enter an invalid email when register");
                request.setAttribute("error_register_invalid_mail", true);
                error = true;
            }
            
            if(password.length() < 6) {
                Logger.getLogger(RegisterServlet.class.getName()).log(Level.ALL, "User enter an invalid password when register");
                request.setAttribute("error_register_password_policy", true);
                error = true;
            }
            
            if(!password.equals(passConfirm)) { // password are differents ...
                Logger.getLogger(RegisterServlet.class.getName()).log(Level.ALL, "User enter an invalid password comfirmation when register");
                request.setAttribute("error_register_password_differ", true);
                error = true;
            }
            
            
            
            if(!error) {
                // try insert into DB our new user
                try {
                    Users user = UsersDAO.create(mail, password);
                    // every thing is fine form here ?
                    // ok user is registred, send an email to confirm.
                    try {
                        Mailer.send(emailAddr, MAIL_SUBJECT, 
                                MAIL_CONTENT + SuplinkDAO.MD5Hash(user.getEmail()+user.getPassword()) + user.getId());
                        request.setAttribute("success_handler", "Inscription nearly complete, please check your mail to get your validation link and continue with us :) !");
                    } catch (Exception ex) {
                        Logger.getLogger(RegisterServlet.class.getName()).log(Level.WARNING, "Failed to send registration mail");
                        // worst case, we have to undo user insert
                        try { UsersDAO.delete(user); } 
                         // then display error ...
                        finally { throw new Exception("Fail to send mail, please check given address or contact administrator.\n" + ex.getMessage(), ex); }
                    }
                } catch (Exception ex) {
                    if(ex.getCause() != null && ex.getCause().getCause() != null && 
                            ex.getCause().getCause() instanceof MySQLIntegrityConstraintViolationException) {
                        throw new Exception("This email is already affiliated to an account ...", ex);
                    }
                    Logger.getLogger(RegisterServlet.class.getName()).log(Level.WARNING, "Failed to create new user when registering");
                    throw new Exception("Server have return an internal error when creating new user.\n" + ex.getMessage(), ex);
                }
            } else {
                Logger.getLogger(RegisterServlet.class.getName()).log(Level.WARNING, "Errors during registration, abording...");
                throw new Exception("Invalid form values, please check that all input are fill and valid.");
            }
        } catch (Exception e) {
            // ok, if we get here, something when wrong.
            // but we don't care because every errors have been handled
            // we just give exception to our page as a param.
            request.setAttribute("error_handler", new Exception("Error(s) occures during registration process.\n" + e.getMessage(), e));
        } finally {
            // damn yes we finally get here. 
            // load my damn html page bitch !
            request.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
        }
        
        
    }
}
