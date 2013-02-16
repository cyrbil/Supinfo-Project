package com.suplink.servlets.auth;

import com.suplink.dao.LinksDAO;
import com.suplink.entities.Links;
import com.suplink.entities.Users;
import java.io.IOException;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "LinkManagement", urlPatterns = {"/auth/linkManagement"})
public class LinkManagement extends HttpServlet {
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String linkId = request.getParameter("id");
        String action = request.getParameter("action");
        Links link = null;
        
        try {
            // look if it's a link of actual user
            if(!LinksDAO.isUserLink(linkId, (Users) request.getSession().getAttribute("user"))) {
                // if not, we don't want to allow him to see anything... so redirect
                try {
                request.getRequestDispatcher("/dashboard").forward(request, response);
                return;
                } catch (Exception e) { }
            }
            link = LinksDAO.getLinkByID(linkId);
            request.setAttribute("link", link);
            
            if(action.equalsIgnoreCase("enable")){
                try {
                    LinksDAO.doEnable(link);
                    request.setAttribute("success_handler", "Link have been enabled.");
                } catch (Exception e) {
                    throw new Exception("Can't enable link :S", e);
                }
            } else if(action.equalsIgnoreCase("disable")) {
                try {
                    LinksDAO.doDisable(link);
                    request.setAttribute("success_handler", "Link have been disabled.");
                } catch (Exception e) {
                    throw new Exception("Can't disable link :S", e);
                }
            } else if(action.equalsIgnoreCase("remove")) {
                try {
                    LinksDAO.delete(link);
                    request.setAttribute("success_handler", "Link have been deleted.");
                    request.getRequestDispatcher("/dashboard").forward(request, response);
                    return;
                } catch (Exception e) {
                    throw new Exception("Can't delete link :S", e);
                }
            }
        } catch (Exception e) {
            request.setAttribute("error_handler", e);
        }
        
        // ok now fetch link data and format it to display in graph and pie charts.
        try {
            // get clics by day
            Map<String, Integer> clicsByDays = LinksDAO.getClicksByDays(link);
            request.setAttribute("clics_by_day", clicsByDays);
            
            // get referrers
            Map<String, Integer> clicsByReferrers = LinksDAO.getClicksByReferrers(link);
            request.setAttribute("clics_by_referrers", clicsByReferrers);
            
            // get countries
            Map<String, Integer> clicsByCountries = LinksDAO.getClicksByCountries(link);
            request.setAttribute("clics_by_countries", clicsByCountries);
        } catch (Exception e) {
            request.setAttribute("error_handler", e);
        }
        
        
        request.getRequestDispatcher("/WEB-INF/link.jsp").forward(request, response);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

}
