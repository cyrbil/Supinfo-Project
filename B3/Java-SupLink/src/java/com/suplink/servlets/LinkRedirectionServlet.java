package com.suplink.servlets;

import com.suplink.dao.LinksDAO;
import com.suplink.entities.Links;
import java.io.IOException;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "LinkRedirectionServlet", urlPatterns = {"/servlets/linkRedirection"})
public class LinkRedirectionServlet extends HttpServlet {

    @Override
    protected void service(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            String id = req.getParameter("id");
            
            // get link associated
            Links link = LinksDAO.getLinkByID(id);
            if(link == null) {
                throw new Exception("This short url does not exist. (yet !)");
            }
            if(!link.isEnabled())
                throw new Exception("This link have been disable.");
            
            // add browser information
            String referrer = "direct";
            try {
                URL url = new URL(req.getHeader("referer"));
                referrer = url.getHost();
            } catch(Exception e) {}
            
            
            try {
               LinksDAO.addRedirectionInfo(
                    link,
                    req.getLocale().getISO3Country(),
                    referrer
                ); 
            } catch (Exception e) {
                throw new Exception("Fail to add redirection information into database.", e);
            }
            
            // finally redirect
            resp.sendRedirect(link.getUrl());
        } catch (Exception e) {
            req.setAttribute("error_handler", e);
            req.getRequestDispatcher("/dashboard").forward(req, resp);
        }
    }
    
}
