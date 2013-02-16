var game;
window.onload = function() {
	try {
		// create new game, with defined size, into 'game' div
		game = new Game(450, 650, "game"); // game.class.js
		
		// preload images
		game.load({
			bg : "images/bg.png",
			frog : "images/frog.sprite.png",
			life : "images/life.png",
			log1 : "images/tree1.png",
			log2 : "images/tree2.png",
			log3 : "images/tree3.png",
			car1 : "images/car1.png", 
			car2 : "images/car2.png", 
			car3 : "images/car3.png", 
			car4 : "images/car4.png", 
			car5 : "images/car5.png",
			gameover : "images/gameover.png",
			win : "images/win.png"
		}, loaded); // callback once loaded

		function loaded() {
			// set keyboard controls to bind
			game.setKeyboard({
				UP    : 38,
				LEFT  : 37,
				RIGHT : 39,
				BOTTOM: 40,
			});

			// create game objects and functions
			var bg   = new Graphic(game.ressources["bg"]); // graphic.class.js
			var frog = new Graphic(game.ressources["frog"], 2, 4); // add sprite params
			// create new actions for our little frog
			createFrogActions(frog); // frog.js
			frog.reset();

			// create a class to easily manipulate our trees log
			// this special graphic use 3 images to draw the log
			var Log = createLogClass(
				game.ressources["log1"], 
				game.ressources["log2"], 
				game.ressources["log3"]
			); // log.class.js
			
			// load config file ...
			var config = loadConfig(game, Log); // config.js
			var logsLines = config[0];
			var carsLines = config[1];

			// create the "win zones"
			var winZones = [];
			var winningFrogs = []; // will be populate with the frog who won a round.

			// create and position score label
			var score = new Label("0 PTS", "yellow", 21, "Verdana", "end");
			score.x = 400;
			score.y = 101;
			score.value = 0;
			Object.defineProperty(score, "value", {
				set : function(v) {
					value = Math.ceil(v);
					this.text = value + " PTS";
				},
				get: function() {
					return value;
				}
			})

			// create and position progressbar
			var pgb = new Progressbar(20, 620, 330, 20, 100); // progressbar.class.js
			pgb.timer = function(time) {
				this.stopAnimation(false);
				this.percent = 100;
				this.animate(
					{ "percent" : 0 }, 
					time*1000, 
					function() {
						roundLost("You didn't make it in time !");
					}
				);
			}

			// create lifes array and object
			var lifes = [
				new Graphic(game.ressources["life"]),
				new Graphic(game.ressources["life"]),
				new Graphic(game.ressources["life"])
			];
			var currentLife = lifes.length;
			
			// create win and lose sprite.
			var gameOverSprite = new Graphic(game.ressources["gameover"], 1, 11);
			gameOverSprite.spriteRun(2000/11, true);
			gameOverSprite.dw = 300;
			gameOverSprite.dh = 70;
			gameOverSprite.x = game.w / 2 - gameOverSprite.dw / 2;
			gameOverSprite.y = 250;
			
			var win = new Graphic(game.ressources["win"], 1, 37);
			win.spriteRun(1000/37, true);
			win.y = 400;



			// all element are created, we now need to add them to our game
			// add a background.
			game.scene.add(bg);
			// parse config and add the trees logs lines and cars.
			// it's a bit of ugly loops, but it add all our elements
			initElements(game, logsLines, carsLines); // init.js
			// add score and timer
			game.scene.add(score);
			game.scene.add(pgb);
			// and finally add our cute little frog.
			game.scene.add(frog);

			// prepare game
			var resetGame = function() {
				game.pause = false;
				// reset lilys
				winZones = [
					new Element(47, 195, 1, 3), new Element(47+90, 195, 1, 3), // drawable.class.js
					new Element(47+90*2, 195, 1, 3), new Element(47+90*3, 195, 1, 3),
					new Element(47+90*4, 195, 1, 3)
				];
				// reset lifes
				for (var i = lifes.length - 1; i >= 0; i--) {
					lifes[i].x = 75 + 36*i;
					lifes[i].y = 83;
					lifes[i].dw = 30;
					lifes[i].dh = lifes[i].h/(lifes[i].w/lifes[i].dw);
					game.scene.add(lifes[i]);
				}; currentLife = lifes.length;
				// delete winningfrogs
				for (var i = winningFrogs.length - 1; i >= 0; i--) {
					game.scene.remove(winningFrogs[i]);
					delete winningFrogs[i];
				}; winningFrogs = [];
				
				// reset score
				score.text = (score.value = 0) + " PTS";
				// reset frog
				frog.reset();
				// reset timer, add difficulty depending of level
				pgb.timer(30 - 4*(4 - winZones.length));
			};
			resetGame();



			// create main game loop function
			// it's THE function that make all the game
			game.main = function() {
				if(game.pause) return;
				score.value -= (score.value > 0) ? 1 : 0;

				// We don't want it to execute when frog is moving.
				if(frog.isOnAction === false) {
					// if we get out of screen
					if(!frog.isTouchingX(bg))
						roundLost("You disappear into Mordor ...");

					// if we are on the tree logs part
					if(frog.position > 0 && frog.position < 6 && !frog.isAnimated) {
						var onWater = true;
						var line = logsLines[logsLines.length - frog.position];
						for (var i = line.logs.length - 1; i >= 0; i--)
							if(frog.isOnX(line.logs[i])) {
								// add some point depending of time.
								score.value += 100*(100/pgb.percent);
								onWater = false;
								
								// make frog move with log
								if(frog.position%2==1)
									frog.animate({ x : 450 }, line.speed*((450-frog.x)/600)); // to left
								else 
									frog.animate({ x : -150 }, line.speed*((150+frog.x)/600)); // to right
							}
						if(onWater)
							roundLost("Sadly, you are the only frog that don't know how to swim.")
					}
					
					// if we are on the road
					else if(frog.position > 6 && frog.position < 12) {
						var cars = carsLines[carsLines.length - frog.position + 6].cars;
						// look if all cars doesn't touch our frog
						for (var i = cars.length - 1; i >= 0; i--)
							// if one does, it die
							if(frog.isTouchingX(cars[i]))
								roundLost("A car make you vanish !")
					}

					// if we are on the lily
					else if(frog.position == 12) {
						// look if we touch a winning square
						for (var i = winZones.length - 1; i >= 0; i--)
						    if(frog.isTouchingX(winZones[i]))
						    	return roundWin(i);
						// else
						roundLost("You didn't land on a lily :(");
					}

					// basic controls
					if(game.keys.UP && frog.position < 12) {
						frog.jump();
					} else if(game.keys.LEFT && frog.x > 10)
						frog.left();
					else if(game.keys.RIGHT && frog.x < 400)
						frog.right();
					else if(game.keys.BOTTOM && frog.position > 0)
						frog.bottom();
				}
			}


			var roundLost = function(reason) {
				console.info("Round lost because of: '"+reason+"'");

				// create our lost elements
				var lost = new Label("ROUND LOST", "yellow", 21, "Verdana", "center");
				lost.x = game.w/2;
				lost.y = 150;
				var lostText = new Label(reason, "yellow", 12, "Verdana", "center");
				lostText.x = game.w/2;
				lostText.y = game.h/2 + 60;

				// display it
				game.scene.add(lost);
				game.scene.add(lostText);

				// do  not display frog
				game.scene.remove(frog);
				frog.reset();

				// remove one life
				game.scene.remove(lifes[--currentLife]);

				if(currentLife == 0)
					return gameOver(lost, lostText);

				// wait 2 seconds before restart
				pgb.stopAnimation(false);
				pgb.percent = 0;
				pgb.animate({percent : 99}, 2000, function() {
					// remove our lost elements
					game.scene.remove(lost);
					game.scene.remove(lostText);
					// reset timer, add difficulty depending of level
					pgb.timer(30 - 4*(4 - winZones.length));
					game.scene.add(frog);
				});
			}

			var roundWin = function(lily) {
				console.info("Successfully land on lily n°"+(lily+1));
				frog.isOnAction = true; // prevent from refalling in this function

				// replace winzone by a frog waiting ...
				var waitingfrog = new Graphic(game.ressources['life']);
				waitingfrog.name = "waitingFrog-"+winningFrogs.length;
				waitingfrog.x = winZones[lily].x - 12;
				waitingfrog.y = winZones[lily].y - 6;
				waitingfrog.dw = 21;
				waitingfrog.dh = waitingfrog.h/(waitingfrog.w/waitingfrog.dw);
				game.scene.add(waitingfrog);
				winningFrogs.push(waitingfrog); // push frog in an array of glory

				winZones.splice(lily, 1);
				
				// give away some pts
				score.value += winningFrogs.length*1000;

				// if all frogs are placed, launch gameWin function
				if(winZones.length == 0) 
					return gameWin();

				// else,
				// reset timer, add difficulty depending of level
				pgb.timer(30 - 4*(4 - winZones.length));
				// make our frog reset
				frog.reset();
			}
			var gameOver = function(lost, lostText) {
				console.info("Game OVER !");
				pgb.stopAnimation(false);
				// reset
				resetGame();
				game.scene.remove(frog);
				// blabla, you failed badly
				game.scene.add(gameOverSprite);
				
				// wait 6 seconds
				setTimeout(function() {
					console.log("BACK TO GAME");
					// know back to game.
					game.scene.add(frog);
					// remove our lost elements
					game.scene.remove(lost);
					game.scene.remove(lostText);
					game.scene.remove(gameOverSprite);
					// reset timer, add difficulty depending of level
					pgb.timer(30 - 4*(4 - winZones.length));
				}, 6000);
				
			}
			var gameWin = function() {
				console.info("Game WIN !");

				// save score before reset
				var userScore = score.value;

				// reset
				resetGame();

				// pause game until animation
				game.pause = true;
				score.value = userScore;


				// youhou, you did it ...
				pgb.stopAnimation(false);
				frog.reset();
				game.scene.remove(frog);
				game.scene.add(win); // EPIC WIN SURPRISE !

				// blabla, sweet congratulation
				var winText = new Label("YOU WIN !", "yellow", 80, "Arial", "center");
				winText.x = game.w/2;
				winText.y = game.h/2 + 60;;

				game.scene.add(winText);

				// wait 10 seconds ...
				win.x = -250;
				win.animate({x : 450}, 10000, function() {
					console.log("BACK TO GAME");
					// know back to game.
					game.scene.add(frog);
					game.scene.remove(winText);
					game.scene.remove(win);
					score.value = 0;
					// reset timer, add difficulty depending of level
					pgb.timer(30 - 4*(4 - winZones.length));
					game.pause = false;
				});
			}
		}
	} catch(err) {
		if(typeof err === "string") err = { message : err };
		console.error(err.message);
		alert("Application as return a fatal error:\n" + err.message);
	}
};