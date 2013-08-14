#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	this->message = "Drag a movie file onto this window to convert.";
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
}

//--------------------------------------------------------------
void testApp::update(){
	float fps = 10.0f;

	for(auto & file : this->toConvert) {
		Poco::Path path(file);
		this->video.loadMovie(path.toString());
		int width = this->video.getWidth();
		int height = this->video.getHeight();
		
		this->encoder.setup(width, height, 1.0f / fps, 256);
		
		int outputFrameCount = this->video.getDuration() * fps;
		int inputFrameCount = this->video.getTotalNumFrames();
		
		for(int i=0; i<outputFrameCount; i++) {
			int inputFrameIndex = (float) i / (float) outputFrameCount * (float) inputFrameCount;
			this->video.setFrame(inputFrameIndex);
			this->video.update();
			this->encoder.addFrame(this->video.getPixels(), width, height, 24, 1.0f / fps);
		}
		
		auto outPath = path;
		outPath.setExtension("png");
		this->encoder.save(outPath.toString());
		
		this->message = "Saving png to " + outPath.toString();
	}
	this->toConvert.clear();
}

//--------------------------------------------------------------
void testApp::draw(){
	this->video.draw(0,0);
	ofDrawBitmapStringHighlight(this->message, 20,20, ofColor::gray, ofColor::black);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	for(auto & file : dragInfo.files) {
		this->toConvert.push_back(file);
	}
	
}

//--------------------------------------------------------------
void testApp::onGifSaved(string &filename) {
	this->message = "Png saved to " + filename + "\nDrag another movie file onto this window to convert.";
}