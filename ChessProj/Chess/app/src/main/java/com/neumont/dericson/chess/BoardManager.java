package com.neumont.dericson.chess;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.neumont.dericson.piece.types.Bishop;
import com.neumont.dericson.piece.types.King;
import com.neumont.dericson.piece.types.Knight;
import com.neumont.dericson.piece.types.Pawn;
import com.neumont.dericson.piece.types.Queen;
import com.neumont.dericson.piece.types.Rook;


public class BoardManager {
	
	private static ChessModel board;
	private static Piece currBlocker;
	private static final int ASCII_ADD = 97;
	
	
	public enum ValidityFlag{
		GOOD_MOVE,
		GOOD_ATTACK,
		MOVE_BLOCKED,
		NOT_IN_MOVE_PATTERN,
		MOVE_ONTO_ENEMY,
		ATTACK_EMPTY_SPACE,
		ATTACKING_ALLY,
		NO_PIECE,
		NOT_PIECE_TURN,
		IN_CHECK,
		GAME_IS_OVER,
	}
	
	public enum PawnPromote{
		NOT_QUEEN{public String toString(){return "You tried to promote a pawn without using a queen.";}},
		NO_PAWN{public String toString(){return "There is no pawn at the promotion location.";}},
		NOT_TEAM{public String toString(){return "You attempted to promote a pawn using the other team's queen.";}},
		GOOD{public String toString(){return "Pawn successfully promoted!!";}},
	}
	
	public enum SpecialMove{
		LIGHT_CASTLE_RIGHT,
		LIGHT_CASTLE_LEFT,
		DARK_CASTLE_RIGHT,
		DARK_CASTLE_LEFT,
		NONE
	}
			
	
	public static void create(ChessModel cm){
		board = cm;
		resetBoard();
	}
	
	public static void resetBoard(){
        board.resetGame();
		for(int i=0; i<board.getBoardLength(); i++){
			for(int j=0; j<board.getBoardLength(); j++){
				board.setSquare(i, j, j*board.getBoardLength()+i);
			}
		}
		setupSide(board.getDarkTeam());
		setupSide(board.getLightTeam());
		King lKing = board.getKingForTeam(board.getLightTeam());
		King dKing = board.getKingForTeam(board.getDarkTeam());;
		CheckManager.create(lKing, dKing);
		for(Piece lp: board.getPiecesForTeam(board.getLightTeam())){
			CheckManager.setupAttacks(lp, board.findPiece(lp));
		}
		for(Piece dp: board.getPiecesForTeam(board.getDarkTeam())){
			CheckManager.setupAttacks(dp, board.findPiece(dp));
		}
		
	}
	
	//Reset up the board.
	private static void setupSide(int team){
		List<Piece> side = board.getPiecesForTeam(team);
		
		int pawnY = (team == board.getDarkTeam())?1:board.getBoardLength()-2;
		int otherY = (team == board.getDarkTeam())?0:board.getBoardLength()-1;
		for(int i=0; i<8; i++){
			side.add(new Pawn(board.getSquare(i,pawnY), team));
			board.placePiece(side.get(side.size()-1),i, pawnY);
		}
		for(int i=0; i<2; i++){
			side.add(new Rook(board.getSquare(i*(board.getBoardLength()-1),otherY), team));
			side.add(new Knight(board.getSquare(1+i*(board.getBoardLength()-3),otherY), team));
			side.add(new Bishop(board.getSquare(2+i*(board.getBoardLength()-5),otherY), team));
			board.placePiece(side.get(side.size()-3), i*(board.getBoardLength()-1), otherY);
			board.placePiece(side.get(side.size()-2), 1+i*(board.getBoardLength()-3), otherY);
			board.placePiece(side.get(side.size()-1), 2+i*(board.getBoardLength()-5), otherY);
		}
		side.add(new Queen(board.getSquare(board.getBoardLength()/2 - 1,otherY), team));
		side.add(new King(board.getSquare(board.getBoardLength()/2,otherY), team));
		board.placePiece(side.get(side.size()-2), board.getBoardLength()/2-1, otherY);
		board.placePiece(side.get(side.size()-1), board.getBoardLength()/2, otherY);
	}
	
	private static void completeMove(Piece moving, List<Piece> pieces, Square toHere){
		for(Piece p: pieces){
			if(p == moving){
				//alterSquare(p, toHere, false);
			}
		}
	}
	
	private static ValidityFlag alterSquare(Square start, Square end, boolean isCapture){
		ValidityFlag result = isValidMove(start.getOccupant(),end,isCapture);
		Square oldLoc = start;
		Logger.setCurrentSquares(start, end, findPiece(currBlocker));
		Piece p = start.getOccupant();
		SpecialMove special = SpecialMove.NONE;
		if(p != null){
			special = isSpecialMove(p, start, end, isCapture);
		}
		if(special != SpecialMove.NONE && result != ValidityFlag.NOT_PIECE_TURN){
			if(CheckManager.isInCheck(p.teamId)){
				result = ValidityFlag.IN_CHECK;
				Logger.addExtraLogInfo("You can't castle when you're in check.");
			}
			else if(!CheckManager.willBeInCheck(board.getCurrTeam(), p, end))
			{
				result = ValidityFlag.GOOD_MOVE;
				completeSpecialMove(special);
			}
			else{
				result = ValidityFlag.IN_CHECK;
				Logger.addExtraLogInfo("You can't castle your King into check.");
			}
		}
		if(result == ValidityFlag.GOOD_MOVE || result == ValidityFlag.GOOD_ATTACK){
			finalizeMove(start, end);
            start.deselectSquare();
			board.switchCurrTeamTurn();
			if(CheckManager.isInCheck(board.getCurrTeam())){
				if(CheckManager.isInCheckmate(board.getCurrTeam())){
					Logger.addCheckMateInfo(board.getCurrTeam());
					board.setWinningTeam();
				}else{
					Logger.addCheckInfo(board.getCurrTeam());
				}
			}
		}
        else{
            start.deselectSquare();
        }
		return result;
	}
	
	private static void finalizeMove(Square oldLoc, Square end){
		Piece p = oldLoc.getOccupant();
		oldLoc.removeOccupant();
		board.removePieceFromSquare(oldLoc);
		if(end.hasOccupant()){
			end.getOccupant().captured = true;
			CheckManager.pieceWasTaken(end.getOccupant());
			board.removePieceFromGame(end.getOccupant());
		}
		end.setOccupant(p);
		board.placePiece(p,end);
		p.moveCondition();
		CheckManager.testMethod();
		CheckManager.pieceWasMoved(p, oldLoc, end);
	}
	
	private static void completeSpecialMove(SpecialMove move){
		switch(move){
			case DARK_CASTLE_LEFT:
				Logger.addExtraLogInfo("Dark Team castled on the left side.");
				finalizeMove(getSquare(0), getSquare(3));
				break;
			case DARK_CASTLE_RIGHT:
				Logger.addExtraLogInfo("Dark Team castled on the right side.");
				finalizeMove(getSquare(7), getSquare(5));
				break;
			case LIGHT_CASTLE_LEFT:
				Logger.addExtraLogInfo("Light Team castled on the left side.");
				finalizeMove(getSquare(56), getSquare(59));
				break;
			case LIGHT_CASTLE_RIGHT:
				Logger.addExtraLogInfo("Light Team castled on the right side.");
				finalizeMove(getSquare(63), getSquare(61));
				break;
		}
	}
	
	private static SpecialMove isSpecialMove(Piece moving, Square start, Square end, boolean isCapture){
		SpecialMove result = SpecialMove.NONE;
		//Castling
		if(moving.boardId == 'k' && !moving.hasMoved && !isCapture){
			if(isCastleMoveHelper(moving, end, 0, 61, 62, 63, 62)){
				result = SpecialMove.LIGHT_CASTLE_RIGHT;
			}
			else if(isCastleMoveHelper(moving, end, 0, 57, 58, 59, 56, 58)){
				result = SpecialMove.LIGHT_CASTLE_LEFT;
			}
			else if(isCastleMoveHelper(moving, end, 1, 1, 2, 3, 0, 2)){
				result = SpecialMove.DARK_CASTLE_LEFT;
			}
			else if(isCastleMoveHelper(moving, end, 1, 6, 5, 7, 6)){
				result = SpecialMove.DARK_CASTLE_RIGHT;
			}
			
		}
		return result;
	}
	
	private static boolean isCastleMoveHelper(Piece moving, Square movingTo, int team, int firstSquare, int secondSquare, int rookSquare, int ending){
		Piece rook = getSquare(rookSquare).getOccupant();
		return (moving.teamId == team && movingTo.equals(getSquare(ending)) && !getSquare(firstSquare).hasOccupant() && !getSquare(secondSquare).hasOccupant() 
				&& rook != null && !rook.hasMoved);
	}
	
	private static boolean isCastleMoveHelper(Piece moving, Square movingTo, int team, int firstSquare, int secondSquare, int thirdSquare, int rookSquare, int ending){
		Piece rook = getSquare(rookSquare).getOccupant();
		return (moving.teamId == team && movingTo.equals(getSquare(ending)) && !getSquare(firstSquare).hasOccupant() && !getSquare(secondSquare).hasOccupant() 
				&& !getSquare(thirdSquare).hasOccupant() && rook != null && !rook.hasMoved);
	}
	
	public static int getCurrTeamTurn(){
		return board.getCurrTeam();
	}
	
	public static Square getSquare(int id){
		Square s = null;
		if(id >= 0 &&  id < board.getBoardLength()*board.getBoardLength())
		{
			s = board.getSquare(id%8,id/8);
		}
		return s;
	}
	
	public static String getTeam(int teamId){
		return (teamId==board.getLightTeam())?"Light":"Dark";
	}
	
	public static int getBoardLength(){
		return board.getBoardLength();
	}
	
	public static boolean areSquaresAdjacent(Square first, Square second){
		boolean result = true;
		int id1 = first.getId();
		int id2 = second.getId();
		int row1 = id1/8;
		int column1 = id1%8;
		int row2 = id2/8;
		int column2 = id2%8;
		result = Math.abs(row1-row2) <= 1 && Math.abs(column1-column2) <= 1;
		return result;
	}
	
	public static Square findPiece(Piece p){
		return board.findPiece(p);
	}
	
	public static boolean movePiece(Piece moving, Square toHere){
		boolean moveWorked = true;
		if(moving.teamId == board.getLightTeam()){
			completeMove(moving, board.getPiecesForTeam(moving.teamId), toHere);
		}
		else if(moving.teamId == board.getDarkTeam()){
			completeMove(moving, board.getPiecesForTeam(moving.teamId), toHere);
		}
		return moveWorked;
	}
	
	public static void movePiece(char pieceId, char teamColor, int column, int row){
		
		if(pieceId == 'q'){
			Square s = board.getSquare(column, board.getBoardLength()-row);
			if(s.hasOccupant() && s.getOccupant().boardId == 'p' && (row == 1 || row == 8)){
				int team = (teamColor == 'l')?board.getLightTeam():board.getDarkTeam();
				if(team == s.getOccupant().teamId && board.getCurrTeam() != team){
					board.removePieceFromSquare(s);
					Piece pawn = s.getOccupant();
                    pawn.captured = true;
					Piece p = new Queen(s, team);
					board.placePiece(p, s);
                    p.setImgPos(pawn.getImgPos());
					Square test = findPiece(p);
					CheckManager.setupAttacks(p, s);
					CheckManager.transferBlocking(pawn, p);
					CheckManager.pieceWasTaken(pawn);
					test = findPiece(p);
					Logger.addExtraLogInfo(PawnPromote.GOOD.toString());
				}else{
					Logger.addExtraLogInfo(PawnPromote.NOT_TEAM.toString());
				}
			}else{
				Logger.addExtraLogInfo(PawnPromote.NO_PAWN.toString());
			}
		}
		else{
			Logger.addExtraLogInfo(PawnPromote.NOT_QUEEN.toString());
		}
		
	}
	
	public static ValidityFlag movePiece(int startColumn, int startRow, int endColumn, int endRow, boolean isCapture){
		int length = board.getBoardLength()-1;
		return alterSquare(board.getSquare(startColumn,length-startRow), board.getSquare(endColumn,length-endRow), isCapture);
	}
	
	public static int getWinningTeam(){
		return board.getWinningTeam();
	}
	
	private static boolean isValidMove(Piece p, Square toCheck){
		boolean result = true;
		result = (!toCheck.hasOccupant() || (toCheck.hasOccupant() && toCheck.getOccupant().teamId != p.teamId));
		return result;
	}

    public static void moveCompleted(){
        board.finishMove();
    }
	
	private static ValidityFlag isValidMove(Piece p, Square toCheck, boolean isCapture){
		ValidityFlag result = ValidityFlag.GOOD_MOVE;
		if(board.getWinningTeam() == -1){
			if(p != null){
				if(p.teamId == board.getCurrTeam()){
					List<Square> possibleMoves = MoveManager.getPossibleMoves((isCapture)?p.attackPattern:p.movePattern, findPiece(p), p.teamId, isCapture);
					if(!possibleMoves.contains(toCheck)){
						if(MoveManager.isSquareRejected(toCheck)){
							currBlocker = MoveManager.getBlocker();
							if(isCapture){
								if(currBlocker == null){
									result = ValidityFlag.ATTACK_EMPTY_SPACE;
								}
								else if(currBlocker.equals(toCheck.getOccupant())){
									result = ValidityFlag.ATTACKING_ALLY;
								}
								else{
									result = ValidityFlag.MOVE_BLOCKED;
								}
							}
							else{
								result =(currBlocker.teamId != p.teamId && currBlocker.equals(toCheck.getOccupant()))?ValidityFlag.MOVE_ONTO_ENEMY:ValidityFlag.MOVE_BLOCKED;
							}
						}
						else{
							result = ValidityFlag.NOT_IN_MOVE_PATTERN;
						}
					}
					else{
						if(!CheckManager.willBeInCheck(board.getCurrTeam(), p, toCheck)){
							result = (isCapture)?ValidityFlag.GOOD_ATTACK:ValidityFlag.GOOD_MOVE;
						}
						else{
							result = ValidityFlag.IN_CHECK;
						}
					}
				}else{
					result = ValidityFlag.NOT_PIECE_TURN;
				}
			}else
			{
				result = ValidityFlag.NO_PIECE;
			}
		}else{
			result = ValidityFlag.GAME_IS_OVER;
		}
		return result;
	}
	
}
