var heroClassEnum = {
    ADVENTURER:0, //Default
    WARRIOR:1, //More dmg + HP + def, low mp
    ROUGE:2, //More dmg, avg mp, less hp
    MAGE:3, //low HP, low def, high mp, low dmg, high mDmg
    RANGER:4, //Avg dmg, avg hp, avg mp, low def
}

function createHero() {
    this.heroClass;
    this.alive;
    this.name;
    this.level;
    this.hpMax;
    this.mpMax;
    this.hpCurr;
    this.mpCurr;
    this.attackPhys;
    this.attackMagic;
    this.defensePhys;
    this.defenseMagic;
    this.abilities;
    this.items;
    this.statuses;
    this.graphic;
	this.move;
	this.param1;
	this.param2;
	this.pos;
	this.gold;
	this.exp;
	this.castChance;
	var me = this;
    
    this.initialize = function(heroClass, level, slot) {
        this.heroClass = heroClass;
        this.alive = true;
        this.name = "";
        this.level = level;
		this.param1 = this;
		this.param2 = boss;
		this.move = attack;
    	if(level > 1) {
    		this.hpMax = 300 * (1 + this.level/6);
    		this.mpMax = 300 * (1 + this.level/8);
    		this.speed = 1 * (1 + this.level/15);
    	}
    	else {
    		this.hpMax = 300;
    		this.mpMax = 300;
    		this.speed = 1;
    	}
        this.attackPhys = 20 + (4.0 * level);
        this.attackMagic = 17 + (3.5 * level);
        this.defensePhys = 15 + (4.5 * level);
        this.defenseMagic = 14 + (3.5 * level);
        this.abilities = [];
        this.items = [];
        this.statuses = [];
        this.castChance = 0;
	    var heroColor;
	       
        switch(heroClass) {
            case heroClassEnum.ADVENTURER:
                this.heroClass = "Adventurer";
				heroColor = "#FD0"
                break;
            case heroClassEnum.WARRIOR:
                this.heroClass = "Warrior";
                this.hpMax = this.hpMax * 1.5;
                this.mpMax = this.mpMax * 0.9;
                this.attackPhys = this.attackPhys * 1.5;
                this.attackMagic = this.attackMagic * 0.8;
                this.defensePhys = this.defensePhys * 1.1;
                this.defenseMagic = this.defenseMagic * 1.0;
                this.speed = this.speed * 0.9;
				this.exp = 100*(this.level);
				this.gold = 25*Math.pow(this.level , 1.2);
				this.abilities = [getAbility("Enrage")]
                this.items = [];
                this.statuses = [];
				this.graphic = new createjs.Bitmap(queue.getResult("warrior"));
				this.graphic.regX = this.graphic.image.width/2;
				this.graphic.regY = this.graphic.image.height/2;
				heroColor = "#960000"
                break;
            case heroClassEnum.MAGE:
                this.heroClass = "Mage";
                this.hpMax = this.hpMax * 0.8;
                this.mpMax = this.mpMax * 2.0;
                this.attackPhys = this.attackPhys * 0.6;
                this.attackMagic = this.attackMagic * 2.0;
                this.defensePhys = this.defensePhys * 0.6;
                this.defenseMagic = this.defenseMagic * 1.2;
                this.speed = this.speed * 0.9;
				this.exp = 90*this.level;
				this.gold = 21*Math.pow(this.level, 1.3);
                this.items = [];
                this.statuses = [];
				this.abilities = [getAbility("Fireball"),getAbility("Lightning Bolt")];
				this.graphic = new createjs.Sprite(mageSheet);
				this.graphic.gotoAndPlay("idle");
				this.graphic.on("animationend", function(evt)
				{
					if(evt.name == "attack")
					{
						me.graphic.gotoAndPlay("idle");
					}
				});
				this.graphic.regY = -60;
				this.graphic.regX = 50;
				heroColor = "#B0C7E7";
                break;
            case heroClassEnum.ROGUE:
                this.heroClass = "Rogue";
                this.hpMax = this.hpMax * 0.9;
                this.mpMax = this.mpMax * 1.0;
                this.attackPhys = this.attackPhys * 1.0;
                this.attackMagic = this.attackMagic * 0.9;
                this.defensePhys = this.defensePhys * 0.8;
                this.defenseMagic = this.defenseMagic * 0.8;
                this.speed = this.speed * 1.7;
				this.exp = 75*this.level;
				this.gold = 22*Math.pow(this.level, 1.25);
                this.items = [];
                this.statuses = [];
				heroColor = "#00964B";
                break;
            case heroClassEnum.RANGER:
                this.heroClass = "Ranger";
                this.hpMax = this.hpMax * 1.0;
                this.mpMax = this.mpMax * 1.0;
                this.attackPhys = this.attackPhys * 1.1;
                this.attackMagic = this.attackMagic * 1.0;
                this.defensePhys = this.defensePhys * 0.9;
                this.defenseMagic = this.defenseMagic * 0.9;
                this.speed = this.speed * 1.2;
				this.exp = 75*this.level;
				this.gold = 23*Math.pow(this.level, 1.2);
                this.abilities = [getAbility("Fireball")];
                this.items = [];
                this.statuses = [];
				this.graphic = new createjs.Bitmap(queue.getResult("archer"));
				this.graphic.regX = this.graphic.image.width/2;
				this.graphic.regY = this.graphic.image.height/2;
				heroColor = "#29610F"
                break;
			default:
                this.heroClass = "Adventurer";
				break;
        }
        this.name = "Level " + this.level + " " + this.heroClass;
		this.hpMax = Math.ceil(this.hpMax);
		this.mpMax = Math.ceil(this.mpMax);
        this.hpCurr = this.hpMax;
        this.mpCurr = this.mpMax;
		this.gold = Math.floor(this.gold);
		this.graphic.x = 600+35*(slot);
		this.graphic.y = 225+60*(slot);
		this.pos = new vec2(this.graphic.x, this.graphic.y);
		this.graphic.on("mouseover", function(evt)
		{
			if(!levelUpContainer.visible && !itemShopContainer.visible)
			{
				selector.pointTo(slot);
			}
		});
		this.graphic.on("click", function(evt)
		{
		    if(selector.graphic.visible)
		    {
				if(currentAbility == undefined)
				{
					boss.move = function()
					{
						attack(boss, party[slot]);
					}
				}
				else if(currentAbility != undefined)
				{
					var spellToUse = currentAbility;
					boss.move = function()
					{
						boss.cast([party[slot]], spellToUse);
					}
					currentAbility = undefined;
				}
				selector.graphic.visible = false;
				selector.descript.hide();
		    }
		});
		party[slot] = this;
		partyContainer.addChild(this.graphic);
    }
	
	this.takeTurn = function()
	{
	    var actionTaken = !me.alive;
		if(me.alive)
		{
		progressHalted = true;
			for(i=0; i<me.statuses.length;i++)
			{
				me.statuses[i].updateStatus();
			}
			if(/*me.mpCurr >= me.minMP &&*/ me.abilities.length > 0) { //Have enough MP to cast a spell and spells to cast
				var spellChance = me.castChance * 0.15; //15% cast chance on 1st turn, 30% on 2nd, etc
				if(me.heroClass == "Mage") { spellChance *= 2; } //double chance of spellcast if mage
				me.castChance++;
			
				if(Math.random() < spellChance) { //use RNG to see if cast
					//--------------------------------------HEAL CASE----------------------------------------//
					if($.inArray(abilitiesENUM.HEAL, me.abilities) != -1) {
						var weakest = party[0];
						for(i = 1; i < party.length; i++) { //find hero with the lowest health
							
							if(party[i].hpCurr <= weakest.hpCurr) {
								weakest = party[i];
							}
						}
					
						var healthPercent = weakest.hpCurr/weakest.hpMax;
						if(healthPercent < 0.7) {
							var healChance = Math.pow(healthPercent - 1, 2) + 0.2; // y = (x-1)^2 + 0.2
							
							if(Math.random() < healChance) {
								me.move = function(){cast([weakest], abilityENUM.HEAL);};
								actionTaken = true;
							}
						}
					}
					//---------------------------------ATTACK SPELL CASE-------------------------------------//
				
					//VERY IMPORTANT TO MAKE SURE A SPELLCASTER DOESN'T HAVE JUST HEAL OR ELSE INFINITE LOOP
					
					var spellIndex;
					while(!actionTaken) {
						spellIndex = Math.floor((Math.random() * me.abilities.length)); //pick random index of spell
						spellIndex -= (spellIndex == me.abilities.length)?1:0;
						if(me.abilities[spellIndex].spellType == abilitiesENUM.BUFF)
						{
							me.move = function(){me.cast([party[0],party[1],party[2]], me.abilities[spellIndex]);}
							new lerp(new vec2(400, boss.graphic.y+25), me.graphic, .05, .02, me.move);
							actionTaken = true;
						}
						else if(me.abilities[spellIndex] != abilitiesENUM.HEAL) {
							if(me.abilities[spellIndex].cost <= me.mpCurr) {
								if(me.heroClass == "Mage")
								{
									me.graphic.gotoAndPlay("attack");
								}
								me.move = function(){me.cast([boss], me.abilities[spellIndex]);}
								new lerp(new vec2(400, boss.graphic.y+25), me.graphic, .05, .02, me.move);
								actionTaken = true;
							}
						}
					}
					me.castChance = 1;
				}
			}
    
        //------------------------------ITEM USE CASE---------------------------//
			if(me.items.length !== 0 && !actionTaken) {
				
				//-------------IF LOW ON HP, USE HP POT-----------------//
				if( (me.hpCurr/me.hpMax) < 0.4) {
					var index = $.inArray(itemsENUM.hpPot, me.items);
					if(index != -1) {
						me.useItem(me.items[index]);
					}
				}
				//-------------IF LOW ON MP, USE MP POT------------------//
				if(me.mpCurr < me.minMP || (me.mpCurr/me.mpMax) < 0.3) {
					var index = $.inArray(itemsENUM.mpPot, me.items);
					if(index != -1) {
						me.useItem(me.items[index]);
					}
				}
			}
        //-------------------LAST RESORT CASE (DIRECT ATTACK)-------------------//
			if(!actionTaken) {
			if(me.heroClass == "Mage")
								{
									me.graphic.gotoAndPlay("attack");
								}
				me.move = function(){attack(me, boss);};
				new lerp(new vec2(400, boss.graphic.y+25), me.graphic, .05, .02, me.move);
				//new lerp(me.pos,me.graphic,.05,.02); 
				actionTaken = true;
			}
		}
		else if(!me.alive)
		{
			actionTaken = false;
		}
		return actionTaken;
	}
	
	this.useItem = function(item) {
        var itemName = 0;
        if(item !== undefined && $.inArray(item, this.items) !== -1) {
            itemName = item.item;
            this.items.splice($.inArray(item, this.items), 1);     
        }
        
        switch(itemName) {
            case itemsENUM.STEROIDS:
                console.log("Steriods used");
                //Steroids effects
                break;
            default:
                console.log("Item does not exist");
                break;
        }
    }
    
	
	//targets is an array of targets
    this.cast = function(targets, ability) {
        var damage = (ability.damageType == "Physical") ? this.attackPhys : this.attackMagic;
        damage += ability.baseDamage;
        var minDamage = damage/3; //min 33% dmg
        minDamage = Math.ceil(minDamage);
		var made = false;
        for(i = 0; i < targets.length && !made; i++) {
            if(ability.spellType == abilitiesENUM.HEAL) {
                heal(targets[i], damage);
            }
			else if(ability.spellType == abilitiesENUM.BUFF)
			{
				progressHalted = true;
				var num = i;
				if(!made)
				{
					ability.particleEffect.initialize(new vec2(targets[num].graphic.x, targets[num].graphic.y), new vec2(targets[num].graphic.x, targets[num].graphic.y-150));
					made = true;
				}
				me.mpCurr -= ability.cost;
				ability.particleEffect.onComplete = function()
				{
					for(j=0;j<targets.length;j++)
					{
						for(s=0;s<ability.statuses.length;s++)
						{
							targets[j].addStatus(ability.statuses[s]);
						}
					}
					new lerp(me.pos, me.graphic, .05, .02, function()
					{
						progressHalted=(itemShopContainer.visible);
					});
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
				if(!made)
				{
					ability.particleEffect.initialize(new vec2(me.graphic.x, me.graphic.y),new vec2(targets[i].graphic.x, targets[i].graphic.y));
					made = true;
				}
                this.mpCurr -= ability.cost;
				var num = i;
                ability.particleEffect.onComplete = function()
				{
					receiveDamage(targets[num], finalDamage);
					new lerp(me.pos, me.graphic, .05, .02, function(){progressHalted=(itemShopContainer.visible);});
				}
            }
        }
    }
	
    this.addAbility = function(ability) {
		if($.inArray(ability, this.abilities) == -1)
			this.abilities.push(ability);
			
			if(abilities.cost < this.minMP) {
                this.minMP = ability.cost;
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
            var temp = new menuItem();
            this.items.push(theItem);
        } else {
            me.items[index].stack += 1;
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
    
    this.logStats = function() {
        console.log(this.name);
        console.log("Alive: " + this.alive);
        console.log("Status: " + this.statuses.toString());
        console.log("HP: " + this.hpCurr + "/" + this.hpMax);
        console.log("MP: " + this.mpCurr + "/" + this.mpMax);
        console.log("Attack Physical: " + this.attackPhys);
        console.log("Attack Magical: " + this.attackMagic);
        console.log("Defense Physical: " + this.defensePhys);
        console.log("Defense Magical: " + this.defenseMagic);
        console.log("Speed: " + this.speed);
        console.log("Abilities: " + this.abilities.toString());
        console.log("Items: ");
        for(var i = 0; i < this.items.length; i++) {
                console.log("   " + this.items[i].item);
        }
    }
}