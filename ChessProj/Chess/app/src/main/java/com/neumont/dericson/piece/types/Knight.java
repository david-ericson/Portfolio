package com.neumont.dericson.piece.types;


import com.neumont.dericson.chess.ChessPattern;
import com.neumont.dericson.chess.Piece;
import com.neumont.dericson.chess.Square;

public class Knight extends Piece {
	
	public Knight(Square start, int team){
		create(start, team);
		movePattern.add(ChessPattern.Type.L, 1);
		attackPattern.add(ChessPattern.Type.L, 1);
		boardId = 'n';
		name = "Knight";
	}

	@Override
	public boolean move(Square moveHere) {
		// TODO Auto-generated method stub
		return false;
	}

}
