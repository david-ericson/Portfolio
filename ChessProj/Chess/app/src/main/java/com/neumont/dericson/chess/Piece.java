package com.neumont.dericson.chess;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

public abstract class Piece {
	protected boolean captured, hasMoved;
	protected int teamId;
	protected char boardId;
	protected ChessPattern movePattern, attackPattern;
	protected String name;
    protected Vector2 imgPos;
    private Paint paint;
    protected static Piece selected;
	
	public void create(Square start, int team){
		start.setOccupant(this);
		teamId = team;
        imgPos = new Vector2(0,0);
		captured = false;
		hasMoved = false;
		movePattern = new ChessPattern();
		attackPattern = new ChessPattern();
        paint = new Paint();
        paint.setColor(Color.BLUE);
        selected = null;
	}
	
	public boolean move(Square moveHere){
		boolean result = BoardManager.movePiece(this, moveHere);
		return result;
	}

    public static void setSelected(Piece p){
        selected = p;
    }

    public static Piece getSelected(){
        return selected;
    }

    public static void removeSelected(){
        selected = null;
    }

    public String getImageKey(){
        return BoardManager.getTeam(teamId) + name;
    }

	public void moveCondition() {
		if(!hasMoved){
			hasMoved = true;
		}
	}

    public void setImgPos(Vector2 pos){
        imgPos.x = pos.x;
        imgPos.y = pos.y;
    }

    public Vector2 getImgPos(){
        return imgPos;
    }

    public void draw(Canvas canvas){
        canvas.drawBitmap(DrawManager.getImage(getImageKey()), imgPos.x, imgPos.y, paint);
    }
}
