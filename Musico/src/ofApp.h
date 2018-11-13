#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define DEFAULT_FONT_SIZE 10
#define DEFAULT_WIDGET_WIDTH 200

typedef struct {
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate;			
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;
}header;

template <typename Word>
std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
{
	for (; size; --size, value >>= 8)
		outs.put(static_cast <char> (value & 0xFF));
	return outs;
}

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void audioOut(float *buffer, int bufferSize, int nChannels);
		void exit();

		/*
		Global State Variables
		*/
		enum State { MAIN, SPECTRUM, INSTRUMENT, EFFECT, SYNTH, AUDIOFINGERPRINT };
		State currentState, prevState;

		/*
		GUI Theme
		*/
		ofxDatGuiTheme *defaultTheme;

		/*
		Global TrueType Font
		*/
		ofTrueTypeFont font;

		/*
		Main Menu Global Handler
		*/
		void MainMenuSetup();
		void MainMenuUpdate();
		void MainMenuDraw();
		void MainMenuButtonEvent(ofxDatGuiButtonEvent e);

		ofxDatGui *mainMenu;
		
		/*
		Spectrum Menu Global Handler 
		*/
		void SpectrumMenuSetup();
		void SpectrumMenuUpdate();
		void SpectrumMenuDraw();
		void SpectrumMenuButtonEvent(ofxDatGuiButtonEvent e);
		void SpectrumMenuSliderEvent(ofxDatGuiSliderEvent e);
		ofxDatGui *spectrumMenu;

		float *spectrumFftSmooth;
		int spectrumBands;
		float spectrumBandwidth;

		ofSoundPlayer spectrumAudio;

		enum SpectrumEffect{BAR, CIRCLE};
		SpectrumEffect currentView;

		ofParameter<float> spectrumVolumeParameter;
		/*
		Instrument Menu Global Handler 
		*/
		void InstrumentMenuSetup();
		void InstrumentMenuUpdate();
		void InstrumentMenuDraw();
		void InstrumentMenuButtonEvent(ofxDatGuiButtonEvent e);
		void InstrumentMenuSliderEvent(ofxDatGuiSliderEvent e);

		ofImage drumBg;
		ofImage imgcrashJazz;
		ofImage imgcrashRock;
		ofImage imgcrashHigh;
		ofImage imgclosedHH;
		ofImage imgopenHH;
		ofImage imgcowbell;
		ofImage imgfloor;
		ofImage imgtomRockHigh;
		ofImage imgtomRockLow;
		ofImage imgkick;
		ofImage imgride;
		ofImage imgsnare;

		ofSoundPlayer crashJazz;
		ofSoundPlayer crashRock;
		ofSoundPlayer crashHigh;
		ofSoundPlayer tomRockHigh;
		ofSoundPlayer tomRockLow;
		ofSoundPlayer kick;
		ofSoundPlayer snare;
		ofSoundPlayer ride;
		ofSoundPlayer closedHH;
		ofSoundPlayer openHH;
		ofSoundPlayer cowbell;
		ofSoundPlayer floor;

		ofParameter<float> instrumentVolumeParameter;

		ofxDatGui *instrumentMenu;
		/*
		Audio Effect Menu Global Handler
		*/
		void EffectMenuSetup();
		void EffectMenuUpdate();
		void EffectMenuDraw();
		void EffectMenuButtonEvent(ofxDatGuiButtonEvent e);
		void EffectMenuDropdownEvent(ofxDatGuiDropdownEvent e);
		void EffectMenuSliderEvent(ofxDatGuiSliderEvent e);


		ofxDatGui *effectGui;

		ofSoundPlayer effectAudio;

		float *effectFftSmooth;
		int effectBands = 64;
		float effectBandwidth;

		vector<string> effectList;

		ofParameter<float> effectVolumeParameter;

		/*
		Synthesizer Menu Global Handler
		*/

		ofxDatGui *synthMenu;

		void SynthesizerMenuSetup();
		void SynthesizerMenuUpdate();
		void SynthesizerMenuDraw();
		void SynthesizerMenuButtonEvent(ofxDatGuiButtonEvent e);

		float synthArray[100];
		ofSoundStream synthStream;

		float synthFrequency;
		float synthPhase;
		float synthAmplitude;
		float synthPhaseIncrement;

		vector<float> synthOutput;
		header *meta;

		ofParameter<float> synthVolume;
		/*
		Audio Fingerprinting Menu Global Handler
		*/
		void AudioFingerprintMenuSetup();
		void AudioFingerprintMenuUpdate();
		void AudioFingerprintMenuDraw();
		void AudioFingerprintMenuButtonEvent(ofxDatGuiButtonEvent e);
		
};
