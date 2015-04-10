package com.neumont.dericson.chess;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;

import com.neumont.dericson.piece.types.King;

public class ChessModel extends Observable {
	
	private Square[][] board;
	private List<Piece> darkPieces, lightPieces;
	private Map<Piece, Square> occupiedSpaces;
	private static final int LIGHT_TEAM = 0;
	private static final int DARK_TEAM = 1;
	private int currTeamTurn;
	private int winningTeam;
	
	public ChessModel(){
		board = new Square[8][8];
		darkPieces = new ArrayList<Piece>();
		lightPieces = new ArrayList<Piece>();
		occupiedSpaces = new HashMap<>();
		resetGame();
	}
	
	public void setWinningTeam(int team){
		winningTeam = team;
	}
	
	public void setSquare(int x, int y, int id){
		if(board[x][y] == null){
			board[x][y] = new Square(id);
		}
		board[x][y].clear();
	}
	
	public int getDarkTeam(){
		return DARK_TEAM;
	}
	
	public int getLightTeam(){
		return LIGHT_TEAM;
	}
	
	public int getBoardLength(){
		return board.length;
	}
	
	public int getWinningTeam(){
		return winningTeam;
	}
	
	public int getCurrTeam(){
		return currTeamTurn;
	}
	
	public void setWinningTeam(){
		winningTeam = (currTeamTurn == LIGHT_TEAM)?DARK_TEAM:LIGHT_TEAM;
	}
	
	public void resetGame(){
		darkPieces.clear();
		lightPieces.clear();
		occupiedSpaces.clear();
		winningTeam = -1;
		currTeamTurn = 0;
	}
	
	public void switchCurrTeamTurn(){
		currTeamTurn = (currTeamTurn == LIGHT_TEAM)?DARK_TEAM:LIGHT_TEAM;
	}
	
	public void placePiece(Piece p, int x, int y){
		occupiedSpaces.put(p, board[x][y]);
	}
	
	public void placePiece(Piece p, Square s){
		occupiedSpaces.put(p, s);
        List<Piece> side = getPiecesForTeam(p.teamId);
        if(!side.contains(p)){
            side.add(p);
        }
	}
	
	public void finishMove(){
		updateObservers();
	}
	
	public void removePieceFromSquare(Square s){
		occupiedSpaces.remove(s);
	}
	
	public void removePieceFromGame(Piece p){
		occupiedSpaces.remove(p);
	}
	
	public Square findPiece(Piece p){
		return occupiedSpaces.get(p);
	}
	
	public Square getSquare(int x, int y){
		return board[x][y];
	}
	
	public List<Piece> getPiecesForTeam(int team){
		return (team == LIGHT_TEAM)?lightPieces:darkPieces;
	}
	
	public King getKingForTeam(int team){
		List<Piece> side = (team == LIGHT_TEAM)?lightPieces:darkPieces;
		King k = null;
		for(Piece p: side){
			k = (p.boardId == 'k')?(King)p:k;
		}
		return k;
	}
	
	public void updateObservers(){
		setChanged();
		this.notifyObservers(this);
	}
}
