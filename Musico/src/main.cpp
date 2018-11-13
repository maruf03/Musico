#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	settings.setPosition(ofVec2f(100, 100));
	settings.resizable = false;
	settings.title = "Musico";

	ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
