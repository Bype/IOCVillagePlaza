//
//  PlayerFace.h
//  Stadium
//
//  Created by Douglas Stanley on 07|09|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "FaceData.h"
#include "Gesture.h"

class PlayerFace {

public:
    
    // static members
    static ofFbo fbo;
    
    static map<string,ofImage> props;
    static map<string,Gesture> gestures;
    static vector<GestureGroup> gestureGroups;
    static vector<GestureAnimation> gestureAnimations;
    static vector<FaceVertex> facemap;
    
    // static functions
    static int size(string newType);

    // init
	void setup(string _name);
    void setupFbo();
    
    // loop
	void update();
    void updateFaceData();
    
    // draw
	void draw(float newAlpha);
    void draw(ofVec2f pt, float newAlpha);
    void draw(float x, float y, float newAlpha);
    
    void drawFace(ofVec2f offset, float scale);
    void drawFeatures(ofVec2f offset, float scale);
    void drawBandanna(ofVec2f offset, float scale);
    void drawPressHat(ofVec2f offset, float scale);
    void drawFanHat(ofVec2f offset, float scale);
    void drawBadguyGlasses(ofVec2f offset, ofVec2f leftEye, ofVec2f rightEye);
    
    // data
    
    FaceData data;
    vector<GestureAnimation> myGestureAnimations;
    
    void loadGestures();
    void loadProps();
    void load(string newType);
    void load(string newType, int index);
    void load(string newType, string identifier);
    void normalizeMouth();
    bool loaded;
    bool isLoaded() { return loaded; }
    
    // state
    string state, lastState;
    void setState(string newState);
    string getState() { return state; }
    
    bool wiggle;
    void setWiggle(bool onOff) { wiggle = onOff; }
    bool isWiggling() { return wiggle; }
    void toggleWiggle() { wiggle = !wiggle; }
    
    bool breathing;
    void setBreathing(bool onOff) { breathing = onOff; }
    bool isBreathing() { return breathing; }
    void toggleBreathing() { breathing = !breathing; }
    
    //
    
    ofImage face;
    ofVec2f halfScreen;
	float alpha;
    
};
