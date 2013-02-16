/*
 * Object with coordinates and collision functions
 */
var Element = function (x, y, w, h, name) {

	this.x = x || 0;
	this.y = y || 0;
	this.w = w || 0;
	this.h = h || 0;
	this.name = name  || 0;


	this.isTouchingX = function(other) {
		if(other.x == undefined || other.w == undefined)
			throw "Object must have coordinates";
		return (other.x + other.w < this.x || other.x > this.x + this.w) ? false : true;
	}
	this.isOnX  = function(other) {
		if(other.x == undefined || other.w == undefined)
			throw "Object must have coordinates";
		return (other.x <= this.x && other.x + other.w >= this.x + this.w)
			? true : false;
	}
	this.isTouchingY = function(other) {
		if(other.y == undefined || other.h == undefined)
			throw "Object must have coordinates";
		return (other.y + other.h < this.y || other.y > this.y + this.h) ? false : true;
	}
	this.isOnY  = function(other) {
		if(other.y == undefined || other.h == undefined)
			throw "Object must have coordinates";
		return (other.y <= this.y && other.y + other.h >= this.y + this.h)
			? true : false;
	}
	this.isTouching = function(other) {
		return (this.isTouchingX(other) || this.isTouchingY(other)) ? false : true;
	}
	this.isOn  = function(other) {
		return (this.isOnX(other) && this.isOnY(other)) ? true : false;
	}

};

/*
 * An element that can be draw and animate
 */
var Drawable = function() {
	Element.call(this);
	this.parent = new Element();

	this.isAnimated = {};
	Object.defineProperty(this, "isAnimated", {
		get : function() { return (this.tickActions !== undefined); }
	})

	this.animateQueue = [];
	this.tickActions = undefined;
	this.update = function(fps) {
		if(!this.isAnimated) { // if no animations are currently running
			// if we have something to animate
			if(this.animateQueue.length > 0) {
				// remove from queue
				this.tickActions = this.animateQueue.shift();

				// transform to tickaction
				this.tickActions.times = Math.ceil(this.tickActions.duration/1000*fps);
				for(var i in this.tickActions.actions) {
					this.tickActions.actions[i].add /= this.tickActions.times;
				}
			}
		}
	}

	this.tick = function(ctx, x, y, w, h) {
		this.x = x;
		this.y = y;
		// tick
		if(this.isAnimated) {
			this.tickActions.times--;
			for(var i in this.tickActions.actions) {
				this[this.tickActions.actions[i].what] += this.tickActions.actions[i].add;
			}
			if(this.tickActions.times < 1)
				this.stopAnimation();
		}
	};

	this.paint = function() {}

	this.animate = function(what_array, duration, callback) {
		if(window.debug && this.name == "frog") {
			var s = "";
			for(var what in what_array)
				s += what+" : "+what_array[what]+", ";
			console.log("what:{"+s+"}, duration:"+duration+", callback:"+callback);
		}
		if(typeof what_array !== "object") throw "First parameter of 'animate' must be an object";
		duration = parseInt(duration);
		if(isNaN(duration) || duration < 0) duration = 0;
		if(typeof callback != "function") callback = function() {};

		var actionsList = new Array();
		for(var what in what_array) {
			// see if what is a propriety of our object.
			// look if object contain that key_string
			if(this[what] == undefined) throw "'" + what + "' is not a property of this graphic";

			actionsList.push({
				what : what,
				add  : (what_array[what] - this[what])
			});
		}
		var action = Object.create({
			actions  : actionsList,
			duration : duration,
			callback : callback
		});
		this.animateQueue.push(action);
	};

	this.stopAnimation = function(callCallback) {
		if(this.isAnimated) {
			if(callCallback !== false) {
				this.callback = this.tickActions.callback; // avoid losing 'this'
				this.callback();
			}
			delete this.tickActions;
		}
	};
}
Drawable.prototype = Object.create(Element.prototype)
Drawable.prototype.constructor = Drawable;