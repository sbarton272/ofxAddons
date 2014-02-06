#include "testApp.h"

using namespace ofxCv;
using namespace cv;

const string testApp::IMG_FILENAME = "faces/face";
const string testApp::IMG_FILEEXT = "png";
const string testApp::SETTINGS_FILE = "settings.xml";
const string testApp::FACE_SETTINGS = "haarcascade_frontalface_alt2.xml";


//--------------------------------------------------------------
void testApp::setup(){

    gui = new ofxUICanvas();
	gui->addLabel("BUTTONS/TOGGLES", OFX_UI_FONT_LARGE);
    gui->addSpacer();
	gui->addLabel("BUTTONS");
    gui->addButton("B1", false, 44, 44);
    gui->addButton("B2", false);
    gui->addSpacer();
	gui->addLabel("TOGGLES");
    gui->addToggle("T1", false, 44, 44);
    gui->addToggle("T2", false);
    gui->addSpacer();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    gui->autoSizeToFitWidgets();
    gui->toggleVisible();

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
    bTakePic = false;

    // reset window size to fit video
    ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);

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

    if(finder.size() > 0) {
        // assume only one object detected which is the face
        ofRectangle faceBox = finder.getObjectSmoothed(0);

        // determine if face is centered and large enough
        ofPoint faceCntr = faceBox.getCenter();

        float windowCntrX = (float)(WINDOW_WIDTH / 2);
        float windowCntrY = (float)(WINDOW_HEIGHT / 2);
        float cntrDist = ofDist(windowCntrX, windowCntrY, faceCntr.x, faceCntr.y);

        if ( (cntrDist <= MAX_CENTERDIST) &&
             (faceBox.getHeight() >= MIN_HEIGHT ) ) {
            bTakePic = true;
        } else {
            bTakePic = false;
        }

    } else {
        // nothing found so don't take pic
        bTakePic = false;
    }

    // take picture
    if (bTakePic) {
        img.setFromPixels(cam.getPixelsRef());

        string fileName = IMG_FILENAME + '-' + todayDate + '.' + ofToString(IMG_FILEEXT);
        img.saveImage(fileName);
        cout << "saved " << fileName.c_str() << endl;

        // photo taken so exit
        XML.save(SETTINGS_FILE);
        std::exit(0);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if( bTakePic ) {
        // pic not yet taken
        ofBackground(100,255,100);
    } else {
        // pic taken, change color
        ofBackground(0);
    }

    cam.draw(CAM_H_OFFSET, CAM_W_OFFSET);
    finder.draw();
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

//----------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();

    if(kind == OFX_UI_WIDGET_BUTTON)
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << name << "\t value: " << button->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_IMAGEBUTTON)
    {
        ofxUIImageButton *button = (ofxUIImageButton *) e.widget;
        cout << name << "\t value: " << button->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_IMAGETOGGLE)
    {
        ofxUIImageToggle *toggle = (ofxUIImageToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
	else if(kind == OFX_UI_WIDGET_LABELBUTTON)
    {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
        cout << name << "\t value: " << button->getValue() << endl;
    }
    else if(kind == OFX_UI_WIDGET_LABELTOGGLE)
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
    }
	else if(name == "B1")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << "value: " << button->getValue() << endl;
	}
    else if(name == "B2")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << "value: " << button->getValue() << endl;
    }
    else if(name == "T1")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << "value: " << toggle->getValue() << endl;
    }
    else if(name == "T2")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << "value: " << toggle->getValue() << endl;
    }
}
