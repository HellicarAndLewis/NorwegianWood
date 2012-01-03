#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	
		//audio
	
		// 0 output channels, 
		// 2 input channels
		// 22050 samples per second
		// 256 samples per buffer
		// 4 num buffers (latency)
	
	ofSoundStreamSetup(0,2,this, 44100, 256, 4);	
	left = new float[256];
	right = new float[256];	
	
	audioLevel = 0.f;
	
		//box2d
	
	box2d.init();
	box2d.setGravity(0,0);
	box2d.createBounds();
	box2d.setFPS(30);
	box2d.registerGrabbing();
	
	box2d.createGround();//defaults to the bottom of the screen, nice
	
	ofEnableSmoothing(); 
	ofSetFrameRate(30);

	clearBack = true;
	
	ofSetBackgroundAuto(clearBack);	
	
//	shapeDirLister.setVerbose(false);
//	shapeDirLister.allowExt("xml");
//    int nShapes = shapeDirLister.listDir("shapes");
//	
//	cout << nShapes << " found." << endl;
	
	ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 60, 200));
	ofxControlPanel::setTextColor(simpleColor(240, 50, 50, 255));
	
	gui.loadFont("MONACO.TTF", 8);		
	gui.setup("Hellicar&Lewis Norwegian Wood Audio Reactive Projection", 0, 0, ofGetWidth(), 700);
	gui.addPanel("Basic Settings", 4, false);
	
	ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 30, 200));	
	
		//--------- PANEL 1
	gui.setWhichPanel(0);
	
	gui.setWhichColumn(0);
	
		//some dummy vars we will update to show the variable lister object
	elapsedTime		= ofGetElapsedTimef();
	appFrameCount	= ofGetFrameNum();	
	appFrameRate	= ofGetFrameRate();
	
	vector <guiVariablePointer> vars;
	vars.push_back( guiVariablePointer("ellapsed time", &elapsedTime, GUI_VAR_FLOAT, 2) );
	vars.push_back( guiVariablePointer("ellapsed frames", &appFrameCount, GUI_VAR_INT) );
	vars.push_back( guiVariablePointer("app fps", &appFrameRate, GUI_VAR_FLOAT, 2) );
	
	vars.push_back( guiVariablePointer("mouse x", &mouseX, GUI_VAR_INT) );
	vars.push_back( guiVariablePointer("mouse y", &mouseY, GUI_VAR_INT) );
	
	gui.addVariableLister("app vars", vars);
	
	gui.addChartPlotter("Audio level", guiStatVarPointer("Audio Level", &audioLevel, GUI_VAR_FLOAT, true, 2), 200, 100, 200, 0.f, 1.f);
	gui.addSlider("Audio Cut Down", "AUDIO_CUT_DOWN", 0.1f, 0.f,1.f, false);
	gui.addSlider("Audio Cut Up", "AUDIO_CUT_UP", 0.9f, 0.f,1.f, false);
	gui.addSlider("Audio Boost ", "AUDIO_BOOST", 0.0f, 0.f,1.f, false);	
	
	timeOfLastFrame = ofGetElapsedTimef();	
	
	bShowMouse = false;
	
	ofHideCursor();
	
	loadPolyShapeFromXML("shapes/blossom.xml");
	loadPolyShapeFromXML("shapes/leaf.xml");
	
		//now the scenes
	spring.setup("Spring", &gui, &box2d, polyShapes[0]);
	summer.setup("Summer", &gui, &box2d);
	autumn.setup("Autumn", &gui, &box2d, polyShapes[1]);
	winter.setup("Winter", &gui, &box2d);		
	
	currentScene = &spring;
	spring.init();
	
		//SETTINGS AND EVENTS
	
		//load from xml!
	gui.loadSettings("controlPanelSettings.xml");
	
		//if you want to use events call this after you have added all your gui elements
	gui.setupEvents();
	gui.enableEvents();
	gui.hide();
}

	//--------------------------------------------------------------
void testApp::update(){
	float elapsedTimeBetweenFrames = ofGetElapsedTimef() - timeOfLastFrame;
	
		//audio
	float totalLeft = 0.f;
	float totalRight = 0.f;
	
	for (int i = 0; i < 256; i++){
		totalLeft += abs(left[i]);
		totalRight += abs(right[i]);
	}
	
	totalLeft = totalLeft / 256.f;
	totalRight = totalRight / 256.f;
	
	audioLevel = (totalLeft+totalRight)/2.f;
	
	audioLevel += gui.getValueF("AUDIO_BOOST");
	
	audioLevel = ofNormalize(audioLevel, gui.getValueF("AUDIO_CUT_DOWN"), gui.getValueF("AUDIO_CUT_UP"));
	
		//box2d
	
	box2d.update();
	
		//gui
	
		//some dummy vars we will update to show the variable lister object
	elapsedTime		= ofGetElapsedTimef();
	appFrameCount	= ofGetFrameNum();	
	appFrameRate	= ofGetFrameRate();
	
	gui.update();
	
	currentScene->update(elapsedTimeBetweenFrames, audioLevel);
	
	timeOfLastFrame = ofGetElapsedTimef();
}


//--------------------------------------------------------------
void testApp::draw(){
	
	ofEnableAlphaBlending();
	
	currentScene->draw();
	
	ofSetColor(0xffffff);
	gui.draw();	
	
	ofDisableAlphaBlending();
}

static float adder = 0;
	//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
		// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
		//no more draw hack...
//	clearBack = !clearBack;
//	
//	ofSetBackgroundAuto(clearBack);
	
	switch (key){
		case '1':{
			currentScene->kill();
			currentScene = &spring;
			currentScene->init();
			break;
		}
		case '2':{
			currentScene->kill();
			currentScene = &summer;
			currentScene->init();
			break;
		}
		case '3':{
			currentScene->kill();
			currentScene = &autumn;
			currentScene->init();
			break;
		}
		case '4':{
			currentScene->kill();
			currentScene = &winter;
			currentScene->init();
			break;
		}				
		case 'f':{
			ofToggleFullscreen();
			break;
		}
		case 'h':{
			gui.toggleView();	
			break;
		}	
		case 'm':{
			if(bShowMouse){
				ofHideCursor();
				bShowMouse = false;
			}else {
				ofShowCursor();
				bShowMouse = true;
			} 
			break;				
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
	gui.mouseDragged(x, y, button);
}

	//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	gui.mousePressed(x, y, button);
	
}

	//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	gui.mouseReleased();
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

void testApp::loadPolyShapeFromXML(string pathToXML){
	
	ofxXmlSettings XML;
	PolygonShape polyShape;	
	
	if( XML.loadFile(pathToXML) ){
		cout << pathToXML << " loaded!" << endl;
	}else{
		cerr << "Unable to load " << pathToXML << endl;
	}	
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
			int totalToRead = numPtTags;
			
			polyShape.shape.resize(totalToRead);
			polyShape.originalShape.resize(totalToRead);
			polyShape.name = pathToXML;
			
			for(int i = 0; i < totalToRead; i++){
					//the last argument of getValue can be used to specify
					//which tag out of multiple tags you are refering to.
				int x = XML.getValue("PT:X", 0, i);
				int y = XML.getValue("PT:Y", 0, i);
				polyShape.originalShape[i].set(x, y); //add to the polyshape one point at a time from the xml
				polyShape.shape[i].set(x, y); //and initial shape...
			}
		}
		
		polyShapes.push_back(polyShape);  // adding to the polyshapes vector too...		
		
			//this pops us out of the SHAPE tag
			//sets the root back to the xml document
		XML.popTag();
	}	
	
		//get ready for drawing.....
	XML.clear();
}


