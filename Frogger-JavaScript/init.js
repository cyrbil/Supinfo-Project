function initElements(game, logsLines, carsLines) {

	for (var i = logsLines.length - 1; i >= 0; i--) {
		var decal = Math.random()*(logsLines[i].margin/logsLines[i].logs.length) - (logsLines[i].margin/logsLines[i].logs.length/2)
		for (var j = logsLines[i].logs.length - 1; j >= 0; j--) {
			var log = logsLines[i].logs[j];
			log.name = "log-"+log.type+"-"+i+j;
			log.speed = logsLines[i].speed;
			log.x = decal + logsLines[i].margin * j;
			log.y = 403 + 31 * i;
			game.scene.add(log);
			if(i%2==0) {
				log.animation = function() {
					this.x = -150;
					this.animate({ x : 450 }, this.speed, this.animation);
				};
				log.animate({ x : 450 }, log.speed*((450-log.x)/600), log.animation);
			} else {
				log.animation = function() {
					this.x = 450;
					this.animate({ x : -150 }, this.speed, this.animation);
				};
				log.animate({ x : -150 }, log.speed*((150+log.x)/600), log.animation);
			}
		};
	};

	// same thing for the cars ...
	for (var i = carsLines.length - 1; i >= 0; i--) {
		var decal = Math.random()*(carsLines[i].margin/carsLines[i].cars.length) - (carsLines[i].margin/carsLines[i].cars.length/2)
		for (var j = carsLines[i].cars.length - 1; j >= 0; j--) {
			var car = carsLines[i].cars[j];
			car.name = "car-"+i+j;
			car.speed = carsLines[i].speed;
			car.x = decal + carsLines[i].margin * j;
			car.y = 213 + 31 * i;
			game.scene.add(car);
			if(i%2) {
				car.animation = function() {
					this.x = -70;
					this.animate({ x : 450 }, this.speed, this.animation);
				};
				car.animate({ x : 450 }, car.speed*((450-car.x)/600), car.animation);
			} else {
				car.animation = function() {
					this.x = 450;
					this.animate({ x : -70 }, this.speed, this.animation);
				};
				car.animate({ x : -70 }, car.speed*((70+car.x)/600), car.animation);
			}
			if(car.rows>1) car.spriteRun(50);
		};
	};
}