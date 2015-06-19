package com.example.brainstormstudiosgameengine;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.content.Context;
import android.opengl.GLES20;

public class SetUpClass {

	public static void load(Context context)
	{
//		setTheNormalIbo();
		ActionStuff.SetUpBodies();

		loadTheLevel(context, "xmlfile.xml");
		loadTheChapterAndLevelMenu(context);
	}
	
	public static void setTheNormalIbo()
	{
        ByteBuffer dlb = ByteBuffer.allocateDirect(Values.drawOrder.length * 2);//2 bytes for short
        dlb.order(ByteOrder.nativeOrder());
        Values.drawListBuffer = dlb.asShortBuffer();
        Values.drawListBuffer.put(Values.drawOrder);
        Values.drawListBuffer.position(0);
        
		GLES20.glGenBuffers(1, Values.iboNormal, 0);

		GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, Values.iboNormal[0]);
		GLES20.glBufferData(GLES20.GL_ELEMENT_ARRAY_BUFFER, Values.drawListBuffer.capacity()
				* Values.BYTES_PER_SHORT, Values.drawListBuffer, GLES20.GL_DYNAMIC_DRAW);
	}
	
	public static void loadTheChapterAndLevelMenu(Context context)
	{
		BSMenus.addTheMenus(context);
		ChaptersAndLevelsMenu.loadChapters(context);
	}
	
	public static void loadTheLevel(Context context, String path)
	{
		if(Values.obstacles.size() > 0)
		{
			for(int i = 0 ; i < Values.obstacles.size(); i++)
			{
				BSRenderClassFunctions.removeBody(Values.obstacles.get(i).textureOfBody, Values.obstacles.get(i).vbo);
			}
		}
		Values.obstacles.clear();
		ActionStuff.incarcaHarta(context, path);
	}
	
}




