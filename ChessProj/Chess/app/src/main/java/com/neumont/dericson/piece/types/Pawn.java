package com.neumont.dericson.piece.types;


import com.neumont.dericson.chess.ChessPattern;
import com.neumont.dericson.chess.Piece;
import com.neumont.dericson.chess.Square;

public class Pawn extends Piece {
	private ChessPattern.Hinderance hinderance;
	
	public Pawn(Square start, int team){
		create(start, team);
		hinderance = (team == 0)? ChessPattern.Hinderance.ONLY_FORWARD: ChessPattern.Hinderance.ONLY_BACKWARD;
		movePattern.add(ChessPattern.Type.PLUS, 2, hinderance);
		attackPattern.add(ChessPattern.Type.CROSS, 1, hinderance);
		boardId = 'p';
		name = "Pawn";
		hasMoved = false;
	}

	@Override
	public void moveCondition() {
		if(!hasMoved){
			hasMoved = true;
			movePattern = new ChessPattern();
			movePattern.add(ChessPattern.Type.PLUS, 1, hinderance);
		}
	}

}
