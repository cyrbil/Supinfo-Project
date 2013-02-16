<%@page import="com.suplink.tools.HTMLFilter"%>
<%@page import="java.io.PrintWriter"%>
<%@page import="java.io.StringWriter"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%><%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<!DOCTYPE html>
<html>
  <head>
    <title>Welcome to SupLink</title>
    <link href="/SupLink/css/bootstrap.min.css" rel="stylesheet" media="screen">
    <link href="/SupLink/css/style.css" rel="stylesheet" media="screen">
  </head>
  <body>
      <div class="about hide" onclick="$('.about').fadeOut();">
        <div class="fade"></div>
        <div class="rounded popup">
        <p>
            This website was developped during <a href="http://supinfo.com">Supinfo International University</a> scolarity.
            Everythings in this website, if not directly quoted in the next lines, is the exclusive property of Cyril DEMINGEON.
            It's include original design, full or part of the source code, and functionnality found in this website.
            The author does not allow anyone or anything to use any part of this site without explicit authorization.
        </p>
        <p>
            Some libraries and tools used in this project are the property of their respective owner and aren't affiliated to the author.
        </p>
        <ul>
            <li>Java JDK</li>
            <li>Apache Tomcat</li>
            <li>Hibernate</li>
            <li>MySQL Connector/J</li>
            <li>Java Mail API</li>
            <li>JSTL</li>
            <li>UrlRewrite</li>
            <li>Twitter Boostrap</li>
            <li>Jquery</li>
            <li>RGraph</li>
        </ul>
        </div>
      </div>
    <div id="wrap">
      <div class="container">
        <!-- menu -->
        <div class="page-header">
          <ul class="nav nav-pills pull-right">
            <c:if test="${empty user}">
            <li><a href="/SupLink/login">Login</a></li>
            <li><a href="/SupLink/register">Register</a></li>
            </c:if>
            <c:if test="${not empty user}">
            <li><a href="/SupLink/dashboard">Dashboard</a></li>
            <li><a href="/SupLink/logout">Logout</a></li>
            </c:if>
            <li><a href="#" onclick="$('.about').fadeIn();">About</a></li>
          </ul>
            <h1 class="title"><a href="/SupLink/dashboard">SupLink <small>Another url shortner</small></a></h1>
        </div>
        <c:if test="${not empty success_handler}">
        <div class="alert alert-success alert-block">
            <button type="button" class="close" data-dismiss="alert">&times;</button>
            <%= HTMLFilter.filter(request.getAttribute("success_handler").toString()) %>
        </div>
        </c:if>
        <c:if test="${not empty error_handler}">
        <div class="alert alert-error alert-block">
          <button type="button" class="close" data-dismiss="alert">&times;</button>
          <h4>Server have return an error...</h4>
          <% Exception ex = (Exception) request.getAttribute("error_handler"); 
             String errors = ""; 
             Throwable t = ex;
            do {
                errors += t.toString() + "\n";
                for (StackTraceElement stackTraceElement : t.getStackTrace()) {
                    errors += "\t" + stackTraceElement.toString() + "\n";
                }
                t = t.getCause();
            } while (t != null); 
          %>
          <h5><%= HTMLFilter.filter(ex.getMessage()) %></h5>
          <h5 class="mute"><a href="#" onclick="if(this.toggle) { $('#stacktrace').slideUp(200); this.toggle = false; } else { $('#stacktrace').slideDown(200); this.toggle = true;}">StackTrace: (clic to show)</a></h5>
          <pre id="stacktrace" class="hide"><%= errors.toString() %></pre>
        </div>
        </c:if>
      </div><!-- end menu -->
