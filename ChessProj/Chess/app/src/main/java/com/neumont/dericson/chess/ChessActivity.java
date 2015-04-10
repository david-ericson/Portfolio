package com.neumont.dericson.chess;

import android.graphics.Canvas;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.Toast;


public class ChessActivity extends ActionBarActivity {
    private ChessModel model;
    private ChessView view;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        view = (ChessView) View.inflate(this, R.layout.activity_chess, null);
        model = new ChessModel();
        BoardManager.create(model);
        view.setModel(model);
        setupOnTouch();
        model.addObserver(view);
        setContentView(view);
    }

    private void setupOnTouch(){
        view.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_UP){
                    if(model.getWinningTeam() == -1) {
                        Square found = null;
                        int x = (int) event.getX();
                        int y = (int) event.getY();
                        for (int i = 0; i < model.getBoardLength() && found == null; i++) {
                            for (int j = 0; j < model.getBoardLength() && found == null; j++) {
                                if (model.getSquare(i, j).wasClicked(x, y)) {
                                    found = model.getSquare(i, j);
                                    InputManager.addSquare(i, j, found.hasOccupant() && found.getOccupant().teamId != model.getCurrTeam());
                                }
                            }
                        }
                    }else{
                        BoardManager.resetBoard();
                        view.invalidate();
                    }
                }
                return true;
            }
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_chess, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
