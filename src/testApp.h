#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#define DEBUG false

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
		string		   todayDate;

		// global constants
		const int CAM_H_OFFSET = 20;
		const int CAM_W_OFFSET = 20;
		const int CAM_WIDTH    = 640;
		const int CAM_HEIGHT   = 480;
		const int WINDOW_WIDTH = 2*CAM_W_OFFSET + CAM_WIDTH;
		const int WINDOW_HEIGHT = 2*CAM_W_OFFSET + CAM_HEIGHT;
		const int MAX_CENTERDIST = 10;
		const int MIN_HEIGHT   = 200;
		const int CAM_ID	   = 0;
		static const string IMG_FILENAME;
		static const string IMG_FILEEXT;
		static const string SETTINGS_FILE;
		static const string FACE_SETTINGS;
};
