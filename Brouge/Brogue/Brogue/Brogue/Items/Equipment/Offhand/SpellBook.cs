﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Brogue.Enums;
using Brogue.Engine;
namespace Brogue.Items.Equipment.Offhand
{
    [Serializable] public class SpellBook : Offhand
    {
        public static DynamicTexture Texture { get; set; }

        public override DynamicTexture GetTexture()
        {
            return Texture;
        }

        public SpellBook(int dLevel, int cLevel)
        {
            LevelReq = 0;
            UsedBy = new List<Classes> { Classes.Mage, Classes.Sorcerer, Classes.SpellWeaver };
            Element = new List<ElementAttributes> { findElement() };
            Name = findName("Spellbook", LevelReq);
        }
    }
}
