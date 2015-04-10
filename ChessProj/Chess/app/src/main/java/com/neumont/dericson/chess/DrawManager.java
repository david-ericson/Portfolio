package com.neumont.dericson.chess;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DrawManager {

    private static Map<String, Bitmap> images;
    private static Paint oddSqr, evenSqr, textPaint, movePaint, attackPaint;
    private static int sqrWidth, startX, startY, winWidth, winHeight;
    private static float densityMlt;

    public static void draw(Canvas canvas, ChessModel board){
        drawScreenText(canvas, board.getBoardLength());
        int length = board.getBoardLength();
        int subtract = 0;//(board.getCurrTeam() == 0)?0:board.getBoardLength()-1;
        for(int i=0; i<length ; i++){
            for(int j=0; j<length; j++){
                int id = length*j+i;
                int left = startX+sqrWidth*i;
                int top = startY+sqrWidth*j;
                board.getSquare(Math.abs(subtract-i), Math.abs(subtract-j)).draw(left, top, sqrWidth, canvas, densityMlt);
                if(i==0){
                    Rect bounds = new Rect();
                    textPaint.getTextBounds(""+(length-(Math.abs(subtract-j))), 0, 1, bounds);
                    canvas.drawText(""+(length-(Math.abs(subtract-j))),left-sqrWidth/2,top+sqrWidth/2+bounds.height()/2,textPaint);
                }
                if(j==length-1){
                    int textWidth = (int)textPaint.measureText(""+(char)((Math.abs(subtract-i))+65));
                    canvas.drawText(""+(char)((Math.abs(subtract-i))+65),left+sqrWidth/2-textWidth/2, top+sqrWidth*1.5f, textPaint );
                }
            }
        }
        Piece selected = Piece.getSelected();
        if(selected!=null){
            highlightSquares(selected, canvas);
        }
        for(Piece p: board.getPiecesForTeam(board.getLightTeam())){
            if(p != selected && !p.captured) {
                p.draw(canvas);
            }
        }
        for(Piece p: board.getPiecesForTeam(board.getDarkTeam())){
            if(p != selected && !p.captured) {
                p.draw(canvas);
            }
        }
        if(selected != null) {
            selected.draw(canvas);
        }
    }

    private static void highlightSquares(Piece selected, Canvas canvas){
        List<Square> attack = MoveManager.getPossibleMoves(selected.attackPattern, BoardManager.findPiece(selected), selected.teamId, true);
        List<Square> move = MoveManager.getPossibleMoves(selected.movePattern, BoardManager.findPiece(selected), selected.teamId, false);
        for(Square s: attack){
            s.highlight(canvas, attackPaint);
        }
        for(Square s: move){
            s.highlight(canvas, movePaint);
        }
    }

    private static void drawScreenText(Canvas canvas, int boardLength){
        textPaint.setTextSize(12*densityMlt);
        String[] logInfo = Logger.getFinalInfo().split("\\n");
        drawLogText(canvas, logInfo);
        textPaint.setTextSize(20*densityMlt);
        String teamTurn = BoardManager.getTeam(BoardManager.getCurrTeamTurn())+" Team's Turn";
        int textWidth = (int)textPaint.measureText(teamTurn);
        canvas.drawText(teamTurn, winWidth/2 - textWidth/2, startY + (boardLength+2)*sqrWidth,textPaint);
    }

    private static void drawLogText(Canvas canvas, String[] logInfo){
        int numLines = 0;
        int xDiff = winWidth-startX*2;
        int yStart = winHeight/16;
        Rect bounds = new Rect();
        textPaint.getTextBounds(logInfo[0],0,logInfo[0].length(), bounds);
        int yGap = bounds.height()+15;
        StringBuilder currSentence = new StringBuilder();
        StringBuilder currWord = new StringBuilder();
        for(int i=0; i<logInfo.length; i++){
            currSentence.setLength(0);
            currWord.setLength(0);
            String currLog = logInfo[i];
            for(int j=0; j<currLog.length(); j++){
                if(currLog.charAt(j) == ' ' || j+1 == currLog.length()){
                    int textWidth = (int)textPaint.measureText(currWord.toString());
                    int currWidth = (int)textPaint.measureText(currSentence.toString());
                    if(textWidth+currWidth > xDiff) {
                        canvas.drawText(currSentence.toString(), startX, yStart + yGap * numLines, textPaint);
                        numLines++;
                        currSentence.setLength(0);
                        if(j+1 == currLog.length()){
                            currWord.append(currLog.charAt(j));
                        }
                        currSentence.append(currWord).append(" ");
                        currWord.setLength(0);
                    }else{
                        if(j+1 == currLog.length()){
                            currWord.append(currLog.charAt(j));
                        }
                        currSentence.append(currWord).append(" ");
                        currWord.setLength(0);
                    }
                }else{
                    currWord.append(currLog.charAt(j));
                }
            }
            canvas.drawText(currSentence.toString(), startX, yStart+yGap*numLines, textPaint);
            numLines++;
        }
    }

    private static Bitmap scaleToSize(Bitmap bmp, int reqWidth, int reqHeight){
        Bitmap test = Bitmap.createScaledBitmap(bmp, reqWidth, reqHeight, false);
        int letMeSee = test.getWidth();
       return Bitmap.createScaledBitmap(bmp, reqWidth, reqHeight, false);
    }

    public static Bitmap getImage(String imageKey){
        return images.get(imageKey);
    }

    public static void setup(Resources r, float densityMult, int width, int height, int boardLength){
       images = new HashMap<>();
       Bitmap dPawn = BitmapFactory.decodeResource(r, R.drawable.darkpawn   );
       Bitmap dRook= BitmapFactory.decodeResource(r, R.drawable.darkrook   );
       Bitmap dKnight= BitmapFactory.decodeResource(r, R.drawable.darkknight);
       Bitmap dBishop= BitmapFactory.decodeResource(r, R.drawable.darkbishop);
       Bitmap dQueen= BitmapFactory.decodeResource(r, R.drawable.darkqueen  );
       Bitmap dKing = BitmapFactory.decodeResource(r, R.drawable.darkking)  ;
       Bitmap dSquare = BitmapFactory.decodeResource(r, R.drawable.darksquare)  ;
       Bitmap lPawn = BitmapFactory.decodeResource(r, R.drawable.lightpawn );
       Bitmap lRook = BitmapFactory.decodeResource(r, R.drawable.lightrook );
       Bitmap lKnight = BitmapFactory.decodeResource(r, R.drawable.lightknight);
       Bitmap lBishop = BitmapFactory.decodeResource(r, R.drawable.lightbishop);
       Bitmap lQueen = BitmapFactory.decodeResource(r, R.drawable.lightqueen);
       Bitmap lKing = BitmapFactory.decodeResource(r, R.drawable.lightking) ;
       Bitmap lSquare = BitmapFactory.decodeResource(r, R.drawable.lightsquare)  ;
       winWidth = width;
       winHeight = height;
       densityMlt = densityMult;
       startX = width/16;
       startY = height/6;
       sqrWidth = (width - 2*startX)/boardLength;
       oddSqr = new Paint();
       oddSqr.setColor(Color.BLACK);
       evenSqr = new Paint();
       evenSqr.setColor(Color.LTGRAY);
       textPaint = new Paint();
       textPaint.setTextSize(20*densityMult);
       textPaint.setColor(Color.WHITE);
        movePaint = new Paint();
        movePaint.setColor(Color.argb(85, 255, 255, 0));
        attackPaint = new Paint();
        attackPaint.setColor(Color.argb(85, 255, 50, 50));
       images.put("DarkPawn", scaleToSize(dPawn, sqrWidth, sqrWidth));
       images.put("DarkRook", scaleToSize(dRook, sqrWidth, sqrWidth));
       images.put("DarkKnight",scaleToSize(dKnight, sqrWidth, sqrWidth));
       images.put("DarkBishop",scaleToSize(dBishop, sqrWidth, sqrWidth));
       images.put("DarkQueen",scaleToSize(dQueen, sqrWidth, sqrWidth));
       images.put("DarkKing", scaleToSize(dKing, sqrWidth, sqrWidth));
       images.put("DarkSquare", scaleToSize(dSquare, sqrWidth, sqrWidth));
       images.put("LightPawn",scaleToSize(lPawn, sqrWidth, sqrWidth));
       images.put("LightRook",scaleToSize(lRook, sqrWidth, sqrWidth));
       images.put("LightKnight",scaleToSize(lKnight, sqrWidth, sqrWidth));
       images.put("LightBishop",scaleToSize(lBishop, sqrWidth, sqrWidth));
       images.put("LightQueen",scaleToSize(lQueen, sqrWidth, sqrWidth));
       images.put("LightKing",scaleToSize(lKing, sqrWidth, sqrWidth));
       images.put("LightSquare", scaleToSize(lSquare, sqrWidth, sqrWidth));
    }


}
