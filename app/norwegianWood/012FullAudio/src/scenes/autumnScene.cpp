/*
 *  AutumnScene.cpp
 *  norwegianWood
 *
 *  Created by Joel Gethin Lewis on 28/02/2011.
 *  Copyright 2011 Hellicar&Lewis. All rights reserved.
 *
 */

#include "AutumnScene.h"

void AutumnScene::setup(string aName, ofxControlPanel* aGUI, ofxBox2d* aBox2D, PolygonShape aPolygon){
	Scene::setup(aName, aGUI, aBox2D);
	
	gui->setWhichColumn(2);
	gui->addSlider("percentage of shapes to effect", sceneName+"PERCENTAGE_TO_EFFECT_", 20, 1,100, true);		
	
	thePolygon = aPolygon;
}

void AutumnScene::update(float timeSinceLastUpdate, float audioLevel){
	int percentageToEffect = gui->getValueI(sceneName+"PERCENTAGE_TO_EFFECT_");
	float ratioToEffect = percentageToEffect/100.f;
	int numberToEffect = ratioToEffect*polygons.size();
	
	for(int i=0; i < numberToEffect; i++){
			//polygons[i].addAttractionPoint(ofGetWidth()/2.f, ofGetHeight(), audioLevel); no good, too slow
			//		ofxVec2f pt = ofxVec2f(ofRandom(0.f, 1.f), ofRandom(0.f, 1.f));
			//		ofxVec2f amt = ofxVec2f(audioLevel,audioLevel);
			//		
			//int randomPolygonIndex = (int)ofRandom(0, polygons.size());
		
			//		polygons[randomPolygonIndex].addImpulseForce(pt,amt); //too much slow down
		
		ofxVec2f oldVel = polygons[i].getVelocity();
		
		float downness = audioLevel;
		float rightness = audioLevel;
		
		if(ofRandomf() > 0){
			downness *= -1;
		}
		
		if(ofRandomf() > 0){
			rightness *= -1; //so they don't all tend in the same direction, effectively four options..
		}
		
		ofxVec2f newVel = oldVel + ofxVec2f(rightness, downness);
		
		polygons[i].setVelocity(newVel);
	}
	
	Scene::update(timeSinceLastUpdate, audioLevel);
}

void AutumnScene::draw(){
	Scene::draw();
	
	ofSetColor(foregroundColour.r, foregroundColour.g, foregroundColour.b);
	
	for(int i=0; i<polygons.size(); i++) {	
		polygons[i].draw();
	}	
	
	Scene::drawMask();
}

void AutumnScene::init(){
	float tenthWidth = ofGetWidth()/10.f;
	float tenthHeight = ofGetHeight()/10.f;
	
	for(int j = 0; j < 10; j++){
		for(int k = 0; k < 10; k++){
			ofxBox2dPolygon poly;
			poly.setup(box2d->world);
			thePolygon.scale(ofRandom(0.05f,0.25f));
			poly.addVertexes(thePolygon.shape);
			poly.simplify(1.75f);
			poly.triangulate();
			poly.create(box2d->world);	
			poly.setPosition(j*tenthWidth, k*tenthHeight);
			poly.setVelocity(ofRandomf(), ofRandomf());
			polygons.push_back(poly);
		}
	}
}

void AutumnScene::kill(){
	while (!polygons.empty())
	{
		polygons.back().destroy();
		polygons.pop_back();
	}
}

