package com.example.brainstormstudiosgameengine;


import java.util.ArrayList;
import java.util.List;

import org.jbox2d.collision.shapes.PolygonShape;
import org.jbox2d.common.Vec2;
import org.jbox2d.dynamics.Body;
import org.jbox2d.dynamics.BodyDef;
import org.jbox2d.dynamics.BodyType;
import org.jbox2d.dynamics.FixtureDef;
import org.jbox2d.dynamics.World;

import android.content.Context;


public class ActionStuff {

	public volatile float theTimeHowFast = 0, newForce = 0, newX = 0, newY = 0;
    
	public void update()
	{
		Values.world.step((float) 1/60 , 8, 3); //1/60, 8, 3
		//world.step(1/30,10,10); //performs a time step in the box2d simulation
		Values.world.clearForces();
		Values.world.drawDebugData();
	}
	
	
	public static void createTextureBody(BSTheSquareBodies theBody, float xPosition, float yPosition, float width, float height, float density, float friction, float restitution, String userData, int texture)
	{    
		theBody.xCord = xPosition;
		theBody.yCord = yPosition;
				
        theBody.widthOfBody = width;
        theBody.heightOfBody = height;
        theBody.textureOfBody[0] = TextureHelper.loadTexture(BSRenderer.context, texture);
        
        theBody.setUpForShaders(width, height);

    }
	
	public static void createSquareBody(BSTheSquareBodies theBody, BodyType type, float xPosition, float yPosition, float width, float height, float density, float friction, float restitution, String userData, World world, int texture)
	{
		if(theBody != null)
    	{
			BodyDef boxDef = new BodyDef();
    	
	        boxDef.position.set(xPosition, yPosition);
	        boxDef.type = type;
	        
	        PolygonShape boxShape = new PolygonShape();
	        boxShape.setAsBox(width / 2f, height / 2f);
	        
	        Body box = world.createBody(boxDef);
	        
	        FixtureDef boxFixture = new FixtureDef();
	        
	        boxFixture.density = density;
	        boxFixture.friction = friction;
	        boxFixture.restitution = restitution;
	        boxFixture.shape = boxShape;
	        
	        ///box.setUserData(userData + " " + width/2f + " " + height/2f);
	        BodyUserData userDataForBody = new BodyUserData();
	        userDataForBody.name = userData;
	        
	        box.setUserData(userDataForBody);
	        
	        box.createFixture(boxFixture);
	        box.setFixedRotation(true);
	        
	        
	        theBody.theBody = box;
    	}
        
        theBody.widthOfBody = width;
        theBody.heightOfBody = height;
        theBody.textureOfBody[0] = TextureHelper.loadTexture(BSRenderer.context, texture);
        theBody.typeOfBody = type;
        
        theBody.setUpForShaders(width, height);

    	
        //Daca nu e eroul, incrementez numarul de obiecte
        if(theBody != Values.hero)
    	{
        	Values.nrOfBodies++;
    	}
        
    }
	
	public static void SetUpBodies()
	{
		Values.world = new World(new Vec2(0, 40), true);
	    

		Values.hero = new BSTheSquareBodies();
		createSquareBody(Values.hero, BodyType.DYNAMIC, -2, -3, 1, 1, 1, 1, 0, "hero", Values.world, R.raw.player);
		
		//the restart image
		BSTheSquareBodies restart = new BSTheSquareBodies();
		Values.onlyTexturesBodies.add(restart);
        createTextureBody(Values.onlyTexturesBodies.get(Values.onlyTexturesBodies.size() - 1), 0, 0, 150, 150, 1, 1, 0, "asd", R.raw.restart);
        
        Values.transparentMenuBlock = new BSTheSquareBodies();
        createTextureBody(Values.transparentMenuBlock, 0, 0, 150, 150, 1, 1, 0, "asd", R.raw.first);
        
        //update();
	}
	
	public static void incarcaHarta(Context context, String Path)
	{
		List<String> listOfNodes = new ArrayList<String>();
		List<String> listOfAttr = new ArrayList<String>();
		listOfNodes.add("xCoordinate");
		listOfNodes.add("yCoordinate");
		listOfNodes.add("width");
		listOfNodes.add("height");
		listOfNodes.add("userName");
		
//		XMLReader.readAnyXML(context, Path, listOfNodes, listOfAttr, "Level", "obstacle");
		XMLReader.writeTheReadedXML(XMLReaderOld.readAnyXML(context, Path, listOfNodes, 
									listOfAttr, "Level", "obstacle"));
	}
}


class BodyUserData
{
	boolean
	canJumpVertically = false,
	canJumpHorizontally = false,
	isOnGround = false,
	isInAir = true,
	isInCorner = false,
	isOnLeftWall = false,
	isOnRightWall = false,
	jumpsUpTheWall = false,
	canKillHero = false,
	isNextLevel = false,
	isToNextLevel = false;
	public static int variableWall = 0;
	String name = "";
}
