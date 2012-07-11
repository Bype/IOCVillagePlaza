//
//  AnimationPlayer.h
//  Stadium
//
//  Created by Douglas Stanley on 07|08|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "AnimationKeyframe.h"
#include "PlayerFace.h"

struct AnimationPlayer {
    
    string name;
    vector<Keyframe> keyframes;
    string lastGesture;
    bool active;
    
    PlayerFace face;
    
    void addKeyframe(Keyframe keyframe);
    
    void setup(string _name);
    void update();
    void draw(string gesture, float alpha=0.f);
    
};