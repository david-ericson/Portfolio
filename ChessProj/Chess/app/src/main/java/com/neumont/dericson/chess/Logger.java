package com.neumont.dericson.chess;

import java.util.ArrayList;
import java.util.List;

public class Logger {
	private static String startSquare, endSquare, blockSquare, startPiece, endPiece, blockPiece;
	private static List<String> extraInfo;
	private static String finalInfo; 

	public static void setValidity(BoardManager.ValidityFlag flag){
		StringBuilder builder = new StringBuilder();
		StringBuilder starter = new StringBuilder();
		String begin = "";
		boolean print = true;
		if(startPiece != null)
		{
			begin = starter.append(InputManager.getCurrCommand()).append("The ").append(getStart()).toString();
		}
		switch(flag){
			case ATTACKING_ALLY:
				builder.append(begin).append(" attempted to attack the ").append(getEnd())
					.append(". You can't attack allies unless you're Germany.");
				break;
			case ATTACK_EMPTY_SPACE:
				builder.append(begin).append(" attempted to attack ").append(endSquare)
					.append(", which is an empty square.");
				break;
			case GOOD_ATTACK:
				builder.append(begin).append(" successfully captured the ").append(getEnd()).append(". #REKT #EasyGameEasyLife");
				//print = InputManager.isVerbose();
				break;
			case GOOD_MOVE:
				builder.append(begin).append(" moved to ").append(endSquare).append(".");
				//print = InputManager.isVerbose();
				break;
			case MOVE_BLOCKED:
				builder.append(begin).append(" was blocked by the ").append(blockPiece).append(" at ").append(blockSquare);
				break;
			case MOVE_ONTO_ENEMY:
				builder.append(begin).append(" attempted to move onto the ").append(getEnd())
					.append(". It would have worked if it was an attack, just saying.");
				break;
			case NOT_IN_MOVE_PATTERN:
				builder.append(begin).append(" can't move to ").append(endSquare)
					.append(". That piece doesn't move like that.");
				break;
			case NOT_PIECE_TURN:
				builder.append(begin).append(" is not able to move because it isn't that team's turn right now.");
				break;
			case NO_PIECE:
				builder.append(InputManager.getCurrCommand()).append("There is no piece at ").append(startSquare);
				break;
			case IN_CHECK:
				builder.append(InputManager.getCurrCommand()).append("The move couldn't be made because it would result in the ").append(BoardManager.getTeam(BoardManager.getCurrTeamTurn()))
					.append(" Team being in check.");
			break;
			case GAME_IS_OVER:
				builder.append(BoardManager.getTeam(BoardManager.getWinningTeam())).append(" Team has won the game. No more commands will be accepted.");
				break;
			default:
				break;
		}
		if(print)
		{
			builder.append("\n");
		}
		if(extraInfo != null){
			for(String s: extraInfo){
				builder.append(s).append("\n");
			}
			if(extraInfo.size() > 0){System.out.println();}
			extraInfo.clear();
		}
		finalInfo = builder.toString();
        BoardManager.moveCompleted();
	}
	
	public static String getFinalInfo(){
		String result = (finalInfo == null)?"":finalInfo;
		return result;
	}
	
	public static String getTeamTurn(int team){
		StringBuilder sb = new StringBuilder();
		return sb.append(BoardManager.getTeam(team)).append(" Team's turn.").toString();
	}
	
	public static void clearExtraInfo(){
		extraInfo.clear();
	}
	
	public static void addCheckInfo(int teamInCheck){
		StringBuilder sb = new StringBuilder();
		addExtraLogInfo(sb.append(BoardManager.getTeam(teamInCheck)).append(" Team is in Check! *gasp* ").toString());
	}
	
	public static void addCheckMateInfo(int teamInCheckmate){
		StringBuilder sb = new StringBuilder();
		addExtraLogInfo(sb.append(BoardManager.getTeam(teamInCheckmate)).append(" Team is in checkmate!! The game is over.\nTouch the screen to restart.").toString());
	}
	
	public static void addExtraLogInfo(String additionalInfo){
		if(extraInfo == null){
			extraInfo = new ArrayList<>();
		}
		extraInfo.add(InputManager.getCurrCommand()+additionalInfo);
	}
	
	public static void setCurrentSquares(Square start, Square end, Square block){
		Piece startingPiece = start.getOccupant();
		Piece endingPiece = end.getOccupant();
		if(startingPiece != null){
			startPiece = getPieceInfo(startingPiece);
		}
		else{
			startPiece = null;
		}
		if(endingPiece != null){
			endPiece = getPieceInfo(endingPiece);
		}
		else{
			endPiece = null;
		}
		if(block != null){
			blockSquare = getSquareInfo(block);
			blockPiece = getPieceInfo(block.getOccupant());
		}
		startSquare = getSquareInfo(start);
		endSquare = getSquareInfo(end);
	}
	
	private static String getStart(){
		return startPiece + " at " + startSquare;
	}
	
	private static String getEnd(){
		return endPiece + " at " + endSquare;
	}
	
	private static String getPieceAndSquareInfo(Square s){
		StringBuilder result = new StringBuilder();
		result.append(getPieceInfo(s.getOccupant())).append(" at ").append(getSquareInfo(s));
		return result.toString();
	}
	
	private static String getSquareInfo(Square s){
		StringBuilder sb = new StringBuilder();
		int row = BoardManager.getBoardLength() - s.getId()/8;
		int column = s.getId()%8;
		sb.append((char)(column+65)).append(row);
		return sb.toString();
	}
	
	private static String getPieceInfo(Piece p){
		StringBuilder result = new StringBuilder();
		result.append(BoardManager.getTeam(p.teamId)).append(" ").append(p.name);
		return result.toString();
	}
}
