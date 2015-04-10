var abilitiesENUM = {
    FIRE:"Fire", //chance of burn, high-ish damage
    THUNDER:"Thunder", //chance of paralysis
    HEAL:"Heal", //single heal. Maybe AoE heal later
    BUFF:"Buff",
    STEAL:"Steal",
	AOE:"AoE",
	DEATH:"Death",
}

function abilities(particleEffect, damage, statuses, damageType, cost, owner, type, name, descript, shopCost)
{
	this.particleEffect = particleEffect;
	this.baseDamage = damage;
	this.damageType = damageType;
	this.cost = cost;
	this.name = name;
	this.owner = owner;
	this.spellType = type;
	this.statuses = statuses;
	this.descript = descript;
	this.shopCost = shopCost;
	var ability = this;
	
	this.chooseTarget = function()
	{
		if(boss.mpCurr < ability.cost)
		{
			new addMovingText(gameContainer, "Not enough mp...", new vec2(300, 90), 1.5, 30, "#F00");
		}
		else
		{		
			if(ability.spellType == abilitiesENUM.BUFF)
			{
				viewAbilityList();
				boss.move = function(){boss.cast([boss], ability);}
			}
			else if(ability.spellType == abilitiesENUM.AOE || ability.spellType == abilitiesENUM.DEATH)
			{
				viewAbilityList();
				targets = [];
				for(i=0; i<party.length; i++)
				{
					if(party[i].alive)
					{
						targets.push(party[i]);
					}
				}
				boss.move = function(){boss.cast(targets, ability);}
			}
			else
			{
				viewAbilityList();
				currentAbility = ability;
				selector.graphic.visible = true;
			}
		}
	}
}