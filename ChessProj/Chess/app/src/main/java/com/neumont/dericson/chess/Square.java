package com.neumont.dericson.chess;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

import com.neumont.dericson.Lerper;

public class Square {
	private Piece occupant;
	private int id, width;
    private Vector2 imgPos;
    private String imageKey;
    private Vector2 piecePos;
    private static int selectedId;
    private static float speed, densityMult;
    private static Lerper lerper;
	
	public Square(int id){
		this.id = id;
        int teamId = (id%2 + id/8)%2;
        String team = BoardManager.getTeam(teamId);
        imageKey = team+"Square";
        speed = 50.0f;
        piecePos = new Vector2(0,0);
        imgPos = new Vector2(0,0);
	}
	
	public boolean hasOccupant(){
		return occupant != null;
	}
	
	public void setOccupant(Piece piece){
		occupant = piece;
	}
	
	public Piece getOccupant(){
		return occupant;
	}
	
	public void removeOccupant(){
		occupant = null;
	}
	
	public int getId(){
		return id;
	}
	
	public void clear(){
		occupant = null;
	}

    public void draw(int startX, int startY, int sqrWidth, Canvas canvas, float densityMult){
        imgPos.x = startX;
        imgPos.y = startY;
        if(piecePos.x == 0 && piecePos.y == 0){
            piecePos.x = imgPos.x;
            piecePos.y = imgPos.y;
        }
        width = sqrWidth;
        this.densityMult = densityMult;
        Paint p = new Paint();
        p.setColor(Color.BLUE);
        canvas.drawBitmap(DrawManager.getImage(imageKey),startX, startY,p );
        if(occupant != null){
            occupant.setImgPos(piecePos);
        }
    }

    public void highlight(Canvas canvas, Paint p){
        canvas.drawRect(imgPos.x, imgPos.y, imgPos.x+width, imgPos.y+width,p);
    }

    public void selectSquare(){
       float yVal = (2*(occupant.teamId - .5f))*20*densityMult;
       Piece.setSelected(occupant);
       startLerp(imgPos, imgPos.add(new Vector2(0, yVal)));
    }

    public void deselectSquare(){
        Piece.removeSelected();
        startLerp(piecePos, imgPos);
    }

    public void startLerp(Vector2 start, Vector2 end){
        lerper = new Lerper();
        lerper.setupLerp(start, end, speed);
        lerper.execute(this);
    }

    public void setPiecePos(Vector2 add){
        piecePos.x = add.x;
        piecePos.y = add.y;
        BoardManager.moveCompleted();
    }

    public static void setSelectedId(int id){
        selectedId = id;
    }

    public boolean wasClicked(int mouseX, int mouseY){
        return isWithinRange(mouseX, (int)imgPos.x) && isWithinRange(mouseY, (int)imgPos.y);
    }

    private boolean isWithinRange(int checkVal, int currVal){
        return checkVal > currVal && checkVal < currVal+width;
    }
}
