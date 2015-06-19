package com.example.brainstormstudiosgameengine;

import org.jbox2d.common.Vec2;

import android.app.ActionBar.LayoutParams;
import android.app.Activity;
import android.content.Context;
import android.content.res.ColorStateList;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.PowerManager;
import android.view.GestureDetector;
import android.view.GestureDetector.OnGestureListener;
import android.view.MotionEvent;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;



public class MainActivity extends Activity implements SensorEventListener, OnGestureListener  {
	
	private final BSRenderer randare = new BSRenderer(this);

	
	
	float mPreviousX = 0, mPreviousY = 0;
	
	/** Hold a reference to our GLSurfaceView */
	public static GLSurfaceView mGLSurfaceView;
    protected PowerManager.WakeLock mWakeLock;
    
	private SensorManager mSensorManager;
	private Sensor GravitySensor;
	
    private GestureDetector gestureDetector;
    View.OnTouchListener gestureListener;
    private GestureDetector gDetector;


	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		
		mGLSurfaceView = new MyGLSurfaceView(this);
//		mGLSurfaceView = new MyGLSurfaceView(this);
	    
		RelativeLayout rl = new RelativeLayout(this);
	    rl.addView(mGLSurfaceView);   
		randare.tv1 = new TextView(this);
	    RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
	    lp.addRule(RelativeLayout.ALIGN_TOP);
	    randare.tv1.setLayoutParams(lp);
	    randare.tv1.setText("FPS: 0");
	    //randare.tv1.setBackgroundColor(0x4060ff70);
	    randare.tv1.setTextColor(ColorStateList.valueOf(0xffff0000));
	    rl.addView(randare.tv1);
	    
	    
	    	    
		setContentView(rl);//mGLSurfaceView);


		mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
		GravitySensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

         //Gesture detection
//        gestureDetector = new GestureDetector(new MyGestureDetector());
//        gestureListener = new View.OnTouchListener() {
//            public boolean onTouch(View v, MotionEvent event) {
//                return gestureDetector.onTouchEvent(event);
//            }
//        };
        gDetector = new GestureDetector(this);
        //mGLSurfaceView.setOnClickListener(onDown); //(SelectFilterActivity.this); 
        mGLSurfaceView.setOnTouchListener(gestureListener);
        

        final PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        this.mWakeLock = pm.newWakeLock(PowerManager.SCREEN_DIM_WAKE_LOCK, "My Tag");
        this.mWakeLock.acquire();
	}

	@Override
	protected void onResume() 
	{
		// The activity must call the GL surface view's onResume() on activity onResume().
		super.onResume();
    	mSensorManager.registerListener(this, GravitySensor, SensorManager.SENSOR_DELAY_UI);
		mWakeLock.acquire();
		mGLSurfaceView.onResume();
	}

	@Override
	protected void onPause() 
	{
		// The activity must call the GL surface view's onPause() on activity onPause().
		super.onPause();
    	mSensorManager.unregisterListener(this, GravitySensor);
		mWakeLock.release();
		mGLSurfaceView.onPause();
	}	

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
		
	}
	
	public void onSensorChanged(SensorEvent event)
	{
//		Values.gravityX = event.values[1] * -1;
//		Values.gravityY = event.values[0] * 1;

		float force = event.values[1] * -1;
		
		String theText = '\n' +  "      gravX: " + Float.toString(Values.gravityX) + 
				'\n' + "      gravY: " + Float.toString(Values.gravityY);
		
		if(Values.nrOfBodies != 0)
		{
			force *= 0.5f;
			if(Math.abs(force) > 1.5f)
			{
				if(force > 0)
				{
					Values.ButtonLeft = false;
					Values.ButtonRight = true;
				}
				else
				{
					Values.ButtonRight = false;
					Values.ButtonLeft = true;
				}
				//Values.hero.theBody.applyLinearImpulse(new Vec2(force, 0), Values.hero.theBody.getWorldCenter());
			}
			else
			{
				Values.ButtonRight = false;
				Values.ButtonLeft = false;
				if(Values.hero.theBody.getLinearVelocity().y == 0)
				{
					Values.hero.theBody.setLinearVelocity(new Vec2(0, Values.hero.theBody.getLinearVelocity().y));
				}
			}
		}
		
		theText = Values.textToShow;
		randare.tv1.setText(theText);
	}
	
	
    @Override
    public void onDestroy() {
        this.mWakeLock.release();
        super.onDestroy();
    }
    
    
	@Override
	public boolean onFling(MotionEvent start, MotionEvent finish, float xVelocity, float yVelocity) 
	{
		try
		{
	        if (start.getRawY() < finish.getRawY()) 
	        {
	        	///Values.ButtonJump = false;
	        	String theText = "swiped down; start: " + Float.toString(start.getRawY()) + 
	        			"; stop: " + Float.toString(finish.getRawY());
	    		Values.textToShow = theText;
	    		
	    		//Values.gravityX = 100;
	    		//Values.gravityY = 100;

//	    		Values.world.setGravity(new Vec2(Values.gravityX, Values.gravityY));
	    		
	    		
	    		///Values.hero.theBody.applyLinearImpulse(new Vec2(0, 20), Values.hero.theBody.getWorldCenter());
	    		
	    		
//                ((ImageView)findViewById(R.id.image_place_holder)).setImageResource(R.drawable.down);
	        } 
	        else 
		        if (start.getRawY() > finish.getRawY()) 
		        {
//		        	if(Values.canJumpVertically)
		        	{
		        		Values.ButtonJump = true;
		        	}
		        	String theText = "swiped up; start: " + Float.toString(start.getRawY()) + 
		        			"; stop: " + Float.toString(finish.getRawY());
		    		Values.textToShow = theText;
		    		
		    		//Values.gravityX = -100;
		    		//Values.gravityY = -100;
		    		
//		    		Values.world.setGravity(new Vec2(Values.gravityX, Values.gravityY));
		    		
		    		///Values.hero.theBody.applyLinearImpulse(new Vec2(0, -20), Values.hero.theBody.getWorldCenter());
		    		
		    		
	//                ((ImageView)findViewById(R.id.image_place_holder)).setImageResource(R.drawable.up);
		        }
	    } 
		catch (Exception e) 
	    {
	        // nothing
	    }
	        return true;
	}
	

	@Override
	public boolean onDown(MotionEvent arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void onLongPress(MotionEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean onScroll(MotionEvent arg0, MotionEvent arg1, float arg2,
			float arg3) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void onShowPress(MotionEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean onSingleTapUp(MotionEvent arg0) {
		// TODO Auto-generated method stub
		return false;
	}


    @Override 
    public boolean onTouchEvent(MotionEvent event){ 
        //mDetector.onTouchEvent(event);
		Values.newForceX = 0.5f;
        return gDetector.onTouchEvent(event);
    }
	

}

class MyGLSurfaceView extends GLSurfaceView {

    ActionStuff action = new ActionStuff();
    private final BSRenderer mRenderer;
    //GestureDetectorCompat mDetector;
    
    private GestureDetector gestureDetector;
    View.OnTouchListener gestureListener;

    public MyGLSurfaceView(Context context) {
        super(context);

        // Create an OpenGL ES 2.0 context.
        setEGLContextClientVersion(2);

       // mDetector = new GestureDetectorCompat(context, new MyGestureListener());

        // Gesture detection
//        gestureDetector = new GestureDetector(new MyGestureDetector());
//        gestureListener = new View.OnTouchListener() {
//            public boolean onTouch(View v, MotionEvent event) {
//                return gestureDetector.onTouchEvent(event);
//            }
//        };
        
        // Set the Renderer for drawing on the GLSurfaceView
        mRenderer = new BSRenderer(context);
        setRenderer(mRenderer);

        // Render the view only when there is a change in the drawing data
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//.RENDERMODE_WHEN_DIRTY);
    }

    private final float TOUCH_SCALE_FACTOR = 180.0f / 320;
    private float mPreviousX;
    private float mPreviousY;
    
    @Override 
    public boolean onTouchEvent(MotionEvent event){ 
        //mDetector.onTouchEvent(event);
		Values.newForceX = 0.5f;
//        return gDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }
}

//class MyGestureDetector extends GestureDetector.SimpleOnGestureListener {
//	
//    private static final int SWIPE_MIN_DISTANCE = 12;
//    private static final int SWIPE_MAX_OFF_PATH = 25;
//    private static final int SWIPE_THRESHOLD_VELOCITY = 20;
//    
//    //LessonOneRenderer randare = new LessonOneRenderer(context);
//
//    @Override
//    public boolean onDown(MotionEvent event) { 
////        Log.d(DEBUG_TAG,"onDown: " + event.toString()); 
//        return true;
//    }
//    
//    @Override
//    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) 
//    {
//    	String theText = "swiped";
////    	String theText = '\n' +  "      gravX: " + Float.toString(value.newForceX) + 
////				'\n' + "      gravY: " + Float.toString(value.newForceY);
//		Values.textToShow = theText;
//		
//		Values.newForceY = 0.5f;
//        try 
//        {
//            if (Math.abs(e1.getY() - e2.getY()) > SWIPE_MAX_OFF_PATH)
//            {
//            	return false;
//            }
//            // right to left swipe
//            if(e1.getX() - e2.getX() > SWIPE_MIN_DISTANCE && Math.abs(velocityX) > SWIPE_THRESHOLD_VELOCITY)
//            {
//            	Values.newForceX = -0.5f;
//                //Toast.makeText(SelectFilterActivity.this, "Left Swipe", Toast.LENGTH_SHORT).show();
//            }  
//            else 
//            	if (e2.getX() - e1.getX() > SWIPE_MIN_DISTANCE && Math.abs(velocityX) > SWIPE_THRESHOLD_VELOCITY)
//	            {
//            		Values.newForceX = 0.5f;
//	                //Toast.makeText(SelectFilterActivity.this, "Right Swipe", Toast.LENGTH_SHORT).show();
//	            }
//            	else
//            	{
//            		Values.newForceX = 0.f;
//            	}
//
//            // up to down swipe
//            if(e1.getY() - e2.getY() > SWIPE_MIN_DISTANCE && Math.abs(velocityY) > SWIPE_THRESHOLD_VELOCITY)
//            {
//            	Values.newForceY = -0.5f;
//                //Toast.makeText(SelectFilterActivity.this, "Left Swipe", Toast.LENGTH_SHORT).show();
//            }  
//            else 
//            	if (e2.getX() - e1.getX() > SWIPE_MIN_DISTANCE && Math.abs(velocityY) > SWIPE_THRESHOLD_VELOCITY)
//	            {
//            		Values.newForceY = 0.5f;
//	                //Toast.makeText(SelectFilterActivity.this, "Right Swipe", Toast.LENGTH_SHORT).show();
//	            }
//            	else
//            	{
//            		Values.newForceY = 0.f;
//            	}
//        } catch (Exception e) {
//            // nothing
//        }
//        return false;
//    }
//
//}
