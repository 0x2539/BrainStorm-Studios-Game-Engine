package com.BrainStormStudios;

public class BSMainLib 
{
	public static int xTouch = -1, yTouch = -1;
    static 
    {
        System.loadLibrary("BSView");
    }
    
    public static native void init(int width, int height, String apkPath);
    public static native void step(int x, int y);

}
