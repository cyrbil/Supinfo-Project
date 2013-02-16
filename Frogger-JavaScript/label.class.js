/*
 * A drawable specific to text
 */
var Label = function(text, color, size, font, textalign) {
	Drawable.call(this); // extend drawable
	this.parent = new Drawable;

	var align = ["start", "end", "left", "right", "center"];

	this.text = text||"";
	this.color = color||"black";
	this.font = font||(window.getComputedStyle(document.body, null ).getPropertyValue("font-family"))||"Arial";
	this.size = size||10;
	this.textalign = (align.indexOf(textalign||"start")>-1) ? textalign : "start";

	this.paint = function(ctx, x, y) {
		ctx.save();
		
		ctx.fillStyle = this.color;
		ctx.font = parseInt(this.size)+"px "+this.font;
		ctx.textAlign = this.textalign;
		ctx.fillText(this.text, this.x, this.y);

		ctx.restore();
	}
}
Label.prototype = Object.create(Drawable.prototype)
Label.prototype.constructor = Label;
