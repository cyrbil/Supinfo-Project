<%@ page pageEncoding="UTF-8" %><%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<jsp:include page="/WEB-INF/header.jsp" />
      <!-- content -->
      <div class="container">
        <h2>Welcome to SupLink<h2>
        <h2><small>Before you start please login or register if not already done !</small></h2>

        <div class="row-fluid">
          <div class="span6">
            <form class="form rounded" method="POST" action="/SupLink/register">
              <h3 class="form-heading">Register</h3>
              <div class="control-group <c:if test="${requestScope['error_register_invalid_mail']}">error</c:if>">
                <label class="control-label">
                    <span class="<c:if test="${empty requestScope['error_register_invalid_mail']}">hide</c:if>">Please enter a valid email address.</span>
                    <input name="register_mail" style="width: 300px" type="email" class="input-block-level" placeholder="Email address" value="<c:out value="${param['register_mail']}"/>" required>
                </label>
              </div>
              <div class="control-group <c:if test="${requestScope['error_register_password_policy']}">error</c:if>">
                <label class="control-label">
                  <span class="<c:if test="${empty requestScope['error_register_password_policy']}">hide</c:if>">Please choose a good password (more than 6 characters).</span>
                  <input name="register_password" type="password" class="input-block-level" placeholder="Password" value="<c:out value="${param['register_password']}"/>" required>
                </label>
              </div>
              <div class="control-group <c:if test="${requestScope['error_register_password_differ']}">error</c:if>">
                <label class="control-label">
                  <span class="<c:if test="${empty requestScope['error_register_password_differ']}">hide</c:if>">Please ensure that you entered the same password.</span>
                  <input name="register_comfirm" type="password" class="input-block-level" placeholder="Confirmation" value="<c:out value="${param['register_comfirm']}"/>" required>
                </label>
              </div>
              <button class="btn btn-primary" type="submit">Register</button>
            </form>
          </div>
          <div class="span6">
            <form class="form rounded"  method="POST" action="/SupLink/login">
              <h3 class="form-heading">Login</h3>
              <div class="control-group <c:if test="${requestScope['error_login_invalid_mail']}">error</c:if>">
                <label class="control-label">
                  <span class="<c:if test="${empty requestScope['error_login_invalid_mail']}">hide</c:if>">Please enter a valid email address.</span>
                  <input name="login_mail" style="width: 300px" type="email" class="input-block-level" placeholder="Email address" value="<c:out value="${param['login_mail']}"/>" required>
                </label>
              </div>
              <input name="login_password" type="password" class="input-block-level" placeholder="Password" value="<c:out value="${param['login_password']}"/>" required>
              <button class="btn btn-primary" type="submit">Sign in</button>
            </form>
          </div>
        </div>
      </div><!-- end content -->
<jsp:include page="/WEB-INF/footer.jsp" />