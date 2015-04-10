
function menuItem()
{
var that = this;
    this.description,
    this.text,
    
     this.hover = function(evt)
        {
          this.text[0].color = "#999";
          that.description.show();
        }
        
        this.leave = function(evt)
        {
          this.text[0].color = "#FFF";
          that.description.hide();
        }
    
    this.initialize = function(theContainer, text, evt, textCenter, fontSize, descript, gap)
    {
        /*button.on("click", function(evt)
        {
            evt();   
        });*/
        this.text = addText(theContainer, text, textCenter, evt, evt != undefined, fontSize, null, gap);
        this.description = new Description();
        if(descript != undefined)
        {
            this.description.initialize(theContainer.parent, descript);
            for(var i=0; i<this.text.length; i++)
            {
                this.text[i].on("mouseover", function(evt)
                {
                  this.color = "#999";
                  that.description.show();
                });
                this.text[i].on("mouseout", function(evt)
                {
                  this.color = "#FFF";
                  that.description.hide();
                });
            }
        }
    }
}

function addText(container, text, center, event, withEvents, fontSize, statText, gap, descript)
    {
        var numChildren = 0;
		var lastIndex = -1;
		var startY = 0;
        for(var i=0;i<container.children.length;i++)
        {
			if(container.children[i].text != undefined && ((lastIndex == -1 || container.children[lastIndex].y != container.children[i].y) && container.children[i].visible))
			{
			  startY += container.children[i].getMeasuredHeight();
			  numChildren += (container.children[i].text != undefined)?1:0;
			  lastIndex = i;
			}
        }
		var description = new Description();
		if(descript != undefined)
		{
			description.initialize(gameContainer, descript);
		}
        var leGap = gap;
		if(gap == null)
		{
			leGap = 8;
		}
        var graphic = new createjs.Text("", fontSize+"px Impact", "#FFF");
        graphic.x = 10+container.children[0].x;
        graphic.y = startY+(leGap*(numChildren+1))+container.children[0].y;
        var count = 0;
        var currentEditingText = [];
        var current = 0;
		var widthToCheck = container.children[0].image.width;
		if(container.children[0].scaleX != undefined)
		{
			widthToCheck *= container.children[0].scaleX;
		}
        currentEditingText.push(graphic);
        for(var i=0; i<text.length; i++)
        {
            currentEditingText[current].text += text[i];
            count++;
            if(text[i] === ' ')
            {
				var test = currentEditingText[current].getMeasuredWidth();
                if(currentEditingText[current].getMeasuredWidth() > widthToCheck - 20)
                {
                    var deletedText = currentEditingText[current].text.substring(currentEditingText[current].text.length-count,currentEditingText[current].text.length);
                    currentEditingText[current].text = currentEditingText[current].text.substring(0, currentEditingText[current].text.length-count);
                    if(center)
                    {
                        currentEditingText[current].x = container.children[0].x + (widthToCheck - currentEditingText[current].getMeasuredWidth())/2
                    }
					var hit = new createjs.Shape();
					hit.graphics.beginFill("#000").drawRect(0,0,currentEditingText[current].getMeasuredWidth(), currentEditingText[current].getMeasuredHeight());
					currentEditingText[current].hitArea = hit;
                    if(withEvents)
                    {
                        currentEditingText[current].on("mouseover", function(evt)
                        {
                           currentEditingText[current].color = "#999"; 
						   description.show();
                        });
                        currentEditingText[current].on("mouseout", function(evt)
                        {
                           currentEditingText[current].color = "#FFF"; 
						   description.hide();
                        });
                         currentEditingText[current].on("click", function(evt)
                        {
                            event();
                        });
                    }
					
                    container.addChild(currentEditingText[current]);
                    currentEditingText.push(new createjs.Text("", fontSize+"px Impact", "#FFF"));
                    current++;
                    currentEditingText[current].x = graphic.x;
                    currentEditingText[current].y = currentEditingText[current-1].y+ graphic.getMeasuredHeight()+8;
                    currentEditingText[current].text = deletedText;
                }
                count=0;
            }
        }
        if(center)
        {
            currentEditingText[current].x =container.children[0].x + (widthToCheck - currentEditingText[current].getMeasuredWidth())/2;
        }
		var hit = new createjs.Shape();
		hit.graphics.beginFill("#000").drawRect(0,0,currentEditingText[current].getMeasuredWidth(), currentEditingText[current].getMeasuredHeight());
		currentEditingText[current].hitArea = hit;
        if(withEvents)
		{
			currentEditingText[current].on("mouseover", function(evt)
			{
			   currentEditingText[current].color = "#999"; 
			   description.show();
			});
			currentEditingText[current].on("mouseout", function(evt)
			{
			   currentEditingText[current].color = "#FFF"; 
			   description.hide();
			});
			 currentEditingText[current].on("click", function(evt)
			{
				event();
			});
		}
		container.addChild(currentEditingText[current]);
			if(statText != undefined)
			{
				statText.graphic.font = fontSize+"px impact"; 
				statText.graphic.y = (currentEditingText[current].getMeasuredWidth()+statText.graphic.getMeasuredWidth() < widthToCheck-20)?currentEditingText[current].y:currentEditingText[current].y+graphic.getMeasuredHeight()+8;
				statText.graphic.x = widthToCheck-20-statText.graphic.getMeasuredWidth()+graphic.x;
				currentEditingText.push(statText);
				container.addChild(statText.graphic);
			}
            return currentEditingText;
    }
	
	function alignTextRight(textObj, alignPoint)
	{
		var widthToCheck = alignPoint;
		if(alignPoint == -1)
		{
			widthToCheck = textObj.parent.children[0].image.width;
			if(textObj.parent.children[0].scaleX != undefined)
			{
				widthToCheck *= textObj.parent.children[0].scaleX;
			}
		}
		var xAdd = textObj.parent.children[0].x;
		textObj.x = 10+widthToCheck - 20 - textObj.getMeasuredWidth();
		if(alignPoint == -1)
		{
			textObj.x += xAdd;
		}
	}
	
	function addStatText(object, statA, statB, fontSize)
	{
		this.object = object;
		this.statA = statA;
		this.statB = statB;
		this.alignPoint = -1;
		this.graphic = new createjs.Text(object[statA], fontSize+"px Impact", "#FFF");
		if(statB != undefined)
		{
			this.graphic.text += "/"+object[statB];
		}
		particles.push(this);
		this.update = function(dt)
		{
			if(this.graphic.parent != null)
			{
				this.graphic.text = this.object[this.statA];
				if(this.statB != undefined)
				{
					this.graphic.text += "/"+this.object[this.statB];
					alignTextRight(this.graphic, this.alignPoint);
				}
			}
			else
			{
				this.graphic = this.graphic;
				this.graphic.visible = false;
			}
		}
		
	}
	
	function addMovingText(container, text, location, lifetime, fontSize, color)
	{
		this.graphic = new createjs.Text(text, fontSize+"px impact", color);
		this.graphic.x = location.x;
		this.graphic.y = location.y;
		this.velocity = -50;
		this.lifetime = lifetime;
		this.startingLife = lifetime;
		particles.push(this);
		container.addChild(this.graphic);
		this.update = function(dt)
		{
			if(this.graphic.visible)
			{
				this.graphic.y += this.velocity*dt;
				this.lifetime -= dt;
				this.graphic.alpha = 2*this.lifetime/this.startingLife;
				if(this.lifetime <= 0)
				{
					this.graphic.visible = 0;
				}
			}
		}
	}
	
	function removeMenuItem(container, text)
	{
		var removed = false;
		var removedHeight = 0;
		for(var i=0; i<container.children.length; i++)
		{
			if(container.children[i].text != undefined)
			{
				if(!removed && container.children[i].text == text)
				{
					removedHeight = container.children[i].getMeasuredHeight();
					container.removeChild(container.children[i]);
					removed = true;
					i--;
				}
				else if(removed && container.children[i].text != undefined)
				{
					container.children[i].y -= removedHeight;
				}
			}
		}
	}
	
	function removeMenuTextObjects(container, textObjs)
	{
		var removed = 0;
		var removedHeight = textObjs[0].getMeasuredHeight();
		var length = textObjs.length;
		for(var i=0; i<container.children.length; i++)
		{
			if(removed != length)
			{
				container.removeChild(textObjs[removed++]);
			}
			if(container.children[i].text != undefined && container.children[i].y > textObjs[0].y && container.children[i].visible)
			{
				container.children[i].y -= removedHeight;
			}
		}
	}
	
	function removeObjectsInLine(container, firstText)
	{
		var removedY = -1;
		var height = 0;
		var found = false;
		for(i=0;i<container.children.length;i++)
		{
			if(container.children[i].text != undefined || found)
			{
				if(container.children[i].y == removedY || container.children[i].text == firstText)
				{
					if(!found)
					{
						height = container.children[i].getMeasuredHeight();
						container.removeChild(container.children[i-1]);
						i--;
					}
					removedY = container.children[i].y;
					container.removeChild(container.children[i]);
					found = true;
					i--;
				}
				else if(removedY != container.children[i].y)
				{
					container.children[i].y -= height;
				}
			}
		}
	}
	
	function setToSingleLine(graphics, container, description, centerAtEnd, event)
	{
	    var width = container.children[0].image.width;
	    var y = graphics[0].y;
	    var x = container.children[0].x+10;
	    if(container.children[0].scaleX != undefined)
	    {
	        width *= container.children[0].scaleX;
	    }
	    width -= 25;
	    var totalGraphicWidth = 0;
		var height = 0;
	    for(var i=0; i<graphics.length; i++)
	    {
	        if(graphics[i].text != undefined)
	        {
	            totalGraphicWidth += graphics[i].getMeasuredWidth();
				height = graphics[i].getMeasuredHeight();
	        }
	        else
	        {
	            totalGraphicWidth += graphics[i].getBounds().width;
	        }
	    }
		var box = new createjs.Shape();
		box.graphics.beginFill("#000").drawRect(0,0, width, height+5);
		box.x = x;
		box.y = y+2;
		box.alpha = .01;
		container.addChild(box);
		var denominator = (centerAtEnd)?graphics.length:graphics.length+1;
	    var gap = (width-totalGraphicWidth)/(denominator);
	    for(var i=0; i<graphics.length;i++)
	    {
	        graphics[i].y = y
	        graphics[i].x = gap*(i+1)+x;
			if(graphics[i].text != null)
			{
				x += graphics[i].getMeasuredWidth();
			}
			else
			{
				x += graphics[i].getBounds().width;
			}
			if(description != null)
			{
				graphics[i].on("mouseover", function(evt)
				{
					if(this.color != undefined)
					{
						this.color = "#999";
					}
					description.show();
				});
				graphics[i].on("mouseout", function(evt)
				{
					if(this.color != undefined)
					{
						this.color = "#FFF";
					}
					description.hide();
				});
			}
	    }
		if(event != undefined)
		{
			box.on("mouseover", function(evt)
			{
				box.alpha = .5;
				description.show();
			});
			box.on("mouseout", function(evt)
			{
				box.alpha = .01;
				description.hide();
			});
			box.on("click", function(evt)
			{
				description.hide();
				event();
			});
		}
	}
	
function setToSpacedRow(container, textObjs, spacing, descript, numRows, placedRow, event)
{
	var gap = 20;
	var width = container.children[0].image.width;
	if(container.children[0].scaleX != undefined)
	{
		width *= container.children[0].scaleX;
	}
	width -= 30;
	var currX = 15+container.children[0].x;
	var currY = textObjs[0][0].y;
	if(numRows != undefined)
	{
		var height = container.children[0].image.height;
		if(container.children[0].scaleY != undefined)
		{
			height *= container.children[0].scaleY;
		}
		var yIncrement = (height-16)/numRows;
		currY = container.children[0].y+yIncrement*(placedRow-1)+8;
	}
	var box = new createjs.Shape();
	box.graphics.beginFill("#000").drawRect(0,0, width, textObjs[0][0].getMeasuredHeight()+5);
	box.x = currX;
	box.y = currY;
	box.alpha = .01;
	if(descript != undefined)
	{
		var info = new Description();
		info.initialize(gameContainer, descript);
		box.on("mouseover", function(evt){
			if(textObjs[0][0].visible)
			{
				info.show();
				if(event != undefined){box.alpha = .5;
			}
			}
		});
		box.on("mouseout", function(evt){info.hide();
				box.alpha=.01;});
		if(event != undefined)
		{
			box.on("click", function(evt)
			{
				event();
			});
		}
		container.addChild(box);
	}
	var increment = width/textObjs.length;
	for(var i=0; i<textObjs.length; i++)
	{
		currX = 15+increment*i+container.children[0].x;
		var totalTextWidth = (textObjs[i].length-1)*gap;
		if(spacing[i].toLowerCase() == "center")
		{
			for(var k=0; k<textObjs[i].length; k++)
			{
				totalTextWidth += textObjs[i][k].getMeasuredWidth();
			}
			currX += (increment-totalTextWidth)/2;
		}
		if(spacing[i].toLowerCase() == "right")
		{
			for(var k=0; k<textObjs[i].length; k++)
			{
				totalTextWidth += textObjs[i][k].getMeasuredWidth();
			}
			currX += increment-totalTextWidth;
		}
		for(var j=0; j<textObjs[i].length; j++)
		{
			textObjs[i][j].x = currX;
			textObjs[i][j].y = currY;
			currX += textObjs[i][j].getMeasuredWidth()+gap;
			container.addChild(textObjs[i][j]);
		}
	}
	
	return box;
} 
    
    
var particleTransitions =
{
  ARC: 0,
  LERP: 1,
};

function vec2(x,y)
{
    this.x = x;
    this.y = y;
}

function distance(vecA, vecB)
{
    return Math.sqrt(Math.pow((vecA.x-vecB.x),2) + Math.pow((vecA.y-vecB.y),2));
}

function subtractVec(vecA, vecB)
{
    return new vec2(vecA.x-vecB.x, vecA.y-vecB.y);
}

function normalize(vec)
{
	var newVec = vec;
	var length = distance(vec, new vec2(0,0));
	newVec = new vec2(vec.x/length, vec.y/length);
	return newVec;
}

function particle()
{
    this.graphic;
	this.lifetime;
    this.velocity;
	this.totalLifetime;
    this.rotation;
	
    this.initialize = function(container, start, image, initialVel, lifetime, scale, rotation)
    {
	this.rotation = rotation;
        this.graphic = new createjs.Bitmap(queue.getResult(image));
        this.graphic.x = start.x;
        this.graphic.y = start.y;
        this.graphic.regX = this.graphic.image.width/2;
        this.graphic.regY = this.graphic.image.height/2;
		this.graphic.scaleX = scale;
		this.graphic.scaleY = scale;
        this.velocity = initialVel;
		this.lifetime = lifetime;
		this.totalLifetime = lifetime;
        container.addChild(this.graphic);
		particles.push(this);
    }
    
    this.update = function(dt)
    {
		if(this.graphic.visible)
		{
			this.graphic.x += this.velocity.x*dt;
			this.graphic.y += this.velocity.y*dt;
			if(this.rotation)
			{
				this.graphic.rotation += this.rotation*dt;
			}
			this.graphic.alpha = this.lifetime/this.totalLifetime;
			this.lifetime -= dt;
			if(this.lifetime < 0)
			{
				this.graphic.visible = false;
				var i = particles.indexOf(this);
				particles.splice(i, 1);
			}
		}
	}
}


function lerp(end, obj, increment, incChange, move)
{
	this.increment = increment;
	this.acceleration = incChange;
	if(incChange == undefined)
	{
		this.acceleration = 0;
	}
	this.start = new vec2(obj.x,obj.y);
	this.end = end;
	this.obj = obj;
	this.beta = 0;
	this.move = move;
	particles.push(this);
	this.update = function(dt)
	{
		if(this.beta < 1)
		{
			this.beta += this.increment;
			if(this.beta>1)
			{
				this.beta = 1;
				if(this.move != undefined)
				{
					this.move();
				}
				var i = particles.indexOf(this);
				particles.splice(i,1);
			}
			this.beta = (this.beta>1)?1:this.beta;
			this.increment += this.acceleration;
			var transformedPos = subtractVec(this.end, this.start);
			this.obj.x = (transformedPos.x*this.beta)+this.start.x;
			this.obj.y = (transformedPos.y*this.beta)+this.start.y;
		}
	}
}

function progressBar()
{
    this.amount,
    this.graphic,
    this.outline,
    this.incrementAmount,
	this.action,
    
    this.initialize = function(container, x, y, w, h, startValue, increment, action)
    {
		var width = w;
		if(w == null)
		{
			width = container.children[0].image.width-30;
			if(container.children[0].scaleX != undefined)
			{
				width *= container.children[0].scaleX;
			}
			x = container.children[0].image.x+15;
			y = container.children[0].image.height + container.children[0].y - 12 - h;
		}
        this.amount = startValue/100;
        this.incrementAmount = increment/100;
        this.graphic = new createjs.Shape();
        this.graphic.graphics.beginFill("#04F").drawRect(0,0, width, h);
        this.graphic.x = x;
        this.graphic.y = y;
        this.outline = new createjs.Shape();
        this.outline.graphics.beginFill("#FFF").drawRect(0,0, width+4,h+4);
        this.outline.x = x-2;
        this.outline.y = y-2;
        this.graphic.scaleX = this.amount;
		var test = w*this.graphic.scaleX;
        this.graphic.setBounds(0,0,width,h);
		this.outline.setBounds(0,0,width,h);
        container.addChild(this.outline);
        container.addChild(this.graphic);
		this.action = action;
    }
	
	this.setSpeed = function(newSpeed)
	{
		this.incrementAmount = newSpeed/100;
	}
    
    this.update = function(dt)
    {
		if(!progressHalted)
		{
			this.graphic.scaleX = this.amount;
			this.graphic.x = this.outline.x+2;
			this.graphic.y = this.outline.y+2;
			this.amount += this.incrementAmount*dt;
		}
		if(this.amount >= 1)
		{
		  this.amount = 1;
		  if(this.action == null || this.action())
		  {
			this.amount = 0;
		  }
		}
    }
}

function Description()
{
    this.textGraphic,
    this.graphic,
    
    this.initialize = function(container, text)
    {
        this.textGraphic = addText(container, text, false, null, false, 20);
        var height = this.textGraphic.length * this.textGraphic[0].getMeasuredHeight()+15*(this.textGraphic.length+1);
        this.graphic = new createjs.Bitmap(queue.getResult("basicWindow80"));
        this.graphic.scaleX = container.children[0].image.width/this.graphic.image.width;
        this.graphic.scaleY = height/this.graphic.image.height;
		height = this.textGraphic[0].getMeasuredHeight();
        container.addChild(this.graphic);
        for(var i=0; i<this.textGraphic.length; i++)
        {
            this.textGraphic[i].x = 10;
			this.textGraphic[i].y = 8+(i*(height+5));
            container.addChild(this.textGraphic[i]);
            this.textGraphic[i].visible = false;
        }
        this.hide();
    }
    
    this.show = function()
    {
		if(this.textGraphic != undefined)
		{
			for(var i=0; i<this.textGraphic.length; i++)
			{
				this.textGraphic[i].visible = true;
			}
			this.graphic.visible = true;
		}
    }
    
    this.hide = function()
    {
		if(this.textGraphic != undefined)
		{
			for(var i=0; i<this.textGraphic.length; i++)
			{
				this.textGraphic[i].visible = false;
			}
			this.graphic.visible = false;
		}
    }
}

function addDescription(container, textObj, descriptText, mouseOverColor)
{
	var descript = new Description();
	descript.initialize(container, descriptText);
	textObj.on("mouseover", function(evt)
	{
		textObj.color = mouseOverColor;
		descript.show();
	});
	textObj.on("mouseout", function(evt)
	{
		textObj.color = "#FFF";
		descript.hide();
	});
}

var particles = [];
var progressHalted = false;

function addProgressBar(container, x, y, w, h, startValue, increment, action)
{
    particles.push(new progressBar());
    particles[particles.length-1].initialize(container, x, y, w, h, startValue, increment, action);
	return particles[particles.length-1];
}

function addParticle(container, start, image, initialVel)
{
    particles.push(new particle());
    particles[particles.length-1].initialize(container,start, image, initialVel);
}

function scaleParticle(image, container, speed)
{
	this.onComplete;
	this._dontDestroy = 0;
	this.firstTime = true;
	this.initialize = function(pos)
	{
		this.graphic = new createjs.Bitmap(queue.getResult(image));
		this.speed = speed;
		this.graphic.sourceRect = new createjs.Rectangle(0,0,0,0);
		container.addChild(this.graphic);
		this.graphic.regX = this.graphic.image.width/2;
		this.graphic.regY = this.graphic.image.height/2;
		this.graphic.x = pos.x;
		this.graphic.y = pos.y;
		this.graphic.visible = true;
		this.currDimension = 0;
		if(this.firstTime)
		{
			particles.push(this);
			this.firstTime = false;
		}
		console.log(this.currDimension);
	}
	this.update = function(dt)
	{
		if(this.graphic.visible)
		{
			this.currDimension += this.speed*dt;
			this.graphic.sourceRect = new createjs.Rectangle(0,0,this.currDimension,this.currDimension);
			if(this.currDimension > this.graphic.image.width)
			{
				this.currDimension = this.graphic.image.width;
				if(this.onComplete != undefined && this.graphic.alpha <= 0)
				{
					this.onComplete();
					this.graphic.visible = false;
				}
				this.graphic.alpha -= 1.5*dt;
			}
			
		}
	}
}


function tutorial()
{
this.currentSlide = 0;
this.lastSlide = -1;
this.slides = [];
var that = this;


function slide(pos, text, extraObjs)
	{
	this.view = function()
		{
			new lerp(pos, tutorialContainer.children[0], .04, .01, function(){
			for(i =0; i<me.content.length; i++)
			{
				me.content[i].visible = true;
			}	
			if(me.extraObjs)
			{
				for(i = 0; i<me.extraObjs.length; i++)
				{
					me.extraObjs[i].visible = true;
				}
			}
			me.skip[0].visible = true;
			me.next[0].visible = true;
			});
		}
		
		this.hide = function()
		{
		
			for(i =0; i<this.content.length; i++)
			{
				this.content[i].visible = false;
			}
			if(this.extraObjs)
			{
				for(i = 0; i<this.extraObjs.length; i++)
				{
					this.extraObjs[i].visible = false;
				}
			}
			this.skip[0].visible = false;
			this.next[0].visible = false;
		}
		
		this.extraObjs = extraObjs;
		if(this.extraObjs)
		{
		for(i=0;i<this.extraObjs.length;i++)
		{
			this.extraObjs.visible = false;
		}
		}
		this.pos = pos;
		var me = this;
		var prevPos = new vec2(tutorialContainer.children[0].x,tutorialContainer.children[0].y);
		tutorialContainer.children[0].x = pos.x;
		tutorialContainer.children[0].y = pos.y;
		this.content = addText(tutorialContainer, text, false, null, false, 20);
		this.skip = addText(tutorialContainer, "Skip Tutorial", false, function(){me.hide();that.currentSlide=that.slides.length;},true, 20);
		this.next = addText(tutorialContainer, "Next", false, function(){me.hide();that.currentSlide++}, true, 20);
		this.skip[0].y = tutorialContainer.children[0].image.height*tutorialContainer.children[0].scaleY - this.skip[0].getMeasuredHeight()-15+this.pos.y;
		setToSpacedRow(tutorialContainer, [[this.skip[0]],[this.next[0]]],["left","right"]);
		tutorialContainer.children[0].x = prevPos.x;
		tutorialContainer.children[0].y = prevPos.y;
		this.hide();
	}

	this.addSlide = function(pos, text, extraObjs)
	{
		var thisSlide = new slide(pos, text, extraObjs);
		this.slides.push(thisSlide);
	}
	
	this.play = function()
	{
		this.box = new createjs.Shape();
		this.box.graphics.beginFill("#000").drawRect(0,0,800,600);
		this.box.alpha = .7;
		var i = gameContainer.children.indexOf(tutorialContainer);
		gameContainer.addChildAt(this.box, i);
		tutorialContainer.visible = true;
		particles.push(this);
	}
	
	this.update = function(dt)
	{
		if(that.currentSlide >= that.slides.length)
		{
			gameContainer.removeChild(that.box);
			tutorialContainer.visible = false;
		}
		else if(that.lastSlide != that.currentSlide)
		{
			that.slides[that.currentSlide].view();
			that.lastSlide = that.currentSlide;
		}
	}
}

function lerpParticle(start, end, image, container, speed, mid, trailImage, trailLife, scale, angleRange)
{
    this.begin = start;
    this.end = end;
	this.container = container;
	this.onComplete;
	this.trailImage = trailImage;
	this.trailLife = trailLife;
	this._dontDestroy = 0;
	this.extraParticles = [];
	this.firstTime = true;
    
    this.beta = 0;
    this.increment = 1/(distance(start,end)/speed);
	this.mid = mid;
	this.graphic = new createjs.Bitmap(queue.getResult(image));
    if(mid != undefined)
    {
      this.midPoint = new vec2((this.end.x-this.begin.x)/2, (this.end.y - this.begin.y)/2);
      this.middle = -(this.midPoint.y+mid);
      this.yDenominator = subtractVec(end, start).x / Math.PI;
    }
	this.created = false;
	
	this.initialize = function(start, end)
	{
	this.firstTime = true;
		if(end != undefined)
		{
			this.begin = start;
			this.end = end;
			this.increment = 1/(distance(start,end)/speed);
			if(this.mid != undefined)
			{
			  this.midPoint = new vec2((this.end.x-this.begin.x)/2, (this.end.y - this.begin.y)/2);
			  this.middle = -(this.midPoint.y+this.mid);
			  this.yDenominator = subtractVec(this.end, this.begin).x / Math.PI;
			}
		}
		this.graphic = new createjs.Bitmap(queue.getResult(image));
		this.container.addChild(this.graphic);
		this.graphic.regX = this.graphic.image.width/2;
		this.graphic.regY = this.graphic.image.height/2;
		this.created = true;
		this.beta = 0;
		this.graphic.visible = true;
		particles.push(this);
	}
    
    this.update = function(dt)
    {
		if(this.created)
		{
			var test = distance(start, end);
			var oldPos = new vec2(this.graphic.x, this.graphic.y);
			this.beta += this.increment;
			this.beta = (this.beta > 1)?1:this.beta;
			var newPos = subtractVec(this.end,this.begin);
			var transformedPos = new vec2(newPos.x*this.beta+this.begin.x, newPos.y*this.beta+this.begin.y);
			this.graphic.x = transformedPos.x;
			this.graphic.y = transformedPos.y;
			if(this.middle != undefined)
			{
			  this.graphic.y =  this.middle*Math.sin(newPos.x*this.beta/this.yDenominator)+transformedPos.y;
			}
			if(this.trailImage && this.beta - this.increment > 0.00001 && this.beta < 1)
			{
				for(i=0;i<5;i++)
				{
					var trail = new particle();
					var targetPos = subtractVec(oldPos, new vec2(this.graphic.x,this.graphic.y));
					targetPos.x *= 10;
					targetPos.y *= 10;
					var angle = (Math.random()*(angleRange)-(angleRange/2));
					angle *= (Math.PI/180);
					var test = Math.cos(angle);
					var newx = ((targetPos.x*Math.cos(angle)))-(targetPos.y*Math.sin(angle));
					var newy = ((targetPos.y*Math.cos(angle))) +((targetPos.x * Math.sin(angle)));
					trail.initialize(this.container, new vec2(this.graphic.x, this.graphic.y),this.trailImage,new vec2(newx,newy), this.trailLife, scale);
					this.extraParticles.push(trail);
				}
			}
			
			if(this.beta == 1)
			{
				var count = 0;
				this.graphic.visible = false;
				for(i =0; i<this.extraParticles.length;i++)
				{
					count += (this.extraParticles[i].graphic.visible)?1:0;
				}
				if(this.onComplete != undefined && this.firstTime)
				{
					this.onComplete();
					this.firstTime = false;
				}
				if(count == 0)
				{
					this.created = false;
					this.beta = 0;
					var index = particles.indexOf(this);
					particles.splice(index, 1);
				}
			}
		}
    };
}

function addScreenShake(lifetime, freq)
{
	this.lifetime = lifetime;
	this.frequency = freq;
	this.goingUp = true;
	this.onComplete;
	particles.push(this);
	this.update = function(dt)
	{
		
		if(this.goingUp)
		{
			gameContainer.children[0].x += 300*dt;
			itemShopContainer.children[0].x += 300*dt;
			bossGoldContainer.children[0].x += 300*dt;
			this.goingUp = (gameContainer.children[0].x <= this.frequency);
		}
		else
		{
			gameContainer.children[0].x -= 300*dt;
			itemShopContainer.children[0].x -= 300*dt;
			bossGoldContainer.children[0].x -= 300*dt;
			this.goingUp = (gameContainer.children[0].x <= -this.frequency);
			if(this.goingUp)
			{
				this.frequency *= .25;
			}
		}
		this.lifetime -= dt;
		if(this.lifetime < 0)
		{
			gameContainer.children[0].x = 0;
			itemShopContainer.children[0].x = 0;
			bossGoldContainer.children[0].x = 0;
			var i = particles.indexOf(this);
			particles.splice(i, 1);
			if(this.onComplete)
			{
				this.onComplete();
			}
		}
	}
}

function addBurstEffect(container, lifetime, numParticles, initialVel, start, image, scale)
{
	this.start = function(){
		for(i=0;i<numParticles;i++)
		{
			var angle = 360*(i/numParticles);
			angle *= (Math.PI/180);
			var x = ((initialVel.x*Math.cos(angle)))-(initialVel.y*Math.sin(angle));
			var y = ((initialVel.y*Math.cos(angle))) +((initialVel.x * Math.sin(angle)));
			var burst = new particle();
			burst.initialize(container, start, image, new vec2(x,y), lifetime, scale);
		}
	}
}

function addConeEffect(container, lifetime, angleRange, start, initialVel, scale, image, rate, rotate)
{
this.lifetime = lifetime;
this.begin = start;
this.container = container;
this.range = angleRange;
this.image = image;
this.myEffects = [];
this.onComplete;
this.rate = rate;
this.time = 0;
	this.initialize = function()
	{
		this.lifetime = lifetime;
		new addScreenShake(this.lifetime*.75, 20); 
		particles.push(this);
	}
	
	this.update = function(dt)
	{
		if(this.lifetime > 0)
		{
			this.lifetime -= dt;
			this.time += dt;
			if(this.time > this.rate)
			{
				var angle = Math.random()*angleRange-(angleRange/2);
				angle *= (Math.PI/180);
				var x = ((initialVel.x*Math.cos(angle)))-(initialVel.y*Math.sin(angle));
				var y = ((initialVel.y*Math.cos(angle))) +((initialVel.x * Math.sin(angle)));
				var prt = new particle();
				prt.initialize(container, this.begin, image, new vec2(x,y), lifetime/2, scale, Math.random()*rotate); 
				this.myEffects.push(prt);
				this.time = 0;
			}
		}
		else
		{
			var alive = false;
			for(i=0;i<this.myEffects.length && !alive;i++)
			{
				alive = this.myEffects[i].graphic.visible;
			}
			if(!alive)
			{
				var i = particles.indexOf(this);
				particles.splice(i,1);
				if(this.onComplete)
				{
					this.onComplete();
				}
			}
		}
	}
}

function addLerpParticle(container, start, end, image, speed, mid, trailImage, trailLife, scale, angleRange)
{
    particles.push(new lerpParticle(start, end, image, container, speed, mid, trailImage, trailLife, scale, angleRange));
	return particles[particles.length-1];
}

var time = 0;

function update(dt)
{
	time += dt;
    for(var i=0; i<particles.length; i++)
    {
        particles[i].update(dt);
    }
	if(time > 1)
	{
		cleanup();
		time = 0;
	}
}

function cleanup()
{
	var goodPrtcls = [];
	for(i=0; i<particles.length; i++)
	{
		if((particles[i].graphic == undefined || particles[i].graphic.visible) || particles[i]._dontDestroy != undefined)
		{
			goodPrtcls.push(particles[i]);
		}
	}
	particles = goodPrtcls;
}

function makeButton(button, sprite, container, event, position)
{
        button.gotoAndPlay(sprite+"Button");
        button.on("mouseover", function(evt)
                  {
                     button.gotoAndPlay(sprite+"Hover"); 
                  });
        button.on("mouseout", function(evt)
                    {
                        button.gotoAndPlay(sprite+"Button");
                    });
        button.on("mousedown", function(evt)
        {
            button.gotoAndPlay(sprite+"Click");
        });
        button.on("click", function(evt)
        {
            event();
        });
		button.x = position.x;
		button.y = position.y;
        container.addChild(button);
}