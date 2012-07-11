//
//  AnimationMovie.cpp
//  Stadium
//
//  Created by Douglas Stanley on 07|08|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "AnimationMovie.h"
#include "ofxXmlSettings.h"


float AnimationMovie::alpha = 255;


void AnimationMovie::setup(string _name) {
    
    name = _name;
    
    movie.loadMovie("animations/" + name + "/" + name + ".mov");
    movie.setSpeed(0.f);
    movie.play();
    movie.setLoopState(OF_LOOP_NONE);
    ratio.y = (float)movie.height / (float)movie.width;
    ratio.x = (float)movie.width / (float)movie.height;
    
    loadKeyframes();
    
}

void AnimationMovie::loadKeyframes() {
    
    ofxXmlSettings xml;
    // load the keyframe file for the smiley face
    xml.loadFile("animations/" + name + "/" + name + ".xml");
    
    // error checking
    if (!xml.getNumTags("data")) return;
    // go into data
    xml.pushTag("data");
    
    int howManyFaces = xml.getNumTags("face");
    
    for(int i=0; i<howManyFaces; i++) {
        
        // figure out which persona this face is attached to
        string playerString = xml.getAttribute("face", "player", "athlete", i);
        //int playerIndex = (char)playerString[0]-65;
        int playerIndex = xml.getAttribute("face", "id", 0, i);
        
        // go into this face
        xml.pushTag("face", i);
        
        // add a face
        players.push_back( AnimationPlayer() );
        // set the face type
        players.back().setup(playerString);
        
        // how many keyframes?
        int keyframeCount = xml.getNumTags("keyframe");
        
        //cout << "loading player " << playerString << "(" << keyframeCount << ")" << endl;
        // go through each keyframe
        for(int j=0; j<keyframeCount; j++) {
            
            // get the properties 
            float t = xml.getAttribute("keyframe", "timePct", 0.f, j);
            float x = xml.getAttribute("keyframe", "x", -100.f, j);
            float y = xml.getAttribute("keyframe", "y", -100.f, j);
            float scaleX = xml.getAttribute("keyframe", "scale", 0.5f, j);
            float scaleY = xml.getAttribute("keyframe", "scale", 0.5f, j);
            float opacity = xml.getAttribute("keyframe", "opacity", 100.f, j);
            string gesture = xml.getAttribute("keyframe", "gesture", "normal", j);
            
            // add this keyframe to local data
            players[i].addKeyframe(Keyframe(playerIndex,x,y,t,scaleX,scaleY,opacity,gesture) );
            
        }
        
        xml.popTag(); // face #i
        
    }
    
    xml.popTag(); // data
    
}



void AnimationMovie::update() {
    
    movie.idleMovie();
    
    for(int i=0; i<players.size(); i++) {
        players[i].update();
    }
    
}



void AnimationMovie::draw() {
    
    // first, draw the big movie on top of which we'll draw our faces
    movie.draw(rectangle);
    
    // now draw faces
    
    ofEnableAlphaBlending();
    
    // move to movie offset
    ofPushMatrix();
    ofTranslate(scale.x, scale.y);
    ofScale(scale.width, scale.height);
    
    // get position of movie from 0.f > 1.f
    float t = movie.getPosition();
    
    // go through all the players
    for(int i=0; i<players.size(); i++) {
        
        // get the current player's keyframes
        vector<Keyframe> keyframes = players[i].keyframes;
        
        // find the right keyframe
        
        // find the first keyframe
        float first = keyframes[0].time;
        float last  = keyframes[keyframes.size()-1].time;
        
        // if we're too early
        // if we're too early or too late, move on to next
        if (t < first || t > last) continue;
        
        // now we can safely start with first keyframe
        int index = 0;
        for(int j=1; j<keyframes.size(); j++) {
            
            // if we're less than time t, then count us in
            if (keyframes[j].time <= t) index = j;
            else break; // until we find one that's later than time t
            
        }
        
        //int index = MIN(keyframes.size()-1,(int)(scenarios[current].movie.getPosition() * keyframes.size()));
        Keyframe keyframe = keyframes[index];
        
        ofPushMatrix();
        
        // draw the face
        ofTranslate(keyframe.x, keyframe.y);
        ofScale(keyframe.scaleX,keyframe.scaleY);
        //ofSetColor(255,255,255,255*keyframe.opacity);
        
        // draw this personae
        float alpha = 255 * keyframe.opacity;
        players[i].draw(keyframe.gesture, alpha);
        
        ofPopMatrix();
        
    }
    
    
    ofPopMatrix();
    
}

