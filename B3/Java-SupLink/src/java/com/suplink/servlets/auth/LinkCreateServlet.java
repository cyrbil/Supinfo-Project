package com.suplink.servlets.auth;

import com.mysql.jdbc.exceptions.jdbc4.MySQLIntegrityConstraintViolationException;
import com.suplink.dao.LinksDAO;
import com.suplink.entities.Users;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "LinkCreateServlet", urlPatterns = {"/auth/link/create"})
public class LinkCreateServlet extends HttpServlet {
    private static final String FORM_LINK_NAME  = "link_name";
    private static final String FORM_LINK_ID    = "link_id";
    private static final String FORM_LINK_URL   = "link_url";
    

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            // get params
            String name = request.getParameter(FORM_LINK_NAME);
            String id = request.getParameter(FORM_LINK_ID).toLowerCase();
            String url = request.getParameter(FORM_LINK_URL);
            Users user = (Users) request.getSession().getAttribute("user");
            
            // parse them
            if(name.length() > 30)
                throw new Exception("Name must not lenght more than 30 characters.");
            if(name.length() < 4)
                throw new Exception("Name must lenght at least 4 characters.");
            
            if(!id.isEmpty() && !id.matches("^[a-z0-9]{1,12}$"))
                throw new Exception("ID can only contain 1 to 12 alphanumeric characters.");
            
            try { new URL(url); }
            catch (MalformedURLException ex) {
                throw new Exception("Url must be a valid link.");
            }
            try {
                // give to DAO to create link
                LinksDAO.create(name, id, url, user);
            } catch (Exception ex) {
                if(ex.getCause() != null && ex.getCause().getCause() != null && 
                        ex.getCause().getCause() instanceof MySQLIntegrityConstraintViolationException) {
                    throw new Exception("This link id already exist ...", ex);
                }
                throw new Exception("Server have retrun an error when creating new shorten url", ex);
            }
            request.setAttribute("success_handler", "Link created !");
        } catch (Exception e) {
            request.setAttribute("error_handler", e);
        } finally {
            request.getRequestDispatcher("/dashboard").forward(request, response);
        }
    }

    
}
