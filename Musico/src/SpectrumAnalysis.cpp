#include "ofApp.h"

void ofApp::SpectrumMenuSetup() {
	spectrumMenu = new ofxDatGui();
	spectrumMenu->setTheme(defaultTheme);
	spectrumMenu->setWidth(DEFAULT_WIDGET_WIDTH);
	spectrumMenu->setPosition(0, 0);

	spectrumMenu->addLabel("File");
	spectrumMenu->addButton("Load");
	spectrumMenu->addButton("Play");
	spectrumMenu->addBreak();
	spectrumMenu->addLabel("View");
	spectrumMenu->addButton("Circle");
	spectrumMenu->addSlider(spectrumVolumeParameter.set("Volume", 0.3, 0.0, 1.0));


	spectrumMenu->onButtonEvent(this, &ofApp::SpectrumMenuButtonEvent);
	spectrumMenu->onSliderEvent(this, &ofApp::SpectrumMenuSliderEvent);

	spectrumMenu->setAutoDraw(false);

	spectrumFftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++) {
		spectrumFftSmooth[i] = 0;
	}

	spectrumBands = 64;

	spectrumBandwidth = ofGetWindowWidth() / float(spectrumBands);

	spectrumAudio.setLoop(true);
	spectrumAudio.setVolume(0.3f);
}

void ofApp::SpectrumMenuUpdate() {
	spectrumMenu->update();

	spectrumBandwidth = ofGetWindowWidth() / float(spectrumBands);

	float *value = ofSoundGetSpectrum(spectrumBands);
	for (int i = 0; i < spectrumBands; i++) {
		spectrumFftSmooth[i] *= 0.9f;
		if (spectrumFftSmooth[i] < value[i]) {
			spectrumFftSmooth[i] = value[i];
		}
	}

}


void ofApp::SpectrumMenuDraw() {
	spectrumMenu->draw();

	if (currentView == CIRCLE) {
		for (int i = 0; i < spectrumBands; i++) {
			ofSetColor(ofRandom(128, 250), ofRandom(128, 250), ofRandom(128, 250));
			ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(spectrumFftSmooth[i] * 150));
		}
	}
	else if(currentView == BAR){
		for (int i = 0; i < spectrumBands; i++) {
			ofSetColor(250, 0, 0);
			ofDrawRectangle(0 + spectrumBandwidth * i, ofGetWindowHeight(), spectrumBandwidth, -(spectrumFftSmooth[i] * 250));
		}
	}	
}


void ofApp::SpectrumMenuButtonEvent(ofxDatGuiButtonEvent e) {
	if (e.target->getLabel() == "Load") {
		ofFileDialogResult file = ofSystemLoadDialog("Open Audio File");
		string filename = file.getPath();
		spectrumAudio.load(filename);
	}
	else if (e.target->getLabel() == "Play") {
		if (spectrumAudio.isLoaded()) {
			spectrumAudio.play();
			e.target->setLabel("Stop");
		}
		else {
			ofSystemAlertDialog("Audio not Loaded");
		}
	}
	else if (e.target->getLabel() == "Stop") {
		if (spectrumAudio.isLoaded()) {
			spectrumAudio.stop();
			e.target->setLabel("Play");
		}
		else {
			ofSystemAlertDialog("Audio not Loaded");
		}
	}
	else if (e.target->getLabel() == "Circle") {
		currentView = CIRCLE;
		e.target->setLabel("Bar");
	}
	else if (e.target->getLabel() == "Bar") {
		currentView = BAR;
		e.target->setLabel("Circle");
	}
}

void ofApp::SpectrumMenuSliderEvent(ofxDatGuiSliderEvent e) {
	spectrumAudio.setVolume(spectrumVolumeParameter);
}