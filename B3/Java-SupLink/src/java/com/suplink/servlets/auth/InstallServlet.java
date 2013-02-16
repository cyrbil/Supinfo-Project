package com.suplink.servlets.auth;

import com.mysql.jdbc.Driver;
import com.suplink.dao.LinksDAO;
import com.suplink.dao.SuplinkDAO;
import com.suplink.dao.UsersDAO;
import com.suplink.entities.Links;
import com.suplink.entities.Users;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.Random;
import javax.persistence.Query;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


@WebServlet(name = "InstallServlet", urlPatterns = {"/servlets/install"})
public class InstallServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Install script</h2>");
        
        int step = 0;
        try { step = Integer.parseInt(request.getParameter("step")); } catch(Exception e) {}
        
        if (step == 1) {
            out.println("<h3>Database tables creation</h3>");
            // try connect with params
            Connection conn = null;
            try {
                String driver = request.getParameter("driver").toString();
                String host = request.getParameter("host").toString();
                String port = request.getParameter("port").toString();
                String db = request.getParameter("db").toString();
                String user = request.getParameter("user").toString();
                String pass = request.getParameter("pass").toString();
                DriverManager.registerDriver(new Driver());
                conn = DriverManager.getConnection("jdbc:" + driver + "://" + host + ":" + port + "/" + db, user, pass);
                out.println("<p>Connection successfull.<br />");


                // load db dump
                Path dbDump = Paths.get(getServletContext().getRealPath("/META-INF/suplink.sql"));
                List<String> rawSql = Files.readAllLines(dbDump, StandardCharsets.UTF_8);
                out.println("SQL file loaded.<br />");
                Statement stmt = null;
                try {
                    stmt = conn.createStatement();
                    // do all the query
                    for (String query : rawSql) {
                        stmt.executeUpdate(query);
                    }
                    out.println("SQL queries done with success !</p>");

                    out.println("<form action='/SupLink/install'>"
                        + "<input type='hidden' name='step' value='2' />"
                        + "<input type='submit' value='continue' />"
                        + "</form>");
                } catch(Exception e) {
                    throw e;
                } finally {
                    try { stmt.close(); } catch(Exception e) {}
                }
            } catch(Exception e) {
                out.println("Fill up database connection information (or use default):<br /><form action='/SupLink/install'>"
                        + "<input type='hidden' name='step' value='1' />"
                        + "Driver: <input type='text' name='driver' value='mysql'><br />"
                        + "Host: <input type='text' name='host' value='localhost'><br />"
                        + "Port: <input type='text' name='port' value='3306'><br />"
                        + "Base: <input type='text' name='db' value='mysql'><br />"
                        + "User: <input type='text' name='user' value='root'><br />"
                        + "Password: <input type='text' name='pass' value=''><br />"
                        + "<input type='submit'><br />"
                        + "</form>");
                if(!(e instanceof NullPointerException)) {
                    Throwable t = e;
                    do {
                        out.println("<h4>" + t.toString() + "</h4>");
                        for (StackTraceElement stackTraceElement : t.getStackTrace()) {
                            out.println(stackTraceElement.toString() + "<br />");
                        }
                        t = t.getCause();
                    } while (t != null);
                }
            } finally { try { conn.close(); } catch(Exception e) {}}
        } else if (step == 2){
            out.println("<h3>Database contents creation</h3><p>");
            try {
                out.println("Creating a user for test (test@test.test with pwd: testtest)<br />");
                Users user = UsersDAO.create("test@test.test", "testtest");
                UsersDAO.activateUser(user);
                
                out.println("Adding some links to user<br />");
                List<Links> links = new ArrayList<Links>();
                links.add(LinksDAO.create("MyLink", "1e99aa", "http://google.fr", user));
                links.add(LinksDAO.create("Facebook", "6e6e71", "http://facebook.fr", user));
                links.add(LinksDAO.create("For fun!", "fun", "http://9gag.com/trending", user));
                links.add(LinksDAO.create("Alias", "56445e", "http://www.supinfo.com", user));
                links.add(LinksDAO.create("Music", "music", "http://grooveshark.com/", user));
                
                out.println("Adding a bit of (fake random) links's statistics<br /></p>");
                ArrayList<String> possibleReferrers = new ArrayList<String>();
                possibleReferrers.add("facebook");
                possibleReferrers.add("Direct"); // means direct
                possibleReferrers.add("9gag");
                possibleReferrers.add("twitter");
                ArrayList<String> possibleCountries = new ArrayList<String>();
                possibleCountries.add("FRA");
                possibleCountries.add("CAN");
                possibleCountries.add("ENG");
                possibleCountries.add("USA");
                Random r = new Random();
                for (Links link : links) {
                    int m = r.nextInt(10)+20;
                    for (int i = 0; i < m; i++) {
                        String referrer = possibleReferrers.get(r.nextInt(possibleReferrers.size()));
                        String country = possibleCountries.get(r.nextInt(possibleCountries.size()));
                        Calendar cal = Calendar.getInstance();
                        cal.set(2013, 1, r.nextInt(7)+1, r.nextInt(24), r.nextInt(60), r.nextInt(60));
                        LinksDAO.addRedirectionInfo(link, country, referrer, cal.getTime());
                    }
                }
                
                out.println("<h1>Installation complete !</h1>"
                        + "<p>Go to <a href='/SupLink/'>Index</a> and log with user test@test.test with password 'testtest' to continue.<br>"
                        + "(Or register a new user ...)<p>");
            } catch(Exception e) {
                Throwable t = e;
                do {
                    out.println("<h4>" + t.toString() + "</h4>");
                    for (StackTraceElement stackTraceElement : t.getStackTrace()) {
                        out.println(stackTraceElement.toString() + "<br />");
                    }
                    t = t.getCause();
                } while (t != null);
            }
        } else {
            out.println("<p>This will add tables and contents into your database specified in the persistence unit.<br />"
                + "Please notice that it absolutly require MYSQL server running and no other db system since <br />"
                + "it uses some mysql specific functions.</p>");
        out.println("<h3>When ready to go, press the install button </h3>");
        out.println("<form action='/SupLink/install'>When ready to go, press the "
                + "<button type='submit'>Install</button> button"
                + "<input type='hidden' name='step' value='1' />"
                + "</form>");
        }
        
        out.println("</body></html>");
    }
}
