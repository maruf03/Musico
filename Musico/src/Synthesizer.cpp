#include "ofApp.h"

void ofApp::SynthesizerMenuSetup() {
	synthMenu = new ofxDatGui();
	synthMenu->setTheme(defaultTheme);
	synthMenu->setWidth(224);
	synthMenu->setPosition(0, 500);

	synthMenu->addHeader("Synthesizer");
	synthMenu->addButton("Save");

	synthMenu->onButtonEvent(this, &ofApp::SynthesizerMenuButtonEvent);

	synthMenu->setAutoDraw(false);

	synthFrequency = 440;
	synthAmplitude = 0.1;
	synthPhase = 0;
	synthPhaseIncrement = (TWO_PI * synthFrequency / 2) / (float)44100;
	ofSoundSetVolume(0.3f);
	synthStream.setup(2, 0, 44100, 512, 4);
	synthStream.stop();
}

void ofApp::SynthesizerMenuUpdate() {
	synthMenu->update();
}

void ofApp::SynthesizerMenuDraw() {
	synthMenu->draw();
	ofSetColor(255, 255, 255);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(40, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(255, 255, 0);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(140, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(255, 0, 0);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(240, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(100, 100, 100);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(340, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(120, 120, 120);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(440, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(100, 100, 100);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(540, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(255, 0, 0);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(640, 50 * i + 20, synthFrequency / 120);
	}

	ofSetColor(255, 255, 255);
	for (int i = 0; i < 12; i++) {
		ofDrawCircle(740, 50 * i + 20, synthFrequency / 120);
	}
}

void ofApp::SynthesizerMenuButtonEvent(ofxDatGuiButtonEvent e) {
	if (e.target->getLabel() == "Save") {
		synthStream.stop();
		ofFileDialogResult file = ofSystemSaveDialog("untitled.wav", "Save as");
		string filename = file.getPath();
		ofstream f(filename.c_str(), ios::binary);

		// Write the file headers
		f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
		write_word(f, 16, 4);  // no extension data
		write_word(f, 1, 2);  // PCM - integer samples
		write_word(f, 2, 2);  // two channels (stereo file)
		write_word(f, 44100, 4);  // samples per second (Hz)
		write_word(f, 176400, 4);  // (Sample Rate * BitsPerSample * Channels) / 8
		write_word(f, 4, 2);  // data block size (size of two integer samples, one for each channel, in bytes)
		write_word(f, 16, 2);  // number of bits per sample (use a multiple of 8)

							   // Write the data chunk header
		size_t data_chunk_pos = f.tellp();
		f << "data----";  // (chunk size to be filled in later)
		for (int i = 0; i < synthOutput.size(); i++) {
			write_word(f, (int)synthOutput[i], 2);
		}
		// (We'll need the final file size to fix the chunk sizes above)
		size_t file_length = f.tellp();

		// Fix the data chunk header to contain the data size
		f.seekp(data_chunk_pos + 4);
		write_word(f, file_length - data_chunk_pos + 8);

		// Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
		f.seekp(0 + 4);
		write_word(f, file_length - 8, 4);
		ofSystemAlertDialog("File Saved Successfully");
		synthStream.start();
	}
}

void ofApp::audioOut(float *buffer, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		float currentSample = 0;
		short val;
		currentSample = sin(synthPhase)*synthAmplitude;
		synthPhase += synthPhaseIncrement;
		buffer[i*nChannels + 0] = currentSample;
		buffer[i*nChannels + 1] = currentSample;
		val = ofMap(currentSample, 0, 0.5, -32768, 32767);
		synthOutput.push_back(val);
		synthOutput.push_back(val);
	}
}