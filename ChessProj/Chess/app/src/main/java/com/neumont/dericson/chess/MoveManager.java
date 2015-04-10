package com.neumont.dericson.chess;

import com.neumont.dericson.chess.ChessPattern.Hinderance;

import java.util.ArrayList;
import java.util.List;

public class MoveManager {
	private static final int SQUARE_ADD = BoardManager.getBoardLength();
	private static Piece currBlocker, foundBlocker;
	private static List<Piece> currBlockers;
	private static Square currOrigin;
	
	public static class BlockedMove{
		public List<Piece> blockers;
		Square move, origin;
		
		public BlockedMove(Square toMove){
			move = toMove;
			origin = currOrigin;
			blockers = new ArrayList<Piece>();
			blockers.addAll(currBlockers);
		}
		public Square getMove(){
			return move;
		}
		public Square getOrigin(){
			return origin;
		}
		public Piece getBlocker(){
			return blockers.get(0);
		}
		public List<Piece> getBlockers(){
			return blockers;
		}
	}
	
	private static List<BlockedMove> rejectedMoves = new ArrayList<BlockedMove>();
	

	public static List<Square> getPossibleMoves(ChessPattern pattern, Square start, int team, boolean isAttack){
		if(currBlockers == null){
			currBlockers = new ArrayList<>();
		}
		List<Square> squares = new ArrayList<>();
		currOrigin = null;
		rejectedMoves.clear();
		List<ChessPattern.MoveTypeAmount> moves = pattern.getMovement();
		for(ChessPattern.MoveTypeAmount move : moves){
			evaluateMove(move, start, team, isAttack, squares);
		}
		return squares;
	}
	
	public static boolean isSquareRejected(Square blockedMove){
		boolean result = false;
		foundBlocker = null;
		for(int i=0; i<rejectedMoves.size() && !result;i++){
			BlockedMove bm = rejectedMoves.get(i);
			if(bm.getMove().equals(blockedMove)){
				result = true;
				foundBlocker = bm.getBlocker();
			}
		}
		return result;
	}
	
	public static List<BlockedMove> getSquares(){
		return rejectedMoves;
	}
	
	public static Piece getBlocker(){
		return foundBlocker;
	}
	
	private static void evaluateMove(ChessPattern.MoveTypeAmount move, Square start, int team, boolean isAttack, List<Square> results){
		ChessPattern.Hinderance h = move.getHinderance();
		switch(move.getT())
		{
			case L:
				findSquaresForL(start, team, isAttack, results);
				break;
			case CROSS:
				if(h == Hinderance.NONE || h == Hinderance.ONLY_BACKWARD){
					findSquaresUsingAddition(SQUARE_ADD+1, start, team, move.getMoveSize(), isAttack, results);
					findSquaresUsingAddition(SQUARE_ADD-1, start, team, move.getMoveSize(), isAttack, results);
				}
				if(h == Hinderance.NONE || h == Hinderance.ONLY_FORWARD){
					findSquaresUsingAddition(-SQUARE_ADD+1, start, team, move.getMoveSize(), isAttack, results);
					findSquaresUsingAddition(-SQUARE_ADD-1, start, team, move.getMoveSize(), isAttack, results);
				}
				break;
			case PLUS:
				if(h == Hinderance.NONE || h == Hinderance.ONLY_BACKWARD){
					findSquaresUsingAddition(SQUARE_ADD, start, team, move.getMoveSize(), isAttack, results);
				}
				if(h == Hinderance.NONE || h == Hinderance.ONLY_FORWARD){
					findSquaresUsingAddition(-SQUARE_ADD, start, team, move.getMoveSize(), isAttack, results);
				}
				if(h == Hinderance.NONE){
					findSquaresUsingAddition(1, start, team, move.getMoveSize(), isAttack, results);
					findSquaresUsingAddition(-1, start, team, move.getMoveSize(), isAttack, results);
				}
				break;
		}
	}
	
	private static void findSquaresUsingAddition(int add, Square start, int team, int length, boolean isAttack, List<Square> results){
		currBlocker = null;
		currBlockers.clear();
		Square prev = start;
		Square lastFound = BoardManager.getSquare(start.getId()+add);
		currOrigin = lastFound;
		int count = 0;
		while(lastFound != null && count < length && !lastFound.hasOccupant() && BoardManager.areSquaresAdjacent(prev, lastFound))
		{
			//If you aren't attacking then add the last square.
			//If you are attacking then that means the last square is vacant and as thus it is a rejected move.
			if(!isAttack)
			{
				results.add(lastFound);
			}
			else
			{
				rejectedMoves.add(new BlockedMove(lastFound));
			}
			prev = lastFound;
			lastFound = BoardManager.getSquare(lastFound.getId()+add);
			count++;
		}
		if(lastFound != null && count < length && BoardManager.areSquaresAdjacent(prev, lastFound) && lastFound.getOccupant().teamId != team && isAttack)
		{
			results.add(lastFound);
			currBlocker = lastFound.getOccupant();
			currBlockers.add(currBlocker);
			rejectedMoves.add(new BlockedMove(lastFound));
		}
		else if(lastFound != null && count < length && BoardManager.areSquaresAdjacent(prev, lastFound)){
			currBlocker = lastFound.getOccupant();
			currBlockers.add(currBlocker);
			rejectedMoves.add(new BlockedMove(lastFound));
		}
		if(currBlocker != null)
		{
			prev = lastFound;
			lastFound = BoardManager.getSquare(lastFound.getId()+add);
			count++;
			findRejectedSquares(add, prev, lastFound, count, length);
		}
	}
	
	private static void findRejectedSquares(int add, Square prev, Square lastFound, int count, int length){
		while(lastFound != null && count < length && BoardManager.areSquaresAdjacent(prev, lastFound)){
			if(lastFound.hasOccupant()){
				currBlockers.add(lastFound.getOccupant());
			}
			rejectedMoves.add(new BlockedMove(lastFound));
			prev = lastFound;
			lastFound = BoardManager.getSquare(lastFound.getId()+add);
			count++;
		}
	}
	
	private static void findSquaresForL(Square start, int team, boolean isAttack, List<Square> results){
		findSquaresForLHelper(start, SQUARE_ADD+2, SQUARE_ADD*2+1, SQUARE_ADD+1, team, isAttack, results);
		findSquaresForLHelper(start, -(SQUARE_ADD+2), -(SQUARE_ADD*2+1), -(SQUARE_ADD+1), team, isAttack, results);
		findSquaresForLHelper(start, SQUARE_ADD-2, SQUARE_ADD*2-1, SQUARE_ADD-1, team, isAttack, results);
		findSquaresForLHelper(start, -(SQUARE_ADD-2), -(SQUARE_ADD*2-1), -(SQUARE_ADD-1), team, isAttack, results);
	}
	
	private static void findSquaresForLHelper(Square start, int firstAdd, int secondAdd, int toCheckDiff, int team, boolean isAttack, List<Square> results)
	{
		currBlockers.clear();
		Square side = BoardManager.getSquare(start.getId() + firstAdd);
		Square top = BoardManager.getSquare(start.getId() + secondAdd);
		Square toCheck = BoardManager.getSquare(start.getId()+toCheckDiff);
		
		if(toCheck != null && BoardManager.areSquaresAdjacent(start, toCheck)){
			if(isSquareValid(toCheck, side, team, isAttack)){
				results.add(side);
			}
			if(isSquareValid(toCheck, top, team, isAttack)){
				results.add(top);
			}
		}
	}
	
	private static boolean isSquareValid(Square start, Square toCheck, int team, boolean isAttack){
		boolean result = false;
		currOrigin = toCheck;
		if(toCheck != null && BoardManager.areSquaresAdjacent(start, toCheck))
		{
			if((!toCheck.hasOccupant() && !isAttack) || (toCheck.hasOccupant() && toCheck.getOccupant().teamId != team && isAttack)){
				result = true;
				rejectedMoves.add(new BlockedMove(toCheck));
			}
			else{
				currBlocker = toCheck.getOccupant();
				rejectedMoves.add(new BlockedMove(toCheck));
			}
			
		}
		return result;
	}
	
}
