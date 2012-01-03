#pragma once


#include "ofMain.h"
#include "ofxDirList.h"
#include "ofxVectorMath.h"
#include "ofxXmlSettings.h"

#include "ofxBox2d.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);
	
		//from ofxBox2D joint example
	ofxBox2d		box2d;
	ofxBox2dJoint	joints[5];
	ofxBox2dCircle	circles[5];
	
	int				index;
	int				num;
	
	bool clearBack;
	
	ofColor colour;
	ofColor midTopColour;
	ofColor midBottomColour;
	ofColor bottomColour;	
	float boundaryVerticalPosition;
	
		//poly shapes
	vector	<ofxBox2dPolygon> polygons;		  //	default box2d polygons	
	vector		<ofxVec2f>			polyShape;
	
	bool drawing;
	
	ofxXmlSettings XML;
	int lastTagNumber;
};
