//
//  Gesture.h
//  PhotoBooth
//
//  Created by Douglas Stanley on 07|01|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"

struct GestureVertex {
    
    string type;
    int index;
    ofVec2f loc;
    string unit;
    
    GestureVertex( string _type, int _index, ofVec2f _loc=ofPoint(0.f,0.f), string _unit="" )
    : type(_type), index(_index), loc(_loc), unit(_unit)
    { }
    
};


struct GestureGroup {
    
    string name;
    vector<GestureVertex> vertices;
    
    GestureGroup(string _name) : name(_name) { }
    
    void addVertex(GestureVertex vertex) {  }
    void addVertex(string type, int index) { vertices.push_back(GestureVertex(type, index)); }
    
};



struct Gesture {
    
    string name;
    vector<GestureVertex> vertices;
    
    Gesture() : name("") {  }
    Gesture(const Gesture &gesture) : name(gesture.name), vertices(gesture.vertices) {  }
    Gesture(string _name) : name(_name) {  }
    
    void addVertex(GestureVertex vertex) {
        vertices.push_back(vertex);
    }
    
};


struct GestureAnimationPair {
    
    string name;
    float delay;
    
    GestureAnimationPair(string _name, float _delay) : name(_name), delay(_delay) {}
    
};



struct GestureAnimation {
    
    string name;
    bool active;
    vector<GestureAnimationPair> delays;
    int index;
    float lastDelay;
    
    GestureAnimation(string _name) : name(_name), active(false), index(0), lastDelay(0) { }
    
    void addPair(string name, float delay) { delays.push_back(GestureAnimationPair(name,delay)); }
    
    string getCurrent() { return delays[index].name; }
    
    bool readyForNextFrame() { 
        return (ofGetElapsedTimef() > lastDelay + delays[index].delay);
    }
    
    string nextFrame() {
        index = ++index % delays.size();
        lastDelay = ofGetElapsedTimef();
        return getCurrent();
    }
    
    void activate() { active = true; }
    void reset() { active = false; index = 0; lastDelay = 0; }
    
};
