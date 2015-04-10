package com.neumont.dericson.piece.types;


import com.neumont.dericson.chess.ChessPattern;
import com.neumont.dericson.chess.Piece;
import com.neumont.dericson.chess.Square;

public class King extends Piece {
	
	public King(Square start, int team){
		create(start, team);
		movePattern.add(ChessPattern.Type.CROSS, 1).add(ChessPattern.Type.PLUS, 1);
		attackPattern.add(ChessPattern.Type.CROSS, 1).add(ChessPattern.Type.PLUS, 1);
		boardId = 'k';
		name = "King";
	}

	@Override
	public boolean move(Square moveHere) {
		// TODO Auto-generated method stub
		return false;
	}

}
