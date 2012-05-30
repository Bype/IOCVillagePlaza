#pragma once

#include "ofMain.h"
#include "Coubertin.h"

// OSC
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "Face.h"

class PhotoBoothKeyOnly : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    // osc
    ofxOscSender osc;
    void setupOsc();
    void sendOsc(Face &face);
    
    ////
    
    void toggleCameraVisibility();
    void toggleStateVisibility();
    void toggleRotation();
    void setTag(string newTag);
    
    ////
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Coubertin coubertin;

};

