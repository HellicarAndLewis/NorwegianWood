/*
 *  scene.h
 *  norwegianWood
 *
 *  Created by Joel Gethin Lewis on 28/02/2011.
 *  Copyright 2011 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once 

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxControlPanel.h"

class Scene{
	
public:
	Scene(){};
	~Scene(){};
	
	virtual void setup(string aName, ofxControlPanel* aGUI, ofxBox2d* aBox2D);
	virtual void update(float timeSinceLastUpdate, float audioLevel);
	virtual void draw();
	
	virtual void init(); //create physics elements;
	virtual void kill(); //kill em
	void drawMask();//draw the circular mask
	
protected:
		//colour for background and foreground element
	
	ofColor topColour;
	ofColor midTopColour;
	ofColor midBottomColour;
	ofColor bottomColour;	
	float boundaryVerticalPosition;
	
	ofColor foregroundColour;
	
		//gui for attaching panel
	
	ofxControlPanel* gui;
	
		//box2D for simulation
	
	ofxBox2d* box2d;
	
	string sceneName;
	
		//for animation
	
	float timeOfLastFrame;
	
		//mask image
	ofImage	circularMaskWhite;	
	ofImage	circularMaskBlack;		
};