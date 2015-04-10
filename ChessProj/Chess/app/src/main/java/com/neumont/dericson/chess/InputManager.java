package com.neumont.dericson.chess;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class InputManager {
	private static final Pattern gridSquarePattern = Pattern.compile("(([qkrnbpQKRNBP])([ldLD]))([a-hA-H])([1-8]{1})$|^([a-hA-H])([1-8]{1})([a-hA-H])([1-8]{1})([a-hA-H])([1-8]{1})([a-hA-H])([1-8]{1})$|^([a-hA-H])([1-8]{1})([a-hA-H])([1-8]{1})([*])?");
	private static boolean isVerbose;
	private static String currCommand;
    private static StringBuilder builder = new StringBuilder();

	
	public static void enterCommand(String moveCommand){
		moveCommand = moveCommand.trim();
		Matcher match = gridSquarePattern.matcher(moveCommand);
		StringBuilder sb = new StringBuilder();
		currCommand = sb.append(moveCommand).append(": ").toString();
		int count = 0;
		while(match.find()){
			count++;
			moveCommand = match.group(0);
			BoardManager.ValidityFlag moveResult = BoardManager.ValidityFlag.GOOD_MOVE;
			//Ex: KLa4 Piece then color then square.
			if(match.group(2) != null){
				BoardManager.movePiece(match.group(2).toLowerCase().charAt(0), match.group(3).toLowerCase().charAt(0), ((int)(match.group(4).toLowerCase().charAt(0))-97), Integer.parseInt(match.group(5)));
			}
			else{
				if(match.group(14) != null){
					int startRow = (int)(match.group(14).toLowerCase().charAt(0))-97;
					int startColumn = Integer.parseInt(match.group(15))-1;
					int endRow = (int)(match.group(16).toLowerCase().charAt(0))-97;
					int endColumn = Integer.parseInt(match.group(17))-1;
					moveResult = BoardManager.movePiece(startRow, startColumn, endRow, endColumn, match.group(18) != null);
				}
				//Ex: a4d5h2c8 Two moves smashed into the same call.
				else if(match.group(6) != null){
					int startRow = ((int)(match.group(6).toLowerCase().charAt(0)))-97;
					int startColumn = Integer.parseInt(match.group(7))-1;
					int endRow = (int)(match.group(8).toLowerCase().charAt(0))-97;
					int endColumn = Integer.parseInt(match.group(9))-1;
					moveResult = BoardManager.movePiece(startRow, startColumn, endRow, endColumn, false);
					Logger.setValidity(moveResult);
					int startRow2 = ((int)(match.group(10).toLowerCase().charAt(0)))-97;
					int startColumn2 = Integer.parseInt(match.group(11))-1;
					int endRow2 = (int)(match.group(12).toLowerCase().charAt(0))-97;
					int endColumn2 = Integer.parseInt(match.group(13))-1;
					moveResult = BoardManager.movePiece(startRow2, startColumn2, endRow2, endColumn2, false);
				}
			}
			Logger.setValidity(moveResult);
		}
		if(count == 0){
			System.out.println("Invalid input " + moveCommand);
		}
	}

    public static void addSquare(int x, int y, boolean isAttack){
        Square s = BoardManager.getSquare(x + y * BoardManager.getBoardLength());
        if(s.hasOccupant() && s.getOccupant().teamId == BoardManager.getCurrTeamTurn() && builder.length() == 0){
            s.selectSquare();
            builder.append((char) (x + 65)).append(BoardManager.getBoardLength() - y);
        }else if(builder.length() > 0){
            builder.append((char) (x + 65)).append(BoardManager.getBoardLength() - y);
            if (isAttack) {
                builder.append("*");
            }
            if (builder.length() >= 4) {
                Piece p = Piece.getSelected();
                int yVal = 7*p.teamId;
                if(y == yVal && p.boardId == 'p'){
                    char teamColor = (p.teamId==0)?'l':'d';
                    builder.append('q').append(teamColor).append((char)(x+65)).append(BoardManager.getBoardLength()-y);
                }
                enterCommand(builder.toString());
                builder.setLength(0);
            }
        }
    }
	
	public static void manageScanner(Scanner scan){
		List<String> inputs = new ArrayList<String>();
		int count = 0;
		while(count < 2){
			String next = scan.nextLine(); 
			if(!next.trim().equals("")){
				inputs.add(next);
				count = 0;
			}
			else{
				count++;
			}
		}
		for(String s: inputs){
			enterCommand(s);
		}
	}
	
	public static String getCurrCommand(){
		return currCommand;
	}
	
	public static boolean isVerbose(){
		return isVerbose;
	}
	
	public static void manageFile(String[] fileArgs){
		String fileName = "No File";
		if(fileArgs.length > 1){
			fileName = fileArgs[1];
			isVerbose = fileArgs[0].toLowerCase().equals("v");
		}
		else{
			fileName = fileArgs[0];
		}
		try{
			BufferedReader br = new BufferedReader(new FileReader(new File(fileName)));
			System.out.println();
			String currLine = br.readLine();
			while(currLine != null){
				enterCommand(currLine);
				currLine = br.readLine();
			}
			br.close();
		}catch(FileNotFoundException e){
			System.out.println("The file couldn't be found. The file was: " + fileName);
		} catch (IOException e) {
			System.out.println("An IOException was caught.");
		}
	}
}
