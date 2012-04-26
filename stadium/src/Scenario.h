//
//  Scenario.h
//  IOC
//
//  Created by Douglas Stanley on 04|26|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"



// Keyframes define positions for the faces
struct Keyframe {
    
    Keyframe(int _player, float _x, float _y, float _t, float _sx, float _sy, float _o)
    : player(_player), x(_x), y(_y), time(_t), scaleX(_sx), scaleY(_sy), opacity(_o)
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
    
};


// A player just contains keyframes for the moment
struct Player {
    vector<Keyframe> keyframes;
};



struct Scenario {
    // the name of the scénario (ex: "HIV", "Drugs", "Peace", ...)
    string              name;
    // the ratio of the movie so as to rescale correctly for screen size
    ofVec2f             ratio;
    ofRectangle         scale;
    ofRectangle         rectangle;
    // the actual video data
    ofVideoPlayer       movie;
    // the indications (keyframes, ...) for compositing faces into the movie
    vector<Player>      players;
};

