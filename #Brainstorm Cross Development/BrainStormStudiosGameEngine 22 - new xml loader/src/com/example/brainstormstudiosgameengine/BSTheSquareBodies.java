package com.example.brainstormstudiosgameengine;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;
import java.util.List;

import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.BodyType;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.os.Environment;

public class BSTheSquareBodies
{
	Body theBody = null;
	float widthOfBody = 0, heightOfBody = 0, xCord = 0, yCord = 0;
	float colorOfBody[] = {1.0f, 1.0f, 1.0f, 1.0f};
	boolean isDestroyed = false, canKillHero = false, isNextLevel = false, heroWasDead = false, heroIsDead = false;
	FloatBuffer vertexBuffer, TextureCoordinateBuffer;
	BodyType typeOfBody;
	int[] textureOfBody = new int[1];
	String nameOfTheTexture = "";

	public int[] vbo = new int[1];

	public void setUpForShaders(float width, float height)
	{
		try
		{
	        float squareCoords[] = {
	        		-width / 2.f - 0.015f / 2.f,  height / 2.f + 0.015f / 2.f, 0.0f,	// top left
		            -width / 2.f - 0.015f / 2.f, -height / 2.f - 0.015f / 2.f, 0.0f,	// bottom left
		             width / 2.f + 0.015f / 2.f, -height / 2.f - 0.015f / 2.f, 0.0f,	// bottom right
		             width / 2.f + 0.015f / 2.f,  height / 2.f + 0.015f / 2.f, 0.0f};	// bottom right
	        ByteBuffer bb = ByteBuffer.allocateDirect((squareCoords.length + Values.TextureCoords.length) * 4); // (# of coordinate values * 4 bytes per float)
	        bb.order(ByteOrder.nativeOrder());
	        vertexBuffer = bb.asFloatBuffer();
	        vertexBuffer.put(squareCoords);
	        vertexBuffer.put(Values.TextureCoords);
	        vertexBuffer.position(0);


	        // initialize byte buffer for the draw list
//	        ByteBuffer dlb = ByteBuffer.allocateDirect(
//	        // (# of coordinate values * 2 bytes per short)
//	        		Values.drawOrder.length * 2);
//	        dlb.order(ByteOrder.nativeOrder());
//	        drawListBuffer = dlb.asShortBuffer();
//	        drawListBuffer.put(Values.drawOrder);
//	        drawListBuffer.position(0);


			GLES20.glGenBuffers(1, vbo, 0);
//			GLES20.glGenBuffers(1, ibo, 0);

			if (vbo[0] > 0 && Values.iboNormal[0] > 0) {
				GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);
				GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, vertexBuffer.capacity() * Values.BYTES_PER_FLOAT,
						vertexBuffer, GLES20.GL_DYNAMIC_DRAW);


//				GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
//				GLES20.glBufferData(GLES20.GL_ELEMENT_ARRAY_BUFFER, drawListBuffer.capacity()
//						* Values.BYTES_PER_SHORT, drawListBuffer, GLES20.GL_DYNAMIC_DRAW);

				GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
				GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			else
			{
				XMLReader.overWriteSDFile("vbos.txt", "eroarea aici");
			}
		}
		catch (Throwable t)
		{
		}
	}

	public void render(float[] mMVPMatrix, float xScale, float yScale)
	{
		if (vbo[0] > 0 && Values.iboNormal[0] > 0)
		{
			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);

			GLES20.glEnableVertexAttribArray(Values.mPositionHandle);
	        GLES20.glVertexAttribPointer(Values.mPositionHandle, Values.COORDS_PER_VERTEX,
                    GLES20.GL_FLOAT, false,
                    Values.vertexStride, 0);

			GLES20.glEnableVertexAttribArray(Values.mTextureCoordinateHandle);
			GLES20.glVertexAttribPointer(Values.mTextureCoordinateHandle, Values.COORDS_PER_VERTEX_TEXTURE,
					GLES20.GL_FLOAT, false,
					Values.textureStride, 12 * 4);


	        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureOfBody[0]);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);
	        GLES20.glUniform1i(Values.mTheActualTexture, 0);

	        GLES20.glUniform1f(Values.ShaderAngle, 0);//theBody.getAngle());



	        GLES20.glUniform1f(Values.ScaleOnX, xScale);//theBody.getAngle());
	        GLES20.glUniform1f(Values.ScaleOnY, yScale);//theBody.getAngle());



	        // Set color for drawing the triangle
	        if(canKillHero)
	        {
	        	float newColorOfBody[] = {3.0f, 0.0f, 0.0f, 1.0f};
	        	//colorOfBody = {1.0f, 0.0f, 0.0f, 1.0f};
	        	GLES20.glUniform4fv(Values.mColorHandle, 1, newColorOfBody, 0);
	        }
	        else
	            if(canKillHero)
		        {
	            	float newColorOfBody[] = {0.0f, 3.0f, 0.0f, 1.0f};
		        	GLES20.glUniform4fv(Values.mColorHandle, 1, newColorOfBody, 0);
		        }
	            else
	            {
		        	GLES20.glUniform4fv(Values.mColorHandle, 1, colorOfBody, 0);
	            }

	        // Apply the projection and view transformation
	        GLES20.glUniformMatrix4fv(Values.mMVPMatrixHandle, 1, false, mMVPMatrix, 0);

	        // Draw the square
			GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, Values.iboNormal[0]);
			GLES20.glDrawElements(GLES20.GL_TRIANGLE_FAN, 4, GLES20.GL_UNSIGNED_SHORT, 0);

			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
			GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, 0);

	        // Disable vertex array
	        GLES20.glDisableVertexAttribArray(Values.mTextureCoordinateHandle);
	        GLES20.glDisableVertexAttribArray(Values.mPositionHandle);

		}
		else
		{
			XMLReader.overWriteSDFile("vbos.txt", "eroarea aici");
		}
	}


}

class BSButtonStructure
{
	float widthOfButton = 0, heightOfButton = 0, xCord, yCord;
	float colorOfButton[] = {1.0f, 1.0f, 1.0f, 1.0f};
	FloatBuffer vertexBuffer, TextureCoordinateBuffer;

	float NextMenuIndex = 0, indexOfButton = 0;
	boolean isSelected = false;

	int[] textureOfButton = new int[1];
	String nameOfTheTexture = "";

	public int[] vbo = new int[1];
	public int[] textureOfButtons = new int[2];

}

class BSMenuStructure
{
	float widthOfBody = 0, heightOfBody = 0;
	float colorOfBody[] = {1.0f, 1.0f, 1.0f, 1.0f};
	FloatBuffer vertexBuffer, TextureCoordinateBuffer;
	BodyType typeOfBody;

	int indexOfMenu = 0, numberOfButtons = 0, MenuIndex = 0;
	List<BSButtonStructure> listOfButtons = new ArrayList<BSButtonStructure>();


	short drawOrder[] = { 0, 1, 2, 3 }; // order to draw vertices
	float color[] = { 1, 1, 1, 1 };

	public String nameOfTheTexture = "";
	public String nameOfTheMenu = "";

	public int[] vbo = new int[1];
	public int[] textureOfMenu = new int[1];


}


class LevelChooserPlayerTexture
{
    public int[] texture = new int[1];
    public float[] color = {1, 1, 1, 1};
    public float xCord = 0, yCord = 0, width = 0, height = 0;
    public int indexOfMenuThatItIsOn = 0, indexOfChapterThatItIsOn = 0;
    public int isMovingLeftRight = 0, isMovingUpDown = 0;
    public int canMove = 0, justFinished = 0;

    public int[] vbo = new int[1];
}

class ChapterStructure
{
	public LevelsFromChapterStructure[] levelFromChapter = new LevelsFromChapterStructure[100];
	public float isFinishedChapter, isAvailableChapter;
	public float nrOfLevels;
	public float xCord, yCord, width, height;
	public String nameOfTheChapter;
	public float[] colorOfTheChapter;
	public int[] textureOfTheChapter = new int[1];

	public int vbo[] = new int[1];
}

class LevelsFromChapterStructure
{
	public int isCurrent, canPlayIt, isFinished;

    public float indexOfLevel;
    public String nameOfTheTexture = "";

    public int[] textureOfLevel = new int[1];
	public int[] textureOfConnectionLeftRight = new int[1];
	public int[] textureOfConnectionUpDown = new int[1];
	public int[] textureOfFinishedLevel = new int[1];

    public int textureOfConnectionLeftRightChapter, textureOfConnectionUpDownChapter, textureOfFinishedLevelChapter;

    public float lengthXConnectionLevel, lengthYConnectionLevel, lengthXConnectionChapter, lengthYConnectionChapter;

    public int[] vboOfLevel = new int[1];
    public int[] vboOfLeftRightLevel = new int[1];
    public int[] vboOfUpDownLevel = new int[1];
    public int[] vboOfFinishedLevel = new int[1];

    public int[] vboOfLeftRightChapter = new int[1];
    public int[] vboOfUpDownChapter = new int[1];
    public int[] vboOfFinishedChapter = new int[1];


    public float[] colorOfLevel;
    public float xCord, yCord, width, height;

}


class BSAnimation
{
	public int[] theTexture = new int[1];
	public int[] vbo = new int[1];
    String nameOfTheAnimation;

    float xCord, yCord, widthOfAnimation, heightOfAnimation;
//    BSTexturedVertex2D dataOfAnimation[4];

    BSTheSquareBodies theSquareBodyBinded;
//    BSTheRoundBodies theRoundBodyBinded;

    boolean canAnimate;
    ///Vad care instanta o randez //de ex, pot avea 2 animatii pentru acelasi corp, animatie cand merge la dreapta sau la stanga
    int animationIndex, animationNR;//animationNR - nr animatiei
    int indexOfAnimation;

    float timeUntilNext;//timpul cat dureaza animatia
    float timeToShow;//timpul in care trece la urmatoarea
    int nrOfAnimations;
    float[] colorOfAnimation = {1, 1, 1, 1};

	//int theCurrentIndexOfAnimation;

    boolean itPlayedThisAnimation;
}

class BSMenus
{

	public static void addTheMenus(Context context)
	{
		///SoundButton inits
		setTheAudioSettingsAnimation();


		String menusDetails = getRawFileAsString(context, "Menus/menus details.txt");


		float nrMeniuri = 0, nrButtons;
		String namesOfMenus = "";

		String[] theFile = menusDetails.split("[ \n]");
		int k = 0;//va retine numarul curent al cuvantului citit din fisier

		nrMeniuri = Float.parseFloat(theFile[k]);
		k++;


		for(int i = 0 ; i < nrMeniuri ; i++)
		{
			BSMenuStructure newMenu = new BSMenuStructure();

			newMenu.MenuIndex = (int) Float.parseFloat(theFile[k]);
			k++;

			namesOfMenus = theFile[k];
			newMenu.nameOfTheMenu = namesOfMenus;
			k++;

			nrButtons = Float.parseFloat(theFile[k]);
			k++;

			newMenu.numberOfButtons = (int) nrButtons;
			newMenu.indexOfMenu = i;

			if(i == 0)
			{
				newMenu.textureOfMenu[0] = getImageFromAssets(context, "Menus/first.png");
			}

			float width, height, xCord = 0, yCord = 0, lastH = 0;
			for(int j = 0 ; j < nrButtons ; j++)
			{
				BSButtonStructure newButton = new BSButtonStructure();

				width = Float.parseFloat(theFile[k]);
				k++;
				height = Float.parseFloat(theFile[k]);
				k++;
				newButton.NextMenuIndex = Float.parseFloat(theFile[k]);
				k++;

				float multiply = 2;

				newButton.indexOfButton = j;
				newButton.widthOfButton = width * multiply;
				newButton.heightOfButton = height * multiply;
				width = width / 2 * multiply;
				height = height / 2 * multiply;

				float[] colorNow = {1, 1, 1, 1};
				newButton.colorOfButton = colorNow;

				///Dau coordonatele primului buton
				if(j == 0)
				{
					xCord = Values.changedScreenWidth / 2;
					yCord = Values.changedScreenHeight / 2;
					lastH = height * 2;
				}
				else
				{
					///Setez pozitia urmatorului buton, in functie de cel de dinainte
					float theHeight = lastH + 0.3f;
					yCord -= theHeight;
					lastH = height * 2;
				}

				newButton.xCord = xCord;
				newButton.yCord = yCord;

				String nameForTexture = "Button images/New Buttons/" + namesOfMenus +
											 "/The Unnamed Buttons/picture" + String.valueOf(j) + ".png";



				newButton.textureOfButtons[0] = getImageFromAssets(context, nameForTexture);





				///Set the data for the menu buttons
				BSRenderClassFunctions.setTheVBO(newButton.widthOfButton, newButton.heightOfButton, newButton.vbo);

				newMenu.listOfButtons.add(newButton);

				if(i == 0 && j == 0)
				{
					Values.currentMenu = newMenu;
					Values.currentButton = newButton;
				}
			}

			Values.listOfMenus.add(newMenu);
		}

//		String message = "";
//
//		for(int i = 0 ; i < Values.listOfMenus.size(); i++)
//		{
//			message += Values.listOfMenus.get(i).nameOfTheMenu + ": ";
//			for(int j = 0 ; j < Values.listOfMenus.get(i).listOfButtons.size(); j++)
//			{
//				message += Values.listOfMenus.get(i).listOfButtons.get(j).indexOfButton + "; ";
//			}
//			message += '\n';
//		}
//
//		XMLReaderNew.overWriteSDFile("menuText.txt", message);

	}


	public static void setTheAudioSettingsAnimation()
	{
		Values.SoundButtonTexture = new BSAnimation();
		Values.SoundButtonTexture.widthOfAnimation = Values.hero.widthOfBody;
		Values.SoundButtonTexture.heightOfAnimation = Values.hero.heightOfBody;
		BSRenderClassFunctions.setTheVBO(Values.hero.widthOfBody, Values.hero.heightOfBody, Values.SoundButtonTexture.vbo);
		Values.SoundButtonTexture.theTexture[0] = Values.hero.textureOfBody[0];
		Values.SoundButtonTexture.colorOfAnimation = new float[] { 1.f, 1.f, 1.f, 1.f };
		Values.SoundButtonTexture.xCord = Values.changedScreenWidth / 2;
		Values.SoundButtonTexture.yCord = Values.changedScreenHeight / 2;
	}


	public static void addTheLevelMenu(Context context)
	{

	}





	public static String getRawFileAsString(Context context, String Path)
	{
		return XMLReaderNew.getXml(Path, context);
	}

	public static int getImageFromAssets(Context context, String Path)
	{
		InputStream bitmapStream = null;
		final int[] textureHandle = new int[1];

		GLES20.glGenTextures(1, textureHandle, 0);

		if (textureHandle[0] != 0)
		{
			try
			{
				// Read in the resource
				bitmapStream = context.getAssets().open(Path);
				final Bitmap bitmap = BitmapFactory.decodeStream(bitmapStream);

				// Bind to the texture in OpenGL
				GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureHandle[0]);

				// Set filtering
				GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
				GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);

				// Load the bitmap into the bound texture.
				GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);

				// Recycle the bitmap, since its data has been loaded into OpenGL.
				bitmap.recycle();
			}
			catch (IOException e)
			{
		    	File sdCard = Environment.getExternalStorageDirectory();

		    	String already = "";
		    	already = XMLReaderNew.getXml(sdCard.getAbsolutePath() + "/Bs Studios Files/failedTextures.txt", context);

		    	already += Path + '\n';
		    	XMLReader.overWriteSDFile("failedTextures.txt", already);

			    e.printStackTrace();
			}
			finally
			{
			    if(bitmapStream != null)
			    {
			    	try
			    	{
						bitmapStream.close();
					}
			    	catch (IOException e)
			    	{
						e.printStackTrace();
					}
			    }
			}
		}

		if (textureHandle[0] == 0)
		{
			throw new RuntimeException("Error loading texture.");
		}



		return textureHandle[0];
	}



	public static void renderAnyButtons(float[] mMVPMatrix, float[] mProjMatrix, float[] mVMatrix, BSMenuStructure theMenu)
	{
//		setTheValuesForShaders();


		for(int i = 0 ; i < theMenu.listOfButtons.size(); i++)
		{
			if(theMenu.listOfButtons.get(i) == Values.currentButton)
			{
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
										Values.currentButton.xCord + Values.MenuCoordinateX,
										Values.currentButton.yCord + Values.MenuCoordinateY,
										Values.currentButton.textureOfButtons[0],
										Values.currentButton.colorOfButton,
										Values.currentButton.vbo, Values.iboNormal, 0.1f, 0.1f);
			}
			else
			{
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
						theMenu.listOfButtons.get(i).xCord + Values.MenuCoordinateX,
						theMenu.listOfButtons.get(i).yCord + Values.MenuCoordinateY,
						theMenu.listOfButtons.get(i).textureOfButtons[0],
						theMenu.listOfButtons.get(i).colorOfButton,
						theMenu.listOfButtons.get(i).vbo, Values.iboNormal, 0, 0);
			}

			if(Values.currentMenu.indexOfMenu == 2)
			{
				for(int j = 0 ; j < theMenu.listOfButtons.size(); j++)
				{
					if(theMenu.listOfButtons.get(j).indexOfButton == 0)
					{
						renderSoundAnimation(mMVPMatrix, mProjMatrix, mVMatrix, theMenu.listOfButtons.get(j).yCord, Values.newVolumeAudio);
					}
					else
						if(theMenu.listOfButtons.get(j).indexOfButton == 1)
						{
							renderSoundAnimation(mMVPMatrix, mProjMatrix, mVMatrix, theMenu.listOfButtons.get(j).yCord, Values.newVolumeSFX);
						}
						else
						{
							break;
						}
				}
			}
		}

	}


	public static void renderSoundAnimation(float[] mMVPMatrix, float[] mProjMatrix, float[] mVMatrix, float yCord, float theVolume)
	{
//		setTheValuesForShaders();

		for(int i = 0 ; i < theVolume * 10 ; i++)
		{
			BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
					Values.SoundButtonTexture.xCord + Values.MenuCoordinateX + Values.hero.widthOfBody * i + 1 + 0.25f * i - 4,
					yCord + Values.MenuCoordinateY,
					Values.SoundButtonTexture.theTexture[0], Values.SoundButtonTexture.colorOfAnimation,
					Values.SoundButtonTexture.vbo, Values.iboNormal, 0, 0);
		}
	}

}

class MyThread implements Runnable
{
	String name;
	Context cont;
	int index;
	BSXmlStruct node;
	Thread runner;

	MyThread(Context context, int i, BSXmlStruct headNode, String nameOfChapter)
	{
		cont = context;
		index = i;
		node = headNode;
		name = nameOfChapter;
//		start();
		runner = new Thread(this, nameOfChapter);
		runner.start();
	}

	public void run()
	{
		ChaptersAndLevelsMenu.loadTheGivenChapter(cont, index, node, name);
	}
}

class ChaptersAndLevelsMenu
{

	public static void loadLevels(Context context, String chapterName, LevelsFromChapterStructure[] theLevelsToAdd,
			int nrOfLevels, int chapterIndex)
	{
		List<String> listOfNodes = new ArrayList<String>();
		List<String> listOfAttr = new ArrayList<String>();
		listOfNodes.add("Level_index");
		listOfNodes.add("Level_texture_name");

		listOfAttr.add("nr");

		BSXmlStruct headNode = XMLReaderNew.readAnyXML(context, "The Levels/playerDetails" + String.valueOf((int)chapterIndex + 1) + ".xml",
				listOfNodes, listOfAttr, "Chapter_of_level", "Level_details");

	 
	    int i = 0;

	    while(i < nrOfLevels)
	    {
	        String nameOfTheTexture = "";
	        theLevelsToAdd[i] = new LevelsFromChapterStructure();
	        theLevelsToAdd[i].indexOfLevel = Float.parseFloat(
	        		headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(0).nodeValue);
		    theLevelsToAdd[i].width = Values.hero.widthOfBody;// + 0.15;
	        theLevelsToAdd[i].height = Values.hero.heightOfBody;// + 0.15;

		    chapterName = "Chapter" + headNode.headNodeAttributes.get(0).attributeValue;


	        ///Incarc texturile de conexiune intre theLevelsToAdd,
	        //doar pentru primul nivel, ca sa nu incarc memoria ram
	        /*if(i == 0)
	        {
	            String name1 = "Menu Of Levels/" + chapterName + "/connectionLeftRight.png",
	                        name2 = "Menu Of Levels/" + chapterName + "/connectionUpDown.png",
	                        name3 = "Menu Of Levels/" + chapterName + "/levelFinished.png";
			    XMLReaderNew.overWriteSDFile("thread errorsA.txt", "4.7 " + i);

	            theLevelsToAdd[0].textureOfConnectionLeftRight[0] = BSMenus.getImageFromAssets(context, name1);
			    XMLReaderNew.overWriteSDFile("thread errorsA.txt", "4.8 " + i);
	            theLevelsToAdd[0].textureOfConnectionUpDown[0] = BSMenus.getImageFromAssets(context, name2);
			    XMLReaderNew.overWriteSDFile("thread errorsA.txt", "4.9 " + i);
	            theLevelsToAdd[0].textureOfFinishedLevel[0] = BSMenus.getImageFromAssets(context, name3);
	        }*/


	        float spaceBetweenLevels = 2.20f;
	        ///Pozitionez nivelul
	        if(i % 5 == 0)
	        {
	            ///Il pun cat mai la stanga
	            theLevelsToAdd[i].xCord = Values.changedScreenWidth / 2 - 2 *
	            		(theLevelsToAdd[i].width + spaceBetweenLevels);//2;

	            ///Verifc daca este pe primul rand sau nu
	            if(i > 0)
	            {
	                theLevelsToAdd[i].yCord = theLevelsToAdd[i - 1].yCord -
	                		theLevelsToAdd[i].height - spaceBetweenLevels;
	            }
	            else
	                ///Daca este primul nivel
	            {
	                theLevelsToAdd[i].yCord = Values.changedScreenHeight / 2 + 2 *
	                		(theLevelsToAdd[i].height + spaceBetweenLevels);//SCREEN_HEIGHT / scaleSize - 2;
	            }
	        }
	        else
	        {
	            theLevelsToAdd[i].xCord = theLevelsToAdd[i-1].xCord + theLevelsToAdd[i].width + spaceBetweenLevels;
	            theLevelsToAdd[i].yCord = theLevelsToAdd[i-1].yCord;
	        }

			theLevelsToAdd[i].isFinished = 0;///atof(levelDetails[k].theCharArray2D[2]);
			theLevelsToAdd[i].canPlayIt = 0;///atof(levelDetails[k].theCharArray2D[3]);
			nameOfTheTexture = headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(1).nodeValue;
			theLevelsToAdd[i].nameOfTheTexture = nameOfTheTexture;


	        ///Daca e terminat nivelul atunci il fac mai luminos(pe else)
	        if(theLevelsToAdd[i].canPlayIt == 0)
	        {
	        	float[] newColor = {0.5f, 0.5f, 0.5f, 1.f};
	            theLevelsToAdd[i].colorOfLevel = newColor;
	        }
	        else
	        {
	        	float[] newColor = {1.f, 1.f, 1.f, 1.f};
	            theLevelsToAdd[i].colorOfLevel = newColor;
	        }

		    /*String newText = "Menu Of Levels/" + chapterName +"/The Levels textures/" + nameOfTheTexture;

	        theLevelsToAdd[i].textureOfLevel[0] = BSMenus.getImageFromAssets(context, newText);*/




	        BSRenderClassFunctions.setTheVBO(Values.chaptere[(int) chapterIndex].levelFromChapter[i].width,
								Values.chaptere[(int) chapterIndex].levelFromChapter[i].height,
								Values.chaptere[(int) chapterIndex].levelFromChapter[i].vboOfLevel);


	        i++;
	    }

	    Values.levelChoserPlayer.xCord = theLevelsToAdd[0].xCord;
	    Values.levelChoserPlayer.yCord = theLevelsToAdd[0].yCord;
	}

	public static void loadChapters(final Context context)
	{
		Values.levelChoserPlayer = new LevelChooserPlayerTexture();

	    ///Set the animation of the texture that i am going to use to select the level i want to play
	    Values.levelChoserPlayer.width = Values.hero.widthOfBody - 0.2f;
	    Values.levelChoserPlayer.height = Values.hero.heightOfBody - 0.2f;
	    float[] colorNew = {1.f, 1.f, 1.f, 1.f};
	    Values.levelChoserPlayer.color = colorNew;
	    Values.levelChoserPlayer.indexOfMenuThatItIsOn = 0;
	    Values.levelChoserPlayer.canMove = 1;

	    /*String levelChooserTextureNameString = "Menu Of Levels/Chapter1/playerTextureLevelChooser.png";

	    Values.levelChoserPlayer.texture[0] = BSMenus.getImageFromAssets(context, levelChooserTextureNameString);
*/
	    Values.levelChoserPlayer.justFinished = 0;

	    BSRenderClassFunctions.setTheVBO(Values.levelChoserPlayer.width, Values.levelChoserPlayer.height,
	    		Values.levelChoserPlayer.vbo);

	    String nameOfChapter = "";


		List<String> listOfNodes = new ArrayList<String>();
		List<String> listOfAttr = new ArrayList<String>();

		listOfNodes.add("Chapter_name");
		listOfNodes.add("Chapter_nr_of_levels");
		listOfNodes.add("Chapter_is_finished");
		listOfNodes.add("Chapter_is_available");
		listOfNodes.add("Chapter_x_coord");
		listOfNodes.add("Chapter_y_coord");
		listOfNodes.add("Chapter_width");
		listOfNodes.add("Chapter_height");

		listOfAttr.add("nr_of_chapters");

		final BSXmlStruct headNode = XMLReaderNew.readAnyXML(context, "Menu Of Chapters/gameDetails.xml",
				listOfNodes, listOfAttr, "Game_details", "Chapter_details");

		Values.nrOfChapters = Float.parseFloat(headNode.headNodeAttributes.get(0).attributeValue);
		///Set it to 1 to load the app faster
		Values.nrOfChapters = 6;

	    for(int i = 0 ; i < Values.nrOfChapters ; i++)
	    {
//	    	loadTheGivenChapter(context, i, headNode, nameOfChapter);
	    	MyThread m1 = new MyThread(context, i, headNode, nameOfChapter);
	    }

	    while(true)
	    {
		    if(Values.doneChap1 == true && Values.doneChap2 == true  && Values.doneChap3 == true
		    		 && Values.doneChap4 == true && Values.doneChap5 == true && Values.doneChap6 == true)
		    {
		    	break;
		    }
	    }
	    
		float sizeOfConnectionStringX = Math.abs(Values.chaptere[0].xCord - Values.chaptere[1].xCord) - Values.chaptere[0].width;
		float sizeOfConnectionStringY = Math.abs(Values.chaptere[0].yCord - Values.chaptere[5].yCord) - Values.chaptere[0].height;

		Values.chaptere[0].levelFromChapter[0].lengthXConnectionChapter = sizeOfConnectionStringX;
		Values.chaptere[0].levelFromChapter[0].lengthYConnectionChapter = sizeOfConnectionStringY;

		
		BSRenderClassFunctions.setTheVBO(sizeOfConnectionStringX, Values.chaptere[0].height / 2.f,
							Values.chaptere[0].levelFromChapter[0].vboOfLeftRightChapter);

		BSRenderClassFunctions.setTheVBO(Values.chaptere[0].width / 2.f, sizeOfConnectionStringY,
							Values.chaptere[0].levelFromChapter[0].vboOfUpDownChapter);



		///Setez textura pentru Finished Chapter
		BSRenderClassFunctions.setTheVBO(Values.chaptere[0].levelFromChapter[0].width,
					Values.chaptere[0].levelFromChapter[0].height,
					Values.chaptere[0].levelFromChapter[0].vboOfFinishedChapter);

		loadUserData(context);
		loadTheChapterTextures(context);
	}

	public static void loadTheGivenChapter(Context context, int i, BSXmlStruct headNode, String nameOfChapter)
	{
		Values.chaptere[i] = new ChapterStructure();

		nameOfChapter = headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(0).nodeValue;

		Values.chaptere[i].nrOfLevels = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(1).nodeValue);

		Values.chaptere[i].isFinishedChapter = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(2).nodeValue);

		Values.chaptere[i].isAvailableChapter = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(3).nodeValue);

		Values.chaptere[i].xCord = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(4).nodeValue);
		Values.chaptere[i].yCord = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(5).nodeValue);
		Values.chaptere[i].width = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(6).nodeValue);
		Values.chaptere[i].height = Float.parseFloat(
				headNode.listOfTheSecondNodes.get(i).listOfTheOtherNodes.get(7).nodeValue);


		Values.chaptere[i].xCord *= (Values.changedScreenWidth - 2);
		Values.chaptere[i].yCord *= (Values.changedScreenHeight - 2);

		float[] col = {1.f, 1.f, 1.f, 1.f};
		Values.chaptere[i].colorOfTheChapter = col;



        loadLevels(context, nameOfChapter, Values.chaptere[i].levelFromChapter, (int) Values.chaptere[i].nrOfLevels, i);
        /*String textureName = "Menu Of Chapters/The Chapters textures/chapterTexture" + String.valueOf(i + 1) + ".png";

        Values.chaptere[i].textureOfTheChapter[0] = BSMenus.getImageFromAssets(context, textureName);*/

        Values.levelChoserPlayer.indexOfChapterThatItIsOn = 0;

	    /*    Values.chaptere[i].levelFromChapter[0].textureOfConnectionLeftRightChapter =
	        			BSMenus.getImageFromAssets(context, "Menu Of Chapters/connectionLeftRight.png");


	        Values.chaptere[i].levelFromChapter[0].textureOfConnectionUpDownChapter =
	        		BSMenus.getImageFromAssets(context, "Menu Of Chapters/connectionUpDown.png");
		*/
		Values.levelChoserPlayer.xCord = Values.chaptere[0].xCord;
		Values.levelChoserPlayer.yCord = Values.chaptere[0].yCord;



		float lengthX = Math.abs(Values.chaptere[i].levelFromChapter[0].xCord -
				Values.chaptere[i].levelFromChapter[1].xCord) - Values.chaptere[i].levelFromChapter[0].width;
		float lengthY = Math.abs(Values.chaptere[i].levelFromChapter[0].yCord -
				Values.chaptere[i].levelFromChapter[7].yCord) - Values.chaptere[i].levelFromChapter[0].height;

		Values.chaptere[i].levelFromChapter[0].lengthXConnectionLevel = lengthX;
		Values.chaptere[i].levelFromChapter[0].lengthYConnectionLevel = lengthY;

		BSRenderClassFunctions.setTheVBO(Values.chaptere[i].width, Values.chaptere[i].height,
				Values.chaptere[i].vbo);

		BSRenderClassFunctions.setTheVBO(lengthX, Values.chaptere[i].levelFromChapter[0].height / 3.f,
							Values.chaptere[i].levelFromChapter[0].vboOfLeftRightLevel);

		BSRenderClassFunctions.setTheVBO(Values.chaptere[i].levelFromChapter[0].width / 3.f, lengthY,
							Values.chaptere[i].levelFromChapter[0].vboOfUpDownLevel);

		///Setez textura pentru Finished Level
		BSRenderClassFunctions.setTheVBO(Values.chaptere[i].levelFromChapter[0].width,
							Values.chaptere[i].levelFromChapter[0].height,
							Values.chaptere[i].levelFromChapter[0].vboOfFinishedLevel);

		if(i + 1 == 1)
		{
			Values.doneChap1 = true;
		}
		else
			if(i + 1 == 2)
			{
				Values.doneChap2 = true;
			}
			else
				if(i + 1 == 3)
				{
					Values.doneChap3 = true;
				}
				else
					if(i + 1 == 4)
					{
						Values.doneChap4 = true;
					}
					else
						if(i + 1 == 5)
						{
							Values.doneChap5 = true;
						}
						else
							if(i + 1 == 6)
							{
								Values.doneChap6 = true;
							}
	}



	public static void loadUserData(Context context)
	{
		for(int i = 0; i < Values.nrOfChapters; i++)
		{
			String levelsDetails = BSMenus.getRawFileAsString(context, "Saves/playerData" + String.valueOf(i + 1) + ".txt");

			String[] theFile = levelsDetails.split("[ \n]");
			int k = 0;//va retine numarul curent al cuvantului citit din fisier

			float chapterIndex, nrOfCurrentLevels, levelIndex, done, available;
			chapterIndex = Float.parseFloat(theFile[k]);
			k++;
			nrOfCurrentLevels = Float.parseFloat(theFile[k]);
			k++;

			for(int j = 0 ; j < nrOfCurrentLevels; j++)
			{
//				levelIndex = Float.parseFloat(theFile[k]);
				Values.chaptere[i].levelFromChapter[j].indexOfLevel = (int) Float.parseFloat(theFile[k]);
				k++;
				Values.chaptere[i].levelFromChapter[j].isFinished = (int) Float.parseFloat(theFile[k]);
				k++;
				Values.chaptere[i].levelFromChapter[j].canPlayIt = (int) Float.parseFloat(theFile[k]);
				k++;

				if(Values.chaptere[i].levelFromChapter[j].canPlayIt == 1)
				{
					float[] newcolor = {1, 1, 1, 1};
					Values.chaptere[i].levelFromChapter[j].colorOfLevel = newcolor;
				}
			}

		}
	}

	
	public static void loadTheChapterTextures(Context context)
	{
	    String levelChooserTextureNameString = "Menu Of Levels/Chapter1/playerTextureLevelChooser.png";
	    Values.levelChoserPlayer.texture[0] = BSMenus.getImageFromAssets(context, levelChooserTextureNameString);
	    
		for(int i = 0 ; i < Values.nrOfChapters; i++)
        {
			String textureName = "Menu Of Chapters/The Chapters textures/chapterTexture" + String.valueOf(i + 1) + ".png";
	        Values.chaptere[i].textureOfTheChapter[0] = BSMenus.getImageFromAssets(context, textureName);
	        
	        Values.chaptere[i].levelFromChapter[0].textureOfConnectionLeftRightChapter =
	    			BSMenus.getImageFromAssets(context, "Menu Of Chapters/connectionLeftRight.png");
	
		    Values.chaptere[i].levelFromChapter[0].textureOfConnectionUpDownChapter =
		    		BSMenus.getImageFromAssets(context, "Menu Of Chapters/connectionUpDown.png");

	        String chapterName = "Chapter" + String.valueOf(i+1);
	               
		    for(int j = 0 ; j < Values.chaptere[i].nrOfLevels; j++)
	    	{	 
		    	if(j == 0)
	            {
		    		String name1 = "Menu Of Levels/" + chapterName + "/connectionLeftRight.png",
	                        name2 = "Menu Of Levels/" + chapterName + "/connectionUpDown.png",
	                        name3 = "Menu Of Levels/" + chapterName + "/levelFinished.png";
	
		            Values.chaptere[i].levelFromChapter[0].textureOfConnectionLeftRight[0] = BSMenus.getImageFromAssets(context, name1);
				    Values.chaptere[i].levelFromChapter[0].textureOfConnectionUpDown[0] = BSMenus.getImageFromAssets(context, name2);
				    Values.chaptere[i].levelFromChapter[0].textureOfFinishedLevel[0] = BSMenus.getImageFromAssets(context, name3);
	            }	        
		    	
		    	String newText = "Menu Of Levels/" + chapterName +"/The Levels textures/" + 
		    						Values.chaptere[i].levelFromChapter[j].nameOfTheTexture;
		    	Values.chaptere[i].levelFromChapter[j].textureOfLevel[0] = BSMenus.getImageFromAssets(context, newText);
	        }
        }
	}
	
	

	public static void walkThroughLevels(int leftRight, int UpDown, LevelsFromChapterStructure theLevelsToAdd[])
	{
	    ///In caz ca se afla in meniul de nivele, si jucatorul nu se misca (ceea ce inseamna ca poate alege un nivel)
	    if(Values.currentMenu.indexOfMenu == 4 && Values.levelChoserPlayer.canMove == 1)
	    {
	        ///In caz ca merge la stanga
	        if(leftRight == -1 && Values.levelChoserPlayer.indexOfMenuThatItIsOn > 0)
	        {
	            ///In caz ca nu este primul de pe rand
	            if( Values.levelChoserPlayer.indexOfMenuThatItIsOn % 5 != 0
	                    && theLevelsToAdd[Values.levelChoserPlayer.indexOfMenuThatItIsOn - 1].canPlayIt == 1)
	            {
	            	Values.levelChoserPlayer.indexOfMenuThatItIsOn--;
	            	Values.levelChoserPlayer.canMove = 0;
	            	Values.levelChoserPlayer.isMovingLeftRight = -1;
	            	Values.levelChoserPlayer.isMovingUpDown = 0;
	            }
	        }
	        else
	            ///In caz ca merge la stanga
	            if(leftRight == 1 && Values.levelChoserPlayer.indexOfMenuThatItIsOn < 25
	                    && theLevelsToAdd[Values.levelChoserPlayer.indexOfMenuThatItIsOn + 1].canPlayIt == 1)
	            {
	                if( (Values.levelChoserPlayer.indexOfMenuThatItIsOn + 1) % 5 != 0 )
	                {
	                	Values.levelChoserPlayer.indexOfMenuThatItIsOn++;
	                	Values.levelChoserPlayer.canMove = 0;
	                	Values.levelChoserPlayer.isMovingLeftRight = 1;
	                	Values.levelChoserPlayer.isMovingUpDown = 0;
	                }
	            }
	            else
	                ///In caz ca merge sus
	                if(UpDown == 1 && Values.levelChoserPlayer.indexOfMenuThatItIsOn > 4
	                        && theLevelsToAdd[Values.levelChoserPlayer.indexOfMenuThatItIsOn - 5].canPlayIt == 1)
	                {
	                    //if( (levelChoserPlayer.indexOfMenuThatItIsOn - 5) % 5 != 0 )
	                    {
	                    	Values.levelChoserPlayer.indexOfMenuThatItIsOn -= 5;
	                    	Values.levelChoserPlayer.canMove = 0;
	                    	Values.levelChoserPlayer.isMovingLeftRight = 0;
	                    	Values.levelChoserPlayer.isMovingUpDown = 1;
	                    }
	                }
	                else
	                    ///In caz ca merge jos
	                    if(UpDown == -1 && Values.levelChoserPlayer.indexOfMenuThatItIsOn < 20
	                            && theLevelsToAdd[Values.levelChoserPlayer.indexOfMenuThatItIsOn + 5].canPlayIt == 1)
	                    {
	                        //if( (levelChoserPlayer.indexOfMenuThatItIsOn + 5) % 5 != 0 )
	                        {
	                        	Values.levelChoserPlayer.indexOfMenuThatItIsOn += 5;
	                        	Values.levelChoserPlayer.canMove = 0;
	                        	Values.levelChoserPlayer.isMovingLeftRight = 0;
	                        	Values.levelChoserPlayer.isMovingUpDown = -1;
	                        }
	                    }
	    }
	    else
	        ///In caz ca jucatorul inca se misca ca sa ajunga la nivel
	        if(Values.levelChoserPlayer.canMove == 0 && Values.currentMenu.indexOfMenu == 4)
	        {
	            int indexOfWantedLevel = Values.levelChoserPlayer.indexOfMenuThatItIsOn;
	            walkingAnimation(theLevelsToAdd[indexOfWantedLevel].xCord,
	                             theLevelsToAdd[indexOfWantedLevel].yCord);
	        }
	}


	public static void walkThroughChapters(int leftRight, int UpDown)
	{
	    ///In caz ca se afla in meniul de nivele, si jucatorul nu se misca (ceea ce inseamna ca poate alege un nivel)
	    if(Values.currentMenu.indexOfMenu == 5 && Values.levelChoserPlayer.canMove == 1)
	    {
	        ///In caz ca merge la stanga
	        if(leftRight == -1)/// || UpDown == -1)
	        {
	        	int theNextIndex = Values.levelChoserPlayer.indexOfChapterThatItIsOn - 1;
	        	///In caz ca are unde sa se duca la stanga
					///In caz ca cel din stanga e pe acelasi Y dar cu X mai mic
					if(theNextIndex >= 0 && Values.chaptere[theNextIndex].xCord < Values.chaptere[theNextIndex + 1].xCord
						&& Values.chaptere[theNextIndex].isAvailableChapter == 1)
					{
						Values.levelChoserPlayer.indexOfChapterThatItIsOn--;
						Values.levelChoserPlayer.canMove = 0;
						Values.levelChoserPlayer.isMovingLeftRight = -1;
						Values.levelChoserPlayer.isMovingUpDown = 0;
					}
					else
						if(theNextIndex + 2 < Values.nrOfChapters &&
								Values.chaptere[theNextIndex + 2].xCord < Values.chaptere[theNextIndex + 1].xCord
						&& Values.chaptere[theNextIndex + 2].isAvailableChapter == 1)
						{
							Values.levelChoserPlayer.indexOfChapterThatItIsOn++;
							Values.levelChoserPlayer.canMove = 0;
							Values.levelChoserPlayer.isMovingLeftRight = -1;
							Values.levelChoserPlayer.isMovingUpDown = 0;
						}

	        }
	        else
	            ///In caz ca merge la dreapta
	            if(leftRight == 1)/// || UpDown == -1)
				{
					int theNextIndex = Values.levelChoserPlayer.indexOfChapterThatItIsOn + 1;
					///In caz ca are unde sa se duca la stanga
						///In caz ca cel din stanga e pe acelasi Y dar cu X mai mic
						if(theNextIndex < Values.nrOfChapters &&
								Values.chaptere[theNextIndex].xCord > Values.chaptere[theNextIndex - 1].xCord
						&& Values.chaptere[theNextIndex].isAvailableChapter == 1)
						{
							Values.levelChoserPlayer.indexOfChapterThatItIsOn++;
							Values.levelChoserPlayer.canMove = 0;
							Values.levelChoserPlayer.isMovingLeftRight = 1;
							Values.levelChoserPlayer.isMovingUpDown = 0;
						}
						else
							if(theNextIndex - 2 >= 0 &&
							Values.chaptere[theNextIndex - 2].xCord > Values.chaptere[theNextIndex - 1].xCord
						&& Values.chaptere[theNextIndex - 2].isAvailableChapter == 0)
							{
								Values.levelChoserPlayer.indexOfChapterThatItIsOn--;
								Values.levelChoserPlayer.canMove = 0;
								Values.levelChoserPlayer.isMovingLeftRight = 1;
								Values.levelChoserPlayer.isMovingUpDown = 0;
							}
				}
				else
					///Daca se duce in jos
					if(UpDown == -1)/// || UpDown == -1)
					{
						int theNextIndex = Values.levelChoserPlayer.indexOfChapterThatItIsOn - 1;
						///In caz ca are unde sa se duca la stanga
							///In caz ca cel din stanga e pe acelasi Y dar cu X mai mic
							if(theNextIndex >= 0 &&
									Values.chaptere[theNextIndex].yCord < Values.chaptere[theNextIndex + 1].yCord
						&& Values.chaptere[theNextIndex].isAvailableChapter == 1)
							{
								Values.levelChoserPlayer.indexOfChapterThatItIsOn--;
								Values.levelChoserPlayer.canMove = 0;
								Values.levelChoserPlayer.isMovingLeftRight = 0;
								Values.levelChoserPlayer.isMovingUpDown = -1;
							}
							else
								if(theNextIndex + 2 < Values.nrOfChapters &&
										Values.chaptere[theNextIndex + 2].yCord < Values.chaptere[theNextIndex + 1].yCord
						&& Values.chaptere[theNextIndex + 2].isAvailableChapter == 1)
								{
									Values.levelChoserPlayer.indexOfChapterThatItIsOn++;
									Values.levelChoserPlayer.canMove = 0;
									Values.levelChoserPlayer.isMovingLeftRight = 0;
									Values.levelChoserPlayer.isMovingUpDown = -1;
								}
					}
					else
						///Daca se duce in sus
						if(UpDown == 1)/// || UpDown == -1)
						{
							int theNextIndex = Values.levelChoserPlayer.indexOfChapterThatItIsOn + 1;
							///In caz ca are unde sa se duca la stanga
								///In caz ca cel din stanga e pe acelasi Y dar cu X mai mic
								if(theNextIndex < Values.nrOfChapters &&
										Values.chaptere[theNextIndex].yCord > Values.chaptere[theNextIndex - 1].yCord
						&& Values.chaptere[theNextIndex].isAvailableChapter == 1)
								{
									Values.levelChoserPlayer.indexOfChapterThatItIsOn++;
									Values.levelChoserPlayer.canMove = 0;
									Values.levelChoserPlayer.isMovingLeftRight = 0;
									Values.levelChoserPlayer.isMovingUpDown = 1;
								}
								else
									if(theNextIndex - 2 >= 0 &&
											Values.chaptere[theNextIndex - 2].yCord > Values.chaptere[theNextIndex - 1].yCord
						&& Values.chaptere[theNextIndex - 2].isAvailableChapter == 1)
									{
										Values.levelChoserPlayer.indexOfChapterThatItIsOn--;
										Values.levelChoserPlayer.canMove = 0;
										Values.levelChoserPlayer.isMovingLeftRight = 0;
										Values.levelChoserPlayer.isMovingUpDown = 1;
									}
						}
	    }
	    else
	        ///In caz ca jucatorul inca se misca ca sa ajunga la nivel
	        if(Values.levelChoserPlayer.canMove == 0 && Values.currentMenu.indexOfMenu == 5)
	        {
	            int indexOfWantedChapter = Values.levelChoserPlayer.indexOfChapterThatItIsOn;

	            walkingAnimation(Values.chaptere[indexOfWantedChapter].xCord,
            						Values.chaptere[indexOfWantedChapter].yCord);
	        }
	}


	public static void walkingAnimation(float xDestination, float yDestination)
	{
	    float moveSpeed = 0.43f;

	    if(Values.levelChoserPlayer.xCord < xDestination && Values.levelChoserPlayer.isMovingLeftRight == 1)
	    {
	    	Values.levelChoserPlayer.xCord += moveSpeed;
	        ///Daca a trecut de nivel, se intoarce la el
	        if(Values.levelChoserPlayer.xCord > xDestination)
	        {
	        	Values.levelChoserPlayer.xCord = xDestination;
	        }
	    }
	    else if(Values.levelChoserPlayer.xCord > xDestination && Values.levelChoserPlayer.isMovingLeftRight == -1)
	    {
	    	Values.levelChoserPlayer.xCord -= moveSpeed;
	        ///Daca a trecut de nivel, se intoarce la el
	        if(Values.levelChoserPlayer.xCord < xDestination)
	        {
	        	Values.levelChoserPlayer.xCord = xDestination;
	        }
	    }
	    else if(Values.levelChoserPlayer.yCord > yDestination && Values.levelChoserPlayer.isMovingUpDown == -1)
	    {
	    	Values.levelChoserPlayer.yCord -= moveSpeed;
	        ///Daca a trecut de nivel, se intoarce la el
	        if(Values.levelChoserPlayer.yCord < yDestination)
	        {
	        	Values.levelChoserPlayer.yCord = yDestination;
	        }
	    }
	    else if(Values.levelChoserPlayer.yCord < yDestination && Values.levelChoserPlayer.isMovingUpDown == 1)
	    {
	    	Values.levelChoserPlayer.yCord += moveSpeed;
	        ///Daca a trecut de nivel, se intoarce la el
	        if(Values.levelChoserPlayer.yCord > yDestination)
	        {
	        	Values.levelChoserPlayer.yCord = yDestination;
	        }
	    }
	    else if(Values.levelChoserPlayer.xCord == xDestination && Values.levelChoserPlayer.yCord == yDestination)
	    {
	    	Values.levelChoserPlayer.canMove = 1;
	    }
	}


	public static void renderMenuLevels(float[] mMVPMatrix, float[] mProjMatrix, float[] mVMatrix,
								int nrOfLevels, LevelsFromChapterStructure theLevelsToRender[])
	{
//		float[] theColorToRender = { 1.f, 1.f, 1.f, 0.9f };
//		if(DarkLevels)
		{
//			theColorToRender = { 2.f, 1.f, 1.f, 0.9f };
		}
//		else
		{
//			theColorToRender = { 1.f, 1.f, 1.f, 0.9f };
		}
//		renderTransparentSquare(theColorToRender, Values.SCREEN_WIDTH / 2 / Values.scaleSize + Values.MenuCoordinateX,
//				Values.SCREEN_HEIGHT / 2 / Values.scaleSize + Values.MenuCoordinateY);

		///Randez nivelele
		for(int i = 0 ; i < nrOfLevels ; i++)
		{

			///Second, render the level images
//			if(DarkLevels)
			{
//				theLevelsToRender[i].colorOfLevel.r = 2.f;
			}
//			else
			{
				theLevelsToRender[i].colorOfLevel[0] = 1.f;
			}
			BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
									theLevelsToRender[i].xCord + Values.MenuCoordinateX,
									theLevelsToRender[i].yCord + Values.MenuCoordinateY,
									theLevelsToRender[i].textureOfLevel[0],
									theLevelsToRender[i].colorOfLevel,
									theLevelsToRender[i].vboOfLevel, Values.iboNormal, 0, 0);

			if(theLevelsToRender[i].isFinished == 1)
			{
//				if(DarkLevels)
				{
//					theLevelsToRender[0].colorOfLevel.r = 2.f;
				}
//				else
				{
					theLevelsToRender[0].colorOfLevel[0] = 1.f;
				}
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
										theLevelsToRender[i].xCord + Values.MenuCoordinateX,
										theLevelsToRender[i].yCord + Values.MenuCoordinateY,
										theLevelsToRender[0].textureOfFinishedLevel[0],
										theLevelsToRender[0].colorOfLevel,
										theLevelsToRender[0].vboOfFinishedLevel, Values.iboNormal, 0, 0);
			}
			float imparte = 1; ///ca sa mute pe prima textura de conexiune unde trebuie (cele 2 coltul stanga-sus)
			if(i == 0)
			{
				imparte = 3;
			}

			///First, render the connection strings
			///Daca poate pune la stanga, atunci pune
			if( (i + 1) % 5 != 0)
			{
//				if(DarkLevels)
				{
//					theLevelsToRender[i + 1].colorOfLevel.r = 2.f;
				}
//				else
				{
					theLevelsToRender[i + 1].colorOfLevel[0] = 1.f;
				}
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
										theLevelsToRender[i].xCord + Values.MenuCoordinateX +
							theLevelsToRender[0].width / 2.f + theLevelsToRender[0].lengthXConnectionLevel / 2.f,
										theLevelsToRender[i].yCord + Values.MenuCoordinateY,
										theLevelsToRender[0].textureOfConnectionLeftRight[0],
										theLevelsToRender[i + 1].colorOfLevel,
										theLevelsToRender[0].vboOfLeftRightLevel, Values.iboNormal, 0, 0);
			}

			if(i < 20)
			{
//				if(DarkLevels)
				{
//					theLevelsToRender[i + 5].colorOfLevel.r = 2.f;
				}
//				else
				{
					theLevelsToRender[i + 5].colorOfLevel[0] = 1.f;
				}
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
										theLevelsToRender[i].xCord + Values.MenuCoordinateX,
										theLevelsToRender[i].yCord + Values.MenuCoordinateY -
							theLevelsToRender[i].height / 2.f - theLevelsToRender[0].lengthYConnectionLevel / 2.f,
										theLevelsToRender[0].textureOfConnectionUpDown[0],
										theLevelsToRender[i + 5].colorOfLevel,
										theLevelsToRender[0].vboOfUpDownLevel, Values.iboNormal, 0, 0);
			}
		}

		///Randez animatia cu care ma voi misca prin nivele
		BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
								Values.levelChoserPlayer.xCord+ Values.MenuCoordinateX,
								Values.levelChoserPlayer.yCord + Values.MenuCoordinateY,
								Values.levelChoserPlayer.texture[0], Values.levelChoserPlayer.color,
								Values.levelChoserPlayer.vbo, Values.iboNormal, 0, 0);

		walkThroughLevels(0, 0, theLevelsToRender);
	}


	public static void renderMenuChapters(float[] mMVPMatrix, float[] mProjMatrix, float[] mVMatrix)
	{
//		float[] theColorToRender = { 1.f, 1.f, 1.f, 0.9f };
//		renderTransparentSquare(theColorToRender, Values.SCREEN_WIDTH / 2 / Values.scaleSize + Values.MenuCoordinateX,
//				Values.SCREEN_HEIGHT / 2 / Values.scaleSize + Values.MenuCoordinateY);

		///Randez chapterele
		for(int i = 0 ; i < Values.nrOfChapters ; i++)
		{
			///Second, render the level images
			BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
									Values.chaptere[i].xCord + Values.MenuCoordinateX,
									Values.chaptere[i].yCord + Values.MenuCoordinateY,
									Values.chaptere[i].textureOfTheChapter[0],
									Values.chaptere[i].colorOfTheChapter,
									Values.chaptere[i].vbo, Values.iboNormal, 0, 0);

			if(Values.chaptere[i].isFinishedChapter == 1)
			{
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
										Values.chaptere[i].xCord+ Values.MenuCoordinateX,
										Values.chaptere[i].yCord + Values.MenuCoordinateY,
										Values.chaptere[0].levelFromChapter[0].textureOfFinishedLevel[0],
										Values.chaptere[0].levelFromChapter[0].colorOfLevel,
										Values.chaptere[0].levelFromChapter[0].vboOfFinishedLevel,
										Values.iboNormal, 0, 0);
			}
		}

		for(int i = 0 ; i < Values.nrOfChapters - 1 ; i++)
		{
			int indexulUrmatoruluiNivel = 0;
			///First, render the connection strings
			///Daca poate pune la stanga, atunci pune
			float sizeOfConnectionStringX = 0, sizeOfConnectionStringY = 0;

			if(i + 1 < Values.nrOfChapters)//( (i + 1) % 5 != 0)
			{
				indexulUrmatoruluiNivel = i + 1;
//				sizeOfConnectionStringX = Math.abs(Values.chaptere[i].xCord - Values.chaptere[i+1].xCord) - Values.chaptere[i].width;
//				sizeOfConnectionStringY = Math.abs(Values.chaptere[i].yCord - Values.chaptere[i+1].yCord) - Values.chaptere[i].height;
			}
			else
			{
				indexulUrmatoruluiNivel = 0;
//				sizeOfConnectionStringX = Math.abs(Values.chaptere[i].xCord - Values.chaptere[0].xCord) - Values.chaptere[i].width;
//				sizeOfConnectionStringY = Math.abs(Values.chaptere[i].yCord - Values.chaptere[0].yCord) - Values.chaptere[i].height;
			}

			///Daca este mai la dreapta
			if(Values.chaptere[indexulUrmatoruluiNivel].xCord > Values.chaptere[i].xCord)
			{
				BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
										Values.chaptere[i].xCord + Values.MenuCoordinateX +
			Values.chaptere[i].width / 2.f + Values.chaptere[0].levelFromChapter[0].lengthXConnectionChapter / 2.f,
										Values.chaptere[i].yCord + Values.MenuCoordinateY,
										Values.chaptere[0].levelFromChapter[0].textureOfConnectionLeftRightChapter,
										Values.chaptere[indexulUrmatoruluiNivel].colorOfTheChapter,
										Values.chaptere[0].levelFromChapter[0].vboOfLeftRightChapter,
										Values.iboNormal, 0, 0);
			}
			else

				///Daca este mai la stanga
				if(Values.chaptere[indexulUrmatoruluiNivel].xCord < Values.chaptere[i].xCord)
				{
					BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
											Values.chaptere[i].xCord + Values.MenuCoordinateX -
			Values.chaptere[i].width / 2.f - Values.chaptere[0].levelFromChapter[0].lengthXConnectionChapter / 2.f,
											Values.chaptere[i].yCord + Values.MenuCoordinateY,
											Values.chaptere[0].levelFromChapter[0].textureOfConnectionLeftRightChapter,
											Values.chaptere[indexulUrmatoruluiNivel].colorOfTheChapter,
											Values.chaptere[0].levelFromChapter[0].vboOfLeftRightChapter,
											Values.iboNormal, 0, 0);
				}
				else

					///Daca este mai jos
					if(Values.chaptere[indexulUrmatoruluiNivel].yCord < Values.chaptere[i].yCord)
					{
						BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
												Values.chaptere[i].xCord + Values.MenuCoordinateX,
												Values.chaptere[i].yCord - Values.chaptere[i].height / 2.f -
			Values.chaptere[0].levelFromChapter[0].lengthYConnectionChapter / 2.f + Values.MenuCoordinateY,
												Values.chaptere[0].levelFromChapter[0].textureOfConnectionUpDownChapter,
												Values.chaptere[indexulUrmatoruluiNivel].colorOfTheChapter,
												Values.chaptere[0].levelFromChapter[0].vboOfUpDownChapter,
												Values.iboNormal, 0, 0);
					}
					else

						///Daca este mai sus
						if(Values.chaptere[indexulUrmatoruluiNivel].yCord > Values.chaptere[i].yCord)
						{
							BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
													Values.chaptere[i].xCord + Values.MenuCoordinateX,
													Values.chaptere[i].yCord + Values.chaptere[i].height / 2.f +
			Values.chaptere[0].levelFromChapter[0].lengthYConnectionChapter / 2.f + Values.MenuCoordinateY,
													Values.chaptere[0].levelFromChapter[0].textureOfConnectionUpDownChapter,
													Values.chaptere[indexulUrmatoruluiNivel].colorOfTheChapter,
													Values.chaptere[0].levelFromChapter[0].vboOfUpDownChapter,
													Values.iboNormal, 0, 0);
						}

		}

		///Randez animatia cu care ma voi misca prin nivele
		BSRenderClassFunctions.renderAnVboAndVaoObject(mMVPMatrix, mProjMatrix, mVMatrix,
								Values.levelChoserPlayer.xCord + Values.MenuCoordinateX,
								Values.levelChoserPlayer.yCord + Values.MenuCoordinateY,
								Values.levelChoserPlayer.texture[0], Values.levelChoserPlayer.color,
								Values.levelChoserPlayer.vbo, Values.iboNormal, 0, 0);

		walkThroughChapters(0, 0);
	}

}


