/*
 *  ofxBox2dBaseShape.cpp
 *  ofxBox2d
 *
 *  Created by Nick Hardeman on 1/14/11.
 *  Copyright 2011 Arnold Worldwide. All rights reserved.
 *
 */

#include "ofxBox2dBaseShape.h"

//----------------------------------------
ofxBox2dBaseShape::ofxBox2dBaseShape() {
	
	setMassFromShape = true;
	dead  = false;
	alive = false;
	
	body  = NULL;
	
	density     = 0.0;
	bounce		= 0.0;
	friction	= 0.0;
	bodyDef.allowSleep = true;
}

//------------------------------------------------
void ofxBox2dBaseShape::destroy() {
	
	if(getWorld() == NULL) {
		ofLog(OF_LOG_NOTICE, "- must have a valid world -");
		return;
	}
	else if(body == NULL) {
		ofLog(OF_LOG_NOTICE, "- null body -");
		return;
	}		
	
	getWorld()->DestroyBody(body);
	body  = NULL;
	dead  = true;
	alive = false;
	
	//printf("--- dead ---\n");
}

//----------------------------------------
ofxBox2dBaseShape::~ofxBox2dBaseShape() {
	if(alive) destroy();
}

//----------------------------------------
bool ofxBox2dBaseShape::isBody() {
	if (body == NULL) {
		//cout << __FILE__ << __func__ << endl;
		ofLog(OF_LOG_ERROR, "- body is not defined -");
		return false;
	}
	return true;
}

bool ofxBox2dBaseShape::isFixed() {
	return density == 0.f ? true : false;
}

//
b2World* ofxBox2dBaseShape::getWorld() {
	if (isBody()) {
		return body->GetWorld();
	}
	return NULL;
}

//----------------------------------------
void ofxBox2dBaseShape::create() {}

//------------------------------------------------ 
void ofxBox2dBaseShape::setBounce(float val) {
	bounce = val;
}

//------------------------------------------------ 
void ofxBox2dBaseShape::setDensity(float val) {
	// -- this is not working ! --
	/*b2MassData data;
	 data.mass = 3;
	 data.center = body->GetPosition();
	 data.I = body->GetInertia();
	 body->SetMass(&data);
	 */
}

//----------------------------------------
void ofxBox2dBaseShape::setFriction(float val) {
	friction	= val;
}

//------------------------------------------------ 
void ofxBox2dBaseShape::setPhysics(float density, float bounce, float friction) {
	this->density = density; this->bounce = bounce; this->friction = friction;
}


//------------------------------------------------ 
void ofxBox2dBaseShape::setData(void*data) {
	printf("data not set");

	if(data == NULL) {
		ofLog(OF_LOG_NOTICE, "- data is NULL -");
		return;
	}
	
	if(isBody()) {
		body->SetUserData(data);
	}
	else {
		ofLog(OF_LOG_NOTICE, "- must have a valid body -");
	}
}

//------------------------------------------------ 
void* ofxBox2dBaseShape::getData() {
	if(body) {
		body->GetUserData();
	}
	else {
		ofLog(OF_LOG_NOTICE, "- must have a valid body -");
	}
}

/*
 //------------------------------------------------ 
 virtual void setFilterData(b2FilterData data) {
 for(b2Shape* s=body->GetShapeList(); s; s=s->GetNext()) {
 
 //b2FilterData filter = s->GetFilterData();
 //			filter.groupIndex = newValue;
 //			myShape->SetFilterData(filter):
 //			myWorld->Refilter(myShape);
 
 s->SetFilterData(data);
 world->Refilter(s);
 }
 
 }
 */

//------------------------------------------------ 
void ofxBox2dBaseShape::enableGravity(bool b) {
	//bodyDef.isGravitated = b;
}

//------------------------------------------------ 
void ofxBox2dBaseShape::setFixedRotation(bool b) {
	bodyDef.fixedRotation = b;
}

//------------------------------------------------ 
void ofxBox2dBaseShape::setRotationFriction(float f) {
	bodyDef.angularDamping = f;
}

//------------------------------------------------
float ofxBox2dBaseShape::getRotation() {
	if(body != NULL) {
		return ofRadToDeg(body->GetAngle());
	}
}


//------------------------------------------------ 
void ofxBox2dBaseShape::setPosition(float x, float y) {
	if(!body || body == NULL) {
		ofLog(OF_LOG_NOTICE, "- Body is NULL -");
		return;
	}
	body->SetTransform(b2Vec2(b2dNum(x), b2dNum(y)), 0);
	//body->SetLinearVelocity(b2Vec2(0, 0)); // maybe bring this back...
	body->SetAwake(false); // this sounds backwards but that is what the doc says todo...
}
void ofxBox2dBaseShape::setPosition(ofxVec2f p) {
	setPosition(p.x, p.y);
}

//------------------------------------------------ 
ofxVec2f ofxBox2dBaseShape::getPosition() {
	ofxVec2f p;
	if(body != NULL) {
		p.set(body->GetPosition().x, body->GetPosition().y);
		p *= OFX_BOX2D_SCALE;
	}
	return p;
}

//------------------------------------------------
ofxVec2f ofxBox2dBaseShape::getB2DPosition() {
	return getPosition() / OFX_BOX2D_SCALE;
}

//------------------------------------------------ 
void ofxBox2dBaseShape::setVelocity(float x, float y) {
	if(body != NULL) {
		body->SetLinearVelocity(b2Vec2(x, y));
	}
}
void ofxBox2dBaseShape::setVelocity(ofxVec2f p) {
	setVelocity(p.x, p.y);
}
ofxVec2f ofxBox2dBaseShape::getVelocity() {
	return ofxVec2f(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
}

//------------------------------------------------ 
void ofxBox2dBaseShape::setDamping(float fx, float fy) {
	if(body != NULL) {
		b2Vec2 v = body->GetLinearVelocity();
		v.x *= fx;	v.y *= fy;
		body->SetLinearVelocity(v);
	}
}
void ofxBox2dBaseShape::setDamping(float f) {
	setDamping(f, f);
}


//------------------------------------------------
void ofxBox2dBaseShape::addForce(ofxVec2f frc, float scale) {
	if(body != NULL) {
		frc *= scale;
		body->ApplyForce(b2Vec2(frc.x, frc.y), body->GetPosition());
	}
}

//------------------------------------------------
void ofxBox2dBaseShape::addImpulseForce(ofxVec2f pt, ofxVec2f amt) {
	if(body != NULL) {
		body->ApplyLinearImpulse(b2Vec2(pt.x/OFX_BOX2D_SCALE, pt.y/OFX_BOX2D_SCALE), b2Vec2(amt.x, amt.y));
	}
}

//------------------------------------------------
void ofxBox2dBaseShape::addAttractionPoint(ofxVec2f pt, float amt, float minDis) {
	
	// if(minDis == NULL) minDis = 1; // not using this
	
	if(body != NULL) {
		b2Vec2 P(pt.x/OFX_BOX2D_SCALE, pt.y/OFX_BOX2D_SCALE);
		b2Vec2 D = P - body->GetPosition(); 
		
		P.Normalize();
		b2Vec2 F = amt * D;
		body->ApplyForce(F, P);
	}
}

void ofxBox2dBaseShape::addAttractionPoint(float x, float y, float amt, float minDis) {
	addAttractionPoint(ofxVec2f(x, y), amt, minDis);
}

//------------------------------------------------
void ofxBox2dBaseShape::addRepulsionForce(ofxVec2f pt, float radius, float amt) {
	/*if(body != NULL) {
	 b2Vec2 P(pt.x/OFX_BOX2D_SCALE, pt.y/OFX_BOX2D_SCALE);
	 b2Vec2 D = P - body->GetPosition(); 
	 if(D.LengthSquared() < minDis) {;
	 P.Normalize();
	 b2Vec2 F = amt * D;
	 body->ApplyForce(F, P);
	 }
	 }*/

	
	if(body != NULL) {
		b2Vec2 P(pt.x/OFX_BOX2D_SCALE, pt.y/OFX_BOX2D_SCALE);
		b2Vec2 D = P - body->GetPosition(); 
		if(D.LengthSquared() < radius) {;
			P.Normalize();
			b2Vec2 F = amt * D;
			body->ApplyForce(-F, body->GetWorldCenter());
		}
	}
}



//------------------------------------------------
void ofxBox2dBaseShape::update() { }
void ofxBox2dBaseShape::draw() { }
