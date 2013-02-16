/*
 * A drawable specific to images
 */
var Graphic = function(from, rows, lines) {
	Drawable.call(this); // extend drawable
	this.parent = new Drawable;


	if(!from instanceof HTMLImageElement) throw "Type of Graphic 'from' parameter must be an image.";
	var rows = parseInt(rows);
	var lines = parseInt(lines);
	if(isNaN(rows) || rows < 1) rows = 1;
	if(isNaN(lines) || lines < 1) lines = 1;

	var img = from;
	this.w = from.width;
	this.h = from.height;
	this.dw = this.w/rows;
	this.dh = this.h/lines;
	this.row = 0;
	this.line = 0;
	this.rows = rows;
	this.lines = lines;
	this.name = img.name;

	var spriteDuration = undefined; // user defined
	var spriteTime = undefined; // engine created
	var spriteFrame = 0;
	var inLines = false;
	this.spriteRun = function(ms, bool) {
		ms = parseInt(ms);
		if(isNaN(ms) || ms < 0) throw "Sprite duration must be greater or egal 0";
		spriteDuration = ms;
		spriteTime = undefined;
		if(bool) inLines = true;
	}
	this.spriteStop = function(stopOnRow) {
		stopOnRow = parseInt(stopOnRow);
		if(!isNaN(stopOnRow) && stopOnRow >= 0)
			this.row = stopOnRow;
		
		spriteDuration = spriteTime = undefined;
	}

	this.update = function(fps) {
		// call default method first (herited from parent)
		this.parent.update.call(this, fps);

		if(spriteDuration !== undefined && spriteTime === undefined) {
			spriteTime = Math.ceil(spriteDuration/fps);
			spriteDuration = undefined;
		}
	}

	this.paint = function(ctx, x, y, w, h) {
		if(spriteTime !== undefined) {
			if(++spriteFrame > spriteTime) {
				spriteFrame = 0;
				if(inLines)
					this.line = (++this.line)%lines;
				else
					this.row = (++this.row)%rows;
			}
		}

		// draw
		ctx.drawImage(img, 
			this.row%rows*(w/rows), this.line%lines*(h/lines), w/rows, h/lines,
			x, y, this.dw, this.dh
		);
	}

	

	this.isTouchingX = function(graphic) {
		if(graphic.x == undefined || graphic.w == undefined)
			throw "Object must have coordinates";
		return (graphic.x + graphic.w/(graphic.rows||1) < this.x || graphic.x > this.x + this.w/rows) ? false : true;
	}
	this.isOnX  = function(graphic) {
		if(graphic.x == undefined || graphic.w == undefined)
			throw "Object must have coordinates";
		return (graphic.x <= this.x && graphic.x + graphic.w/(graphic.rows||1) >= this.x + this.w/rows)
			? true : false;
	}
	this.isTouchingY = function(graphic) {
		if(graphic.y == undefined || graphic.h == undefined)
			throw "Object must have coordinates";
		return (graphic.y + graphic.h/(graphic.lines||1) < this.y || graphic.y > this.y + this.h/(graphic.lines||1)) ? false : true;
	}
	this.isOnY  = function(graphic) {
		if(graphic.y == undefined || graphic.h == undefined)
			throw "Object must have coordinates";
		return (graphic.y <= this.y && graphic.y + graphic.h/(graphic.lines||1) >= this.y + this.h/lines)
			? true : false;
	}
}
Graphic.prototype = Object.create(Drawable.prototype)
Graphic.prototype.constructor = Graphic;
