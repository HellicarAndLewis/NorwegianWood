#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
	
	ofEnableSmoothing(); 
	ofSetFrameRate(60);

	clearBack = true;
	
	ofSetBackgroundAuto(clearBack);	
	
		//gradient
	boundaryVerticalPosition = 0.5f;	
	
	colour.r = ofRandom(0,255);
	colour.g = ofRandom(0,255);
	colour.b = ofRandom(0,255);
	
	midTopColour.r = ofRandom(0,255);
	midTopColour.g = ofRandom(0,255);
	midTopColour.b = ofRandom(0,255);
	
	midBottomColour.r = ofRandom(0,255);
	midBottomColour.g = ofRandom(0,255);
	midBottomColour.b = ofRandom(0,255);	
	
	bottomColour.r = ofRandom(0,255);
	bottomColour.g = ofRandom(0,255);
	bottomColour.b = ofRandom(0,255);
	
	drawing = true;
	
		//we load our shape file
		//if it doesn't exist we can still make one
		//by hitting the 's' key
	if( XML.loadFile("shape.xml") ){
		cout << "shape.xml loaded!" << endl;
	}else{
		cerr << "unable to load shape.xml check data/ folder" << endl;
	}
	
		//we initalize some of our variables
	lastTagNumber	= 0;
	
		//-------
		//this is a more advanced use of ofXMLSettings
		//we are going to be reading multiple tags with the same name
	
		//lets see how many <SHAPE> </SHAPE> tags there are in the xml file
	int numShapeTags = XML.getNumTags("SHAPE:PT");
	
		//if there is at least one <SHAPE> tag we can read the list of points
		//and then try and draw it as a line on the screen
	if(numShapeTags > 0){
		
			//we push into the last SHAPE tag
			//this temporarirly treats the tag as
			//the document root.
		XML.pushTag("SHAPE", numShapeTags-1);
		
			//we see how many points we have stored in <PT> tags
		int numPtTags = XML.getNumTags("PT");
		
		if(numPtTags > 0){
			
				//We then read those x y values into our
				//array - so we can add a polygon with this shape to the box2d world
			
				//we have only allocated a certan amount of space for our array
				//so we don't want to read more than that amount of points
			int totalToRead = numPtTags;
			
			polyShape.resize(totalToRead);
			
			for(int i = 0; i < totalToRead; i++){
					//the last argument of getValue can be used to specify
					//which tag out of multiple tags you are refering to.
				int x = XML.getValue("PT:X", 0, i);
				int y = XML.getValue("PT:Y", 0, i);
				polyShape[i].set(x, y); //add to the polyshape one point at a time from the xml
			}
		}
		
			//put it in the world
		
		ofxBox2dPolygon poly;
		
		poly.setup(box2d.world);
		poly.addVertexes(polyShape);
		poly.triangulate();
		poly.create(box2d.world);
		
		polygons.push_back(poly);
		
		polyShape.clear();		
		
			//this pops us out of the SHAPE tag
			//sets the root back to the xml document
		XML.popTag();
	}	
	
		//get ready for drawing.....
	XML.clear();
	lastTagNumber	= XML.addTag("SHAPE");
}

//--------------------------------------------------------------
void testApp::update(){
	box2d.update();
}


//--------------------------------------------------------------
void testApp::draw(){
	float gradientHeight = ofGetHeight();
	float gradientWidth = ofGetWidth();
	float gradientX = 0.f;
	float gradientY = 0.f;
	
	float divisionHeight = boundaryVerticalPosition*gradientHeight;
	
	ofPushStyle();
	
	glBegin(GL_QUAD_STRIP);
	
	glColor3f(colour.r/255.f, colour.g/255.f, colour.b/255.f);
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
	
	for(int i=0; i<polygons.size(); i++) {
		ofSetColor(0, 64, 128);		
		polygons[i].draw();
	}
	
	ofBeginShape();
	for(int i=0; i< polyShape.size(); i++) {
		ofVertex(polyShape[i].x, polyShape[i].y);
	}
	ofEndShape(true);
	
	string message;
	
	message = "s to Save. ";
	
	if(drawing){
		message += "Drawing: d to flip";
	}else{
		message += "Grabbing: d to flip";
	}
	
	ofSetColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
	ofDrawBitmapString(message, 100, ofGetHeight() - 20.f);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
		//no more draw hack...
//	clearBack = !clearBack;
//	
//	ofSetBackgroundAuto(clearBack);
	
//	colour.r = ofRandom(0,255);
//	colour.g = ofRandom(0,255);
//	colour.b = ofRandom(0,255);
//	
//	midTopColour.r = ofRandom(0,255);
//	midTopColour.g = ofRandom(0,255);
//	midTopColour.b = ofRandom(0,255);
//	
//	midBottomColour.r = ofRandom(0,255);
//	midBottomColour.g = ofRandom(0,255);
//	midBottomColour.b = ofRandom(0,255);	
//	
//	bottomColour.r = ofRandom(0,255);
//	bottomColour.g = ofRandom(0,255);
//	bottomColour.b = ofRandom(0,255);	
//	
//	boundaryVerticalPosition = ofRandomuf();
	
	switch (key){
		case 'd':
		{
			drawing = !drawing;
			break;
		}
		case 'c':
		{
			polyShape.clear();
				//we can also add tags with the same name.
				//here we are just adding an empty tag
				//and when the user drags their mouse
				//we will store the pts in this tag
			XML.clear();
			lastTagNumber	= XML.addTag("SHAPE");
			break;
		}
		case 's':
		{
			ofxBox2dPolygon poly;
			
			poly.setup(box2d.world);
			poly.addVertexes(polyShape);
			poly.triangulate();
			poly.create(box2d.world);
			
			polygons.push_back(poly);
			
			polyShape.clear();
			
			XML.saveFile("shape.xml");
			cout << "shape saved to xml!" << endl;
		}
		default:
		{
			break;
		}
	}	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){	
	if(drawing){
		polyShape.push_back(ofxVec2f(x, y));	
		
		if( XML.pushTag("SHAPE", lastTagNumber) ){
			
				//now we will add a pt tag - with two
				//children - X and Y
			
			int tagNum = XML.addTag("PT");
			XML.setValue("PT:X", x, tagNum);
			XML.setValue("PT:Y", y, tagNum);
			
			XML.popTag();
		}		
	}	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(drawing){
		polyShape.push_back(ofxVec2f(x, y));
		
		if( XML.pushTag("SHAPE", lastTagNumber) ){
			
				//now we will add a pt tag - with two
				//children - X and Y
			
			int tagNum = XML.addTag("PT");
			XML.setValue("PT:X", x, tagNum);
			XML.setValue("PT:Y", y, tagNum);
			
			XML.popTag();
		}			
	}		
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	if(drawing){

	}
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

