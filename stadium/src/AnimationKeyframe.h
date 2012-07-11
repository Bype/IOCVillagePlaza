//
//  AnimationKeyframe.h
//  Stadium
//
//  Created by Douglas Stanley on 07|07|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"

// Keyframes define positions for the faces
struct Keyframe {
    
    Keyframe(int _player, float _x, float _y, float _t, float _sx, float _sy, float _o, string _g)
    : player(_player), x(_x), y(_y), time(_t), scaleX(_sx), scaleY(_sy), opacity(_o), gesture(_g)
    { };
    
    // the index of the player (which player? 0, 1, 2, 3, ...)
    int player;
    // the x/y position of the keyframe (percentage 0.d > 1.d)
    double x,y;
    // where in time this keyframe is (percentage 0.d > 1.d)
    double time;
    // resizing of the face
    double scaleX,scaleY;
    // fade in/out value of the face
    double opacity;
    // what is the gesture type
    string gesture;
    
};

