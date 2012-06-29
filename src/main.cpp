#include "ofMain.h"
#include "testApp.h"

// Windows
// #include "ofAppGlutWindow.h"

//========================================================================
int main() {

	// Windows
    // ofAppGlutWindow window;
	// ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context
	navigator_set_orientation( 90, NULL );
	navigator_set_window_angle( 90 );
	navigator_rotation_lock( true );

	ofAppQNXWindow window;
	ofSetupOpenGL(&window, 1280, 768, OF_WINDOW);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

	return 0;
}
