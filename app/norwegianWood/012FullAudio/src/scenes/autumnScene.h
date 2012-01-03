/*
 *  AutumnScene.h
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
#include "scene.h"
#include "polygonShape.h"

class AutumnScene: public Scene{
	
public:
	AutumnScene(){};
	~AutumnScene(){};
	
	void setup(string aName, ofxControlPanel* aGUI, ofxBox2d* aBox2D, PolygonShape aPolygon);
	void update(float timeSinceLastUpdate, float audioLevel);
	void draw();
	
	void init(); //create physics elements
	void kill(); //kill em
	
private:
	PolygonShape thePolygon;
	vector	<ofxBox2dPolygon> polygons;	
};