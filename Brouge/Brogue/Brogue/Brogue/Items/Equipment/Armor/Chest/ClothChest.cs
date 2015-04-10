﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Brogue.Engine;
using Brogue.Enums;

namespace Brogue.Items.Equipment.Armor.Chest
{
    [Serializable] public class ClothChest : Chest
    {
        public static DynamicTexture Texture { get; set; }

        public override DynamicTexture GetTexture()
        {
            return Texture;
        }

        public ClothChest(int dLevel, int cLevel)
        {
            LevelReq = findLevelReq(dLevel, cLevel);
            UsedBy = new List<Classes> { Classes.Mage, Classes.Sorcerer, Classes.SpellWeaver, Classes.Magus, Classes.SpellBlade };
            TypeBonus = 1;
            ArmorValue = findArmorValue(BaseArmor, dLevel, TypeBonus);
            Name = findName("Cloth Chest", LevelReq);
        }
    }
}
