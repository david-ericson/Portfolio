﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Brogue.Enums;

namespace Brogue.Items.Equipment.Accessory
{

    [Serializable] public abstract class Accessory : Gear
    {
        public int BaseIncrease { get; protected set; }
        public int StatIncrease { get; protected set; }
        public List<Modifiers> StatIncreased { get; protected set; }

        private static Random rand = new Random();

        public Accessory()
        {
            BaseIncrease = rand.Next(1, 6);
            ItemType = ITypes.Accessory;
        }

        public int findStatIncrease(int bSI, int dLevel, int lReq)
        {
            return (bSI * dLevel) + lReq;
        }

        public Modifiers findStatIncreased()
        {
            Random rand = new Random();
            int size = Enum.GetNames(typeof(Modifiers)).Length;

            return (Modifiers)rand.Next(size);
        }
    }
}
