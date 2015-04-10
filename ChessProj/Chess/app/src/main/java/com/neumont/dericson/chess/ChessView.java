package com.neumont.dericson.chess;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Point;
import android.util.AttributeSet;
import android.view.WindowManager;
import android.widget.LinearLayout;

import java.util.Observable;
import java.util.Observer;

/**
 * Created by dericson on 3/10/2015.
 */
public class ChessView extends LinearLayout implements Observer {

    private WindowManager wm;
    private final float densityMult;
    private ChessModel model;

    public ChessView(Context context, AttributeSet attrs) {
        super(context, attrs);
        wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        densityMult = context.getResources().getDisplayMetrics().density;
        this.setWillNotDraw(false);

    }

    public void setModel(ChessModel board){
        model = board;
        Point size = new Point();
        wm.getDefaultDisplay().getSize(size);
        DrawManager.setup(getResources(), densityMult, size.x, size.y, model.getBoardLength());
    }

    @Override
    public void onFinishInflate(){
        super.onFinishInflate();

    }

    @Override
    protected void onDraw(Canvas canvas){
        super.onDraw(canvas);
        Point size = new Point();
        wm.getDefaultDisplay().getSize(size);
        int width = size.x;
        int height = size.y;
        DrawManager.draw(canvas, model);
    }


    @Override
    public void update(Observable observable, Object data) {
        model = (ChessModel)data;
        invalidate();
    }
}
