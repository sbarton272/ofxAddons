#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#define DEBUG true

class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void printAllCameras(void);

		ofVideoGrabber cam;
		ofImage 	   img;
		ofxCv::ObjectFinder finder;
		ofXml XML;

		bool           bTakePic;

		// global constants
		const int CAM_H_OFFSET = 20;
		const int CAM_W_OFFSET = 20;
		const int CAM_WIDTH    = 640;
		const int CAM_HEIGHT   = 480;
		const int CAM_ID	   = 0;
		const string IMG_FILENAME = "faces/face";
		const string IMG_FILEEXT = "png";
		const string SETTINGS_FILE = "settings.xml";
		const string FACE_SETTINGS = "haarcascade_frontalface_alt2.xml";
};
