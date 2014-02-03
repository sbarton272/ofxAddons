#include "testApp.h"

using namespace ofxCv;
using namespace cv;

const string testApp::IMG_FILENAME = "faces/face";
const string testApp::IMG_FILEEXT = "png";
const string testApp::SETTINGS_FILE = "settings.xml";
const string testApp::FACE_SETTINGS = "haarcascade_frontalface_alt2.xml";


//--------------------------------------------------------------
void testApp::setup(){

    // load config file and determine if the app should run
    if( !XML.load(SETTINGS_FILE) ){
        // create new
        XML.addChild("PHOTOS");
        XML.setTo("PHOTOS");
        XML.addChild("DATE");
        XML.save(SETTINGS_FILE);
        if (DEBUG) {cout << "Created new XML Settings File" << endl;}
    }

    // today is
    todayDate = ofToString(ofGetYear()) +
                '-' + ofToString(ofGetMonth()) + '-' +
                ofToString(ofGetDay());
    if (DEBUG) { cout << "Today is: " << todayDate << endl;}

    // check date of last photo
    if(XML.exists("//DATE")) {
        if ( todayDate == XML.getValue<string>("//DATE") ) {
            // dates equal so have photo from today already so exit
            std::exit(0);
        }
    }

    if (DEBUG) { cout << "Taking picture" << endl; }

    // take a picture if none taken today, record the date in settings
    XML.setValue("//DATE", todayDate);
    XML.save(SETTINGS_FILE);
    bTakePic = true;

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

        string fileName = IMG_FILENAME + '-' + todayDate + '.' + ofToString(IMG_FILEEXT);
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
