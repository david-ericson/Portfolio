var statusENUM = {
    BURN:"Burn",
    ZAP:"Zap",

    PHYSATKBOOST:"Physical Attack Boost",
    PHYSDEFBOOST:"Physical Defense Boost",
    MAGICATKBOOST:"Magic Attack Boost",
    MAGICDEFBOOST:"Magic Defense Boost",
};

function createStatus() {
    this.name;
    this.duration;
    this.maxDuration;
    this.owner;
    this.isApplied;
    this.chance;
    
    var me = this;
    
    this.initialize = function(statusEffect, owner) {
        me.name = statusEffect;
        me.owner = owner;
        me.applyStatus();
        
        me.maxDuration = me.duration;
        
//        var durationStatText = new addStatText(me, "duration", "maxDuration", 20);
//        var statusText = new addText(bossInfoContainer, me.name + " ", false, null, false, 20, durationStatText, 8);
    }
    
    this.applyStatus = function() {
        me.isApplied = false;
        switch(me.name) {
            case statusENUM.PHYSATKBOOST:
                me.duration = 5;
				if(!me.ownerHasBuff(me.name))
				{
					me.owner.attackPhys += 15;
					new addMovingText(gameContainer, "Phys. Atk +15", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 25, "#F90");
				}
				else
				{
					new addMovingText(gameContainer, "Phys. Atk ", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#F90");
					new addMovingText(gameContainer, "Buff Refresh", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+25), 2, 20, "#F90");
				}
                break;
            case statusENUM.PHYSDEFBOOST:
                me.duration = 5;
				if(!me.ownerHasBuff(me.name))
				{
					me.owner.defensePhys += 15;
					new addMovingText(gameContainer, "Phys. Def +15", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 25, "#6BFF9A");
				}
				else
				{
					new addMovingText(gameContainer, "Phys. Def ", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#6BFF9A");
					new addMovingText(gameContainer, "Buff Refresh", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+25), 2, 20, "#6BFF9A");
				}
                break;
            case statusENUM.MAGICATKBOOST:
                me.duration = 5;
				if(!me.ownerHasBuff(me.name))
				{
					me.owner.attackMagic += 15;
					new addMovingText(gameContainer, "Magic Atk +15", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 25, "#09F");
				}
				else
				{
					new addMovingText(gameContainer, "Magic Atk ", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#09F");
					new addMovingText(gameContainer, "Buff Refresh", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+25), 2, 20, "#09F");
				}
                break;
            case statusENUM.MAGICDEFBOOST:
                me.duration = 5;
				if(!me.ownerHasBuff(me.name))
				{
					me.owner.defenseMagic += 15;
					new addMovingText(gameContainer, "Magic Def +15", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+25), 2, 25, "#03F");
				}
				else
				{
					new addMovingText(gameContainer, "Magic Def ", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+50), 2, 20, "#03F");
					new addMovingText(gameContainer, "Buff Refresh", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+75), 2, 20, "#03F");
				}
                break;
                
                
            case statusENUM.BURN:
                me.chance = .4;
                me.attemptStatus();
                if(me.isApplied) {
                    me.duration = 5;
					new addMovingText(gameContainer, "BURNED!!!", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#F33");
                }
                break;
            case statusENUM.ZAP:
                me.chance = .25;
                me.attemptStatus();
                if(me.isApplied) {
                    me.duration = 3;
                }
                break;
        }
    }
	
	this.ownerHasBuff = function(buffToCheck)
	{
	var found = false;
		for(i=0; i<me.owner.statuses.length && !found; i++)
		{
			found = (me.owner.statuses[i].name == buffToCheck);
		}
		return found;
	}
    
    this.attemptStatus = function() {
        if(Math.random() <= me.chance)
            me.isApplied = true;
    }
    
    this.updateStatus = function() {
          switch(me.name) {
            
            case statusENUM.PHYSATKBOOST:
                if(me.duration == 0) {
                    me.owner.attackPhys -= 15;
					new addMovingText(gameContainer, "Phys. Atk Boost", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#F90");
					new addMovingText(gameContainer, "Has Ended", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+25), 2, 20, "#F90");
                }
                break;
            case statusENUM.PHYSDEFBOOST:
                if(me.duration == 0) {
                    me.owner.defensePhys -= 15;
					new addMovingText(gameContainer, "Phys. Def Boost", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#6BFF9A");
					new addMovingText(gameContainer, "Has Ended", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+25), 2, 20, "#6BFF9A");
                }
                break;
            case statusENUM.MAGICATKBOOST:
                if(me.duration == 0) {
                    me.owner.attackMagic -= 15;
					new addMovingText(gameContainer, "Magic Atk Boost", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#09F");
					new addMovingText(gameContainer, "Has Ended", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#09F");
                }
                break;
             case statusENUM.MAGICDEFBOOST:
                if(me.duration == 0) {
                    me.owner.defenseMagic -= 15;
					new addMovingText(gameContainer, "Magic Def Boost", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+50), 2, 20, "#03F");
					new addMovingText(gameContainer, "Has Ended", new vec2(me.owner.graphic.x-50, me.owner.graphic.y+75), 2, 20, "#03F");
                }
                break;    
                
            case statusENUM.BURN:
                if(me.duration > 0) {
                    me.owner.hpCurr += -Math.ceil(me.owner.hpMax * .02);
                    new addMovingText(gameContainer, "-" + Math.ceil(me.owner.hpMax * .02)+" BURN", new vec2(me.owner.graphic.x, me.owner.graphic.y), 2, 20, "#F33");
                }
				else
				{
					new addMovingText(gameContainer, "Burn over", new vec2(me.owner.graphic.x-50, me.owner.graphic.y), 2, 20, "#F33");
				}
                break;
            case statusENUM.ZAP:
                new addMovingText(gameContainer, "You're paralysed, turn skipped", new vec2(me.owner.graphic.x,me.owner.graphic.y), 2, 20, "#F33");
                break;
        }
        me.duration--;
    }
}