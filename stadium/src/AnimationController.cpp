//
//  AnimationController.cpp
//  Stadium
//
//  Created by Douglas Stanley on 07|07|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "AnimationController.h"

// addons
#include "ofxXmlSettings.h"

// defines
#define MOVIE_SPEED 1.0f


// MARK: Init

void AnimationController::setup() {
    
    ofBackground(0);
    
    fade = 0.f;
    nextName = "";
    
    // load the possible animation names
    loadScenarios();
    
    // if possible, load first animation
    if (movies.size()) {
        current = -1;
        select(0);
    } else {
        current = -1;
        cout << "error" << endl;
    }
    
}



void AnimationController::loadScenarios() {
    
    // load the filenames
    ofDirectory directory;
    int count = directory.listDir(ofToDataPath("animations",true));
    
    for(int i=0; i<count; i++) {
        
        // get the path for this directory
        ofDirectory subDirectory = ofDirectory(directory.getPath(i));
        
        // make sure it's a directory
        if (!subDirectory.isDirectory()) continue;
        
        // it's a directory, so let's make a movie!
        // scenarios.push_back(Scenario());
        
        // get the folder name
        string name = directory.getName(i);
        
        // create the local instance
        movies.push_back(AnimationMovie());
        movies.back().setup(name);
        
    }
    
}



// MARK: Loop

void AnimationController::update() {
    
    if (-1 == current) return;
	
    updateFade();
    
    movies[current].update();
    
    // do we need to play?
    if (needsPlay()) next();
    
}


void AnimationController::updateFade() {
    
    float fadeSpeed = 0.05f;
    
    // fade in
    if (nextName == "" && fade > 0.f) {
        fade = MAX(0.f,fade-fadeSpeed);
    }
    
    // fade out
    if (nextName != "" && fade < 1.f) {
        fade = MIN(1.f,fade+fadeSpeed);
    }
    
    // fade out complete, change animation
    if (nextName != "" && fade == 1.f) {
        select(nextName);
        // ready for next fade out
        nextName = "";
    }
    
}



void AnimationController::draw() {
    
    if (-1 == current) return;
    
    ofBackground(0);
    
    // now draw movie
	ofSetColor(255,255,255);
    movies[current].draw();
    
    if (fade > 0.f && fade < 1.f) drawFade();
    
}



void AnimationController::drawFade() {
    
    // fade out, if necessary
    
    ofEnableAlphaBlending();
    ofSetColor(244, 244, 244, fade*255);
    ofFill();
    ofRect(movies[current].rectangle);
    
}



// MARK: Playback

void AnimationController::play() {
    if (0.f == movies[current].movie.getPosition()) rewind();
    movies[current].movie.setSpeed(MOVIE_SPEED);
}



bool AnimationController::needsPlay() {
    return 1.f == movies[current].movie.getPosition();
}



void AnimationController::pause() {
    movies[current].movie.setSpeed(0.f);
}



void AnimationController::rewind() {
    movies[current].movie.setPosition(0.f);
}



// MARK: Select

void AnimationController::next() {
    
    // if only one film
    if (movies.size() == 1) {
        
        setNextName(movies[0].name);
        
    } else { // otherwise, choose a random film
        
        int nextIndex = current;
        while(nextIndex == current) {
            nextIndex = (int)ofRandom(movies.size());
        }
        setNextName(movies[nextIndex].name);
    }
    
}



void AnimationController::select(string _name) {
    
    // go through all the movies
    for(int i=0; i<movies.size(); i++) {
        // if not us, move on to next
        if (movies[i].name != _name) continue;
        // ok, time to select
        select(i);
        return;
    }
    
}



void AnimationController::select(int index) {
    
    // if the selection is out of bounds, do nothing
    if (movies.size() <= index || 0 > index) return;
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


void AnimationController::setNextName(string _nextName) {
    
    nextName = _nextName;
    
}



// MARK: Interaction

void AnimationController::keyPressed(int key){
    
    switch(key){
            
        case ' ':
            if (movies[current].movie.getSpeed() == 0.f) play();
            else pause();
            break;
            
        case OF_KEY_LEFT:
            movies[current].movie.previousFrame();
            break;
            
        case OF_KEY_RIGHT:
            movies[current].movie.nextFrame();
            break;
            
        default:
            
            // use number keys to choose animation
            if (key >= 48 && key <= 57) {
                int index = key-48;
                setNextName(movies[index%movies.size()].name);
            }
            break;
            
            
    }
}



void AnimationController::keyReleased(int key){
    
}



void AnimationController::mouseMoved(int x, int y ){
    
}



void AnimationController::mouseDragged(int x, int y, int button){
    
    if (0 == button) {
        
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        movies[current].movie.setPosition(pct);
        
    } else {
        
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        movies[current].movie.setSpeed(speed);
        
    }
    
}



void AnimationController::mousePressed(int x, int y, int button){
    
    // make sure there's a movie loaded
    movies[current].movie.setPaused(true);
}



void AnimationController::mouseReleased(int x, int y, int button){
    
    // make sure there's a movie loaded
    movies[current].movie.setPaused(false);
}



void AnimationController::windowResized(int w, int h){
    
    ofVec2f window;
    
    if (OF_FULLSCREEN == ofGetWindowMode()) {
        window = ofVec2f(ofGetScreenWidth(),ofGetScreenHeight());
    } else {
        window = ofVec2f(w,h);
    }
    
    // make sure there's a movie loaded
    if (-1 == current) return;
    
    float height = window.x * movies[current].ratio.y;
    float offset = (window.y/2) - (height/2);
    
    movies[current].rectangle = ofRectangle(0,offset,window.x,height);
    // how much have we reduced this movie's size in relation to the original
    movies[current].scale = ofRectangle(0,offset,window.x/(float)movies[current].movie.width,height/(float)movies[current].movie.height);
    
}

