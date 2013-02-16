/*
 * A drawable specific to rectangle draw
 */
var Progressbar = function(x, y, w, h, percent) {
	Drawable.call(this); // extend drawable
	this.parent = new Drawable;

	this.x = x || 0;
	this.y = y || 0;
	this.w = w || 0;
	this.h = h || 0;
	this.percent = percent || 0;

	this.paint = function(ctx, x, y, w, h) {
		percent %= 100;

		var radius = h/2;
		ctx.save();

		// Define the shadows
		ctx.shadowOffsetX = 0;
		ctx.shadowOffsetY = 0;
		ctx.shadowBlur = 5;
		ctx.shadowColor = '#FFF';

		// draw round rect
		ctx.fillStyle = 'rgba(189,189,189,1)';
		ctx.beginPath();
	    ctx.moveTo(x + radius, y);
	    ctx.lineTo(x + w - radius, y);
	    ctx.arc(x+w-radius, y+radius, radius, -Math.PI/2, Math.PI/2, false);
	    ctx.lineTo(x + radius, y + h);
	    ctx.arc(x+radius, y+radius, radius, Math.PI/2, 3*Math.PI/2, false);
	    ctx.closePath();
	    ctx.fill();

		// color of percent bar
		ctx.shadowColor = 'rgba(0,0,0,0)';
		var progress_lingrad = ctx.createLinearGradient(x, y+h, x, y);
        progress_lingrad.addColorStop(0, 'rgba('+Math.ceil(25+(100-this.percent)*2.30)+',100,25,1)');
        progress_lingrad.addColorStop(1, 'rgba('+Math.ceil(100+(100-this.percent)*1.55)+','+Math.ceil(255-(100-this.percent)*2.30)+',50,1)');

		ctx.fillStyle = progress_lingrad;

	    ctx.beginPath();
	    if (w*(this.percent/100) < radius) { 
	        offset = radius - Math.sqrt(Math.pow(radius,2)-Math.pow((radius-w*(this.percent/100)),2));
	        // Left angle
	        var left_angle = Math.acos((radius - w*(this.percent/100)) / radius);
	        ctx.moveTo(x + w*(this.percent/100), y+offset);
	        ctx.lineTo(x + w*(this.percent/100), y+h-offset);
	        ctx.arc(x + radius, y + radius, radius, Math.PI - left_angle, Math.PI + left_angle, false);
	    }
	    else if (w*(this.percent/100)+radius>w) {
	        offset = radius - Math.sqrt(Math.pow(radius,2)-Math.pow((radius - (w-w*(this.percent/100))),2));
	        // Right angle
	        var right_angle = Math.acos((radius - (w-w*(this.percent/100))) / radius);
	        ctx.moveTo(x + radius, y);
	        ctx.lineTo(x + w*(this.percent/100), y);
	        ctx.arc(x+w-radius, y + radius, radius, -Math.PI/2, -right_angle, false);
	        ctx.lineTo(x + w*(this.percent/100), y+h-offset);
	        ctx.arc(x+w-radius, y + radius, radius, right_angle, Math.PI/2, false);
	        ctx.lineTo(x + radius, y + h);
	        ctx.arc(x+radius, y+radius, radius, Math.PI/2, 3*Math.PI/2, false);
	    }
	    else {
	        ctx.moveTo(x + radius, y);
	        ctx.lineTo(x + w*(this.percent/100), y);
	        ctx.lineTo(x + w*(this.percent/100), y + h);
	        ctx.lineTo(x + radius, y + h);
	        ctx.arc(x+radius, y+radius, radius, Math.PI/2, 3*Math.PI/2, false);
	    }//
	    /*{
	    	ctx.beginPath();
		    ctx.moveTo(x + radius, y);
		    ctx.lineTo(x + w*(this.percent/100) - radius, y);
		    ctx.arc(x+w*(this.percent/100)-radius, y+radius, radius, -Math.PI/2, Math.PI/2, false);
		    ctx.lineTo(x + radius, y + h);
		    ctx.arc(x+radius, y+radius, radius, Math.PI/2, 3*Math.PI/2, false);
		    ctx.closePath();
		    ctx.fill();
	    }*/
	    ctx.closePath();
	    ctx.fill();

		ctx.restore();
	}

}
Progressbar.prototype = Object.create(Drawable.prototype)
Progressbar.prototype.constructor = Progressbar;
