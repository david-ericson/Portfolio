package com.neumont.dericson.piece.types;

import com.neumont.dericson.chess.BoardManager;
import com.neumont.dericson.chess.ChessPattern;
import com.neumont.dericson.chess.Piece;
import com.neumont.dericson.chess.Square;

public class Bishop extends Piece {
	
	public Bishop(Square start, int team){
		create(start, team);
		movePattern.add(ChessPattern.Type.CROSS, BoardManager.getBoardLength());
		attackPattern.add(ChessPattern.Type.CROSS, BoardManager.getBoardLength());
		boardId = 'b';
		name = "Bishop";
	}
	@Override
	public boolean move(Square moveHere) {
		return false;
	}

}
