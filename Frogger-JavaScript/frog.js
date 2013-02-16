function createFrogActions(frog) {
	// create new actions for our little frog
	frog.isOnAction = false;
	frog.jump = function() {
		this.stopAnimation(false);
		this.animate({ y : this.y - 31 }, 300, 
			function() { this.position++; frog.spriteStop(0); frog.isOnAction = false; });
		this.row = 1;
		this.line = 1;
		frog.isOnAction = true;
	};
	frog.left = function() {
		this.stopAnimation(false);
		this.animate({ x : this.x - 30 }, 300, 
			function() { frog.spriteStop(0); frog.isOnAction = false; });
		this.row = 1;
		this.line = 2;
		frog.isOnAction = true;
	};
	frog.right = function() {
		this.stopAnimation(false);
		this.animate({ x : this.x + 30 }, 300, 
			function() { frog.spriteStop(0); frog.isOnAction = false; });
		this.row = 1;
		this.line = 0;
		frog.isOnAction = true;
	};
	frog.bottom = function() {
		this.stopAnimation(false);
		this.position--;
		this.animate({ y : this.y + 31 }, 300, 
			function() { frog.spriteStop(0); frog.isOnAction = false; });
		this.row = 1;
		this.line = 3;
		frog.isOnAction = true;
	}
	frog.reset = function() {
		this.y = 555;
		this.x = 210;
		this.line = 1;
		this.position = 0;
		this.stopAnimation(false);
		this.spriteStop();
		frog.isOnAction = false;
	}
}