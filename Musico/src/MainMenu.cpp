#include "ofApp.h"

void ofApp::MainMenuSetup() {
	mainMenu = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	mainMenu->setTheme(defaultTheme);

	mainMenu->addHeader("Menu", false);

	mainMenu->addButton("Spectrum Analysis");
	mainMenu->addButton("Instrument Simulation");
	mainMenu->addButton("Audio Effect");
	mainMenu->addButton("Synthesizer");
	mainMenu->addButton("Audio Fingerprinting");
	mainMenu->addButton("Exit");

	mainMenu->onButtonEvent(this, &ofApp::MainMenuButtonEvent);

	mainMenu->setWidth(224);
	mainMenu->setPosition(800, 0);
	
}


void ofApp::MainMenuUpdate() {
	
}

void ofApp::MainMenuDraw() {
	
}

//Button event function to handle buttons
void ofApp::MainMenuButtonEvent(ofxDatGuiButtonEvent e) {
	if (e.target->getLabel() == "Spectrum Analysis") {
		prevState = currentState;
		currentState = SPECTRUM;
		//cout << "Spectrum Analysis" << currentState << endl;
	}
	else if (e.target->getLabel() == "Instrument Simulation") {
		prevState = currentState;
		currentState = INSTRUMENT;
		//cout << "Instrument Simulation" << currentState << endl;
	}
	else if (e.target->getLabel() == "Audio Effect") {
		prevState = currentState;
		currentState = EFFECT;
	}
	else  if (e.target->getLabel() == "Synthesizer") {
		prevState = currentState;
		currentState = SYNTH;
	}
	else  if (e.target->getLabel() == "Audio Fingerprinting") {
		prevState = currentState;
		currentState = AUDIOFINGERPRINT;
	}
	else if (e.target->getLabel() == "Exit") {
		ofExit();
	}
}
