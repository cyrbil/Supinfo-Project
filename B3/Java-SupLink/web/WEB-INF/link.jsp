<%@ page pageEncoding="UTF-8" %><%@taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<jsp:include page="/WEB-INF/header.jsp" />

      <!-- content -->
      <div class="container">
        <div>
          <div class="pull-right counter-clic"><i class="icon-hand-up"></i> Clics: <c:out value="${link.getRedirectionsCollection().size()}"/></div>
          <h2>Link Detail <small><c:out value="${link.getName()}"/></small></h2>
          <span class="lead">
            <a target="_blank" href="/SupLink/<c:out value="${link.getId()}"/>"><c:out value="${link.getId()}"/></a> > <a target="_blank" href="<c:out value="${link.getUrl()}"/>"><c:out value="${link.getUrl()}"/></a>
          </span>
          <c:set var="isEnabled" value="disable" />
          <c:if test="${not link.isEnabled()}">
              <c:set var="isEnabled" value="enable" />
          </c:if>
          <p>Action: <a href="/SupLink/link/<c:out value="${link.getId()}"/>/<c:out value="${isEnabled}"/>"><c:out value="${isEnabled}"/></a> - <a href="/SupLink/link/<c:out value="${link.getId()}"/>/remove" onclick="return confirm('This action will DEFINITLY remove the link. Are you sure you want to proceed ?')">delete</a></p>
        </div>
         
        <c:if test="${empty clics_by_day}">
            This link have not been clicked yet.
        </c:if>
         <c:if test="${not empty clics_by_day}">
        <div class="row-fluid">
          <h3 style="text-align: center">Statistics:</h3>
          <div class="span12" style="position: relative; margin-left: 0px">
            <span class="png_link" onclick="RGraph.showPNG(this.nextElementSibling, event)">Get PNG</span>
            <canvas id="chart-visits">Your browser does not support canvas ...</canvas>
          </div>
          <div class="span6" style="position: relative; margin-left: 0px">
            <span class="png_link" onclick="RGraph.showPNG(this.nextElementSibling, event)">Get PNG</span>
            <canvas id="pie-referrer">Your browser does not support canvas ...</canvas>
            <table class="table table-bordered table-striped table-hover">
              <thead>
                <tr>
                  <th>Referrer</th>
                  <th>Clics</th>
                </tr>
              </thead>
              <tbody>
                <c:forEach items="${clics_by_referrers}" var="data">
                <tr>
                  <td>${data.key}</td>
                  <td>${data.value}</td>
                </tr>
                </c:forEach>
              </tbody>
            </table>
          </div>
          <div class="span6" style="position: relative">
            <span class="png_link" onclick="RGraph.showPNG(this.nextElementSibling, event)">Get PNG</span>
            <canvas id="pie-country">Your browser does not support canvas ...</canvas>
            <table class="table table-bordered table-striped table-hover">
              <thead>
                <tr>
                  <th>Country</th>
                  <th>Clics</th>
                </tr>
              </thead>
              <tbody>
                <c:forEach items="${clics_by_countries}" var="data">
                <tr>
                  <td>${data.key}</td>
                  <td>${data.value}</td>
                </tr>
                </c:forEach>
              </tbody>
            </table>
          </div>
        </div>
         </c:if>
      </div><!-- end content -->
      
      
      
      <script src="http://code.jquery.com/jquery-latest.js"></script>
    <script src="/SupLink/js/bootstrap.min.js"></script>

    <!--[if lt IE 9]><script src="js/excanvas/excanvas.js"></script><![endif]-->
    <script src="/SupLink/js/RGraph/RGraph.common.core.js"></script>

    <script src="/SupLink/js/RGraph/RGraph.common.annotate.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.context.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.dynamic.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.effects.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.key.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.resizing.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.tooltips.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.common.zoom.js"></script>

    <script src="/SupLink/js/RGraph/RGraph.bar.js"></script>
    <script src="/SupLink/js/RGraph/RGraph.pie.js"></script>
    <script type="text/javascript">

        RGraph.Async(function() {
            // set canvas size to the size of his container (avoid pointer error)
            var c = document.getElementById("chart-visits");
            c.width = c.parentElement.clientWidth;
            c.height = c.width/Math.SQRT2/2; // nice proportions is multiple of sqrt(2)

            var tooltips = [
                <c:forEach items="${clics_by_day}" var="data" end="0">"${data.key}"</c:forEach><c:forEach items="${clics_by_day}" var="data" begin="1">, "${data.key}"</c:forEach>
            ];
            var data = [
                <c:forEach items="${clics_by_day}" var="data" end="0">${data.value}</c:forEach><c:forEach items="${clics_by_day}" var="data" begin="1">, ${data.value}</c:forEach>
            ];

            var colors = [];
            for (var i = 0; i < data.length; i++) {
                colors[i] = 'rgb('+Math.ceil(255-255*data[i]/Math.max.apply(null,data))+', '+Math.ceil(Math.sqrt((255*data[i]/Math.max.apply(null,data))*255))+', 0)';
            };
            var labels = [];
            var nbrLabels = (tooltips.length > 8) ? tooltips.length/8 : 1;
            for (var i = 0; i < ((tooltips.length > 8) ? 8 : tooltips.length); i++) {
              labels[i] = tooltips[Math.ceil(i*nbrLabels)];
            };

            var bar = new RGraph.Bar("chart-visits", data);
            bar.Set('title', 'Clics By Day');
            bar.Set('hmargin', 1)
            bar.Set('tooltips', tooltips);
            bar.Set('tooltips.event', 'onmousemove');
            bar.Set('tooltips.coords.page', true);
            bar.Set('labels', labels);
            bar.Set('labels.above', true);
            bar.Set('chart.labels.specific.align', 'center');
            bar.Set('colors', colors);
            bar.Set('colors.sequential', true);
            bar.Set('chart.zoom.frames', 1);
            bar.Set('chart.zoom.delay', 0);
            bar.Draw();
            c.onclick = function(e) { RGraph.Zoom(e); }
            c.previousElementSibling.style.left = (c.width - 75)+"px";
        });
        
        
        RGraph.Async(function() {
            // set canvas size to the size of his container (avoid pointer error)
            var c = document.getElementById("pie-referrer");
            c.width = c.height = c.parentElement.clientWidth;

            var labels = [
                <c:forEach items="${clics_by_referrers}" var="data" end="0">"${data.key}"</c:forEach><c:forEach items="${clics_by_referrers}" var="data" begin="1">, "${data.key}"</c:forEach>
            ];
            var data = [
                <c:forEach items="${clics_by_referrers}" var="data" end="0">${data.value}</c:forEach><c:forEach items="${clics_by_referrers}" var="data" begin="1">, ${data.value}</c:forEach>
            ];

            var colors = [];
            for (var i = 0; i < data.length; i++) {
                colors[i] = 'rgb('+Math.ceil(Math.random()*255)+', '+Math.ceil(Math.random()*255)+', '+Math.ceil(Math.random()*255)+')';
            };
            
            var tooltips = [];
            for(var i = 0; i < data.length; i++) {
                tooltips[i] = data[i] + " clics";
            }

            var pie = new RGraph.Pie("pie-referrer", data);
            pie.Set('title', 'Referrers');
            pie.Set('tooltips', tooltips);
            pie.Set('tooltips.event', 'onmousemove');
            pie.Set('tooltips.coords.page', true);
            pie.Set('labels', labels);
            pie.Set('colors', colors);
            pie.Set('chart.zoom.frames', 1);
            pie.Set('chart.zoom.delay', 0);
            pie.Set('chart.exploded', 7);
            pie.Set("gutter.top", 70);
            pie.Set("gutter.left", 100);
            pie.Set("gutter.right", 100);
            pie.Draw();
            c.onclick = function(e) { RGraph.Zoom(e); }
            c.previousElementSibling.style.left = (c.width - 75)+"px";
            c.previousElementSibling.style.top = "50px";
        });
        
        
        RGraph.Async(function() {
            // set canvas size to the size of his container (avoid pointer error)
            var c = document.getElementById("pie-country");
            c.width = c.height = c.parentElement.clientWidth;

            var labels = [
                <c:forEach items="${clics_by_countries}" var="data" end="0">"${data.key}"</c:forEach><c:forEach items="${clics_by_countries}" var="data" begin="1">, "${data.key}"</c:forEach>
            ];
            var data = [
                <c:forEach items="${clics_by_countries}" var="data" end="0">${data.value}</c:forEach><c:forEach items="${clics_by_countries}" var="data" begin="1">, ${data.value}</c:forEach>
            ];

            var colors = [];
            for (var i = 0; i < data.length; i++) {
                colors[i] = 'rgb('+Math.ceil(Math.random()*255)+', '+Math.ceil(Math.random()*255)+', '+Math.ceil(Math.random()*255)+')';
            };
            
            var tooltips = [];
            for(var i = 0; i < data.length; i++) {
                tooltips[i] = data[i] + " clics";
            }

            var pie = new RGraph.Pie("pie-country", data);
            pie.Set('title', 'Countries');
            pie.Set('tooltips', tooltips);
            pie.Set('tooltips.event', 'onmousemove');
            pie.Set('tooltips.coords.page', true);
            pie.Set('labels', labels);
            pie.Set('colors', colors);
            pie.Set('chart.zoom.frames', 1);
            pie.Set('chart.zoom.delay', 0);
            pie.Set('chart.exploded', 7);
            pie.Set("gutter.top", 70);
            pie.Set("gutter.left", 100);
            pie.Set("gutter.right", 100);
            pie.Draw();
            c.onclick = function(e) { RGraph.Zoom(e); }
            c.previousElementSibling.style.left = (c.width - 75)+"px";
            c.previousElementSibling.style.top = "50px";
        });
        
    </script>


<jsp:include page="/WEB-INF/footer.jsp" />