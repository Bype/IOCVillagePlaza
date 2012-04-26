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
            
        case 'c':
            photobooth.toggleCameraVisibility();
            break;
            
        case 's':
            photobooth.toggleStateVisibility();
            break;
            
        case 'r':
            photobooth.toggleRotation();
            break;
            
        default:
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
