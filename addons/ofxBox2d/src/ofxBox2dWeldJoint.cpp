/*
 *  ofxBox2dWeldJoint.cpp
 *  Taken from ofxBox2dJoint by Nick Hardeman 
 *
 *
 *  Created by Joel Gethin Lewis on 20/2/2011
 *
 */

#include "ofxBox2dWeldJoint.h"

//----------------------------------------
ofxBox2dWeldJoint::ofxBox2dWeldJoint() {
	world = NULL;
	alive = false;
}

ofxBox2dWeldJoint::ofxBox2dWeldJoint(b2World* b2world, b2Body* body1, b2Body* body2, bool bCollideConnected) {
	ofxBox2dWeldJoint();
	setup(b2world, body1, body2, bCollideConnected);
}

//----------------------------------------
ofxBox2dWeldJoint::ofxBox2dWeldJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, bool bCollideConnected) {
	ofxBox2dWeldJoint();
	setup(b2world, body1, body2, anchor, bCollideConnected);
}

	//----------------------------------------
void ofxBox2dWeldJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, bool bCollideConnected) {
	b2Vec2 a1, a2;
	a1 = body1->GetWorldCenter();
	a2 = body2->GetWorldCenter();
	
	b2Vec2 anchor = a2 - a1;
	anchor *= 0.5f;
	anchor += a1;
	
	setup(b2world, body1, body2, anchor, bCollideConnected);	
}

//----------------------------------------
void ofxBox2dWeldJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, bool bCollideConnected) {
	setWorld(b2world);
	b2WeldJointDef jointDef;
	jointDef.Initialize(body1, body2, anchor);
	jointDef.collideConnected	= bCollideConnected;
	joint						= (b2WeldJoint*)world->CreateJoint(&jointDef);
	
	alive						= true;
}

//----------------------------------------
void ofxBox2dWeldJoint::setWorld(b2World* w) {
	if(w == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: setWorld : - box2d world needed -");	
		return;
	}
	world = w;
}

//----------------------------------------
bool ofxBox2dWeldJoint::isSetup() {
	if (world == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: world must be set!");
		return false;
	}
	if (joint == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dWeldJoint :: setup function must be called!");
		return false;
	}
	return true;
}


//----------------------------------------
void ofxBox2dWeldJoint::draw() {
	if(!alive) return;
	
	b2Vec2 p1 = joint->GetAnchorA();
	b2Vec2 p2 = joint->GetAnchorB();
	
	p1 *= OFX_BOX2D_SCALE;
	p2 *= OFX_BOX2D_SCALE;
	ofLine(p1.x, p1.y, p2.x, p2.y);
}

//----------------------------------------
void ofxBox2dWeldJoint::destroy() {
	if (!isSetup()) return;
	world->DestroyJoint(joint);
	joint = NULL;
	alive = false;
}


//----------------------------------------
ofxVec2f ofxBox2dWeldJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofxVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dWeldJoint::getReactionForceB2D(float inv_dt) const {
	return joint->GetReactionForce(inv_dt);
}
float ofxBox2dWeldJoint::getReactionTorque(float inv_dt) const {
	return (float)joint->GetReactionTorque(inv_dt);
}




