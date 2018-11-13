#include "ofApp.h"

void ofApp::InstrumentMenuSetup() {
	drumBg.load("drumkit\\gfx\\bg.png");
	drumBg.resize(800, WINDOW_HEIGHT);
	ofBackground(0);

	instrumentMenu = new ofxDatGui();
	instrumentMenu->setTheme(defaultTheme);
	instrumentMenu->setWidth(224);
	instrumentMenu->setPosition(800, 200);

	instrumentMenu->addHeader("Controls", false);

	instrumentMenu->addLabel("KICK : SPACE");
	instrumentMenu->addLabel("SNARE : V/B");
	instrumentMenu->addLabel("FLOOR : M");
	instrumentMenu->addLabel("TOM HIGH : F");
	instrumentMenu->addLabel("TOM LOW : H");
	instrumentMenu->addLabel("RIDE : L");
	instrumentMenu->addLabel("OPEN HI HAT : X");
	instrumentMenu->addLabel("CLOSE HI HAT : D");
	instrumentMenu->addLabel("COWBELL : K");
	instrumentMenu->addLabel("CRASH HIGH: E");
	instrumentMenu->addLabel("CRASH ROCK : T");
	instrumentMenu->addLabel("CRASH JAZZ: U");

	instrumentMenu->addSlider(instrumentVolumeParameter.set("Volume", 0.3, 0.0, 1.0));

	instrumentMenu->onSliderEvent(this, &ofApp::InstrumentMenuSliderEvent);

	instrumentMenu->setAutoDraw(false);

	imgcrashJazz.load("drumkit\\gfx\\crash1.png");
	imgcrashRock.load("drumkit\\gfx\\crash2.png");
	imgcrashHigh.load("drumkit\\gfx\\crash3.png");
	imgtomRockHigh.load("drumkit\\gfx\\tom1.png");
	imgtomRockLow.load("drumkit\\gfx\\tom2.png");
	imgkick.load("drumkit\\gfx\\kick.png");
	imgsnare.load("drumkit\\gfx\\snare.png");
	imgride.load("drumkit\\gfx\\ride.png");
	imgclosedHH.load("drumkit\\gfx\\closehhl.png");
	imgopenHH.load("drumkit\\gfx\\openhhl.png");
	imgcowbell.load("drumkit\\gfx\\cowbellr.png");
	imgfloor.load("drumkit\\gfx\\floorr.png");

	//imgcrashJazz.resize(imgcrashJazz.getWidth()*0.75, imgcrashJazz.getHeight()*0.75);
	//imgcrashRock.resize(imgcrashRock.getWidth()*0.75, imgcrashRock.getHeight()*0.75);
	imgcrashHigh.resize(imgcrashHigh.getWidth()*0.9, imgcrashHigh.getHeight()*0.9);
	imgclosedHH.resize(imgclosedHH.getWidth()*0.9, imgclosedHH.getHeight()*0.9);
	imgopenHH.resize(imgopenHH.getWidth()*0.9, imgopenHH.getHeight()*0.9);
	imgcowbell.resize(imgcowbell.getWidth()*0.75, imgcowbell.getHeight()*0.75);
	//imgfloor.resize(280, 300);
	//imgtomRockHigh.resize(imgtomRockHigh.getWidth()*0.75, imgtomRockHigh.getHeight()*0.75);
	//imgtomRockLow.resize(imgtomRockLow.getWidth()*0.75, imgtomRockLow.getHeight()*0.75);
	imgkick.resize(imgkick.getWidth()*1.25, imgkick.getHeight()*1.25);
	imgride.resize(imgride.getWidth()*0.75, imgride.getHeight()*0.75);
	//imgsnare.resize(imgsnare.getWidth()*0.75, imgsnare.getHeight()*0.75);
	
	crashJazz.load("drumkit\\sfx\\crash1.ogg");
	crashRock.load("drumkit\\sfx\\crash2.ogg");
	crashHigh.load("drumkit\\sfx\\crash3.ogg");
	tomRockHigh.load("drumkit\\sfx\\tom1.ogg");
	tomRockLow.load("drumkit\\sfx\\tom2.ogg");
	kick.load("drumkit\\sfx\\kick.ogg");
	snare.load("drumkit\\sfx\\snare.ogg");
	ride.load("drumkit\\sfx\\ride.ogg");
	closedHH.load("drumkit\\sfx\\closehh.ogg");
	openHH.load("drumkit\\sfx\\openhh.ogg");
	cowbell.load("drumkit\\sfx\\cowbell.ogg");
	floor.load("drumkit\\sfx\\floor.ogg");
}


void ofApp::InstrumentMenuUpdate() {
	instrumentMenu->update();
}

void ofApp::InstrumentMenuDraw() {
	instrumentMenu->draw();
	ofSetColor(255, 255, 255);
	drumBg.draw(0, 0);

	
	imgkick.draw(400 - imgkick.getWidth() / 2, 600 - imgkick.getHeight());
	imgsnare.draw(400 - imgsnare.getWidth() / 2, 600 - imgkick.getHeight() - 150);
	
	imgtomRockHigh.draw(400 - imgtomRockHigh.getWidth(), 0);
	imgtomRockLow.draw(400 , 0);

	imgfloor.draw(800 - imgfloor.getWidth(), 600 - imgfloor.getHeight());

	imgcowbell.draw(550, 270);

	imgride.draw(800 - imgride.getWidth(), 240);

	imgopenHH.draw(10, 600 - imgopenHH.getHeight() - 20);
	imgclosedHH.draw(30, 600 - imgopenHH.getHeight() - 130);
	
	imgcrashJazz.draw(550, 0);
	imgcrashRock.draw(300, 0);
	imgcrashHigh.draw(0, 0);

	
	ofSetColor(255, 255, 255);
}

void ofApp::InstrumentMenuButtonEvent(ofxDatGuiButtonEvent e) {

}

void ofApp::InstrumentMenuSliderEvent(ofxDatGuiSliderEvent e) {
	crashJazz.setVolume(instrumentVolumeParameter);
	crashRock.setVolume(instrumentVolumeParameter);
	crashHigh.setVolume(instrumentVolumeParameter);
	tomRockHigh.setVolume(instrumentVolumeParameter);
	tomRockLow.setVolume(instrumentVolumeParameter);
	kick.setVolume(instrumentVolumeParameter);
	snare.setVolume(instrumentVolumeParameter);
	ride.setVolume(instrumentVolumeParameter);
	closedHH.setVolume(instrumentVolumeParameter);
	openHH.setVolume(instrumentVolumeParameter);
	cowbell.setVolume(instrumentVolumeParameter);
	floor.setVolume(instrumentVolumeParameter);
}