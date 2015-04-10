var itemsENUM = {
    STEROIDS:"Steroids",
    HEALTHPOTSMALL:"Small HP Potion",
    HEALTHPOTMED:"Medium HP Potion",
    HEALTHPOTLARGE:"Large HP Potion",
    MANAPOTSMALL:"Small MP Potion",
    MANAPOTMED:"Medium MP Potion",
    MANAPOTLARGE:"Large MP Potion",
	HOLYHANDGRENADE:"Holy Hand Grenade",
}

function createItem() {
    this.item;
    this.particleEffect;
    this.description;
    this.owner;
    this.stack;
    this.shopCost;
    
    var me = this;    
        
    this.initialize = function(item, owner) {
        this.owner = owner;
        this.item = item;
        this.stack = 1;
        //this.increaseStack();
        switch(item) { 
            case itemsENUM.STEROIDS:
                this.particleEffect = null //change this;
                this.description = "Increases all stats.";
				this.shopCost = 100;
                break;
            case itemsENUM.HEALTHPOTSMALL:
                this.particleEffect = null //change this;
                this.description = "Heals 10% of your maximum HP";
				this.shopCost = 50;
                break;
            case itemsENUM.HEALTHPOTMED:
                this.particleEffect = null //change this;
                this.description = "Heals 25% of your maximum HP";
				this.shopCost = 100;
                break;
            case itemsENUM.HEALTHPOTLARGE:
                this.particleEffect = null //change this;
                this.description = "Heals 40% of your maximum HP";
				this.shopCost = 200;
                break;
            case itemsENUM.MANAPOTSMALL:
                this.particleEffect = null //change this;
                this.description = "Recover 10% of your maximum MP";
				this.shopCost = 50;
                break;
            case itemsENUM.MANAPOTMED:
                this.particleEffect = null //change this;
                this.description = "Recover 25% of your maximum MP";
				this.shopCost = 75;
                break;
            case itemsENUM.MANAPOTLARGE:
                this.particleEffect = null //change this;
                this.description = "Recover 40% of your maximum MP";
				this.shopCost = 150;
                break;
			case itemsENUM.HOLYHANDGRENADE:
				this.particleEffect = new addConeEffect(gameContainer, 1, 360, new vec2(650, 300), new vec2(150, 0), 2, "fireball", 1/60);
				this.description = "Destroys all of the enemies on a given level. One use, one buy maximum.";
				this.shopCost = 1253;
            default:
                //Default stuff here. Probably unnecessary.
                break;
        }
    }
    
    this.useItem = function() {
        var itemName = 0;
        var found = false;
        var index = 0;
        
        while(!found && me.item !== undefined) {
            if(index > me.owner.items.length) {
                found = true;
                index = -1;
            }
            else if(me.owner.items[index].item == me.item) {
                if(me.stack > 0 ) {
					createjs.Sound.play(soundDrinkPotion.src);
                    itemName = me.item;
                    me.stack--;
                }
                //me.owner.items.splice(index, 1);
                found = true;
            }
            else {
                index++;
            }
        }
        
        console.log(itemName + " used");
        
        switch(itemName) { 
            case itemsENUM.STEROIDS:
                me.owner.addStatus(statusENUM.PHYSATKBOOST);
                me.owner.addStatus(statusENUM.PHYSDEFBOOST);
                me.owner.addStatus(statusENUM.MAGICATKBOOST);
                me.owner.addStatus(statusENUM.MAGICDEFBOOST);
                break;
            case itemsENUM.HEALTHPOTSMALL:
                var healAmount = 0;
                this.particleEffect = null //change this;
                this.description = "Heals 10% HP";
                if(Math.ceil(me.owner.hpCurr + (me.owner.hpMax * .1)) > me.owner.hpMax)
                    healAmount = me.owner.hpMax - me.owner.hpCurr;
                else
                    healAmount = Math.ceil(me.owner.hpMax * .1);

                me.owner.hpCurr += healAmount;
                new addMovingText(gameContainer, "+" + healAmount, new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 25, "#5F5");
                break;
            case itemsENUM.HEALTHPOTMED:
                var healAmount = 0;
                this.particleEffect = null //change this;
                this.description = "Heals 25% HP";
                if(Math.ceil(me.owner.hpCurr + (me.owner.hpMax * .25)) > me.owner.hpMax)
                    healAmount = me.owner.hpMax - me.owner.hpCurr;
                else
                    healAmount = Math.ceil(me.owner.hpMax * .25);

                me.owner.hpCurr += healAmount;
                new addMovingText(gameContainer, "+" + healAmount, new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 25, "#5F5");
                break;
            case itemsENUM.HEALTHPOTLARGE:
                var healAmount = 0;
                this.particleEffect = null //change this;
                this.description = "Heals 40% HP";
                if(Math.ceil(me.owner.hpCurr + (me.owner.hpMax * .4)) > me.owner.hpMax)
                    healAmount = me.owner.hpMax - me.owner.hpCurr;
                else
                    healAmount = Math.ceil(me.owner.hpMax * .4);

                me.owner.hpCurr += healAmount;
                new addMovingText(gameContainer, "+" + healAmount, new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 25, "#5F5");
                break;
            case itemsENUM.MANAPOTSMALL:
                var recoverAmount = 0;
                this.particleEffect = null //change this;
                this.description = "Recovers 10% MP";
               if(Math.ceil(me.owner.mpCurr + (me.owner.mpMax * .1)) > me.owner.mpMax)
                    recoverAmount = me.owner.mpMax - me.owner.mpCurr;
                else
                    recoverAmount = Math.ceil(me.owner.mpMax * .1);

                me.owner.mpCurr += recoverAmount;
                new addMovingText(gameContainer, "+" + recoverAmount, new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 25, "#55F");
                break;
            case itemsENUM.MANAPOTMED:
                var recoverAmount = 0;
                this.particleEffect = null //change this;
                this.description = "Recovers 25% MP";
               if(Math.ceil(me.owner.mpCurr + (me.owner.mpMax * .25)) > me.owner.mpMax)
                    recoverAmount = me.owner.mpMax - me.owner.mpCurr;
                else
                    recoverAmount = Math.ceil(me.owner.mpMax * .25);

                me.owner.mpCurr += recoverAmount;
                new addMovingText(gameContainer, "+" + recoverAmount, new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 25, "#55F");
                break;
            case itemsENUM.MANAPOTLARGE:
                var recoverAmount = 0;
                this.particleEffect = null //change this;
                this.description = "Recovers 40% MP";
               if(Math.ceil(me.owner.mpCurr + (me.owner.mpMax * .4)) > me.owner.mpMax)
                    recoverAmount = me.owner.mpMax - me.owner.mpCurr;
                else
                    recoverAmount = Math.ceil(me.owner.mpMax * .4);

                me.owner.mpCurr += recoverAmount;
                new addMovingText(gameContainer, "+" + recoverAmount, new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 25, "#55F");
                break;
			case itemsENUM.HOLYHANDGRENADE:
				me.particleEffect.initialize();
				progressHalted = true;
				me.particleEffect.onComplete = function()
				{
					nextLevel();
				}
            default:
                console.log("No item");
                break;
        }
            
        
        
        if(me.owner == boss && me.stack == 0) {
            removeObjectsInLine(itemListContainer, me.item);
        }
    }
                                
    this.increaseStack = function() {
        if(me.stack == 0 && me.owner == boss) {
            var spacing = "";
            for(var i = 0; i < (me.item.length) ; i++)
                spacing += " ";
            
            var removeKey = addText(itemListContainer, me.item, false, null, false, 20);
            var stackStat = new addStatText(me, "stack", null, 20);
			setToSpacedRow(itemListContainer, [[removeKey[0]],[stackStat.graphic]],["left","right"], me.description, null, null, function() {
				boss.move = function()
				{
					me.useItem(me.item);
					new lerp(boss.pos, boss.graphic, .04, .01, function(){progressHalted = false;});
				}
				viewItemList();}
				);
            
        }
        
        me.stack++;
    }
}