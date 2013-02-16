package com.suplink.filters;

import com.suplink.dao.UsersDAO;
import com.suplink.entities.Users;
import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;


public final class AuthentificationFilter implements Filter {
    private FilterConfig filterConfig = null; 

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest req = null;
        try {
            // look if we got a user with a valid session
            req = (HttpServletRequest) request;
            Users user = (Users) req.getSession().getAttribute("user");
            UsersDAO.exist(user.getEmail(), user.getPassword(), true);
        } catch (Exception e) {
            try {
                req.getSession().invalidate();
                // we have an error, send to index.
                req.getRequestDispatcher("/WEB-INF/index.jsp").forward(request, response);
                return;
            } catch (Exception ex) { } // chuuuut
        }
        
        // if everything went fine, user is considered valid,
        // so redirect
        chain.doFilter(request, response);
    }

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        this.filterConfig = filterConfig;
    }

    @Override
    public void destroy() { }
}
