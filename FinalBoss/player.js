
function createPlayer() {
    this.level;
    this.alive;
    this.name;
    this.hpMax;
    this.mpMax;
    this.hpCurr;
    this.mpCurr;
    this.attackPhys;
    this.attackMagic;
    this.defensePhys;
    this.defenseMagic;
	this.viewedAtkPhys;
	this.viewedDefPhys;
	this.viewedAtkMagic;
	this.viewedDefMagic;
	this.viewedSpeed;
    this.speed;
	this.progressBar;
    this.allocationPoints;
    this.ptsAllocatedAtkPhys;
    this.ptsAllocatedAtkMagic;
    this.ptsAllocatedDefPhys;
    this.ptsAllocatedDefMagic;
	this.ptsAllocatedSpeed;
    this.abilities;
    this.items;
    this.statuses;
    this.graphic;
    this.move;
    this.param1;
    this.param2;
	this.pos
	this.gold;
	this.exp;
	this.expRequired;
	var me = this;
    
    this.initialize = function(startLevel) {
        this.allocationPoints = 3*startLevel;
        this.ptsAllocatedAtkPhys = 0;
        this.ptsAllocatedAtkMagic = 0;
        this.ptsAllocatedDefPhys = 0;
        this.ptsAllocatedDefMagic = 0;
		this.ptsAllocatedSpeed = 0;
        this.level = startLevel;
        this.alive = true;
        this.name = "Final Boss";
		if(this.level > 1) {
			this.hpMax = 250 * (1 + this.level/3);
			this.mpMax = 125 * (1 + this.level/4);
			this.speed = 1.5 * (1 + this.level/10); 
		} 
		else {
			this.hpMax = 250;
			this.mpMax = 125;
			this.speed = 1.5;
		}
		this.hpMax = Math.ceil(this.hpMax);
		this.mpMax = Math.ceil(this.mpMax);
        this.hpCurr = this.hpMax;
        this.mpCurr = this.mpMax;
        this.attackPhys = 10 + (3 * this.level);
        this.attackMagic = 10 + (3 * this.level);
        this.defensePhys = 10 + (3 * this.level);
        this.defenseMagic = 10 + (3 * this.level);
		this.viewedAtkPhys = this.attackPhys;
		this.viewedDefPhys = this.defensePhys;
		this.viewedAtkMagic = this.attackMagic;
		this.viewedDefMagic = this.defenseMagic;
		this.viewedSpeed = Math.ceil(this.speed*15);
        this.abilities = [];
        this.items = [];
        this.statuses = [];
        this.graphic = new createjs.Sprite(bossSheet);
		this.graphic.gotoAndPlay("attack");
		this.graphic.regX = 175;
		this.graphic.regY = -this.graphic.spriteSheet._frames[0].rect.height/2+50;
		this.graphic.x = 150;
		this.graphic.y = 250;
		this.expRequired = 50*(Math.pow(this.level, 1.3));
		this.exp = 0;
		this.pos = new vec2(this.graphic.x, this.graphic.y);
		gameContainer.addChildAt(this.graphic, 1);
		
		}
	
	this._setupLevelUp = function()
	{
		progressHalted = true;
		
		var levelText = addText(levelUpContainer, "LEVEL", true, null, false, 25);
		var currLevelText = new addStatText(this, "level", null, 25);
		var achievedText = addText(levelUpContainer, " ACHIEVED!!!", true, null, false, 25);
		setToSpacedRow(levelUpContainer, [[levelText[0], currLevelText.graphic, achievedText[0]]], ["center"], null, 8, 1); 
		var dottedText = addText(levelUpContainer, "---------------------------", true, null, false, 25);
		setToSpacedRow(levelUpContainer, [[dottedText[0]]], ["center"], null, 8, 2);
		
		this._setupLevelUpHelper("Physical Attack: ", "deallocateAtkPhys", "allocateAtkPhys", "ptsAllocatedAtkPhys", "viewedAtkPhys", 8, 3
			,"Physical Attack increases the damage of all of your basic attacks. It also increases the damage of physical abilities. Don't forget that your basic attacks will always deal at least 1/4 damage.");
		this._setupLevelUpHelper("Physical Defense: ", "deallocateDefPhys", "allocateDefPhys", "ptsAllocatedDefPhys", "viewedDefPhys", 8, 4
			,"Physical Defense decreases the amount of damage you take from enemy attacks and physical abilities. Remember that attacks will always deal at least 1/4 the hero's damage.");
		this._setupLevelUpHelper("Magical Attack: ", "deallocateAtkMagic", "allocateAtkMagic", "ptsAllocatedAtkMagic", "viewedAtkMagic", 8, 5
			,"Magical Attack increases the damage of all magical abilities and magical attacks. Abilities will always deal at least 1/3 damage.");
		this._setupLevelUpHelper("Magical Defense: ", "deallocateDefMagic", "allocateDefMagic", "ptsAllocatedDefMagic", "viewedDefMagic", 8, 6
			,"Magical Defense decreases the damage taken from enemy heroes' magical abilities and magical attacks. Enemy hero abilities, much like your own, will always deal at least 1/3 damage.");
		this._setupLevelUpHelper("Speed: ", "deallocateSpeed", "allocateSpeed", "ptsAllocatedSpeed", "viewedSpeed", 8, 7,
			"Speed increases how fast your character can take his turn. Enemy bars will continue progressing even when yours is filled if you haven't selected an action.");
		
		var ptsLeftText = new addText(levelUpContainer, "Points Left: ", false, null, false, 25);
		var ptsLeft = new addStatText(this, "allocationPoints", null, 25);
		var closeText = addText(levelUpContainer, "Finished", false, function()
		{
			if(!tutorialContainer.visible)
			{
				levelUpContainer.visible = false;
				progressHalted = false;
			}
		}, true, 25);
		
		setToSpacedRow(levelUpContainer, [[ptsLeftText[0], ptsLeft.graphic],[],[closeText[0]]], ["right","center","center"], null, 8,8);
		levelUpContainer.visible = true;
	}
	
	this._setupLevelUpHelper = function(text, subFunc, addFunc, stat, viewStat, numRows, placedRow, descript)
	{
		var magDefAttack = addText(levelUpContainer, text, false, null, false, 20);
		var magDefSub = addText(levelUpContainer, "- ", false, this[subFunc], true, 20, null, null, descript);
		var magDefAllocated = new addStatText(this, stat, null, 20);
		var magDefAdd = new addText(levelUpContainer, " +", false, this[addFunc], true, 20, null, null, descript);
		var magDefStat = new addStatText(this, viewStat, null, 20);
		setToSpacedRow(levelUpContainer, [[magDefAttack[0]],[magDefSub[0],magDefAllocated.graphic,magDefAdd[0]],[magDefStat.graphic]], 
			["right","center","center"], descript, numRows, placedRow);
	}
    
      this.takeTurn = function()
    {
        if(me.move != undefined && !progressHalted)
        {
			progressHalted = true;
            var zapped = false;
            for(var i = 0; i < me.statuses.length; i++) {
                console.log(me.statuses[i].name + " " + me.statuses[i].duration);
                me.statuses[i].updateStatus();
                if(me.statuses[i].name == "Zap" && me.statuses[i].duration > 0) {
                    me.move = null;
                    me.param1 = null;
                    me.param2 = null;
                    return true;
                }
            }
			new lerp(new vec2(me.graphic.x+100, me.graphic.y), me.graphic, .04, .02, me.move);
            me.move = null;
            me.param1 = null;
            me.param2 = null;
            
            
			return true;
        }
		return false;
    }
    
    this.levelUp = function() {
        this.level++;
		this.hpMax += Math.ceil(250 * (1/3));
		this.mpMax += Math.ceil(125 * (1/3));
        this.allocationPoints += 3;
        this.attackPhys += 3;
        this.attackMagic += 3;
        this.defensePhys += 3;
        this.defenseMagic += 3;
		this.viewedAtkPhys = Math.ceil(this.attackPhys);
		this.viewedAtkMagic = Math.ceil(this.attackMagic);
		this.viewedDefPhys = Math.ceil(this.defensePhys);
		this.viewedDefMagic = Math.ceil(this.defenseMagic);
        this.speed += 1.5 * (1/10);
		this.expRequired = 50*Math.pow(this.level, 1.3);
		this.viewedSpeed = Math.ceil(this.speed*15);
		this.progressBar.setSpeed(this.speed*15);
		progressHalted = true;
		levelUpContainer.visible = true;
		selector.descript.hide();
    }
    
    this.allocateAtkPhys = function() {
        if(me.allocationPoints > 0) {
            me.allocationPoints--;
            me.attackPhys += 5 * Math.pow(.95, me.ptsAllocatedAtkPhys);
			me.viewedAtkPhys = Math.ceil(me.attackPhys);
            me.ptsAllocatedAtkPhys++;
		}
    }
    
    this.allocateAtkMagic = function() {
        if(me.allocationPoints > 0) {
            me.allocationPoints--;
            me.attackMagic += 5 * Math.pow(.95, me.ptsAllocatedAtkMagic);
			me.viewedAtkMagic = Math.ceil(me.attackMagic);
            me.ptsAllocatedAtkMagic++;
		}
    }
    
    this.allocateDefPhys = function() {
        if(me.allocationPoints > 0) {
            me.allocationPoints--;
            me.defensePhys += 5 * Math.pow(.95, me.ptsAllocatedDefPhys);
			me.viewedDefPhys = Math.ceil(me.defensePhys);
            me.ptsAllocatedDefPhys++;
		}   
    }
    
    this.allocateDefMagic = function() {
	
        if(me.allocationPoints > 0) {
            me.allocationPoints--;
            me.defenseMagic += 5 * Math.pow(.95, me.ptsAllocatedDefMagic);
			me.viewedDefMagic = Math.ceil(me.defenseMagic);
			me.ptsAllocatedDefMagic++;
		}   
    }
	
	this.allocateSpeed = function() {
        if(me.allocationPoints > 0) {
            me.allocationPoints--;
            me.speed += (Math.pow(2, -(me.ptsAllocatedSpeed/2))/2);
			me.viewedSpeed = Math.ceil(me.speed*15);
            me.ptsAllocatedSpeed++;
			me.progressBar.setSpeed(me.speed*15);
		}   
    }
	
	this.deallocateSpeed = function() {
        if(me.ptsAllocatedSpeed > 0) {
            me.allocationPoints++;
            me.ptsAllocatedSpeed--;
            me.speed -= (Math.pow(2, -(me.ptsAllocatedSpeed/2))/2);
			//me.viewedSpeed = (me.speed - Math.floor(me.speed)<.00001)?Math.floor(me.speed):Math.ceil(me.speed);
			me.viewedSpeed = Math.ceil(15*me.speed);
			me.progressBar.setSpeed(me.speed*15);
		}   
    }
	
	this.deallocateAtkPhys = function()
	{
		me._deallocateHelper("ptsAllocatedAtkPhys", "attackPhys", "viewedAtkPhys");
	}
	
	this.deallocateAtkMagic = function()
	{
		me._deallocateHelper("ptsAllocatedAtkMagic", "attackMagic", "viewedAtkMagic");
	}
	
	this.deallocateDefPhys = function()
	{
		me._deallocateHelper("ptsAllocatedDefPhys", "defensePhys", "viewedDefPhys");
	}
	
	this.deallocateDefMagic = function()
	{
		me._deallocateHelper("ptsAllocatedDefMagic", "defenseMagic", "viewedDefMagic");
	}
	
	this._deallocateHelper = function(pts, stat, viewedStat)
	{
		if(me[pts] > 0)
		{
			me.allocationPoints++;
			me[pts]--;
			me[stat] -= 5*Math.pow(.95, me[pts]);
			me[viewedStat] = (me[stat] - Math.floor(me[stat])<.00001)?Math.floor(me[stat]):Math.ceil(me[stat]);
		}
	}
	
	 this.cast = function(targets, ability) {
        var damage = (ability.damageType == "Physical") ? this.attackPhys : this.attackMagic;
        damage += ability.baseDamage;
        var minDamage = damage/3; //min 33% dmg
        minDamage = Math.ceil(minDamage);
		var created = false;
        for(i = 0; i < 1; i++) {
            if(ability.spellType == abilitiesENUM.HEAL) {
                heal(targets[i], damage);
            }
			else if(ability.spellType == abilitiesENUM.BUFF)
			{
				progressHalted = true;
				var num = i;
				ability.particleEffect.initialize(new vec2(targets[num].graphic.x, targets[num].graphic.y), new vec2(targets[num].graphic.x, targets[num].graphic.y-150));
				me.mpCurr -= ability.cost;
				ability.particleEffect.onComplete = function()
				{
					var func = function() 
					{
						progressHalted = false;
						for(s=0;s<ability.statuses.length;s++)
						{
							targets[num].addStatus(ability.statuses[s]);
						}
					}
					new lerp(me.pos, me.graphic, .04, .02, func);
				}
			}
			else if(ability.spellType == abilitiesENUM.DEATH)
			{
				ability.particleEffect.initialize(vec2(targets[0].graphic.x, targets[0].graphic.y), new vec2(targets[0].graphic.x, targets[0].graphic.y-150));
				me.mpCurr -= ability.cost;
				ability.particleEffect.onComplete = function()
				{
					var func = function(){
					for(s=0;s<targets.length;s++)
					{
						death(targets[s]);
					}
					}
					new lerp(me.pos, me.graphic, .04, .02, func);
				}
			}
            else {
                var defense = (ability.damageType == "Physical") ? targets[i].defensePhys : targets[i].defenseMagic;
                
                var finalDamage = damage - defense;
				finalDamage = Math.ceil(finalDamage);
                if(finalDamage < minDamage) {
                    finalDamage = minDamage;
                }
                
                if(ability.status !== null) {
                    targets[i].addStatus(ability.status);
                }
				progressHalted = true;
				if(!created)
				{
					ability.particleEffect.initialize(new vec2(me.graphic.x,me.graphic.y),new vec2(targets[i].graphic.x, targets[i].graphic.y));
					this.mpCurr -= ability.cost;
				}
				new addMovingText(gameContainer, "-"+ability.cost,new vec2(175, 430), 2, 25, "#0FF"); 
				var num = i;
				ability.particleEffect.onComplete = function()
				{
					var func = function(){
					progressHalted = false;
						for(j=0;j<targets.length;j++)
						{
						receiveDamage(targets[j], finalDamage);
						}
					}
					new lerp(me.pos, me.graphic, .04, .02, func);
				}
            }
        }
    }
    
     this.addAbility = function(ability) {
		if($.inArray(ability, this.abilities) == -1)
		{
			this.abilities.push(ability);
			var abilityName = addText(abilityListContainer, ability.name, false, ability.chooseTarget, true, 20);
			var abilityDamage = addText(abilityListContainer, ability.baseDamage+"", false, ability.chooseTarget, true, 20);
			var abilityCost = addText(abilityListContainer, ability.cost+"", false, ability.chooseTarget, true, 20);
			var description = new Description();
			description.initialize(gameContainer, ability.descript);
			setToSingleLine([abilityName[0], abilityDamage[0], abilityCost[0]], abilityListContainer, description, false, ability.chooseTarget);
			setToSpacedRow(abilityListContainer, [[abilityName[0]],[abilityDamage[0]],[abilityCost[0]]], ["center","center","center"], ability.descript, null, null, ability.chooseTarget);

		}	
    }
    
     this.addStatus = function(status) {
        //var index = $.inArray(tempStatus, this.statuses);
        console.log(status);
        console.log(me.statuses.length);
        var tempStatus = new createStatus();
        tempStatus.initialize(status, me);
        
        var found = false;
        var index = 0;
        
        while(!found) {
            if(index >= me.statuses.length) {
                found = true;
                index = -1;
            }
            else if(me.statuses[index].name == status) {
                found = true;
            }
            else {
                index++;
            }
        }
        
        if(index == -1) {
            me.statuses.push(tempStatus);
        } else {
            me.statuses[index].applyStatus(); //refresh duration
        }
    }
    
      this.addItem = function(item) {
        var theItem = new createItem();
        theItem.initialize(item, me);
        
        
        var found = false;
        var index = 0;
        
        while(!found) {
            if(index >= me.items.length) {
                found = true;
                index = -1;
            }
            else if(me.items[index].item == item) {
                found = true;
            }
            else {
                index++;
            }
        }
                
        if(index == -1) {
            this.items.push(theItem);
            theItem.stack = -1;
            theItem.increaseStack();
        } else {
            me.items[index].increaseStack();
        }
        
    }
    
    this.useItem = function(item) {
        var found = false;
        var index = 0;
        
        console.log(item);
        
        while(!found) {
            if(index >= me.items.length) {
                found = true;
                console.log("Not found");
            }
            else if(me.items[index].item == item) {
                found = true;
                me.items[index].useItem();
            }
            else {
                index++;
            }
        }
    }
	
	this.setup = function()
	{
		this.hpCurr = this.hpMax;
		this.mpCurr = this.mpMax;
	}
	
	this.deathAnimation = function(dt)
	{
		this.graphic.alpha -= .5*dt;
		if(this.graphic.alpha <= 0)
		{
			gameContainer.visible = false;
			defeatContainer.visible = true;
		}
	}
    
    this.logStats = function() {
        console.log("");
        console.log("Level " + this.level + " " + this.name);
        console.log("Alive: " + this.alive);
        console.log("Status: " + this.statuses.toString());
        console.log("HP: " + this.hpCurr + "/" + this.hpMax);
        console.log("MP: " + this.mpCurr + "/" + this.mpMax);
        console.log("Attack Physical: " + this.attackPhys);
	}
}

