function createLogClass(img1, img2, img3) {
	var Log = function( size ) {
		Graphic.call(this, img1);
		this.type = size;

		// a log use 3 images, that's why it's also a special class.
		this.ressources = {
			log_start  : new Graphic(img1),
			log_middle : new Graphic(img2),
			log_end    : new Graphic(img3)
		};

		Object.defineProperty(this, "w", {
			get : function() {
				switch(this.type) {
					case "medium" :
						return 70 + this.ressources.log_end.w;
					case "large"  :
						return 50 + this.ressources.log_middle.w + this.ressources.log_end.w;
					case "xxl"    :
						return 70 + this.ressources.log_middle.w + this.ressources.log_end.w;
					default: 
						return 50 + this.ressources.log_end.w;
				}
			}
		});

		this.draw = this.paint; // remember initial paint method
		this.paint = function(ctx, x, y, w, h) {
			this.draw(ctx, x, y, this.ressources.log_start.w, this.ressources.log_start.h);
			this.ressources.log_middle.paint(ctx, x + this.ressources.log_start.w, y, this.ressources.log_middle.w, this.ressources.log_start.h);

			switch(this.type) {
				case "medium" :
					this.ressources.log_end.paint(ctx, x + 70, y, this.ressources.log_end.w, this.ressources.log_start.h);
					break;
				case "large"  :
					this.ressources.log_middle.paint(ctx, x + 50, y, this.ressources.log_middle.w, this.ressources.log_start.h);
					this.ressources.log_end.paint(ctx, x + 50 + this.ressources.log_middle.w, y, this.ressources.log_end.w, this.ressources.log_start.h);
					break;
				case "xxl"    :
					this.ressources.log_middle.paint(ctx, x + 70, y, this.ressources.log_middle.w, this.ressources.log_start.h);
					this.ressources.log_end.paint(ctx, x + 70 + this.ressources.log_middle.w, y, this.ressources.log_end.w, this.ressources.log_start.h);
					break;
				default: 
					this.ressources.log_end.paint(ctx, x + 50, y, this.ressources.log_end.w, this.ressources.log_start.h);					
			}
		};
	};
	Log.prototype = Object.create(Graphic.prototype);
	Log.prototype.constructor = Log;

	return Log;
}