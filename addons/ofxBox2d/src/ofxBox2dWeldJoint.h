#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dUtils.h"

class ofxBox2dWeldJoint {
	
public:
	
	b2World			*	world;
	b2WeldJoint	*	joint;
	int					jointType;
	bool				alive;
	
	//----------------------------------------
	ofxBox2dWeldJoint();
	ofxBox2dWeldJoint(b2World* b2world, b2Body* body1, b2Body* body2, bool bCollideConnected=true);		/// Initialize the bodies, anchor, and reference angle using a world;	
	ofxBox2dWeldJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, bool bCollideConnected=true);		/// Initialize the bodies, anchor, and reference angle using a world;
		/// anchor point.
	//----------------------------------------
	void setWorld(b2World * w);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, bool bCollideConnected=true);		
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, bool bCollideConnected=true);
	
	//----------------------------------------
	bool isSetup();
	void draw();
	void destroy();
	
	//----------------------------------------
	ofxVec2f getReactionForce(float inv_dt) const;
	b2Vec2  getReactionForceB2D(float inv_dt) const;
	float  getReactionTorque(float inv_dt) const;
};
