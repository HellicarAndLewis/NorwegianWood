/*
 *  scene.cpp
 *  norwegianWood
 *
 *  Created by Joel Gethin Lewis on 28/02/2011.
 *  Copyright 2011 Hellicar&Lewis. All rights reserved.
 *
 */

#include "scene.h"

void Scene::setup(string aName, ofxControlPanel* aGUI, ofxBox2d* aBox2D){
	
	circularMaskWhite.allocate(1920, 1200, OF_IMAGE_COLOR_ALPHA);
	circularMaskWhite.loadImage("circularMaskWhite.png");
	circularMaskWhite.resize(ofGetWidth(), ofGetHeight());	
	
	circularMaskBlack.allocate(1920, 1200, OF_IMAGE_COLOR_ALPHA);
	circularMaskBlack.loadImage("circularMaskBlack.png");
	circularMaskBlack.resize(ofGetWidth(), ofGetHeight());		
	
	gui = aGUI;
	box2d = aBox2D;
	sceneName = aName;
	gui->addPanel(sceneName, 4, false);
	gui->setWhichPanel(sceneName);
	gui->setWhichColumn(0);
	gui->addSlider("Foreground Colour RED", sceneName+"FOREGROUND_COLOUR_RED", 0, 0, 255, true);	
	gui->addSlider("Foreground Colour GREEN", sceneName+"FOREGROUND_COLOUR_GREEN", 0, 0, 255, true);	
	gui->addSlider("Foreground Colour BLUE", sceneName+"FOREGROUND_COLOUR_BLUE", 0, 0, 255, true);	
	gui->addSlider("Velocity of background", sceneName+"BACKGROUND_VELOCITY", 0.f, -0.1f, 0.1f, false);	
	gui->addToggle("show white circle mask", sceneName+"CIRCLE_MASK_WHITE", true);
	gui->addToggle("show black circle mask", sceneName+"CIRCLE_MASK_BLACK", true);	
	gui->setWhichColumn(1);
	gui->addSlider("Top Colour RED", sceneName+"TOP_COLOUR_RED", 0, 0, 255, true);
	gui->addSlider("Top Colour GREEN", sceneName+"TOP_COLOUR_GREEN", 0, 0, 255, true);	
	gui->addSlider("Top Colour BLUE", sceneName+"TOP_COLOUR_BLUE", 0, 0, 255, true);	
	gui->addSlider("Middle Top Colour RED", sceneName+"MIDDLE_TOP_COLOUR_RED", 0, 0, 255, true);	
	gui->addSlider("Middle Top Colour GREEN", sceneName+"MIDDLE_TOP_COLOUR_GREEN", 0, 0, 255, true);	
	gui->addSlider("Middle Top Colour BLUE", sceneName+"MIDDLE_TOP_COLOUR_BLUE", 0, 0, 255, true);	
	gui->addSlider("Middle Bottom Colour RED", sceneName+"MIDDLE_BOTTOM_COLOUR_RED", 0, 0, 255, true);	
	gui->addSlider("Middle Bottom Colour GREEN", sceneName+"MIDDLE_BOTTOM_COLOUR_GREEN", 0, 0, 255, true);	
	gui->addSlider("Middle Bottom Colour BLUE", sceneName+"MIDDLE_BOTTOM_COLOUR_BLUE", 0, 0, 255, true);		
	gui->addSlider("Bottom Colour RED", sceneName+"BOTTOM_COLOUR_RED", 0, 0, 255, true);	
	gui->addSlider("Bottom Colour GREEN", sceneName+"BOTTOM_COLOUR_GREEN", 0, 0, 255, true);	
	gui->addSlider("Bottom Colour BLUE", sceneName+"BOTTOM_COLOUR_BLUE", 0, 0, 255, true);		
	
		//gradient
	boundaryVerticalPosition = 0.5f;	
}

void Scene::update(float timeSinceLastUpdate, float audioLevel){
	foregroundColour.r = gui->getValueI(sceneName+"FOREGROUND_COLOUR_RED");
	foregroundColour.g = gui->getValueI(sceneName+"FOREGROUND_COLOUR_GREEN");
	foregroundColour.b = gui->getValueI(sceneName+"FOREGROUND_COLOUR_BLUE");
	topColour.r = gui->getValueI(sceneName+"TOP_COLOUR_RED");
	topColour.g = gui->getValueI(sceneName+"TOP_COLOUR_GREEN");
	topColour.b = gui->getValueI(sceneName+"TOP_COLOUR_BLUE");
	midTopColour.r = gui->getValueI(sceneName+"MIDDLE_TOP_COLOUR_RED");
	midTopColour.g = gui->getValueI(sceneName+"MIDDLE_TOP_COLOUR_GREEN");
	midTopColour.b = gui->getValueI(sceneName+"MIDDLE_TOP_COLOUR_BLUE");
	midBottomColour.r = gui->getValueI(sceneName+"MIDDLE_BOTTOM_COLOUR_RED");
	midBottomColour.g = gui->getValueI(sceneName+"MIDDLE_BOTTOM_COLOUR_GREEN");
	midBottomColour.b = gui->getValueI(sceneName+"MIDDLE_BOTTOM_COLOUR_BLUE");	
	bottomColour.r = gui->getValueI(sceneName+"BOTTOM_COLOUR_RED");
	bottomColour.g = gui->getValueI(sceneName+"BOTTOM_COLOUR_GREEN");
	bottomColour.b = gui->getValueI(sceneName+"BOTTOM_COLOUR_BLUE");
	
		//background
	float backgroundVelocity = gui->getValueF(sceneName+"BACKGROUND_VELOCITY");
	
	boundaryVerticalPosition += timeSinceLastUpdate*backgroundVelocity;
	
	if(boundaryVerticalPosition < 0.f){
		cout << "Boundary reset to bottom of screen" << endl;
		
		boundaryVerticalPosition = 1.f;
		
			//now change the colours correctly
			//bit below is so that on change over, don't get a colour snap.
		
		ofColor tempTopColour = topColour;
		ofColor tempMidTopColour = midTopColour;
		ofColor tempMidBottomColour = midBottomColour;		
		ofColor tempBottomColour = bottomColour;
		
		topColour = tempMidBottomColour;
		midTopColour = tempBottomColour;
		midBottomColour = tempMidTopColour;
		bottomColour = tempTopColour;
	}
	
	if(boundaryVerticalPosition > 1.f){
		cout << "Boundary reset to top of screen" << endl;		
		boundaryVerticalPosition = 0.f;
		
			//now change the colours correctly
		
			//bit below is so that on change over, don't get a colour snap.
		
		ofColor tempTopColour = topColour;
		ofColor tempMidTopColour = midTopColour;
		ofColor tempMidBottomColour = midBottomColour;		
		ofColor tempBottomColour = bottomColour;
		
	
		
		topColour = tempMidBottomColour;
		midTopColour = tempBottomColour;
		midBottomColour = tempTopColour;
		bottomColour = tempMidTopColour;			
	}	
}

void Scene::draw(){
	float gradientHeight = ofGetHeight();
	float gradientWidth = ofGetWidth();
	float gradientX = 0.f;
	float gradientY = 0.f;
	
	float divisionHeight = boundaryVerticalPosition*gradientHeight;
	
	ofPushStyle();
	
	glBegin(GL_QUAD_STRIP);
	
	glColor3f(topColour.r/255.f, topColour.g/255.f, topColour.b/255.f);
	glVertex3f(gradientX, gradientY,0);
	glVertex3f(gradientX+gradientWidth,gradientY,0);
	
	glColor3f(midTopColour.r/255.f, midTopColour.g/255.f, midTopColour.b/255.f);
	glVertex3f(gradientX,gradientY+divisionHeight,0);
	glVertex3f(gradientX+gradientWidth, gradientY+divisionHeight,0);
	
	glColor3f(midBottomColour.r/255.f,midBottomColour.g/255.f,midBottomColour.b/255.f);
	glVertex3f(gradientX,gradientY+divisionHeight,0);
	glVertex3f(gradientX+gradientWidth, gradientY+divisionHeight,0);		
	
	glColor3f(bottomColour.r/255.f,bottomColour.g/255.f,bottomColour.b/255.f);
	glVertex3f(gradientX, gradientY+gradientHeight,0);
	glVertex3f(gradientX+gradientWidth, gradientY+gradientHeight,0);
	
	glEnd();
	
	ofPopStyle();	
}

void Scene::init(){
}

void Scene::kill(){
}

void Scene::drawMask(){
	if(gui->getValueB(sceneName+"CIRCLE_MASK_WHITE")){
			//then draw the mask
		ofSetColor(255,255,255);
		circularMaskWhite.draw(0,0);
	}
	if(gui->getValueB(sceneName+"CIRCLE_MASK_BLACK")){
			//then draw the mask
		ofSetColor(255,255,255);
		circularMaskBlack.draw(0,0);
	}	
}
