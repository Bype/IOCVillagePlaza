#pragma once

// OF

#include "ofMain.h"
#include "defines.h"

// My Classes

#include "Animation.h"

// Main Controller

class Controller : public ofBaseApp{
    
public:
    
    //// init + loop ////
    
    void setup();
    void exit();
    void update();
    void draw();
    
    //// interaction ////
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    
    //// system notification ////
    
    void gotMessage(ofMessage msg);
    
    //// my class members ////
    
    Animation animation;
    
    
};
