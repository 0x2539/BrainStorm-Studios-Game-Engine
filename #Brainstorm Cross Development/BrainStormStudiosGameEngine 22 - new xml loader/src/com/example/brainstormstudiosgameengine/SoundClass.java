package com.example.brainstormstudiosgameengine;


import java.io.IOException;
import java.io.InputStream;

import android.util.Log;


public class SoundClass
{
    static
    {
        // make sure al-android is loaded before any shared libraries that use it
        System.loadLibrary("al-android");
        System.loadLibrary("ogg-decoder");
    }
    
    public static final int BUFFER_COUNT = 4;
    public static final String AUDIO_FILE = "beats.ogg";
    
    public static native boolean oggInitialize( byte[] rawData );
    public static native int oggGetRate();
    public static native int oggGetChannels();
    public static native byte[] oggDecode();
    public static native void oggCleanup();
    
    
    public void loadSound()
    {
    	Log.v( "ALANDemo", "Starting up AL-Android" );
    	if( !ALAN.create() || checkALError() )
    	{
    		Log.e( "ALANDemo", "Error starting up AL-Android" );
    		cleanup();
        	return;
    	}
    	
        byte[] rawData = readRawData( AUDIO_FILE );
        if( rawData == null )
        {
    		Log.e( "ALANDemo", "No raw data was read" );
        	cleanup();
        }
 
    	Log.v( "ALANDemo", "Initializing Ogg decoder" );
    	if( !oggInitialize( rawData ) )
    	{
    		Log.e( "ALANDemo", "Ogg stream was not initialized" );
        	cleanup();
    	}
    	
    	int rate = oggGetRate();
    	int channels = oggGetChannels();
    	int format = ( channels == 1 ? ALAN.AL_FORMAT_MONO16 : ALAN.AL_FORMAT_STEREO16 );
    	int[] ALBufferIDs = new int[BUFFER_COUNT];
    	
    	Log.v( "ALANDemo", "Creating a source" );
    	int[] source = new int[1];
    	ALAN.alGenSources( 1, source );
    	checkALError();
    	
    	Log.v( "ALANDemo", "Generating buffer IDs" );
    	ALAN.alGenBuffers( BUFFER_COUNT, ALBufferIDs );
    	checkALError();
    	
    	Log.v( "ALANDemo", "Generating initial stream buffers" );
    	byte[] buffer = null;
    	int c = 0;
   	    for( int i = 0; i < BUFFER_COUNT; i++ )
   	    {
   	        buffer = oggDecode();
   	        if( buffer == null )
   	        	break;  // Finished reading data
            ALAN.alBufferData( ALBufferIDs[i], format, buffer, buffer.length, rate );
            checkALError();
            c++;
   	    }
   	    if( c == 0 )
   	    {
    		Log.e( "ALANDemo", "No initial buffers were read" );
        	cleanup();
   	    }
   	    
    	Log.v( "ALANDemo", "Queueing up initial stream buffers" );
        ALAN.alSourceQueueBuffers( source[0], c, ALBufferIDs );
        checkALError();
    	
    	Log.v( "ALANDemo", "Setting the source's volume" );
        ALAN.alSourcef( source[0], ALAN.AL_GAIN, 0.3f );
        checkALError();

    	Log.v( "ALANDemo", "Initiating playback" );
        ALAN.alSourcePlay( source[0] );
        checkALError();
        
    	Log.v( "ALANDemo", "Entering stream loop" );
        boolean endOfStream = false;
        int[] processed = new int[1];
        int[] state = new int[1];
        while( !endOfStream )
        {
        	// See if any buffers have finished processing:
            ALAN.alGetSourcei( source[0], ALAN.AL_BUFFERS_PROCESSED, processed );
            checkALError();

            // If so, queue up some more:
            for( ; processed[0] > 0; processed[0]-- )
            {
            	// dequeue a finished buffer:
                ALAN.alSourceUnqueueBuffers( source[0], 1, ALBufferIDs );
                checkALError();
                
                // decode some more audio data:
       	        buffer = oggDecode();
       	        if( buffer == null )
       	        {
       	        	Log.v( "ALANDemo", "Reached end of stream" );
       	        	endOfStream = true;
       	        	break;
       	        }
       	        
       	        // generate a new buffer and queue it up:
                ALAN.alBufferData( ALBufferIDs[0], format, buffer, buffer.length, rate );
                checkALError();
                ALAN.alSourceQueueBuffers( source[0], 1, ALBufferIDs );
                checkALError();
            }

            // Make sure the source didn't stop playing while we were busy decoding:
            ALAN.alGetSourcei( source[0], ALAN.AL_SOURCE_STATE, state );
            checkALError();
            if( state[0] != ALAN.AL_PLAYING )
                ALAN.alSourcePlay( source[0] );
            
            try{ Thread.sleep( 10 ); }
                catch( InterruptedException ie ){}
        }
       	Log.v( "ALANDemo", "Waiting for source to finish playing" );
        ALAN.alGetSourcei( source[0], ALAN.AL_SOURCE_STATE, state );
        checkALError();
        while( state[0] == ALAN.AL_PLAYING )
        {
            try{ Thread.sleep( 10 ); }
                catch( InterruptedException ie ){}
			ALAN.alGetSourcei( source[0], ALAN.AL_SOURCE_STATE, state );
			checkALError();
        }
        
       	Log.v( "ALANDemo", "Finished playing the source" );
        
        cleanup();
    }
    
    public boolean checkALError()
    {
    	int erID = ALAN.alGetError();
    	if(erID != ALAN.AL_NO_ERROR )
    	{
            Log.e( "ALANDemo", "OpenAL error: " + Integer.toHexString(erID) );
            return true;
        }
    	return false;
    }
    
    public void cleanup()
    {
    	Log.v( "ALANDemo", "Cleaning up" );
    	ALAN.destroy();
    	
    	Log.v( "ALANDemo", "Goodbye.  Hope you had fun!" );
        System.runFinalizersOnExit( true );
        System.exit(0);
    }
    
    public byte[] readRawData( String filename )
    {
    	Log.v( "ALANDemo", "Opening audio file" );
    	byte[] data = null;
        InputStream is = null;
    	try
    	{
    		is = BSRenderer.context.getAssets().open( filename );
    	}
    	catch( IOException ioe )
    	{
    		Log.e( "ALANDemo", "Error opening audio file '" + filename + "'" );
        	return null;
    	}
    	Log.v( "ALANDemo", "Reading raw audio data" );
    	try
    	{
    		int length = is.available();
            data = new byte[length];
            is.read(data);
    	}
    	catch( IOException ioe )
    	{
    		Log.e( "ALANDemo", "Error reading from file '" + filename + "'" );
        	return null;
    	}
    	Log.v( "ALANDemo", "Closing audio file" );
    	try
    	{
    		is.close();
    	}
    	catch( IOException ioe )
    	{}
    	
    	return data;
    }
}
