/*
 *  polygonShape.h
 *  norwegianWood
 *
 *  Created by Joel Gethin Lewis on 01/03/2011.
 *  Copyright 2011 Hellicar&Lewis. All rights reserved.
 *
 */

#pragma once

struct PolygonShape{
	string name;
	vector	<ofxVec2f> originalShape;
	vector	<ofxVec2f> shape;	
	
	void scale(float newScale){
		for(int i=0; i<shape.size(); i++){
			shape[i] = originalShape[i]*newScale;
		}
	}
};