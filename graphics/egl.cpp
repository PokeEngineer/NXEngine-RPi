#include <EGL/egl.h>
#include <SDL/SDL_syswm.h>
#include <X11/Xlib.h>
#include "../common/basics.h"
#include "egl.fdh"

	EGLDisplay g_eglDisplay = 0;
	EGLConfig g_eglConfig = 0;
	EGLContext g_eglContext = 0;
	EGLSurface g_eglSurface = 0;
        Display *g_x11Display = NULL;

// consts
#define COLOURDEPTH_RED_SIZE  		5
#define COLOURDEPTH_GREEN_SIZE 		6
#define COLOURDEPTH_BLUE_SIZE 		5
#define COLOURDEPTH_DEPTH_SIZE		16

static const EGLint g_configAttribs[] ={
										  EGL_RED_SIZE,      	    COLOURDEPTH_RED_SIZE,
										  EGL_GREEN_SIZE,    	    COLOURDEPTH_GREEN_SIZE,
										  EGL_BLUE_SIZE,     	    COLOURDEPTH_BLUE_SIZE,
										  EGL_DEPTH_SIZE,	    COLOURDEPTH_DEPTH_SIZE,
										  EGL_SURFACE_TYPE,         EGL_WINDOW_BIT,
										  EGL_RENDERABLE_TYPE,      EGL_OPENGL_ES_BIT,
										  EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
										  EGL_NONE
									   };

/*===========================================================
Initialise EGL. Call straight after SDL_SetVideoMode()
===========================================================*/

int InitEGL()
{
	// use EGL to initialise DispmanX
	g_x11Display = XOpenDisplay(NULL);

	if (!g_x11Display)
	{
		staterr("ERROR: unable to get display!n");
		return 0;
	}

	g_eglDisplay = eglGetDisplay((EGLNativeDisplayType)g_x11Display);
	if (g_eglDisplay == EGL_NO_DISPLAY)
	{
		staterr("Unable to initialise EGL display.");
		return 0;
	}
	
	// Initialise egl
	if (!eglInitialize(g_eglDisplay, NULL, NULL))
	{
		staterr("Unable to initialise EGL display.");
		return 0;
	}
	
	// Find a matching config
	EGLint numConfigsOut = 0;
	if (eglChooseConfig(g_eglDisplay, g_configAttribs, &g_eglConfig, 1, &numConfigsOut) != EGL_TRUE || numConfigsOut == 0)
	{
		staterr("Unable to find appropriate EGL config.");
		return 0;
	}
	
	// Get the SDL window handle
	SDL_SysWMinfo sysInfo; //Will hold our Window information
	SDL_VERSION(&sysInfo.version); //Set SDL version
	if(SDL_GetWMInfo(&sysInfo) <= 0) 
	{
		staterr("Unable to get window handle");
		return 0;
	}

	g_eglSurface = eglCreateWindowSurface(g_eglDisplay, g_eglConfig, (EGLNativeWindowType)sysInfo.info.x11.window, 0);
	if ( g_eglSurface == EGL_NO_SURFACE)
	{
		staterr("Unable to create EGL surface!");
		return 0;
	}
	return 1;
}

/*======================================================
 * Kill off any EGL specific details
  ====================================================*/
void TerminateEGL()
{
	eglMakeCurrent(g_eglDisplay, NULL, NULL, EGL_NO_CONTEXT);
	eglDestroySurface(g_eglDisplay, g_eglSurface);
	eglDestroyContext(g_eglDisplay, g_eglContext);
	g_eglSurface = 0;
	g_eglContext = 0;
	g_eglConfig = 0;
	eglTerminate(g_eglDisplay);
	g_eglDisplay = 0;
    XCloseDisplay(g_x11Display);
    g_x11Display = NULL;
}


int SwapBuffers()
{
	eglSwapBuffers(g_eglDisplay, g_eglSurface);
}