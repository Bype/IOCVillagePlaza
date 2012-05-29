//
//  PhotoBooth.h
//  IOC_Stadium
//
//  This class interacts with the user in order to retreive badge/login data
//  It also records their face using Kinect/XtiaPro and Face capture addons
//
//  Created by Douglas Stanley on 03|03|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

// data structures, debugging, etc
#include "defines.h"

// OF
#include "ofMain.h"
#include "ofxXmlSettings.h"

// classes
#include "Face.h"
#include "Coubertin.h"

// Tracking
#include "ofxOpenNI.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"

// OSC
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

// class
class PhotoBooth : public ofBaseApp {
    
public:
    
    // init
    void setup();
    void setupFaceTracking();
    void setupOpenNI();
    void exit();
    
    // timer function
    float timeSince(float t) { return ofGetElapsedTimef() - t; }
    void resetTimer(float& t) { t = ofGetElapsedTimef(); }
    
    // osc
    ofxOscSender osc;
    void setupOsc();
    void sendOsc(string identifier);
    
    // loop
    void update();
    void updateState();
    
    // behaviors
    void detectPresence();
    bool detectFace();
    void adjustTilt();
    void findTopRectangle();
    
    // bar-code
    void setTag(string newTag);
    string tag;
    
    // draw
    void draw();
    void drawContours();
    void drawState();
    void drawFace();
    void drawSlideshow();
    void drawFaceIntoFbo(ofMesh &mesh, ofImage &image);
    
    // interaction
    void mousePressed(int x, int y, int button);
    
    // should we rotate 90°?
    bool rotationOn;
    void setRotation(bool isOn) { rotationOn = true; }
    void toggleRotation() { rotationOn = !rotationOn; }
    bool isRotationOn() { return rotationOn; }
    
    // for debugging, do we show the camera?
    bool cameraVisible;
    void setCameraVisibility(bool shouldShow) { cameraVisible = shouldShow; }
    void toggleCameraVisibility() { cameraVisible = !cameraVisible; }
    bool isCameraVisible() { return cameraVisible; } 
    
    // for debugging, do we show state variables?
    bool stateVisible;
    void setStateVisibility(bool shouldShow) { stateVisible = shouldShow; }
    void toggleStateVisibility() { stateVisible = !stateVisible; }
    bool isStateVisible() { return stateVisible; } 
    
    // state
    photobooth_state getState() { return state; }
    void changeState(photobooth_state newState);
    photobooth_state state;
    bool present;
    bool isPresent() { return present; }
    float lastPresence;
    float lastAbsence;
    float lastStateChange;
    
    // De Coubertin
    Coubertin coubertin;
    
    // OpenNI
    bool                kinected;
	ofxHardwareDriver	hardware;  // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
    ofxOpenNIContext	context;
	ofxDepthGenerator	depth;
    ofxImageGenerator	image;
    ofxUserGenerator	user;
    int					nearThreshold, farThreshold;
	float				filterFactor;
    //ofImage             userMask;
	ofImage				depthRangeMask;
    int                 tiltAngle;
    float               lastTilt;
    void setTiltAngle(int newAngle);
	
	// contour
	ofxCv::ContourFinder contours;
    ofImage contourImage;
    ofRectangle contourRectangle;
    int contourThreshold;
    
    // FaceTracker
	ofxFaceTracker faceTracker;
    bool foundFace;
    vector<Face> faces;
    void eraseFaces();
    void rememberFace();
    
    // From Face Substitution
    
	ofImage src;
	vector<ofVec2f> srcPoints;
    ofFbo srcFbo;
	ofFbo maskFbo;
    
    // the paparazzi photos
    int photoCount;
    
    // athlete persona
    ofImage athlete;
    
};