var extend = function(source, target) {
    var keys = Object.keys(source),
        i = keys.length,
        target = target || {};
    while (i--) {
        target[keys[i]] = source[keys[i]];
    }
    return target;
}



var Game = function(width, height, div) {
    // never lose the "north" !
    var self = this;

	// parse params
    console.log("Parsing params");
	width = parseInt(width);
	height = parseInt(height);
	if(isNaN(width) || width < 1) width = 600;
	if(isNaN(height) || height < 1) height = 400;
	if(!(div instanceof HTMLElement) && !(typeof div === "string" && (div = document.getElementById(div)) != null)) div = document.body;

    // variables
    this.canvas = null;
    this.ctx = null;
    this.ressources = {};
    this.fps = 30; // frame per second
    this.lps = 15; // game loop per second
    this.w = width;
    this.h = height;

	// create canvasElement in div
	(function() {
        console.log("Create canvas "+width+"x"+height);
		self.canvas = document.createElement('canvas');
		// canvas size
        self.canvas.setAttribute('width', width);
        self.canvas.setAttribute('height',  height);

        // displayed size
        screenWidth = document.width - div.offsetLeft;
        screenHeight = document.height - div.offsetTop;
        if(screenWidth > window.screen.height) {
            div.style.height = self.canvas.style.height  = (screenHeight)+"px";
            div.style.width  = self.canvas.style.width   = (width/(height/screenHeight))+"px";
        } else {
            div.style.width  = self.canvas.style.width   = (screenWidth)+"px";
            div.style.height = self.canvas.style.height  = (height/(width/screenWidth))+"px";
        }

        // text error message
        self.canvas.innerHTML = "Your browser does not support canvas, "
        	+ " you won't be able to run the game. "
        	+ "Please update or change your browser to continue.";

        
        if(!self.canvas.getContext) 
            throw "This web browser does not support canvas.";

        div.appendChild(self.canvas);
        self.ctx = self.canvas.getContext("2d");
	}());

    var toLoad = 0;
    var loaded = 0;
    var loadCallback = function() {};
    var loadHandler = function(event, timeout) {
        if(timeout != undefined) { 
            if(loaded !== toLoad) console.error("Unable to load " + (toLoad-loaded) + " ressources, try refresh page.");
            return;
        }
        if(this.className == "loaded") return;
        this.className = "loaded";
        console.log("'" + this.name + "' loaded - Done: " + (++loaded) + "/" + toLoad);
        self.ressources[this.name] = this;
        if(loaded === toLoad) loadCallback();
    }
    
    this.load = function(imgArray, callback) {
        toLoad = Object.keys(imgArray).length;
        if(typeof callback !== "function") throw "Load second parameter must be a callback function.";
        loadCallback = callback;
        console.log("Loading " + toLoad + " ressources ...");
        for(var img in imgArray) {
            var imageElem = new Image();
            imageElem.src = imgArray[img];
            imageElem.name = img;
            imageElem.onload = loadHandler;
            if(imageElem.complete) // sometime, onload event is not fired when image came from cache. Fire it here.
                imageElem.onload();
        }
        setTimeout(function() { loadHandler(null, true); }, 5000); // wait 2s before sending timeout
    }

    var drawables = [];
    this.scene = { name : "default-scene" };
    this.scene.add = function(drawable) {
        if (!(drawable instanceof Drawable))
            throw "Only 'Drawable' can be added to a scene.";

        drawables.push(drawable);
        console.log("Graphic '" + drawable.name + "' added to scene '" + this.name + "'");
    }
    this.scene.remove = function(drawable) {
        if (!(drawable instanceof Drawable))
            throw "Only 'Drawable' can be remove from a scene.";

        for (var i = drawables.length - 1; i >= 0; i--) {
            if(drawables[i] == drawable)
                drawables.splice(i,1); // remove
        };
        console.log("Graphic '" + drawable.name + "' removed from scene '" + this.name + "'");
    }
    this.scene.get = function() {
        return drawables;
    }

    var updater = function() {
        for(var drawable in drawables) {
            // update calc drawables animations
            // and put results in an animation queue
            drawables[drawable].update(self.fps);
        }
    }

    var painter = function() {
        for(var drawable in drawables) {
            try {
                drawables[drawable].tick(self.ctx,  // update coord for animation
                    drawables[drawable].x, drawables[drawable].y, 
                    drawables[drawable].w, drawables[drawable].h);
                drawables[drawable].paint(self.ctx,  // draw it on canvas
                    drawables[drawable].x, drawables[drawable].y, 
                    drawables[drawable].w, drawables[drawable].h);
            } catch (ex) {
                console.error("Can't draw Drawable '" + drawable.name + "'");
                throw ex;
            }
        }
    }

    this.main = null;
    Object.defineProperty(
        this, "main", {
            set: function(func) {
                if(typeof func !== "function")
                    throw "Game 'main' must be a function.";
                main = func;

                console.log("Launching game loops");
                // tricky timed loop (as lps or fps can change).
                function mainloop(that) {
                    main(); // game runtime
                    updater(); // prepare drawables
                    that.events();
                    setTimeout(function() { mainloop(that); }, 1000/that.lps); // use anonyme function for IE T.T
                }; mainloop(this);
                function drawloop(that) {
                    painter();
                    setTimeout(function() { drawloop(that); }, 1000/that.fps); // use anonyme function for IE T.T
                }; drawloop(this);
                console.log("Game is running");
            }
        }
    );

    var keyboard = {};
    this.keys = {};
    this.setKeyboard = function(userKeys) {
        if(typeof userKeys != "object")
            throw "Keys must be an object";

        keyboard = {};
        for(var key in userKeys) {
            keyboard[parseInt(userKeys[key])%255] = key;
            this.keys[key] = false;
        }
        
        // add events catcher
        var that = this;
        window.onkeydown   = function(e) { that.events(e, that); };
        this.canvas.onmousemove = function(e) { that.events(e, that); };
        this.canvas.onmousedown = function(e) { that.events(e, that); };
        this.canvas.onmouseup   = function(e) { that.events(e, that); };
        
    };

    this.mouse = {
        left:   false,
        middle: false,
        right:  false,
        x : 0, y : 0
    };
    this.events = function(e, that) {
        // reset events
        if(e == undefined){
            for(var key in self.keys)
                self.keys[key] = false;
            this.mouse.left   = false;
            this.mouse.middle = false;
            this.mouse.right  = false;
            return;
        }


        var e = window.event || e;

        if(e.type=="keydown") {
            var c = e.charCode || e.keyCode || null;
            if(keyboard[c] != undefined)
                self.keys[keyboard[c]] = true;
            else
                self.keys[c] = true;
            console.debug("Key "+((keyboard[c]==undefined)?"n°"+c:"'"+keyboard[c]+"'")+" pressed");
        } else if(e.type == "mousemove" || e.type == "mousedown" || e.type == "mouseup") {
            var x,y;
            if (e.pageX || e.pageY) { 
                x = e.pageX;
                y = e.pageY;
            } else { 
                x = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft; 
                y = e.clientY + document.body.scrollTop + document.documentElement.scrollTop; 
            }
            self.mouse = {
                left:   (e.type == "mousedown" && e.button == 0)?true:self.mouse.left,
                middle: (e.type == "mousedown" && e.button == 1)?true:self.mouse.middle,
                right:  (e.type == "mousedown" && e.button == 2)?true:self.mouse.right,
                x: x - that.canvas.offsetLeft,
                y: y - that.canvas.offsetTop
            }

            if(e.type == "mousedown") console.debug("Mouse clic at ("+self.mouse.x+", "+ self.mouse.y+")");
        }
    }

};