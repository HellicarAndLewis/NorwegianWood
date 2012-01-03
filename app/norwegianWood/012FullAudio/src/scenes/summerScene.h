/*
 *  SummerScene.h
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
#include "ofxPerlin.h"
#include "blade.h"
#include "scene.h"

class SummerScene: public Scene{
	
public:
	SummerScene(){};
	~SummerScene(){};
	
	void setup(string aName, ofxControlPanel* aGUI, ofxBox2d* aBox2D);
	void update(float timeSinceLastUpdate, float audioLevel);
	void draw();
	
	void init(); //create physics elements
	void kill(); //kill em
	
private:
	//grass
	
	vector <Blade> grass;	
	
	ofxPerlin *noise;
};