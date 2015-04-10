package com.neumont.dericson.piece.types;

import com.neumont.dericson.chess.BoardManager;
import com.neumont.dericson.chess.ChessPattern;
import com.neumont.dericson.chess.Piece;
import com.neumont.dericson.chess.Square;

public class Rook extends Piece {

	public Rook(Square start, int team){
		create(start, team);
		movePattern.add(ChessPattern.Type.PLUS, BoardManager.getBoardLength());
		attackPattern.add(ChessPattern.Type.PLUS, BoardManager.getBoardLength());
		boardId = 'r';
		name = "Rook";
	}
	
	@Override
	public boolean move(Square moveHere) {
		// TODO Auto-generated method stub
		return false;
	}

}
