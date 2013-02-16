package com.suplink.servlets.auth;

import com.suplink.dao.LinksDAO;
import com.suplink.entities.Links;
import com.suplink.entities.Users;
import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "DashboardServlet", urlPatterns = {"/auth/dashboard"})
public class DashboardServlet extends HttpServlet {
    // use service because we want all methods to be handled here. (majorly get and post ...)
    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            // retrieve user links.
            Users user = (Users) request.getSession().getAttribute("user");
            List<Links> userLinks = LinksDAO.getAllUserLink(user);
            // pass them to our page
            request.setAttribute("user_links", userLinks);
        } catch (Exception e) {
            request.setAttribute("error_handler", e);
        } finally {
            // simple as fuck; just show our page !
            request.getRequestDispatcher("/WEB-INF/dashboard.jsp").forward(request, response);
        }
        
    }
    
    
}
