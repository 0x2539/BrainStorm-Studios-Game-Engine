package com.example.brainstormstudiosgameengine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import org.jbox2d.common.Vec2;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.widget.TextView;

public class BSRenderer implements GLSurfaceView.Renderer {
	
    private static final String TAG = "MyGLRenderer";
    
    public volatile float newForceX = 0, newForceY = 0;
    
    ActionStuff action = new ActionStuff();
//	MainActivity mainAct = new MainActivity();
	public TextView tv1, tv2;
	
	public static float restartGoUpOrDown = 0;

    public final float[] mMVPMatrix = new float[16];
    public final float[] mProjMatrix = new float[16];
    public final float[] mVMatrix = new float[16];
    private final float[] mRotationMatrix = new float[16];

    // Declare as volatile because we are updating it from another thread
    public volatile float mAngle, GravityOnX = 0, GravityOnY = 0;
    
    public static Context context = null;
    
    public BSRenderer(Context context)
    {
    	if(this.context == null)
    	{
    		this.context = context;
    	}
    }


    @Override
    public void onDrawFrame(GL10 unused) 
    {
	    GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

		renderTheLoadingImage(0, 0);

//	    addTheMenus.renderAnyButtons(mMVPMatrix, mProjMatrix, mVMatrix, Values.currentMenu);
	    //ColidingBodies.moveThePlayer();
    	if(Values.obstacles.size() != 0)//Values.canRenderGameNow == true)
    	{	
    		if(!Values.hero.heroIsDead)
		    {
		    	action.update();
		    	DrawTheGame();
		    }
		    else
		    {
		    	DrawTheGame();
		    	DrawRestart();
		    }
		    DrawTheMenu();
    	}
		    
    	if(Values.canRenderGameNow == false)
    	{
            if(Values.obstacles.size() == 0)
    		{
            	SetUpClass.load(context);
    		}
    	}
    }

    
    public void DrawTheGame()
    {
		ColidingBodies.heroTouchesObjects();
    	ColidingBodies.moveThePlayer();
	    // Draw background color
	    
	//    float time = SystemClock.uptimeMillis() % 1000;

	    
	    Matrix.setLookAtM(mVMatrix, 0, 
	    		Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 2,    
	    		Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 0,     
	    		0f, 1.0f, 0.0f);

	    
	    
	    //1 si 2 muta camera odata cu jucatorul
	    
	    ///1***************************
        Matrix.translateM(mVMatrix, 0, Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 0);
        //******************************
	    Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	    
	    
	    // Draw square
//	    Values.hero.drawTheBody(mMVPMatrix);
	    Values.hero.render(mMVPMatrix, 0, 0);
	    
	    //heroBody.draw(mMVPMatrix, Values.hero.theBody.getAngle());
	    
	    for(int i = 0 ; i < Values.obstacles.size() ; i ++)
	    {
	    	Matrix.setLookAtM(mVMatrix, 0, 
	    			Values.obstacles.get(i).theBody.getPosition().x, Values.obstacles.get(i).theBody.getPosition().y, 2,    
	    			Values.obstacles.get(i).theBody.getPosition().x, Values.obstacles.get(i).theBody.getPosition().y, 0,     
	        		0f, 1.0f, 0.0f);
	        
	    	//2*******************************
	        Matrix.translateM(mVMatrix, 0, Values.hero.theBody.getPosition().x, 
	        								Values.hero.theBody.getPosition().y, 0);
	        //********************************
	
	        // Calculate the projection and view transformation
	        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	
	        // Draw square
//	        Matrix.translateM(m, mOffset, x, y, z)
//	        Matrix.translateM(mVMatrix, 0, Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 0);
//	        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	        
	        
//	        Values.obstacles.get(i).drawTheBody(mMVPMatrix);
//		    BSRenderVBOs.render(Values.obstacles.get(i), mMVPMatrix);
	        Values.obstacles.get(i).render(mMVPMatrix, 0, 0);
	        
		    
		    //walls[i].draw(mMVPMatrix, 0);
	    }
    }
    
    public void DrawTheMenu()
    {
    	if(Values.nrOfChapters > 1)
    	{
    		DrawMenuBackground();
			//renders level menu
	//		ChaptersAndLevelsMenu.renderMenuLevels(mMVPMatrix, mProjMatrix, mVMatrix, 
	//				(int) Values.chaptere[0].nrOfLevels, Values.chaptere[0].levelFromChapter);
    		
			//renders chapters
			ChaptersAndLevelsMenu.renderMenuChapters(mMVPMatrix, mProjMatrix, mVMatrix);
	
			//renders buttons
	//    	BSMenus.renderAnyButtons(mMVPMatrix, mProjMatrix, mVMatrix, Values.currentMenu);
    	}
    }
    
    
    public void DrawMenuBackground()
    {
		//Rnder The Background with an alpha black
		float[] theColorToRender = { 1.f, 1.f, 1.f, 0.9f };
		BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix, 
				//Values.SCREEN_WIDTH / 2 / Values.scaleSize + Values.MenuCoordinateX,
				//Values.SCREEN_HEIGHT / 2 / Values.scaleSize + Values.MenuCoordinateY,
				-Values.hero.theBody.getPosition().x,
				-Values.hero.theBody.getPosition().y,
				Values.currentMenu.textureOfMenu[0], theColorToRender, 
				Values.transparentMenuBlock.vbo, Values.iboNormal, 0, 0);
    }
    
    
    public void DrawTheNextLevelScene()
    {
    	
    }
    
    public void DrawDeadScene()
    {
    	
    }
    
    public void DrawRestart()
    {
	    Matrix.setLookAtM(mVMatrix, 0, 
	    		0, 0, 2,    
	    		0, 0, 0,     
	    		0f, 1.0f, 0.0f);
	    
	 
	    Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	    
	    if(restartGoUpOrDown == 1 && Values.sinusRestart < 90)
	    {
	    	Values.sinusRestart ++;
	    	float newColor[] = { 0.0f, 0.0f, 0.0f, (float)Math.sin(Math.toRadians(Values.sinusRestart))};
	    	Values.onlyTexturesBodies.get(0).colorOfBody = newColor;
	    	
	    	if(Values.sinusRestart >= 90)
	    	{
	    		Values.hero.theBody.setTransform(new Vec2(0, 0), 0);
		    	
	    		float newColor2[] = { 1.0f, 1.0f, 1.0f, 1.0f};
		    	Values.hero.colorOfBody = newColor2;
		    	
	    		restartGoUpOrDown = -1;
	    		Values.sinusRestart = 90;
	    	}
	    }
	    else
	    	if(restartGoUpOrDown == -1  && Values.sinusRestart > 0)
		    {
		    	Values.sinusRestart --;
		    	float newColor[] = { 0.0f, 0.0f, 0.0f, (float)Math.sin(Math.toRadians(Values.sinusRestart))};
		    	Values.onlyTexturesBodies.get(0).colorOfBody = newColor;
		    	
		    	if(Values.sinusRestart <= 0)
		    	{
		    		Values.hero.theBody.applyLinearImpulse(new Vec2(0, 0.1f), Values.hero.theBody.getWorldCenter());
		    		Values.hero.heroIsDead = false;
		    		Values.hero.heroWasDead = false;
		    		
		    		Values.sinusRestart = 0;
		    	}
		    }

	    
	    // Draw square
	    Values.onlyTexturesBodies.get(0).render(mMVPMatrix, 0, 0);
    }
    

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) 
    {
        // Set the background frame color
        GLES20.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        
        BSTexturedPolygonProgram2D.setShaders();

//        SetUpClass.setTheNormalIbo();
//        loadTheLoadingImage();
//	    GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
	    
//	    this.onDrawFrame(unused);
//	    MainActivity.mGLSurfaceView.requestRender();
//		XMLReader.overWriteSDFile("a1.txt", String.valueOf(Calendar.getInstance().getTime().getSeconds()));
//		SoundClass s = new SoundClass();
//		s.loadSound();
    }

    @Override
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        // Adjust the viewport based on geometry changes,
        // such as screen rotation
    	
        GLES20.glViewport(0, 0, width, height);
        
        Values.SCREEN_WIDTH = width;
        Values.SCREEN_HEIGHT = height;
        Values.scaleSize = 8;
        		Values.CameraExtremeLeft = Values.SCREEN_WIDTH / 2 / Values.scaleSize;
        		Values.CameraExtremeRight = Values.SCREEN_WIDTH / 2 / Values.scaleSize + 2000 / Values.scaleSize;
				Values.CameraExtremeUp = Values.SCREEN_HEIGHT / 2 / Values.scaleSize + 230 / Values.scaleSize;
				Values.CameraExtremeDown =  Values.SCREEN_HEIGHT / 2 / Values.scaleSize;
				Values.MenuCoordinateX = 0;//Values.SCREEN_WIDTH / 2 / Values.scaleSize;
				Values.MenuCoordinateY = 0;//Values.SCREEN_HEIGHT / 2 / Values.scaleSize;

        float ratio = (float) width / height;
        
        ratio *= Values.scaleSize;
        
        Values.changedScreenHeight = 2 * Values.scaleSize;
        Values.changedScreenWidth = 2 * ratio;

        // this projection matrix is applied to object coordinates
        // in the onDrawFrame() method
        //Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 3, 7);
//        Matrix.frustumM(m, offset, left, right, bottom, top, near, far)
        Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -Values.scaleSize, Values.scaleSize, 2, 7);
        //Matrix.frustumM(mProjMatrix, 0, 0, width, 0, height, 2, 7);

        SetUpClass.setTheNormalIbo();
        loadTheLoadingImage();
//        SetUpClass.setTheNormalIbo();
////	    GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
//	    
//        loadTheLoadingImage();
//	    this.onDrawFrame(unused);
//	    MainActivity.mGLSurfaceView.requestRender();

//		XMLReader.overWriteSDFile("a2.txt", String.valueOf(Calendar.getInstance().getTime().getSeconds()));
        
        
        if(Values.obstacles.size() == 0)
		{
//        	SetUpClass.load(context);
//        	List<String> listOfNodes = new ArrayList<String>();
//			List<String> listOfAttr = new ArrayList<String>();
//			listOfNodes.add("xCoordinate");
//			listOfNodes.add("yCoordinate");
//			listOfNodes.add("width");
//			listOfNodes.add("height");
//			listOfNodes.add("userName");
//			
//			XMLReader.readAnyXML(context, "xmlfile.xml", listOfNodes, listOfAttr, "Level", "obstacle");
//			addTheMenus.addTheMenus(context);
		}
        
    }

    
    public void loadTheLoadingImage()
    {
    	Values.theLoadingImage = new BSTheSquareBodies();
    	
//    	ActionStuff.createSquareBody(Values.theLoadingImage, BodyType.STATIC, 0, 0, 1, 1, 1, 1, 0,
//    			"qwe", Values.world, R.raw.smbloading);
		
    	ActionStuff.createTextureBody(Values.theLoadingImage, 0, 0, 
				Values.changedScreenWidth, Values.changedScreenHeight, 1, 1, 0, "asd", R.raw.smbloading);
    }
    
    
    float loadImageCosValue = 0;
    public void renderTheLoadingImage(float xCord, float yCord)
    {
    	if(loadImageCosValue < 90)
    	{
    		loadImageCosValue += 0.5f;
    	}
    	else
    	{
    		Values.canRenderGameNow = true;
    		return;
    	}
    	
    	Values.theLoadingImage.colorOfBody[3] = (float) Math.cos(Math.toRadians(loadImageCosValue));
    	
    	
    	/*Matrix.setLookAtM(mVMatrix, 0, 
	    		Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 2,    
	    		Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 0,     
	    		0f, 1.0f, 0.0f);

	    
	    
	    //1 si 2 muta camera odata cu jucatorul
	    
	    ///1***************************
        Matrix.translateM(mVMatrix, 0, Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 0);
        //******************************
	    Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	    */
	    
	    // Draw square
//	    Values.hero.drawTheBody(mMVPMatrix);
//	    Values.hero.render(mMVPMatrix, 0, 0);
    	Matrix.setLookAtM(mVMatrix, 0, 
    			xCord, yCord, 2,    
    			xCord, yCord, 0,     
	    		0f, 1.0f, 0.0f);

	    
        Matrix.translateM(mVMatrix, 0, xCord, yCord, 0);
	    Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
	    Values.theLoadingImage.render(mMVPMatrix, 0, 0);
    }
    
    
    
    
    public static int loadShader(int type, String shaderCode)
    
    {

        // create a vertex shader type (GLES20.GL_VERTEX_SHADER)
        // or a fragment shader type (GLES20.GL_FRAGMENT_SHADER)
        int shader = GLES20.glCreateShader(type);

        // add the source code to the shader and compile it
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);

        return shader;
    }
    
    
    

}


class BSTexturedPolygonProgram2D
{
    public static void setShaders()
    {
    	// enable face culling feature
    	GLES20.glEnable(GLES20.GL_CULL_FACE);
    	// specify which faces to not draw
    	GLES20.glCullFace(GLES20.GL_BACK);
    	
    	GLES20.glBlendFunc(GLES20.GL_ONE, GLES20.GL_ONE_MINUS_SRC_ALPHA);
    	GLES20.glEnable(GLES20.GL_BLEND);
    	
    	// create empty OpenGL Program
        Values.mProgram = GLES20.glCreateProgram(); 

    	final String vertexShaderCode = 
    		RawResourceReader.readTextFileFromRawResource(BSRenderer.context, R.raw.vertexshader);
        final String fragmentShaderCode =
    		RawResourceReader.readTextFileFromRawResource(BSRenderer.context, R.raw.fragmentshader);

        // prepare shaders and OpenGL program
        final int vertexShader = BSRenderer.loadShader(GLES20.GL_VERTEX_SHADER,
                                                   vertexShaderCode);
        final int fragmentShader = BSRenderer.loadShader(GLES20.GL_FRAGMENT_SHADER,
                                                     fragmentShaderCode);
        
    	// add the vertex shader to program
        GLES20.glAttachShader(Values.mProgram, vertexShader);
        // add the fragment shader to program
        GLES20.glAttachShader(Values.mProgram, fragmentShader);
        
//        GLES20.glBindAttribLocation(Values.mProgram, 0, "vPosition");
//        GLES20.glBindAttribLocation(Values.mProgram, 0, "TexCoordinate");
//        GLES20.glBindAttribLocation(mProgramId, Shader.VERTEX_POS, "position");
        
        // create OpenGL program executables
        GLES20.glLinkProgram(Values.mProgram);
        

        Values.mPositionHandle = GLES20.glGetAttribLocation(Values.mProgram, "vPosition"); //1
        Values.mTextureCoordinateHandle = GLES20.glGetAttribLocation(Values.mProgram, "TexCoordinate");//0
        Values.mTheActualTexture = GLES20.glGetUniformLocation(Values.mProgram, "theActualTexture");//3
        Values.ShaderAngle = GLES20.glGetUniformLocation(Values.mProgram, "RotationAngle");//0
        Values.mColorHandle = GLES20.glGetUniformLocation(Values.mProgram, "vColor");//2
        Values.ScaleOnX = GLES20.glGetUniformLocation(Values.mProgram, "ScaleOnX");//2
        Values.ScaleOnY = GLES20.glGetUniformLocation(Values.mProgram, "ScaleOnY");//2

//        Values.mColorHandle = GLES20.glGetAttribLocation(Values.mProgram, "colorCoordinate");//2
        
        Values.mMVPMatrixHandle = GLES20.glGetUniformLocation(Values.mProgram, "uMVPMatrix");//1
        
        GLES20.glUseProgram(Values.mProgram);
        String message = Values.mPositionHandle + "\n" + Values.mTextureCoordinateHandle + '\n' +
        					Values.mTheActualTexture + "\n" + Values.mColorHandle + '\n' +
        					Values.ScaleOnX + " " + Values.ScaleOnY;
        XMLReader.overWriteSDFile("shader det.txt", message);
//    	//This will get the SD Card directory and create a folder named MyFiles in it.
//    	File sdCard = Environment.getExternalStorageDirectory();
//    	File directory = new File (sdCard.getAbsolutePath() + "/Bs Studios Files");
//    	directory.mkdirs();
//
//    	//Now create the file in the above directory and write the contents into it
//    	File file = new File(directory, "Loaded Shaders.txt");
//    	FileOutputStream fOut = null;
//		try 
//		{
//			fOut = new FileOutputStream(file);
//		} 
//		catch (FileNotFoundException e) 
//		{
//			e.printStackTrace();
//		}
//    	OutputStreamWriter osw = new OutputStreamWriter(fOut);
//    	try 
//    	{
//			osw.write(Float.toString(Values.mPositionHandle) + '\n' +
//					Float.toString(Values.mTextureCoordinateHandle) + '\n' +
//					Float.toString(Values.mTheActualTexture) + '\n' +
//					Float.toString(Values.ShaderAngle) + '\n' +
//					Float.toString(Values.mColorHandle) + '\n' +
//					Float.toString(Values.mMVPMatrixHandle));
//			
//	    	osw.flush();
//	    	osw.close();
//		} 
//    	catch (IOException e) 
//    	{
//			e.printStackTrace();
//		}
    }
}




