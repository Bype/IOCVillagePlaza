//
//  AnimationPlayer.cpp
//  Stadium
//
//  Created by Douglas Stanley on 07|08|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "AnimationPlayer.h"

void AnimationPlayer::setup(string _name) { 
    
    name = _name; 
    
    // setup the face
    face.setup(name);
    
    lastGesture = "";
    active = false;
    
}


void AnimationPlayer::addKeyframe(Keyframe keyframe) {
    keyframes.push_back(keyframe);
}

void AnimationPlayer::update() { 
    
    face.update();
    
}

void AnimationPlayer::draw(string gesture, float alpha) { 
    
    if (lastGesture != gesture) {
        lastGesture = gesture;
        face.setState(gesture); 
    }
    face.draw(alpha); 
    
}

