/*
 *  SummerScene.cpp
 *  norwegianWood
 *
 *  Created by Joel Gethin Lewis on 28/02/2011.
 *  Copyright 2011 Hellicar&Lewis. All rights reserved.
 *
 */

#include "SummerScene.h"

void SummerScene::setup(string aName, ofxControlPanel* aGUI, ofxBox2d* aBox2D){
	Scene::setup(aName, aGUI, aBox2D);
	
	gui->setWhichColumn(2);
	gui->addSlider("number of octaves", sceneName+"NOISE_NUMBER_OF_OCTAVES", 8, 1,20, true);
	gui->addSlider("falloff", sceneName+"NOISE_FALLOFF", 0.5, 0.0, 1.f, false);	
	gui->addSlider("noise scale", sceneName+"NOISE_SCALE", 1.f, 1.f, 200.f, false);	
	
		//noise
	noise = new ofxPerlin();	
	
	grass.resize(50);
	
	float spaceBetweenBlades = ofGetWidth()/grass.size();
	
	for(int i = 0; i < grass.size(); i++){
		
		float heightOfBlades = ofRandom(0.6f*ofGetHeight(), 1.2f * ofGetHeight());
		
		grass[i].setup(spaceBetweenBlades*i+ofRandom(0,3*spaceBetweenBlades), ofGetHeight()+10.f /* to hide bases */, 2, heightOfBlades, 8);
	}	
}

void SummerScene::update(float timeSinceLastUpdate, float audioLevel){
	Scene::update(timeSinceLastUpdate, audioLevel);
	
		//noise
	
	int numberOfOctaves = gui->getValueI(sceneName+"NOISE_NUMBER_OF_OCTAVES");
	float fallOff = gui->getValueF(sceneName+"NOISE_FALLOFF");
	float scale = gui->getValueF(sceneName+"NOISE_SCALE");
	
	fallOff *= audioLevel;
	
	noise->noiseDetail(numberOfOctaves,fallOff);
	
	float div = grass.size(); 	
	
	for(int i = 0; i < grass.size(); i++){
		
			//2d noise
		
		float noiseValue = noise->noise((float)i/div, (float)ofGetFrameNum()/div);
		
		noiseValue -= 0.5f; //+ve and -ve values required
		noiseValue *= scale;
		
		//ofClamp(noiseValue,0.f,1.f);
		
		grass[i].update(noiseValue);
	}	
}

void SummerScene::draw(){
	Scene::draw();
	
	ofSetColor(foregroundColour.r, foregroundColour.g, foregroundColour.b);
	
	for(int i = 0; i < grass.size(); i++){
		grass[i].draw();
	}	
	
	Scene::drawMask();
}

void SummerScene::init(){
}

void SummerScene::kill(){
}

