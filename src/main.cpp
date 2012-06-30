#include "ofMain.h"
#include "testApp.h"

/*
#include <bps/screen.h>
#include <bps/bps.h>
#include <bps/event.h>
#include <bps/orientation.h>
*/

#include "bbutil.h"
// Windows
// #include "ofAppGlutWindow.h"
//========================================================================
int main() {

//Request and process available BPS events
//    for(;;) {
//        bps_event_t *event = NULL;
//
//        if (event) {
//            int domain = bps_event_get_domain(event);
//            if (domain == navigator_get_domain()) {
//                handleNavigatorEvent(event);
//            }
//        } else {
//            break;
//        }
//    }

	//navigator_rotation_lock( true );
	//navigator_set_orientation( 0, NULL );
	//navigator_set_window_angle( 0 );

	ofAppQNXWindow window;
	ofSetupOpenGL(&window, 1280, 768, OF_FULLSCREEN);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

	return 0;
}
/*
static void handleNavigatorEvent(bps_event_t *event)
{
	int rc;
	bps_event_t *activation_event = NULL;

	int angle = navigator_event_get_orientation_angle(event);

	if(angle > 0 && angle < 90)
	{
		navigator_set_orientation( 0, NULL );
		navigator_set_window_angle( 0 );
	}
	else if(angle > 90 && angle < 180)
	{
		navigator_set_orientation( -90, NULL );
		navigator_set_window_angle( -90 );
	}
	else if(angle > 180 && angle < 270)
	{
		navigator_set_orientation( -180, NULL );
		navigator_set_window_angle( -180 );
	}
	else if(angle > 270 && angle < 360)
	{
		navigator_set_orientation( 90, NULL );
		navigator_set_window_angle( 90 );
	}

	navigator_rotation_lock( true );
}
*/
