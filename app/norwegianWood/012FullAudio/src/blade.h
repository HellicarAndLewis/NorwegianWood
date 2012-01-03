/*
 *  blade.h
 *  norwegianWood
 *
 *  Created by Joel Gethin Lewis on 01/03/2011.
 *  Copyright 2011 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class Blade{ //just up here for now....
	
		//straight port of reach2 demo from http://processing.org
		//which was based on code from Keith Peters (www.bit-101.com)
	
public:
	Blade(){
		_x = _y = _width = _height = 0.f;
	}
	~Blade(){
	}
	void setup(float xPos, float yPos, float width, float height, int numberOfWelds){
		_x = xPos;
		_y = yPos;
		_width = width;
		_height = height;
		
		_numberOfWelds = numberOfWelds;
		
		_segmentLength = height/numberOfWelds;
		
		segments.resize(numberOfWelds);
		segmentAngles.resize(numberOfWelds);
		
			//setting the base of the blade correctly
		segments.back().x = _x;     // Set base x-coordinate
		segments.back().y = _y;  // Set base y-coordinate
	}
	
	void update(float noiseValue){
		ofPoint aimFor;
		
		aimFor.x = getX() + noiseValue;
		aimFor.y = ofGetHeight()-getHeight();
		
		reachSegment(0, aimFor.x, aimFor.y);
		
		for(int i=1; i< _numberOfWelds; i++) {
			reachSegment(i, _targetX, _targetY);
		}
		
		for(int i = _numberOfWelds -1; i>=1; i--) {
			positionSegment(i, i-1);  
		} 
	}
	
	void draw(){	
		for(int i=0; i < _numberOfWelds; i++) {
				//drawSegment(segments[i].x, segments[i].y, segmentAngles[i], (i+1)*2); 
			drawSegment(segments[i].x, segments[i].y, segmentAngles[i], _width); 
		}		
	}
	
	void positionSegment(int a, int b) {
		segments[b].x = segments[a].x + cos(segmentAngles[a]) * _segmentLength;
		segments[b].y = segments[a].y + sin(segmentAngles[a]) * _segmentLength;
	}
	
	void reachSegment(int i, float xin, float yin) {
		float dx = xin - segments[i].x;
		float dy = yin - segments[i].y;
		segmentAngles[i] = atan2(dy, dx);  
		_targetX = xin - cos(segmentAngles[i]) * _segmentLength; //mmm tasty
		_targetY = yin - sin(segmentAngles[i]) * _segmentLength;
	}
	
	void drawSegment(float x, float y, float a, float sw) {
		ofPushStyle();
		ofSetLineWidth(sw);
		
		ofPushMatrix();
		
		ofTranslate(x, y, 0);
		ofRotateZ(ofRadToDeg(a));
		ofLine(0, 0, _segmentLength, 0);
		
		ofPopMatrix();
		
		ofPopStyle();
	}	
	
	float getX(){
		return _x;
	}
	
	float getY(){
		return _y;
	}
	
	float getWidth() {
		return _width;
	}
	
	float getHeight() {
		return _height;
	}
	
	
private:
	
	int _numberOfWelds;
	
	float _width;
	float _height;
	
	float _x;
	float _y;
	
	vector <ofPoint> segments;
	vector <float> segmentAngles;
	
	float _segmentLength;
	
	float _targetX;
	float _targetY;
};