//
//  AnimationMovie.h
//  Stadium
//
//  Created by Douglas Stanley on 07|07|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"

#include "AnimationKeyframe.h"
#include "AnimationPlayer.h"

struct AnimationMovie {
    
    static float alpha;
    
    void setup(string _name);
    void update();
    void draw();
    
    void loadKeyframes();
    
    string name;
    ofVideoPlayer movie;
    ofVec2f ratio;
    ofRectangle rectangle;
    ofRectangle scale;
    
    vector<AnimationPlayer> players;
    
};

