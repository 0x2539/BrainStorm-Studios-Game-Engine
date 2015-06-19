package com.example.brainstormstudiosgameengine;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import android.opengl.GLES20;
import android.opengl.Matrix;


public class BSRenderClassFunctions
{
	public static void renderAnVboAndVaoObject(float[] mMVPMatrix, float[] mProjMatrix, float[] mVMatrix, 
									float coordX, float coordY, int theTextureIdToRender,
									float[] theColorOfObstacle, int[] vbo, int[] ibo, float ScaleOnX, float ScaleOnY)
	{
		if (vbo[0] > 0 && ibo[0] > 0) 
		{
			coordX *= -1;
			coordY *= -1;
			
		    Matrix.setLookAtM(mVMatrix, 0,
		    		coordX, coordY, 2, coordX, coordY, 0,
		    		//Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 2,    
		    		//Values.hero.theBody.getPosition().x, Values.hero.theBody.getPosition().y, 0,     
					    		0f, 1.0f, 0.0f);

	        Matrix.translateM(mVMatrix, 0, Values.hero.theBody.getPosition().x, 
	        								Values.hero.theBody.getPosition().y, 0);
		    Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
		    
		    
		    
			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);

			GLES20.glEnableVertexAttribArray(Values.mPositionHandle);
	        GLES20.glVertexAttribPointer(Values.mPositionHandle, Values.COORDS_PER_VERTEX,
                    GLES20.GL_FLOAT, false,
                    Values.vertexStride, 0);
	        
			GLES20.glEnableVertexAttribArray(Values.mTextureCoordinateHandle);
			GLES20.glVertexAttribPointer(Values.mTextureCoordinateHandle, Values.COORDS_PER_VERTEX_TEXTURE, 
					GLES20.GL_FLOAT, false,
					Values.textureStride, 12 * 4);
			
	        
	        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, theTextureIdToRender); 
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
	        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);
	        GLES20.glUniform1i(Values.mTheActualTexture, 0);

	        GLES20.glUniform1f(Values.ShaderAngle, 0);//theBody.getAngle());
	        
	        
	        
	        GLES20.glUniform1f(Values.ScaleOnX, ScaleOnX);//theBody.getAngle());
	        GLES20.glUniform1f(Values.ScaleOnY, ScaleOnY);//theBody.getAngle());
	        

        	GLES20.glUniform4fv(Values.mColorHandle, 1, theColorOfObstacle, 0);

	        // Apply the projection and view transformation
	        GLES20.glUniformMatrix4fv(Values.mMVPMatrixHandle, 1, false, mMVPMatrix, 0);

	        // Draw the square
			GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
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

	public static void removeBody(int[] textureToDelete, int[] vboToDelete)
	{
		GLES20.glDeleteTextures(1, textureToDelete, 0);
		GLES20.glDeleteBuffers(1, vboToDelete, 0);
	}

	public static void setTheVBO(float width, float height, int vbo[])
	{
		try
		{
	        float squareCoords[] = { 
	        		-width / 2.f - 0.015f / 2.f,  height / 2.f + 0.015f / 2.f, 0.0f,	// top left
		            -width / 2.f - 0.015f / 2.f, -height / 2.f - 0.015f / 2.f, 0.0f,	// bottom left
		             width / 2.f + 0.015f / 2.f, -height / 2.f - 0.015f / 2.f, 0.0f,	// bottom right
		             width / 2.f + 0.015f / 2.f,  height / 2.f + 0.015f / 2.f, 0.0f};	// bottom right 
	        ByteBuffer bb = ByteBuffer.allocateDirect((squareCoords.length + 
	        		Values.TextureCoords.length) * 4); // (# of coordinate values * 4 bytes per float)
	        bb.order(ByteOrder.nativeOrder());
	        FloatBuffer vertexBuffer = bb.asFloatBuffer();
	        vertexBuffer.put(squareCoords);
	        vertexBuffer.put(Values.TextureCoords);
	        vertexBuffer.position(0);
	        
	        
	        // initialize byte buffer for the draw list
//	        ByteBuffer dlb = ByteBuffer.allocateDirect(
//	        // (# of coordinate values * 2 bytes per short)
//	        		Values.drawOrder.length * 2);
//	        dlb.order(ByteOrder.nativeOrder());
//	        ShortBuffer drawListBuffer = dlb.asShortBuffer();
//	        drawListBuffer.put(Values.drawOrder);
//	        drawListBuffer.position(0);
	        
	
			GLES20.glGenBuffers(1, vbo, 0);
//			GLES20.glGenBuffers(1, ibo, 0);
	
			if (vbo[0] > 0 && Values.iboNormal[0] > 0) 
			{
				GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);
				GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, vertexBuffer.capacity() * Values.BYTES_PER_FLOAT,
						vertexBuffer, GLES20.GL_DYNAMIC_DRAW);
	
	
				GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, Values.iboNormal[0]);
				GLES20.glBufferData(GLES20.GL_ELEMENT_ARRAY_BUFFER, Values.drawListBuffer.capacity()
						* Values.BYTES_PER_SHORT, Values.drawListBuffer, GLES20.GL_DYNAMIC_DRAW);
	
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
	
}
