<%@page import="com.suplink.entities.Links"%>
<%@ page pageEncoding="UTF-8" %><%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<jsp:include page="/WEB-INF/header.jsp" />
      <!-- content -->
      <div class="container">
        <h2>Dashboard</h2>

        <div class="container">
          <fieldset class="rounded">
            <legend>Shortner</legend>
            <form style="width: 750px; margin: 0 auto;" action="/SupLink/link/create" method="POST">
              <input type="text" name="link_name" placeholder="Name" maxlength="12" minlength="3" title="Simple name for the redirection." required/>
              <input type="text" name="link_id" placeholder="Short Id (empty = random)" maxlength="12" minlength="3" title="Enter the unique id you want for your url, or let this empty for a random one."/>
              <input type="url" name="link_url" placeholder="Url to shorten" title="Past a link to shorten here." required/>
              <button class="btn btn-primary btn-small" style="margin: 0 0 10px 10px" type="submit">Short it !</button>
            </form>
          </fieldset>

          <c:if test="${not empty user_links}">
          <!-- link list -->
          <table class="table table-bordered table-striped table-hover">
            <thead>
              <tr>
                <th>Name</th>
                <th>Url ID</th>
                <th>Destination Url</th>
                <th>Clicks</th>
                <th>Creation Date</th>
              </tr>
            </thead>
            <tbody class="clickable">
                <c:forEach items="${user_links}" var="link" >
              <tr onclick="if(window.event.srcElement.href !== undefined) return true; window.location = window.location.origin + '/SupLink/link/' + this.children[1].firstChild.innerText; return false;">
                  <td><c:out value="${link.getName()}" /></td>
                  <td><a target="_blank" href="/SupLink/<c:out value="${link.getId()}" />"><c:out value="${link.getId()}" /></a></td>
                <td><a href="<c:out value="${link.getUrl()}" />"><c:out value="${link.getUrl()}" /></a></td>
                <td><c:out value="${link.getRedirectionsCollection().size()}" /></td>
                <td><c:out value="${link.getCreationDate().toString()}" /></td>
              </tr>
              </c:forEach>
            </tbody>
          </table><!-- link list end -->
          </c:if>
        </div>
      </div><!-- end content -->
      
<jsp:include page="/WEB-INF/footer.jsp" />