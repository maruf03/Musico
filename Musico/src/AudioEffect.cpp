#include "ofApp.h"

void ofApp::EffectMenuSetup() {
	effectGui = new ofxDatGui();
	effectGui->setTheme(defaultTheme);
	effectGui->setWidth(DEFAULT_WIDGET_WIDTH);
	effectGui->setPosition(200, 0);

	effectGui->addLabel("File");
	effectGui->addButton("Load");
	effectGui->addButton("Play");

	effectGui->addSlider(effectVolumeParameter.set("Volume", 0.3, 0.0, 1.0));

	effectList.push_back("NORMAL");
	effectList.push_back("GRIM");
	effectList.push_back("FUNNY");

	effectGui->addDropdown("Effects", effectList);
	
	

	effectGui->onDropdownEvent(this, &ofApp::EffectMenuDropdownEvent);
	effectGui->onButtonEvent(this, &ofApp::EffectMenuButtonEvent);
	effectGui->onSliderEvent(this, &ofApp::EffectMenuSliderEvent);

	effectGui->setAutoDraw(false);

	effectFftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++) {
		effectFftSmooth[i] = 0;
	}

	effectBands = 64;

	effectBandwidth = ofGetWindowWidth() / float(effectBands);
}


void ofApp::EffectMenuUpdate() {
	effectGui->update();

	effectBandwidth = ofGetWindowWidth() / float(effectBands);

	float *value = ofSoundGetSpectrum(effectBands);
	for (int i = 0; i < effectBands; i++) {
		effectFftSmooth[i] *= 0.9f;
		if (effectFftSmooth[i] < value[i]) {
			effectFftSmooth[i] = value[i];
		}
	}
}


void ofApp::EffectMenuDraw() {
	effectGui->draw();

	for (int i = 0; i < effectBands; i++) {
		ofSetColor(255, 0, 0);
		ofDrawRectangle(0 + effectBandwidth * i, ofGetWindowHeight(), effectBandwidth, -(effectFftSmooth[i] * 250));
	}

}

void ofApp::EffectMenuDropdownEvent(ofxDatGuiDropdownEvent e) {
	switch(e.child) {
	case 0:
		effectAudio.setSpeed(1.0);
		break;
	case 1:
		effectAudio.setSpeed(0.5f);
		break;
	case 2:
		effectAudio.setSpeed(1.5f);
		break;
	default:
		break;
	}
}

void ofApp::EffectMenuButtonEvent(ofxDatGuiButtonEvent e) {
	if (e.target->getLabel() == "Load") {
		ofFileDialogResult file = ofSystemLoadDialog("Open Audio File");
		string filename = file.getPath();
		effectAudio.load(filename);
	}
	else if (e.target->getLabel() == "Play") {
		if (effectAudio.isLoaded()) {
			effectAudio.play();
			e.target->setLabel("Stop");
		}
		else {
			ofSystemAlertDialog("Audio not Loaded");
		}
	}
	else if (e.target->getLabel() == "Stop") {
		if (effectAudio.isLoaded()) {
			effectAudio.stop();
			e.target->setLabel("Play");
		}
		else {
			ofSystemAlertDialog("Audio not Loaded");
		}
	}
}

void ofApp::EffectMenuSliderEvent(ofxDatGuiSliderEvent e) {
	effectAudio.setVolume(effectVolumeParameter);
}