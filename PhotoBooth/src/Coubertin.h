//
//  Coubertin.h
//  DeCoubertin
//
//  Created by Douglas Stanley on 04|05|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"


class Coubertin {
    
public:
    
    void setup();
    
    void update();
    void updatePoireauter();
    void updateHello();
    void updateBulle();
    void updateRemove();
    void updateSmile();
    void updateFlash();
    void updateSelect();
    
    void draw();
    void drawBulle();
    void drawSmile();
    void drawSelect();
    void drawText();
    
    void forward(string name, float speed=1.f);
    void reverse(string name, float speed=1.f);
    
    bool atBeginning(string name);
    bool atEnd(string name);
    
    void rewind(string name);
    
    float getPosition(string name);
    float getSpeed(string name);
    
    bool isReady() { return ready; }
    string getState() { return current; }
    
    void setCurrent(string newState);
    void setState(string newState, string text="");
    void setSpeech(string text);
    
    int w,h;
        
    map<string,ofVideoPlayer> coubertin;
    
    string target, current;
    bool triggered;
    bool ready;
    
    string speechText;
    vector<string> speechLines;
    ofTrueTypeFont speechFont;

};