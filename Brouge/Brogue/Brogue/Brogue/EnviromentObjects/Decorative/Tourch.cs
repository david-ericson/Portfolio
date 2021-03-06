﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Brogue;
using Brogue.Engine;
using Brogue.Mapping;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;


namespace Brogue.EnviromentObjects.Decorative
{
    [Serializable] class Tourch : IEnvironmentObject, IRenderable, ILightSource
    {

        static DynamicTexture texture = Engine.Engine.GetTexture("Enviroment/Tourch");

        Direction directionFacing { get; set; }

        Microsoft.Xna.Framework.Color color { get; set; }

        float currentFlicker { get; set; }

        public float intensity { get; set; }

        int flickerWait { get; set; }

        bool isSolid = false;

        public Tourch(Direction setDirection, Microsoft.Xna.Framework.Color setColor)
        {
            directionFacing = setDirection;
            flickerWait = 8;
            intensity = 1;
            color = setColor;
        }

        public Tourch(Direction setDirection, Microsoft.Xna.Framework.Color setColor, int filck, float strength)
        {
            directionFacing = setDirection;
            flickerWait = filck;
            intensity = strength;
            color = setColor;
        }

        public Sprite GetSprite()
        {
            //return new Sprite(texture);
            return new Sprite(texture, directionFacing);
        }

        public bool IsSolid()
        {
            return isSolid;
        }


        public float GetLightIntensity()
        {
            return intensity;
        }

        public Microsoft.Xna.Framework.Color GetLightColor()
        {
            return color;
        }

        public int GetLightFlickerWait()
        {
            return 8;
        }

        int flickerCountdown = 5;

        public float GetCurrentFlicker()
        {
            if (flickerCountdown == 0)
            {
                currentFlicker = (float)Engine.Engine.enginerand.NextDouble() / 6;
                flickerCountdown = Engine.Engine.enginerand.Next(8) + 3;
            }
            else
            {
                flickerCountdown--;
            }
            return currentFlicker;
        }
    }
}
