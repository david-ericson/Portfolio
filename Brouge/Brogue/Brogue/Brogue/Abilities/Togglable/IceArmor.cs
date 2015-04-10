﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Brogue.Abilities.Togglable
{
    [Serializable] public class IceArmor : ToggleAbility
    {
        const int armorBoost = 10;

        public IceArmor()
        {
            name = "Ice Armor";
            description = "The mage summons armor to protect \nhimself during battle.";
            abilityIndex = 13;
        }

        public override void updateToggle(int heroLevel, HeroClasses.Hero hero) 
        {
            if (createdLevel < heroLevel && isActive)
            {
                hero.setArmorBoost(armorBoost + (int)(heroLevel * 2));
                hero.damageBoost += (int)(createdLevel * 1.5);
                hero.damageBoost -= (int)(heroLevel);
                createdLevel = heroLevel;
            }
        }



        public override void toggledAttackEffects(HeroClasses.Hero hero) { }

        public override void finishCastandDealDamage(int heroLevel, int heroDamage, Mapping.Level mapLevel, HeroClasses.Hero hero)
        {
            if (!isActive)
            {
                createdLevel = heroLevel;
                Engine.Engine.Log(hero.getArmorBoost().ToString());
                hero.ApplyArmorBoost(armorBoost + (int)(heroLevel * 2), int.MaxValue);
                hero.damageBoost -= (heroLevel);
                Engine.Engine.Log(hero.getArmorBoost().ToString());
                Engine.Engine.AddVisualAttack(hero, "Hero/IceAttack", .25f, 1.5f, .1f);
                isActive = true;
                wasJustCast = true;
            }
            else if (isActive)
            {
                hero.ApplyArmorBoost(0, 0);
                hero.damageBoost += (heroLevel);
                isActive = false;
                wasJustCast = true;
            }
            cooldown = 0;
        }
    }
}
