package com.neumont.dericson;

import android.os.AsyncTask;

import com.neumont.dericson.chess.Square;
import com.neumont.dericson.chess.Vector2;

/**
 * Created by dericson on 3/13/2015.
 */
public class Lerper extends AsyncTask<Square, Vector2, Void> {
    private Vector2 start, end;
    private float beta, betaIncrement, dt;
    private long prevStart;
    private Square square;
    public Lerper(){
        beta = 0;
        betaIncrement = 0;
        dt = .00166f;
    }
    @Override
    protected Void doInBackground(Square... params) {
        square = params[0];
        while (beta < 1){
            beta += betaIncrement;
            Vector2 subtract = end.subtract(start);
            Vector2 whereAt = start.add(subtract.multiply(beta));
            beta = (beta > 1)?1:beta;
            publishProgress(whereAt);
        }
        return null;
    }

    protected void onProgressUpdate(Vector2... params){
        Vector2 curr = params[0];
        square.setPiecePos(curr);
    }

    public void setupLerp(Vector2 start, Vector2 end, float speed){
        betaIncrement = 1/(Vector2.lengthBetween(start,end)/speed)*dt;
        beta = 0;
        this.start = start;
        this.end = end;
    }
}
