
// put it in fonction because off the use of instancied ressources
function loadConfig(game, Log) {
	// create and initialize our tree logs
	var difficulty = 7500;
	var randomness = 5000;
	var logsLines = [
		{
			logs : [new Log("xxl"), new Log("xxl")],
			margin : 300,
			speed : difficulty + Math.random() * randomness
		}, {
			logs : [new Log("small"), new Log("small"), new Log("small"), new Log("small")],
			margin : 130,
			speed : difficulty + Math.random() * randomness
		}, {
			logs : [new Log("large"), new Log("large"), new Log("large")],
			margin : 190,
			speed : difficulty + Math.random() * randomness
		}, {
			logs : [new Log("medium"), new Log("medium"), new Log("medium")],
			margin : 200,
			speed : difficulty + Math.random() * randomness
		}, {
			logs : [new Log("small"), new Log("medium"), new Log("small"), new Log("medium")],
			margin : 150,
			speed : difficulty + Math.random() * randomness
		}
	];

	// create and initialize our cars
	var carsLines = [
		{
			cars : [new Graphic(game.ressources["car1"]), new Graphic(game.ressources["car1"]), new Graphic(game.ressources["car1"]), new Graphic(game.ressources["car1"])],
			margin : 120,
			speed : difficulty + Math.random() * randomness
		}, {
			cars : [new Graphic(game.ressources["car2"],2), new Graphic(game.ressources["car2"],2), new Graphic(game.ressources["car2"],2)],
			margin : 150,
			speed : difficulty + Math.random() * randomness
		}, {
			cars : [new Graphic(game.ressources["car3"]), new Graphic(game.ressources["car3"]), new Graphic(game.ressources["car3"])],
			margin : 135,
			speed : difficulty + Math.random() * randomness
		}, {
			cars : [new Graphic(game.ressources["car4"]), new Graphic(game.ressources["car4"]), new Graphic(game.ressources["car4"])],
			margin : 100,
			speed : 500 + difficulty + Math.random() * randomness
		}, {
			cars : [new Graphic(game.ressources["car5"]), new Graphic(game.ressources["car5"]), new Graphic(game.ressources["car5"])],
			margin : 200,
			speed : difficulty + Math.random() * randomness
		}
	];

	return [logsLines, carsLines];
}