//
//  AnimationController.h
//  Stadium
//
//  Created by Douglas Stanley on 07|07|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimationMovie.h"


class AnimationController {

public:

    // init
	void setup();
    void loadScenarios();
    
    // loop
	void update();
    void updateFade();
	void draw();
    void drawFade();
    
    // playback
    void play();
    bool needsPlay();
    void pause();
    void rewind();
    
    // chapter
    void next();
    void select(string _name);
    void select(int index);
    void setNextName(string _nextName);
    
    // interaction
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    // animation index
    int current;
    string nextName;
    
    // the vector of all the movies, players and their keyframes
    vector<AnimationMovie> movies;
    
    // cosmetics (current fade in/out value)
    float fade;
	
};
