﻿using Brogue.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Brogue.Items.Equipment.Armor.Legendary.Chest
{
    [Serializable]
    public abstract class LegendaryChest : LegendaryArmor
    {
        private static Random rand = new Random();

        public LegendaryChest()
        {
            BaseArmor = rand.Next(20, 31);
            EquipableIn = new List<Slots> { Slots.Chest };
        }
    }
}
