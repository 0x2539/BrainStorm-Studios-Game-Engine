package com.example.brainstormstudiosgameengine;

import java.nio.ShortBuffer;
import java.util.ArrayList;
import java.util.List;

import org.jbox2d.dynamics.World;

public class Values
{
	public static float gravityX = 0, gravityY = 10, newForceX = 0, newForceY = 0, sinusRestart = 0;
	///public static float BodySize[][];
	public static String textToShow = "";
	
	public static World world;
	public static BSTheSquareBodies hero;
	
	public static List<BSTheSquareBodies> obstacles = new ArrayList<BSTheSquareBodies>(); 
	public static List<BSTheSquareBodies> onlyTexturesBodies = new ArrayList<BSTheSquareBodies>();
	public static List<BSMenuStructure> listOfMenus = new ArrayList<BSMenuStructure>();
	
	public static int nrOfBodies = 0;

    public static int mProgram;
    public static int mPositionHandle; //vPosition
    public static int mColorHandle; //vColor
    public static int mMVPMatrixHandle; //uMVPMatrix
    public static int mTextureCoordinateHandle; //TexCoordinate
    public static int mTheActualTexture; //theActualTexture
    public static int ShaderAngle; //RotationAngle
    public static int ScaleOnX, ScaleOnY;

    // number of coordinates per vertex in this array
    public static final int COORDS_PER_VERTEX = 3;
    public static final int COORDS_PER_VERTEX_TEXTURE = 2;
    
    public static final int vertexStride = COORDS_PER_VERTEX * 4; // 4 bytes per vertex
    public static final int textureStride = COORDS_PER_VERTEX_TEXTURE * 4; // 4 bytes per vertex
    public static final int fullStride = (COORDS_PER_VERTEX + COORDS_PER_VERTEX_TEXTURE) * 4; // 4 bytes per vertex
    
    public static boolean ButtonJump = false, canJumpHorizontally = false, canJumpVertically = true, 
    			ButtonRight = false, ButtonLeft, isOnLeftWall = false, isOnRightWall = false;
    
    public static float speedWalk = 25, speedRun = 1.2f, speedJumpUp = -17.7f, speedJumpToSide = 17, speedGoDown = -20,
	speedWalkInAir = 25, speedJumpToTheSameSide = 17.1f, speedJumpUpOnWall = 21.f,
	timeToStayInAirWhenJumpsOnTheSameWall = 175, timeToStayOnWall = 250;
    
    public static float theTimeHowFast = 60, lastPositionOfHeroX = 0, lastPositionOfHeroY = 0;
    
    public static boolean itMovedX = false, itMovedY = false;
    
    public static float SCREEN_WIDTH, SCREEN_HEIGHT, scaleSize, changedScreenWidth, changedScreenHeight;

    public static float CameraExtremeLeft, CameraExtremeRight, CameraExtremeUp, CameraExtremeDown, 
    				MenuCoordinateX, MenuCoordinateY;

    public static float newVolumeAudio = 1, newVolumeSFX = 1, currentVolumeAudio = 1, currentVolumeSFX = 1;

	public static final int BYTES_PER_FLOAT = 4;
	public static final int BYTES_PER_SHORT = 2;
    public static float TextureCoords[] = 
		{ 
        0.0f, 0.0f,   // bottom left
		0.0f, 1.0f,   // top left
        1.0f, 1.0f, // top right
        1.0f, 0.0f,   // bottom right
		};
	
	public static BSMenuStructure currentMenu;
	public static BSButtonStructure currentButton;
	
	public static BSAnimation SoundButtonTexture;// = new BSAnimation();
	public static BSTheSquareBodies transparentMenuBlock;
	
	public static float nrOfChapters = 0;
	public static LevelChooserPlayerTexture levelChoserPlayer;
	public static BSTheSquareBodies theLoadingImage;
	public static boolean canRenderGameNow = false;
	
	public static ChapterStructure[] chaptere = new ChapterStructure[100];
    
    public static int[] iboNormal = new int[1];
	public static short drawOrder[] = { 0, 1, 2, 3 }; // order to draw vertices
	public static ShortBuffer drawListBuffer;
	public static boolean doneChap1 = false, doneChap2 = false, doneChap3 = false, doneChap4 = false,
							doneChap5 = false, doneChap6 = false;

//	public final File sdCard = Environment.getExternalStorageDirectory();
//	public final File directory = new File (sdCard.getAbsolutePath() + "/BS Studios Files");

}
