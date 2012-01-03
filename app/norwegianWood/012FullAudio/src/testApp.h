#pragma once


#include "ofMain.h"
#include "ofxDirList.h"
#include "ofxVectorMath.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "ofxVectorGraphics.h"

#include "ofxBox2d.h"

#include "ofxControlPanel.h"

#include "ofxNoise.h"

#include "scene.h"
#include "springScene.h"
#include "summerScene.h"
#include "autumnScene.h"
#include "winterScene.h"

#include "polygonShape.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
	
	void eventsIn(guiCallbackData & data);
	void grabBackgroundEvent(guiCallbackData & data);	

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void resized(int w, int h);
	void loadPolyShapeFromXML(string pathToXML);
	
		//from ofxBox2D joint example
	ofxBox2d		box2d;
	
	bool clearBack;
	
	ofColor colour;
	ofColor midTopColour;
	ofColor midBottomColour;
	ofColor bottomColour;	
	float boundaryVerticalPosition;
	
		//poly shapes
	vector	<PolygonShape> polyShapes;	
	
//		//directory list for shapes
//	ofxDirList   shapeDirLister;	
	
		//from GUI example
	ofxControlPanel gui;
	
	float elapsedTime;
	int appFrameCount;
	float appFrameRate;
	
	ofTrueTypeFont TTF;
	
	float timeOfLastFrame;
	
	bool bShowMouse;
	
		//scenes
	SpringScene spring;
	SummerScene summer;
	AutumnScene autumn;
	WinterScene winter;
	
		//current scene
	Scene* currentScene;
	
		//audio
	void audioReceived 	(float * input, int bufferSize, int nChannels); 
	
	float * left;
	float * right;	
	float audioLevel;
};
