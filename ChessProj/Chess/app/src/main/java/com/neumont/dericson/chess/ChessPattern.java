package com.neumont.dericson.chess;

import java.util.ArrayList;
import java.util.List;

public class ChessPattern {
	
	public static class MoveTypeAmount
	{
		private Type t;
		private Hinderance hinderance;
		private int moveSize;
		
		public MoveTypeAmount(Type t, int size, Hinderance h){
			moveSize = size;
			this.t = t;
			hinderance = h;
		}
		
		public Type getT() {
			return t;
		}
		public int getMoveSize() {
			return moveSize;
		}
		public Hinderance getHinderance(){
			return hinderance;
		}
	}
	
	private List<MoveTypeAmount> movement;
	
	public enum Type{
		PLUS,
		CROSS,
		L
	};
	public enum Hinderance{
		ONLY_FORWARD,
		ONLY_BACKWARD,
		NONE,
	}
	
	public ChessPattern(){
		movement = new ArrayList<MoveTypeAmount>();
	}
	
	public ChessPattern add(Type patternType, int length){
		movement.add(new MoveTypeAmount(patternType, length, Hinderance.NONE));
		return this;
	}
	
	public ChessPattern add(Type patternType, int length, Hinderance h){
		movement.add(new MoveTypeAmount(patternType, length, h));
		return this;
	}
	
	public List<MoveTypeAmount> getMovement()
	{
		return movement;
	}
}
