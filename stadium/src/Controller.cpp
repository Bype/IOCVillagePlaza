
// MARK: includes
#include "Controller.h"




// MARK: Init

void Controller::setup() {
    
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    photobooth.kinected = false;
    //photobooth.setup();
    animation.setup();
    
    // by default, cursor is hidden
    ofHideCursor();
    
}


void Controller::exit() {
    
    //photobooth.exit();
    
}



// MARK: Loop

void Controller::update() {
    
    photobooth.update();
    animation.update();
    
}

void Controller::draw() {
	
    if (animation.isVisible()) animation.draw();
    else photobooth.draw();
    
}




// MARK: interaction 

void Controller::keyPressed(int key) {

    switch (key) {
            
        case 'p':
            
            if (!photobooth.kinected) photobooth.setup();
            photobooth.toggleVisibility();
            // set animation to opposite
            animation.setVisibility(!photobooth.isVisible());
            // show/hide cursor
            if (photobooth.isVisible()) ofShowCursor();
            else ofHideCursor();
            
            break;
            
        case 'c':
            
            if (!photobooth.kinected) photobooth.setup();
            photobooth.toggleCameraVisibility();
            break;
            
        case 'f':
            
            ofToggleFullscreen();
            windowResized(ofGetWidth(), ofGetHeight());
            break;
            
        default:
            
            animation.keyPressed(key);
            break;
    }
    
}

void Controller::keyReleased(int key) {

}

void Controller::mouseMoved(int x, int y ) {
    if(animation.isVisible()) animation.mouseMoved(x,y);
}

void Controller::mouseDragged(int x, int y, int button) {
    if(animation.isVisible()) animation.mouseDragged(x,y,button);
}

void Controller::mousePressed(int x, int y, int button) {
    if(animation.isVisible()) animation.mousePressed(x,y,button);
    else photobooth.mousePressed(x,y,button);
}

void Controller::mouseReleased(int x, int y, int button) {
    if(animation.isVisible()) animation.mouseReleased(x,y,button);
}




// MARK: Window
void Controller::windowResized(int w, int h) {
    animation.windowResized(w,h);
}

void Controller::dragEvent(ofDragInfo dragInfo) { 
    
}



// MARK: System notification

void Controller::gotMessage(ofMessage msg) {
    

}
