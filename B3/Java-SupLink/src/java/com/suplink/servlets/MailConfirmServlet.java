package com.suplink.servlets;

import com.suplink.dao.SuplinkDAO;
import com.suplink.dao.UsersDAO;
import com.suplink.entities.Users;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "MailConfirmServlet", urlPatterns = {"/servlets/mailconfirm"})
public class MailConfirmServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            Integer id = Integer.parseInt(request.getParameter("id"));
            String hash = request.getParameter("hash").toLowerCase();
            
            // get user info
            Users user = UsersDAO.getUserByID(id);
            
            // and compare with hash.
            if(!hash.equalsIgnoreCase(SuplinkDAO.MD5Hash(user.getEmail()+user.getPassword())))
                throw new Exception("Bad security checksum to activate user account.");
            
            // if it's match activate user.
            UsersDAO.activateUser(user);
            
            request.setAttribute("success_handler", "Account validation complete.");
        } catch (Exception e) {
            request.setAttribute("error_handler", e);
        } finally {
            request.getRequestDispatcher("/dashboard").forward(request, response);
        }
    }

}
