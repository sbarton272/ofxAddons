#include "testApp.h"

const int VID_H_OFFSET = 20;
const int VID_W_OFFSET = 20;
const int VID_WIDTH    = 640;
const int VID_HEIGHT   = 480;
const string IMG_FILENAME = "test.png";



//--------------------------------------------------------------
void testApp::setup(){

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();

    for(int i = 0; i < devices.size(); i++){
        cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
    }

    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(VID_WIDTH, VID_HEIGHT);

    ofSetVerticalSync(true);

    bTakePic = false;

}

//--------------------------------------------------------------
void testApp::update(){

    vidGrabber.update();

    if (bTakePic) {
        // test save pic
        faceImg.grabScreen(VID_H_OFFSET, VID_W_OFFSET, VID_WIDTH, VID_HEIGHT);

        faceImg.saveImage(IMG_FILENAME);
        cout << "saved " << IMG_FILENAME.c_str() << '\n';

        bTakePic = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);

    vidGrabber.draw(VID_H_OFFSET, VID_W_OFFSET);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    cout << "key: " << key << '\n';
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
