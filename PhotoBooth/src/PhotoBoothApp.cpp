//
//  PhotoBoothApp.cpp
//  PhotoBooth
//
//  Created by Douglas Stanley on 04|26|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "PhotoBoothApp.h"

//--------------------------------------------------------------
void PhotoBoothApp::setup(){
    
	ofBackground(255,255,255);
    
    tag = "";
    
    photobooth.setup();
    
}

//--------------------------------------------------------------
void PhotoBoothApp::update(){
    photobooth.update();
}

//--------------------------------------------------------------
void PhotoBoothApp::draw(){
    photobooth.draw();
}

//--------------------------------------------------------------
void PhotoBoothApp::keyPressed(int key){

    switch(key) {
            
        case OF_KEY_UP:
            photobooth.toggleCameraVisibility();
            break;
            
        case OF_KEY_DOWN:
            photobooth.toggleStateVisibility();
            break;
            
        case OF_KEY_RIGHT:
            photobooth.toggleRotation();
            break;
            
        case OF_KEY_RETURN:
            photobooth.setTag(tag);
            tag = "";
            break;
            
        case OF_KEY_DEL:
        case OF_KEY_BACKSPACE:
            tag = "";
            break;
            
        default:
            // add key
            if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || (key >= '0' && key <= '9')) {
                tag += key;
            } else {
                tag = "";
            }
            break;
            
    }
    
}


//--------------------------------------------------------------
void PhotoBoothApp::keyReleased(int key){

}

//--------------------------------------------------------------
void PhotoBoothApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void PhotoBoothApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PhotoBoothApp::mousePressed(int x, int y, int button){
	photobooth.mousePressed(x,y,button);
}


//--------------------------------------------------------------
void PhotoBoothApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PhotoBoothApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void PhotoBoothApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void PhotoBoothApp::dragEvent(ofDragInfo dragInfo){ 
    
}
