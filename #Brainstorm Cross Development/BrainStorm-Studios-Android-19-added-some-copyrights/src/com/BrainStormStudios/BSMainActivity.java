/*
 * Some of the code from this class was taken from the google's jni samples, so all copyrights reserved to Google
 */

package com.BrainStormStudios;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.Toast;

import java.io.File;

public class BSMainActivity extends Activity {

    BSView mView;
    private boolean isTouch = false;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new BSView(getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        int X = (int) event.getX();
        int Y = (int) event.getY();
        BSMainLib.xTouch = X;
        BSMainLib.yTouch = Y;

        int eventaction = event.getAction();

        switch (eventaction) {

        case MotionEvent.ACTION_DOWN:

            //Toast.makeText(this, "ACTION_DOWN AT COORDS "+"X: "+X+" Y: "+Y,             Toast.LENGTH_SHORT).show();

            isTouch = true;
            break;

        case MotionEvent.ACTION_MOVE:

            //Toast.makeText(this, "MOVE "+"X: "+X+" Y: "+Y, Toast.LENGTH_SHORT).show();

            break;

        case MotionEvent.ACTION_UP:
        	BSMainLib.xTouch = -1;
        	BSMainLib.yTouch = -1;
            //Toast.makeText(this, "ACTION_UP "+"X: "+X+" Y: "+Y, Toast.LENGTH_SHORT).show();

            break;

        }

        return true;

    }

}
