#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	window.setGlutDisplayString("rgba double samples>=4");  ///smoothing
	ofSetupOpenGL(&window, 1440, 900, OF_FULLSCREEN);			// <-------- setup the GL context //full size	
															//	ofSetupOpenGL(&window, 1920, 1200, OF_WINDOW);			// <-------- setup the GL context //full size
//	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);			// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	ofRunApp( new testApp());

}
