package com.neumont.dericson.chess;

/**
 * Created by dericson on 3/13/2015.
 */
public class Vector2 {
    public float x, y;

    public Vector2(float x, float y){
        this.x = x;
        this.y = y;
    }

    public Vector2 add(Vector2 other){
        return new Vector2(other.x + x, other.y + y);
    }

    public Vector2 subtract(Vector2 other){
        return new Vector2(x - other.x, y - other.y);
    }

    public Vector2 multiply(Vector2 other){
        return new Vector2(other.x*x, other.y *y);
    }

    public Vector2 multiply(float scalar){
        return new Vector2(x*scalar,y*scalar);
    }

    public static float lengthBetween(Vector2 start, Vector2 end){
        Vector2 vec = end.subtract(start);
        float length = (float)Math.sqrt(vec.x*vec.x+vec.y*vec.y);
        return length;
    }


}
