
// OF
#include "ofMain.h"
#include "ofAppGlutWindow.h"

// Shared
#include "defines.h"

// PhotoBooth
#include "PhotoBoothApp.h"
#include "PhotoBoothKeyOnly.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
    
	// can be OF_WINDOW or OF_FULLSCREEN
	ofSetupOpenGL(&window, 1200,800, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// pass in width and height too:
	
    
#ifdef KEYBOARD_ONLY
    ofRunApp( new PhotoBoothKeyOnly());
 #else
    ofRunApp( new PhotoBoothApp());
#endif
    
}
