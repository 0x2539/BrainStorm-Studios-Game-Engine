/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include "BSValues.h"
#include "BSUtilities.h"
#include "main.h"

//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "BS-Activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "BS-Activity", __VA_ARGS__))

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

struct android_app* androidOpener;

/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
    		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, //important
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
    const EGLint attrib_list [] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    context = eglCreateContext(display, config, NULL, attrib_list);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;


    glEnable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );

    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	setupGraphics(w, h);
	//BSUtilities *rend = new BSUtilities();
	//rend->loadGP(w, h);

    // Initialize GL state.
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glDisable(GL_DEPTH_TEST);

    return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine) {
    if (engine->display == NULL) {
        // No display.
        return;
    }

    // Just fill the screen with a color.
    //glClearColor(((float)engine->state.x)/engine->width, engine->state.angle,
      //      ((float)engine->state.y)/engine->height, 1);
    //glClear(GL_COLOR_BUFFER_BIT);

    renderFrame();

    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
    struct engine* engine = (struct engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
    	if (AMotionEvent_getFlags(event) == AMOTION_EVENT_ACTION_DOWN)
    	{
    		LOGI("%s", "is down");
    	}
    	//else
        	if (AMotionEvent_getFlags(event) == AMOTION_EVENT_ACTION_UP)
    		{
        		LOGI("%s", "is up");
    		}

        engine->animating = 1;
        xTouch = AMotionEvent_getX(event, 0);
        yTouch = AMotionEvent_getY(event, 0);
        lastMovementPosition.x = xTouch;
        lastMovementPosition.y = yTouch;

		isButtonDown = false;
		//startPoint = lastMovementPosition;


    	//LOGI("%i  %i", lastMovementPosition.x, lastMovementPosition.y);
        //engine->state.x = AMotionEvent_getX(event, 0);
        //engine->state.y = AMotionEvent_getY(event, 0);
        return 1;
    }
 	//LOGI("%i  %i", lastMovementPosition.x, lastMovementPosition.y);
 	return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                engine_init_display(engine);
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                        engine->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
            }
            // Also stop animating.
            engine->animating = 0;
            engine_draw_frame(engine);
            break;
    }
}

double getDistance(int x1, int y1, int x2, int y2)
{
    return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) );
}

static bool isTouchInButtonRange(BackButton *btn, BSPoint point)
{
	if(point.x < btn->x * cross_platform_scale - (btn->w * cross_platform_scale) / 2)
	{
		return false;
	}
	if(point.x > btn->x * cross_platform_scale + (btn->w * cross_platform_scale) / 2)
	{
		return false;
	}
	if(point.y < btn->y * cross_platform_scale - (btn->h * cross_platform_scale) / 2)
	{
		return false;
	}
	if(point.y > btn->y * cross_platform_scale + (btn->h * cross_platform_scale) / 2)
	{
		return false;
	}
	return true;
}

static void onTouchBegin()
{
	if(isTouchInButtonRange(backBtn, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
	           hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
	{
		//std::cout<<"hold back"<<'\n';
		isButtonDown = true;
		backBtn->isDown = true;
		startPoint.x = 0;
		startPoint.y = 0;
	}
	else
		if(isTouchInButtonRange(btnDarkLevels, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
		   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
		{
			//std::cout<<"hold dark"<<'\n';
			isButtonDown = true;
			btnDarkLevels->isDown = true;
			startPoint.x = 0;
			startPoint.y = 0;
		}
		else
			if(isTouchInButtonRange(btnTimeControl, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
			   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
			{
				//std::cout<<"hold time"<<'\n';
				isButtonDown = true;
				btnTimeControl->isDown = true;
				startPoint.x = 0;
				startPoint.y = 0;
			}
			else
				if(isTouchInButtonRange(btnPowerUp1, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
				   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
				{
					//std::cout<<"hold power 1"<<'\n';
					isButtonDown = true;
					btnPowerUp1->isDown = true;
					startPoint.x = 0;
					startPoint.y = 0;
				}
				else
					if(isTouchInButtonRange(btnPowerUp2, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
					   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
					{
						//std::cout<<"hold power 2"<<'\n';
						isButtonDown = true;
						btnPowerUp2->isDown = true;
						startPoint.x = 0;
						startPoint.y = 0;
					}
					else
						if(isTouchInButtonRange(btnPowerUp3, lastMovementPosition) && levelChoserPlayer->justFinished == false && deadScene->CosValueColorOfTheScene == 0 &&
						   hero->heroIsDead == false && deadScene->SinValueColorOfTheScene == 0)
						{
							//std::cout<<"hold power 3"<<'\n';
							isButtonDown = true;
							btnPowerUp3->isDown = true;
							startPoint.x = 0;
							startPoint.y = 0;
						}
						else
						{
							isButtonDown = false;
							startPoint = lastMovementPosition;
						}
}

static void onTouchEnd()
{
	if(isTouchInButtonRange(backBtn, lastMovementPosition) && backBtn->isDown == true)
	{
		//std::cout<<"clicked back"<<'\n';
		backBtn->isDown = false;
		backBtn->canClick = true;
		endPoint.x = 0;
		endPoint.y = 0;
		moved = false;
		tapped = false;
	}
	else
		if(isTouchInButtonRange(btnDarkLevels, lastMovementPosition) && btnDarkLevels->isDown == true)
		{
			//std::cout<<"clicked dark"<<'\n';
			btnDarkLevels->isDown = false;
			btnDarkLevels->canClick = true;
			endPoint.x = 0;
			endPoint.y = 0;
			moved = false;
			tapped = false;
		}
		else
			if(isTouchInButtonRange(btnTimeControl, lastMovementPosition) && btnTimeControl->isDown == true)
			{
				//std::cout<<"clicked time"<<'\n';
				btnTimeControl->isDown = false;
				btnTimeControl->canClick = true;
				endPoint.x = 0;
				endPoint.y = 0;
				moved = false;
				tapped = false;
			}
			else
				if(isTouchInButtonRange(btnPowerUp1, lastMovementPosition) && btnPowerUp1->isDown)
				{
					//std::cout<<"clicked power 1"<<'\n';
					btnPowerUp1->isDown = false;
					btnPowerUp1->canClick = true;
					endPoint.x = 0;
					endPoint.y = 0;
					moved = false;
					tapped = false;
				}
				else
					if(isTouchInButtonRange(btnPowerUp2, lastMovementPosition) && btnPowerUp2->isDown)
					{
						//std::cout<<"clicked power 2"<<'\n';
						btnPowerUp2->isDown = false;
						btnPowerUp2->canClick = true;
						endPoint.x = 0;
						endPoint.y = 0;
						moved = false;
						tapped = false;
					}
					else
						if(isTouchInButtonRange(btnPowerUp3, lastMovementPosition) && btnPowerUp3->isDown)
						{
							//std::cout<<"clicked power 3"<<'\n';
							btnPowerUp3->isDown = false;
							btnPowerUp3->canClick = true;
							endPoint.x = 0;
							endPoint.y = 0;
							moved = false;
							tapped = false;
						}
						else
						{
							isButtonDown = false;

							backBtn->isDown = false;
							backBtn->canClick = false;
							btnTimeControl->isDown = false;
							btnTimeControl->canClick = false;
							btnDarkLevels->isDown = false;
							btnDarkLevels->canClick = false;

							btnPowerUp1->isDown = false;
							btnPowerUp1->canClick = false;
							btnPowerUp2->isDown = false;
							btnPowerUp2->canClick = false;
							btnPowerUp3->isDown = false;
							btnPowerUp3->canClick = false;

							endPoint = lastMovementPosition;
							lastMovementPosition.x = 0;
							lastMovementPosition.y = 0;

							movedX = endPoint.x - startPoint.x;
							movedY = -endPoint.y + startPoint.y;
							swipeDistance = getDistance(startPoint.x, startPoint.y, endPoint.x, endPoint.y);

							if(movedX == 0)
							{
								movedX++;
							}
							if(movedY == 0)
							{
								movedY++;
							}

							//when tap the screen
							if(abs(movedX) < 10 && abs(movedY) < 10)
							{
								tapX = (startPoint.x + endPoint.x ) / 2;
								tapY = (startPoint.y + endPoint.y ) / 2;
								tapped = true;
								moved = false;
								//std::cout<<"tapped"<<'\n';
							}
							else
							{
								moved = true;
								tapped = false;
							}

							LOGI("%i %i : %i %i", startPoint.x, startPoint.y, endPoint.x, endPoint.y);
						}
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    struct engine engine;


    	ANativeActivity* activity = state->activity;
        JNIEnv* env=0;

        activity->vm->AttachCurrentThread(&env, 0);

        jclass clazz = env->GetObjectClass(activity->clazz);
        jmethodID methodID = env->GetMethodID(clazz, "getPackageCodePath", "()Ljava/lang/String;");
        jobject result = env->CallObjectMethod(activity->clazz, methodID);

        const char* str;
        jboolean isCopy;
        str = env->GetStringUTFChars((jstring)result, &isCopy);
        LOGI("Looked up package code path: %s", str);

        activity->vm->DetachCurrentThread();

    loadAPK(str);
    // Make sure glue isn't stripped.
    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    // Prepare to monitor accelerometer
    //engine.sensorManager = ASensorManager_getInstance();
    //engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    //engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL)
    {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*)state->savedState;
    }
    androidOpener = state;

    long long nr = 0;
	BSPoint lastLastPos = {0, 0};
    // loop waiting for stuff to do.
    while (1)
    {
    	lastLastPos = lastMovementPosition;
        lastMovementPosition.x = 0;
        lastMovementPosition.y = 0;
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;
        //engine.animating = 1;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(1, NULL, &events, (void**)&source)) >= 0)
        {
            //engine.animating = 1;
            // Process this event.
            if (source != NULL)
            {
                source->process(state, source);
            }
            //printGLString("Version", GL_VERSION);
            //printGLString("Vendor", GL_VENDOR);
            //printGLString("Renderer", GL_RENDERER);
            //printGLString("Extensions", GL_EXTENSIONS);

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER)
            {
                if (engine.accelerometerSensor != NULL)
                {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue, &event, 1) > 0)
                    {
                        //LOGI("accelerometer: x=%f y=%f z=%f",
                        //        event.acceleration.x, event.acceleration.y,
                        //        event.acceleration.z);
                    }
                }
			}

            // Check if we are exiting.
            if (state->destroyRequested != 0)
            {
                engine_term_display(&engine);
                return;
            }
        }
        if(lastLastPos.x == 0 && lastLastPos.y == 0)
        {
        	nr++;
        	//LOGI("%lli", nr);
        }
        //LOGI("%i %i", lastMovementPosition.x, lastMovementPosition.y);
        //LOGI("%i %i : %i %i", lastLastPos.x, lastLastPos.y, lastMovementPosition.x, lastMovementPosition.y);
        if((lastLastPos.x != 0 && lastMovementPosition.x == 0) || (lastLastPos.y != 0 && lastMovementPosition.y == 0))
        {
        	lastMovementPosition = lastLastPos;
        	onTouchEnd();
        	lastMovementPosition.x = 0;
        	lastMovementPosition.y = 0;
        	//LOGI("%s", "touches ended");
        	///touches ended;
        }
        else
        	if((lastLastPos.x == 0 && lastMovementPosition.x != 0) || (lastLastPos.y == 0 && lastMovementPosition.y != 0))
        	{
        		onTouchBegin();
            	//LOGI("%s", "touches began");
        		///touches began;
        	}
/*
        if (engine.animating) {
            // Done with events; draw next animation frame.
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }*/

            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(&engine);
    }
}

//END_INCLUDE(all)
