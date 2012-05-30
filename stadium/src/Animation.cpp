//
//  Animation.cpp
//  IOC_Stadium
//
//  Created by Douglas Stanley on 03|03|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "Animation.h"
#include "Personae.h"

// MARK: Init

void Animation::setup() {
    
    visible = true;
    
    // load the possible animation names
    loadScenarios();
    
    // if possible, load first animation
    if (scenarios.size()) {
        current = 0;
        rewind();
        play();
    } else {
        current = -1;
    }
    
    // load the personae into memory
    Personae::Instance().load();
    
    // this is the face mesh
    showMesh = false;
    
}


void Animation::loadScenarios() {
    
    // load the filenames
    ofDirectory directory;
    int count = directory.listDir(ofToDataPath("animations",true));
    
    for(int i=0; i<count; i++) {
        
        // get the path for this directory
        ofDirectory subDirectory = ofDirectory(directory.getPath(i));
        
        // make sure it's a directory
        if (!subDirectory.isDirectory()) continue;
        
        // it's a directory, so let's make a movie!
        scenarios.push_back(Scenario());
        
        // get the folder name
        string name = directory.getName(i);
        
        scenarios.back().name = name;
        
        scenarios.back().movie.loadMovie("animations/" + name + "/" + name + ".mov");
        scenarios.back().movie.setSpeed(0.f);
        scenarios.back().movie.play();
        scenarios.back().movie.setLoopState(OF_LOOP_NORMAL);
        
        scenarios.back().ratio.y = (float)scenarios.back().movie.height / (float)scenarios.back().movie.width;
        scenarios.back().ratio.x = (float)scenarios.back().movie.width / (float)scenarios.back().movie.height;
        
        loadKeyframes(i);
        
    }
    
}




void Animation::loadKeyframes(int index) {
    
    ofxXmlSettings xml;
    // load the keyframe file for the smiley face
    xml.loadFile("animations/" + scenarios[index].name + "/" + scenarios[index].name + ".xml");
    
    // error checking
    if (!xml.getNumTags("data")) return;
    // go into data
    xml.pushTag("data");
    
    int howManyFaces = xml.getNumTags("face");
    for(int i=0; i<howManyFaces; i++) {
        
        // figure out which persona this face is attached to
        string playerString = xml.getAttribute("face", "player", "A", i);
        int playerIndex = (char)playerString[0]-65;
        
        // go into this face
        xml.pushTag("face", i);
        
        // add a face
        scenarios[index].players.push_back( Player() );
        
        // how many keyframes?
        int keyframeCount = xml.getNumTags("keyframe");
        // go through each keyframe
        for(int j=0; j<keyframeCount; j++) {
            
            // get the properties 
            float t = xml.getAttribute("keyframe", "timePct", 0.f, j);
            float x = xml.getAttribute("keyframe", "x", -100.f, j);
            float y = xml.getAttribute("keyframe", "y", -100.f, j);
            float scaleX = xml.getAttribute("keyframe", "scaleX", 41.f, j) / 100.f;
            float scaleY = xml.getAttribute("keyframe", "scaleY", 41.f, j) / 100.f;
            float opacity = xml.getAttribute("keyframe", "opacity", 100.f, j) / 100.f;
            
            // add this keyframe to local data
            scenarios[index].players[i].keyframes.push_back( Keyframe(playerIndex,x,y,t,scaleX,scaleY,opacity) );
            
        }
        
        xml.popTag(); // face #i
        
    }
    
    xml.popTag(); // data
    
}


// MARK: Select

void Animation::select(int index) {
    
    // if the selection is out of bounds, do nothing
    if (index >= scenarios.size()) return;
    // stop current movie, if playing
    if (current > -1) pause();
    // ok, use the index to load the animation #n
    current = index;
    // set dimensions/scale
    windowResized(ofGetWidth(),ofGetHeight());
    // start at the beginning
    rewind();
    play();
    
}


void Animation::select(string _name) {
    
    // go through all the scenarios
    for(int i=0; i<scenarios.size(); i++) {
        // find one with this name
        if (scenarios[i].name != _name) continue;
        // ok, select it
        select(i);
        // get outta here
        return;
    }
    
    cout << "error: could not find an animation named \"" << _name << "\"";
    
}


// MARK: Loop

void Animation::update() {
    
    if (-1 == current) return;
    
    scenarios[current].movie.idleMovie();
    
}


void Animation::draw() {
    
    if (-1 == current) return;
    
    ofBackground(255,255,255);
    //ofEnableAlphaBlending();
    
    // now draw movie
	ofSetColor(255,255,255);
    scenarios[current].movie.draw(scenarios[current].rectangle);
    
    // move to movie offset
    ofPushMatrix();
    ofTranslate(scenarios[current].scale.x, scenarios[current].scale.y);
    ofScale(scenarios[current].scale.width, scenarios[current].scale.height);
    
    // get position of movie from 0.f > 1.f
    float t = scenarios[current].movie.getPosition();
    
    // go through all the players
    for(int i=0; i<scenarios[current].players.size(); i++) {
        
        // get the current player's keyframes
        vector<Keyframe> keyframes = scenarios[current].players[i].keyframes;
        
        // find the right keyframe
        
        // find the first keyframe
        float first = keyframes[0].time;
        float last  = keyframes[keyframes.size()-1].time;
        // if we're too early or too late, move on to next
        if (t < first || t > last) continue;
        
        // since we're not too early/late, we can safely start with first keyframe
        int index = 0;
        for(int j=1; j<keyframes.size(); j++) {
            
            // if we're less than time t, then count us in
            if (keyframes[j].time < t) index = j;
            else break; // until we find one that's later than time t
            
        }
        
        //int index = MIN(keyframes.size()-1,(int)(scenarios[current].movie.getPosition() * keyframes.size()));
        Keyframe keyframe = keyframes[index];
        
        ofPushMatrix();
        
        // draw the face
        ofTranslate(keyframe.x, keyframe.y+5);
        ofScale(keyframe.scaleX,keyframe.scaleY);
        //ofScale(0.41f, 0.41f);
        ofSetColor(255,255,255,255*keyframe.opacity);
        Personae::Instance().back(keyframe.player).draw();
        
        ofPopMatrix();
        
        
    }
    
    ofPopMatrix();
    
}


// MARK: Playback

void Animation::play() {
    scenarios[current].movie.setSpeed(MOVIE_SPEED);
}


void Animation::pause() {
    scenarios[current].movie.setSpeed(0.f);
}


void Animation::rewind() {
    scenarios[current].movie.setPosition(0.f);
}


// MARK: Visibility

void Animation::setVisibility(bool _visible) {
    
    visible = _visible;
    
    if (!visible) {
        rewind();
    }
    
}


// MARK: Interaction

void Animation::keyPressed(int key){
    
    // for &#@*$% French keyboards
    
   /* switch(key) {
        case 38 : key = '1'; break;
        case '&' : key = '1'; break;
        case 'é' : key = '2'; break;
        case '"' : key = '3'; break;
        case '\'': key = '4'; break;
        case '(' : key = '5'; break;
        case '§' : key = '6'; break;
        case 'è' : key = '7'; break;
        case '!' : key = '8'; break;
        case 'ç' : key = '9'; break;
    }*/
    
    switch(key){
            
        case ' ':
            if (scenarios[current].movie.getSpeed() == 0.f) play();
            else pause();
            break;
            
        case OF_KEY_LEFT:
            scenarios[current].movie.previousFrame();
            break;
            
        case OF_KEY_RIGHT:
            scenarios[current].movie.nextFrame();
            break;
            
        case 't':
        case 'T':
            
            // toggle on/off showing face mesh
            showMesh = !showMesh;
            
            break;
            
        default:
            
            // use number keys to choose animation
            if (key >= 48 && key <= 57) {
                int index = key-48;
                select(index);
            }
            break;
            
            
    }
}


void Animation::keyReleased(int key){
    
}

void Animation::mouseMoved(int x, int y ){
    
}


void Animation::mouseDragged(int x, int y, int button){
    
    if (0 == button) {
        
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        scenarios[current].movie.setPosition(pct);
        
    } else {
        
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        scenarios[current].movie.setSpeed(speed);
        
    }
    
}


void Animation::mousePressed(int x, int y, int button){
    
    // make sure there's a movie loaded
    scenarios[current].movie.setPaused(true);
}



void Animation::mouseReleased(int x, int y, int button){
    
    // make sure there's a movie loaded
    scenarios[current].movie.setPaused(false);
}


void Animation::windowResized(int w, int h){
    
    if (OF_FULLSCREEN == ofGetWindowMode()) {
        window = ofVec2f(ofGetScreenWidth(),ofGetScreenHeight());
    } else {
        window = ofVec2f(w,h);
    }
    
    // make sure there's a movie loaded
    if (-1 == current) return;
    
    float height = window.x * scenarios[current].ratio.y;
    float offset = (window.y/2) - (height/2);
    
    scenarios[current].rectangle = ofRectangle(0,offset,window.x,height);
    // how much have we reduced this movie's size in relation to the original
    scenarios[current].scale = ofRectangle(0,offset,window.x/(float)scenarios[current].movie.width,height/(float)scenarios[current].movie.height);
    
}

