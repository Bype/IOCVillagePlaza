//
//  PlayerFace.cpp
//  Stadium
//
//  Created by Douglas Stanley on 07|09|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "PlayerFace.h"
#include "ofxXmlSettings.h"

// MARK: static members

// da big fbo
ofFbo PlayerFace::fbo;

// the props placed on top of faces (hats, caps, glasses, etc)
map<string,ofImage> PlayerFace::props;

// gestures
map<string,Gesture> PlayerFace::gestures; // the gesture instructions
vector<GestureGroup> PlayerFace::gestureGroups; // grouping of several vertices
vector<GestureAnimation> PlayerFace::gestureAnimations;
vector<FaceVertex> PlayerFace::facemap; // the map of the face


// MARK: static methods

int PlayerFace::size(string newType) {
    
    ofDirectory dir;
    
    // go into folder to get saved faces
    string filepath = ofToDataPath("players/" + newType + "/");
    return dir.listDir(filepath);
    
}


// MARK: Init

void PlayerFace::setup(string _name) {
    
    loaded = false;
    data.type = "none";
    
    alpha = 255.f;
    
    state = "normal";
    lastState = "";
    
    wiggle = true;
    breathing = true;
    
    halfScreen = ofVec2f(240,240);
    
    setupFbo();
    
    loadGestures();
    loadProps();
    
    load(_name);
    
    myGestureAnimations = gestureAnimations;
    
}


void PlayerFace::setupFbo() {
    
    if (fbo.isAllocated()) return; 
    
    ofFbo::Settings settings;
    settings.width = 480; //face.getWidth();
    settings.height = 480; //face.getHeight();
    settings.internalformat = GL_RGBA;
    settings.numSamples = 0;
    settings.useDepth = false;
    settings.useStencil = false;
    
    // draw fbo
    fbo.allocate(settings);
    
}

// MARK: Load

void PlayerFace::loadGestures() {
    
    if (gestureGroups.size() > 0) return;
    
    gestureAnimations.clear();
    
    // first, load xml file and push into first tag
    ofxXmlSettings xml;
    xml.loadFile("personae/settings.xml");
    xml.pushTag("personae");
    
    // extract group indexes
    
    // push into groups
    xml.pushTag("groups");
    
    int howManyGroups = xml.getNumTags("group");
    
    for(int i=0; i<howManyGroups; i++) {
        
        // get the name of this group
        string name = xml.getAttribute("group", "name", "", i);
        
        // create the group
        gestureGroups.push_back(GestureGroup(name));
        
        // add indexes to this group
        xml.pushTag("group",i);
        int howManyVertices = xml.getNumTags("vertex");
        
        for(int j=0; j<howManyVertices; j++) {
            
            // get this index
            int index = xml.getAttribute("vertex", "index", -1, j);
            // error correction
            if (index < 0) continue;
            // get type
            string type = xml.getAttribute("vertex", "type", "feature", j);
            // add this index to the group
            gestureGroups.back().addVertex(type, index);
            
        }
        
        xml.popTag(); // group
        
    }
    
    xml.popTag(); // groups
    
    // extract gestures
    
    // push into gestures
    xml.pushTag("gestures");
    
    int howManyGestures = xml.getNumTags("gesture");
    
    for(int i=0; i<howManyGestures; i++) {
        
        // get the name of this gesture
        string gestureName = xml.getAttribute("gesture", "name", "", i);
        // error checking
        if ("" == gestureName) continue;
        // push into this gesture
        xml.pushTag("gesture", i);
        
        int howManyAnimations = xml.getNumTags("animation");
        
        // found any animations in this gesture?
        if (howManyAnimations > 0) {
            
            gestureAnimations.push_back(GestureAnimation(gestureName));
            
            for(int j=0; j<howManyAnimations; j++) {
                
                // get the name of the gesture to run
                string animationName = xml.getAttribute("animation", "name", "", j);
                // error checking
                if ("" == animationName) continue;
                // get delay
                float delay = xml.getAttribute("animation", "delay", 0.f, j);
                // add this animation
                gestureAnimations.back().addPair(animationName, delay);
                
            }
            
            xml.popTag(); // gesture
                          // move on to next gesture
            continue;
            
        }
        
        // create this gesture locally
        Gesture gesture = Gesture(gestureName);
        
        // get number of vertices
        int howManyVertices = xml.getNumTags("vertex");
        
        // go through all the individualized vertices
        for(int j=0; j<howManyVertices; j++) {
            
            // get this vertex
            int index = xml.getAttribute("vertex", "index", -1, j);
            // error checking
            if (index < 0) continue;
            // get its' type
            string type = xml.getAttribute("vertex", "type", "", j);
            // error checking
            if ("" == type) continue;
            // get its' unit
            string unit = xml.getAttribute("vertex", "unit", "pixel", j);
            // get x & y, convert into vector
            float x = xml.getAttribute("vertex", "x", 0.f, j);
            float y = xml.getAttribute("vertex", "y", 0.f, j);
            ofVec2f loc = ofVec2f(x,y);
            // create this gesture vertex
            GestureVertex gestureVertex = GestureVertex(type, index, loc, unit);
            // add this vertex to gesture
            gesture.addVertex(gestureVertex);
            
        }
        
        // get the number of groups
        int howManyGroups = xml.getNumTags("group");
        
        for(int j=0; j<howManyGroups; j++) {
            
            // get the name of this group
            string groupName = xml.getAttribute("group", "name", "", j);
            // error checking
            if ("" == groupName) continue;
            // get unit
            string unit = xml.getAttribute("group", "unit", "pixel", j);
            // get offset
            float x = xml.getAttribute("group", "x", 0.f, j);
            float y = xml.getAttribute("group", "y", 0.f, j);
            ofVec2f loc = ofVec2f(x,y);
            
            // go through current groups and try to find one with this name
            for(int k=0; k<gestureGroups.size(); k++) {
                
                // go grab this GestureGroup's data
                GestureGroup gestureGroup = gestureGroups[k];
                // if not a match, try next one
                if (groupName != gestureGroup.name) continue;
                
                // now go through the list of indexes
                for(int l=0; l<gestureGroup.vertices.size(); l++) {
                    
                    // grab this vertex
                    GestureVertex vertex = gestureGroup.vertices[l];
                    // get the index
                    int index = vertex.index;
                    string type = vertex.type;
                    // create this gesture vertex
                    GestureVertex gestureVertex = GestureVertex(type, index, loc, unit);
                    // add this vertex to gesture
                    gesture.addVertex(gestureVertex);
                    
                } // vertices [l]
                
            } // gesture groups[k]
            
        } // groups[j]
        
        // add this gesture (containing direct vertices & de-grouped vertices)
        gestures[gestureName] = gesture;
        
        xml.popTag(); // gesture
        
    } // gestures[i]
    
    xml.popTag(); // gestures
    
    
    // facemap
    
    xml.pushTag("facemap");
    
    int howManyVertices = xml.getNumTags("vertex");
    
    for(int i=0; i<howManyVertices; i++) {
        int index = xml.getAttribute("vertex", "index", -1, i);
        if (index < 0) continue;
        string type= xml.getAttribute("vertex", "type", "feature", i);
        facemap.push_back(FaceVertex(index,type));
    }
    
    xml.popTag(); // facemap
    
    xml.popTag(); // personae
    
}


// load the latest of this type
void PlayerFace::load(string newType) {
    
    load(newType, -1);
    
}


// load this type, using index
void PlayerFace::load(string newType, int index) {
    
    ofDirectory dir;
    
    // go into folder to get saved faces
    string filepath = ofToDataPath("players/" + newType + "/");
    
    // how many of this type?
    int howMany = dir.listDir(filepath);
    
    // if none, get outta here
    if (0 == howMany) return;
    
    // if index is negative
    if (index < 0) {
        // start from end of list (i.e. from back of list, i.e. latest)
        index = ABS(howMany + index);
    }
    
    // make sure we stay within bounds of filelist
    index %= howMany;
    
    // get this identifier
    string filename = dir.getPath(index);
    
    vector<string> tokens = ofSplitString(filename, "/");
    
    // if none, get outta here
    if (0 == tokens.size()) return;
    
    // extract the identifier from the filename
    string identifier = tokens[tokens.size()-1];
    
    // go load that image
    load(newType,identifier);
    
}


void PlayerFace::load(string newType, string identifier) {
    
    // go into folder to get saved faces
    string filepath = ofToDataPath("players/" + newType + "/" + identifier);
    
    // try to find this directory
    ofDirectory dir;
    dir.open(filepath);
    
    if (!dir.exists()) return;
    
    // load image
    
    face.loadImage(filepath + "/" + "image.png");
    halfScreen = ofVec2f(face.getWidth()/2,face.getHeight()/2);
    
    // clear previous data
    
    //data.clear();
    
    // load data
    
    ofxXmlSettings xml;
    xml.loadFile(filepath + "/" + "data.xml");
    
    // load the mesh
    
    xml.pushTag("data");
    
    // vertices
    
    xml.pushTag("outline");
    int howManyOutlinePoints = xml.getNumTags("point");
    
    for(int i=0; i<howManyOutlinePoints; i++) {
        
        xml.pushTag("point", i);
        
        float x = xml.getValue("x", 0.f);
        float y = xml.getValue("y", 0.f);
        
        // ok, we've extracted this vertex from the xml file, add it to mesh
        data.outline.push_back( ofVec2f(x,y) );
        
        xml.popTag(); // point #i
    }
    
    xml.popTag(); // outline
    
    // features
    
    xml.pushTag("features");
    int howManyFeaturePoints = xml.getNumTags("point");
    for(int i=0; i<howManyFeaturePoints; i++) {
        
        xml.pushTag("point", i);
        
        float x = xml.getValue("x", 0.f);
        float y = xml.getValue("y", 0.f);
        
        // ok, we've extracted this vertex from the xml file, add it to mesh
        data.features.push_back( ofVec2f(x,y) );
        
        xml.popTag(); // point #i
    }
    
    xml.popTag(); // features
    
    xml.popTag(); // data
    
    // set loaded flag
    
    loaded = true;
    data.type = newType;
    
    normalizeMouth();
    
    lastState = "";
    
}


void PlayerFace::normalizeMouth() {
    
    // figure out mouth center
    ofVec2f center = ofVec2f(0.f,0.f);
    
    for(int i=48; i<=65; i++) {
        center += data.features.original[i];
    }
    
    // mean
    center /= ofVec2f(17,17);
    
    for(int i=48; i<=65; i++) {
        float delta = center.y - data.features.original[i].y;
        data.features.normalized[i].y += delta * 0.65f;
    }
}




// MARK: state

void PlayerFace::setState(string newState) {
    
    // reset all the animations
    int animationIndex = -1;
    for(int i=0; i<myGestureAnimations.size(); i++) {
        myGestureAnimations[i].reset();
        // if this is the one we're looking for
        if (myGestureAnimations[i].name == newState) animationIndex = i;
    }
    
    // is this an animation?
    if (animationIndex >= 0) {
        myGestureAnimations[animationIndex].activate();
        state = myGestureAnimations[animationIndex].getCurrent();
    } else {
        state = newState;
    }
    
}


void PlayerFace::loadProps() {
    
    if (!props["press_hat"].isAllocated()) {
        //cout << "load images" << endl;
        props["press_hat"] = ofImage();
        props["press_hat"].loadImage("personae/press_hat.png");
        props["fan_hat"] = ofImage();
        props["fan_hat"].loadImage("personae/fan_hat.png");
        props["badguy_glasses"] = ofImage();
        props["badguy_glasses"].loadImage("personae/badguy_glasses.png");
    }
    
}



// MARK: Loop

void PlayerFace::update() {
    
    if (!loaded) return;
    
    // update face data
    updateFaceData();
		
}


void PlayerFace::updateFaceData() {
    
    // si if any animations need the next frame
    for(int i=0; i<myGestureAnimations.size(); i++) {
        
        // if not active, move on to next
        if (!myGestureAnimations[i].active) continue;
        
        // ok, we're active, do we need to change frames?
        if (myGestureAnimations[i].readyForNextFrame()) {
            // set state to next frame
            state = myGestureAnimations[i].nextFrame();
        }
        
    }
    
    
    
    // if we've changed state
    
    if (lastState != state) {
        
        // reset all vertex data in both features && outline
        
        for(int i=0; i<data.features.current.size(); i++) {
            data.features.target[i] = data.features.normalized[i];
        }
        
        for(int i=0; i<data.outline.current.size(); i++) {
            data.outline.target[i] = data.outline.normalized[i];
        }
        
        // set state to this new state
        lastState = state;
        
    }
    
    
    
    // find out if there's a data set with this name
    
    if (gestures[state].name != "") {
        
        // grab that gesture set's data
        Gesture gesture = gestures[state];
        // extract vertices
        vector<GestureVertex> vertices = gesture.vertices;
        
        // run through all the vertices
        for(int i=0; i<vertices.size(); i++) {
            
            // get the vertice type
            string type = vertices[i].type;
            int index = vertices[i].index;
            string unit = vertices[i].unit;
            ofVec2f loc = vertices[i].loc;
            
            if ("outline" == type) {
                data.outline.target[index] = data.outline.original[index] + loc;
            } else if ("feature" == type) {
                data.features.target[index] = data.features.original[index] + loc;
            } else {
                cout << "GestureVertex data type error" << endl;
            }
            
        }
        
    }
    
    
    
    
    float breath = 0.f;
    if (breathing) {
        breath = 1 + sinf(ofGetElapsedTimef()*1.5f)*0.0075f;
    }
    
    // Zenon our way towards new values
    for(int i=0; i<data.features.current.size(); i++) {
        
        // create the wiggle
        ofVec2f wiggleVec = ofVec2f(0.f,0.f);
        if (wiggle) {
            wiggleVec = ofVec2f(sinf(ofGetElapsedTimef()*4+i)*0.5,cosf(ofGetElapsedTimef()*4+i)*0.5);
        }
        
        ofVec2f delta = data.features.target[i] - data.features.current[i] + wiggleVec;
        data.features.current[i] += delta * 0.25f;
        data.features.current[i] *= breath;
        
    }
    
    
    
    
    // Zenon our way towards new values
    for(int i=0; i<data.outline.current.size(); i++) {
        ofVec2f delta = data.outline.target[i] - data.outline.current[i];
        data.outline.current[i] += delta * 0.25f;
    }
    
    
    
    
}




// MARK: Draw

void PlayerFace::draw(float newAlpha) {
    
    if (!loaded) return;
    
    alpha = newAlpha;
    float scale = 0.7f;
    
    drawFace( ofVec2f(0,-70), scale);
    
    if ("athlete" == data.type) {
        ofVec2f loc = ofVec2f(0,-70);
        drawBandanna( loc, scale );
    }
    
    if ("press" == data.type) {
        ofVec2f loc = data.outline.current[4] + (data.outline.current[5] - data.outline.current[4]) * 0.5;
        drawPressHat( ofVec2f(5,-40) + loc, scale);   
    }
    
    if ("fan" == data.type) {
        ofVec2f loc = data.outline.current[4] + (data.outline.current[5] - data.outline.current[4]) * 0.5;
        drawFanHat( ofVec2f(5,-20) + loc, scale);   
    }
    
    if ("badguy" == data.type) {
        ofVec2f leftPupil = data.features.current[36];
        ofVec2f rightPupil = data.features.current[45];
        drawBadguyGlasses(ofVec2f(0,-70), leftPupil, rightPupil);
    }
    
}



void PlayerFace::draw(ofVec2f pt, float newAlpha) {
    
    if (!loaded) return;
    
    draw(pt.x, pt.y, alpha);
    
}


void PlayerFace::draw(float x, float y, float newAlpha) {
    
    if (!loaded) return;
    
    ofPushMatrix();
    ofTranslate(x,y);
    draw(newAlpha);
    ofPopMatrix();	
    
}


// MARK: Draw Face


void PlayerFace::drawFace(ofVec2f offset, float scale) {
    
    if (!loaded) return;
    
    // make sure we have a list of vertices
    if (data.features.current.size() == 0) return;
    
    // in case this has been deactivated
    ofEnableAlphaBlending();
    
    fbo.begin();
    
    // move to center of fbo
    ofPushMatrix();
    
    // clear out previous garbage
    ofClear(0,0);
    
    // draw features
    
	ofMesh featuresMesh;
    featuresMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    // fix hole in face
    for(int i=0; i<facemap.size(); i++) {
        
        // get index of vertex
        int index = facemap[i].index;
        string type = facemap[i].type;
        
        ofVec2f currentVertex, textureVertex;
        
        if ("outline" == type) {
            currentVertex = data.outline.current[index];
            textureVertex = data.outline.textureCoordinates[index];
        } else {
            currentVertex = data.features.current[index];
            textureVertex = data.features.textureCoordinates[index];
        }
        
        // generate geometry
        featuresMesh.addVertex(currentVertex+halfScreen);
        featuresMesh.addTexCoord(textureVertex+halfScreen);
        
    }
    
    // get the pixels of the outline
    face.getTextureReference().bind();
    // draw mesh info fbo
    ofSetColor(255);
    featuresMesh.draw();
    
    face.getTextureReference().unbind();
    
    ofPopMatrix();
    
    fbo.end();
    
    ofPushMatrix();
    
    // go to center of second spot
    ofTranslate(offset.x, offset.y);
    ofScale(scale,scale,1.f);
    // draw result
	ofSetColor(255,alpha);
    fbo.draw(-fbo.getWidth()/2, -fbo.getHeight()/2);
    
    ofPopMatrix();
    
}



void PlayerFace::drawBandanna(ofVec2f offset, float scale) {
    
    if (!loaded) return;
    
    ofPushMatrix();
    
    ofTranslate(offset.x, offset.y);
    ofScale(scale, scale, 1.f);
    
    // draw bandanna
    if (data.outline.current.size() > 0) {
        
        ofSetColor(116,196,247,alpha*0.9);
        ofFill();
        
        ofBeginShape();
        
        int s = data.outline.current.size();
        ofPoint z = ofPoint(data.outline.current[s-1].x,data.outline.current[s-1].y);
        ofPoint a = ofPoint(data.outline.current[0].x,  data.outline.current[0].y);
        ofPoint b = ofPoint(data.outline.current[1].x,  data.outline.current[1].y);
        ofPoint c = ofPoint(data.outline.current[8].x,  data.outline.current[8].y);
        ofPoint d = ofPoint(data.outline.current[9].x,  data.outline.current[9].y);
        ofPoint e = ofPoint(data.outline.current[10].x, data.outline.current[10].y);
        
        ofPoint diffBA = b - a;
        ofPoint diffDC = c - d;
        
        a += (z - a) * 0.25;
        b = a + diffBA;
        
        d += (e - d) * 0.25;
        c = d + diffDC;
        
        a += ofPoint(-2,5);
        b += ofPoint(-9,-5);
        c += ofPoint(9,-5);
        d += ofPoint(2,5);
        
        //        a += (z - a);
        //        b += (z - a);
        //        c += (e - d);
        //        d += (e - d);
        
        ofVertex(a);
        ofVertex(b);
        ofVertex(c);
        ofVertex(d);
        
        ofEndShape(true);
    }
    
    ofPopMatrix();
    
}




void PlayerFace::drawPressHat(ofVec2f offset, float scale) {
    
    if (!loaded) return;
    
    ofPushMatrix();
    
    ofTranslate(offset.x, offset.y);
    ofScale(scale, scale, 1.f);
    ofScale(0.65f, 0.65f, 1.f);
    
    ofEnableAlphaBlending();
    
    ofSetColor(255, 255, 255, alpha);
    props["press_hat"].draw(-props["press_hat"].getWidth()/2,-props["press_hat"].getHeight()/2);
    
    ofPopMatrix();
    
}




void PlayerFace::drawFanHat(ofVec2f offset, float scale) {
    
    if (!loaded) return;
    
    ofPushMatrix();
    
    ofTranslate(offset.x, offset.y);
    ofScale(scale, scale, 1.f);
    ofScale(0.65f, 0.65f, 1.f);
    
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, alpha);
    props["fan_hat"].draw(-props["fan_hat"].getWidth()/2,-props["fan_hat"].getHeight()/2);
    
    ofPopMatrix();
    
}




void PlayerFace::drawBadguyGlasses(ofVec2f offset, ofVec2f leftEye, ofVec2f rightEye) {
    
    if (!loaded) return;
    
    ofPushMatrix();
    ofTranslate(offset);
    
    float angle = atan2f(rightEye.y-leftEye.y, rightEye.x-leftEye.x);
    ofTranslate(leftEye);
    ofRotate(ofRadToDeg(angle), 0.f, 0.f, 1.f);
    
    float w = ofDist(rightEye.x,rightEye.y,leftEye.x,leftEye.y);
    float h = w * props["badguy_glasses"].getHeight() / (float)props["badguy_glasses"].getWidth();
    
    ofSetColor(255, alpha);
    ofEnableAlphaBlending();
    props["badguy_glasses"].draw(-w/2,-h+10,w*2,h*2);
    ofSetColor(255, alpha);
    
    /* 
     ofScale(scale, scale, 1.f);
     ofScale(1.f, 1.f, 1.f);
     
     ofEnableAlphaBlending();
     ofSetColor(255, 255, 255);
     badguyGlasses.draw(-badguyGlasses.getWidth()/2,-badguyGlasses.getHeight()/2);
     */
    ofPopMatrix();
    
}



