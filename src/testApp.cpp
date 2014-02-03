#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){

    // load config file and determine if the app should run
    XML.load(SETTINGS_FILE);

    // reset window size to fit video
    ofSetWindowShape(2*CAM_W_OFFSET + CAM_WIDTH, 2*CAM_H_OFFSET + CAM_HEIGHT);

    // set-up camera
    if (DEBUG) { printAllCameras(); }
    cam.setDeviceID(CAM_ID);
    cam.setDesiredFrameRate(60);
    cam.initGrabber(CAM_WIDTH, CAM_HEIGHT);

    // set-up face finder
    finder.setup(FACE_SETTINGS);
    finder.setPreset(ObjectFinder::Fast);

    ofSetVerticalSync(true);

    // picture not taken yet
    bTakePic = false;

}

//--------------------------------------------------------------
void testApp::update(){

    cam.update();

    // update face tracker
    if(cam.isFrameNew()) {
        finder.update(cam);
    }

    // take picture
    if (bTakePic) {
        img.setFromPixels(cam.getPixelsRef());

        string fileName = IMG_FILENAME + '-' + ofToString(ofGetYear()) +
                          '-' + ofToString(ofGetMonth()) + '-' +
                          ofToString(ofGetDay()) + '.' + ofToString(IMG_FILEEXT);
        img.saveImage(fileName);
        cout << "saved " << fileName.c_str() << endl;

        bTakePic = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);

    cam.draw(CAM_H_OFFSET, CAM_W_OFFSET);

    finder.draw();
    // face finder text highlighting
    //ofDrawBitmapStringHighlight(ofToString(finder.size()), 10, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    cout << "key: " << key << endl;
    bTakePic = true;
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

}

//--------------------------------------------------------------
// Print available cameras if in debug mode
void testApp::printAllCameras(){

    vector<ofVideoDevice> devices = cam.listDevices();

    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }

}
