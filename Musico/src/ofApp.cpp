#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(50);
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();

	//Default Theme Override
	defaultTheme = new ofxDatGuiTheme();
	defaultTheme->font.size = 10;
	defaultTheme->init();

	//Default Font
	font.load("ofxbraitsch\\fonts\\Verdana.ttf", DEFAULT_FONT_SIZE);

	//Default scene
	currentState = MAIN;
	prevState = MAIN;
	
	//Setup all scenes
	MainMenuSetup();
	EffectMenuSetup();
	SpectrumMenuSetup();
	InstrumentMenuSetup();
	SynthesizerMenuSetup();
	AudioFingerprintMenuSetup();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	if (prevState != currentState) {
		switch (prevState)
		{
		case MAIN:
			break;
		case SPECTRUM:
			spectrumAudio.stop();
			break;
		case INSTRUMENT:
			break;
		case EFFECT:
			effectAudio.stop();
			break;
		case SYNTH:
			synthStream.stop();
			synthOutput.clear();
			break;
		case AUDIOFINGERPRINT:
			break;
		default:
			break;
		}
	}
	switch (currentState) {
	case MAIN:
		MainMenuUpdate();
		break;
	case EFFECT:
		EffectMenuUpdate();
		break;
	case SPECTRUM:
		SpectrumMenuUpdate();
		break;
	case INSTRUMENT:
		InstrumentMenuUpdate();
		break;
	case SYNTH:
		synthStream.start();
		SynthesizerMenuUpdate();
		break;
	case AUDIOFINGERPRINT:
		AudioFingerprintMenuUpdate();
		break;
	default:
		MainMenuUpdate();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	switch (currentState) {
	case MAIN:
		MainMenuDraw();
		break;
	case EFFECT:
		EffectMenuDraw();
		break;
	case SPECTRUM:
		SpectrumMenuDraw();
		break;
	case INSTRUMENT:
		InstrumentMenuDraw();
		break;
	case SYNTH:
		SynthesizerMenuDraw();
		break;
	case AUDIOFINGERPRINT:
		AudioFingerprintMenuDraw();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'a':
		break;
	case 'b':
		if (currentState == INSTRUMENT) {
			snare.play();
		}
		break;
	case 'c':
		break;
	case 'd':
		if (currentState == INSTRUMENT) {
			closedHH.play();
		}
		break;
	case 'e':
		if (currentState == INSTRUMENT) {
			crashHigh.play();
		}
		break;
	case 'f':
		if (currentState == INSTRUMENT) {
			tomRockHigh.play();
		}
		break;
	case 'g':
		break;
	case 'h':
		if (currentState == INSTRUMENT) {
			tomRockLow.play();
		}
		break;
	case 'i':
		break;
	case 'j':
		break;
	case 'k':
		if (currentState == INSTRUMENT) {
			cowbell.play();
		}
		break;
	case 'l':
		if (currentState == INSTRUMENT) {
			ride.play();
		}
		break;
	case 'm':
		if (currentState == INSTRUMENT) {
			floor.play();
		}
		break;
	case 'n':
		break;
	case 'o':
		break;
	case 'p':
		break;
	case 'q':
		break;
	case 'r':
		break;
	case 's':
		break;
	case 't':
		if (currentState == INSTRUMENT) {
			crashRock.play();
		}
		break;
	case 'u':
		if (currentState == INSTRUMENT) {
			crashJazz.play();
		}
		break;
	case 'v':
		if (currentState == INSTRUMENT) {
			snare.play();
		}
		break;
	case 'w':
		break;
	case 'x':
		if (currentState == INSTRUMENT) {
			openHH.play();
		}
		break;
	case 'y':
		break;
	case 'z':
		break;
	case ' ':
		if (currentState == INSTRUMENT) {
			kick.play();
		}
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	switch (currentState) {
	case MAIN:
		break;
	case EFFECT:
		break;
	case SPECTRUM:
		break;
	case INSTRUMENT:
		break;
	case SYNTH:
		synthFrequency = ofMap(x, 0, 800, 40, 2000);
		synthPhaseIncrement = (TWO_PI * synthFrequency / 2) / (float)44100;
		synthAmplitude = ofMap(y, 0, 600, 0.5, 0.0);
		break;
	case AUDIOFINGERPRINT:
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::exit() {
	synthStream.close();
}