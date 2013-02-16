package com.suplink.servlets;

import com.suplink.dao.UsersDAO;
import com.suplink.entities.Users;
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


@WebServlet(name = "LoginServlet", urlPatterns = {"/servlets/login"})
public class LoginServlet extends HttpServlet {
    private final String FORM_MAIL_NAME = "login_mail";
    private final String FORM_PASSWORD_NAME = "login_password";

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
        
        try {
            String username;
            String password;
            try {
                // check params
                username = request.getParameter(FORM_MAIL_NAME).toLowerCase().trim();
                // to string is useless, but if param doesn't exist it fires an null exception
                // so we know than param is invalid or inexistant
                password = request.getParameter(FORM_PASSWORD_NAME).toString();
            } catch (Exception e) {
                throw new Exception("All input field must be fill.");
            }
            
            // if arrives here, params exist, so valid them
            // only email need validation, because password will be hashed and we don't really care about what it contain
            InternetAddress emailAddr = null;
            try {
                emailAddr = new InternetAddress(username, true);
                emailAddr.validate();
            } catch(AddressException ex) { // if email is invalid
                Logger.getLogger(RegisterServlet.class.getName()).log(Level.ALL, "User enter an invalid email when register");
                request.setAttribute("error_login_invalid_mail", true);
                // we don't want to continu since we know email is invalid.
                throw new Exception("Invalid email address given.");
            }
            // see if match db entry
            Users user;
            try {
                user = UsersDAO.exist(username, password, true); // last param specifie that user account must have been activated
            } catch (Exception ex) {
                throw new Exception("Database error when try to login user.", ex);
            }
            if (user == null) {
                throw new Exception("Bad email address or password. Please verify what you've typed.");
            }
            // create user session
            request.getSession().setAttribute("user", user);
            // arrive here, well we are logged.
            // so redirect to dashboard and display sweet message
            request.setAttribute("success_handler", "You are now logged, enjoy your session !");
            request.getRequestDispatcher("/dashboard").forward(request, response);
        } catch (Exception e) {
            // ok, if we get here, something when wrong.
            // but we don't care because every errors have been handled
            // we just give exception to our page as a param.
            request.setAttribute("error_handler", new Exception("Error(s) occures during login process.\n" + e.getMessage(), e));
            // load my damn html page bitch !
            request.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
        }
    }
}
