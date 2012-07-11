
// MARK: includes
#include "AppController.h"




// MARK: Init

void AppController::setup() {
    
    ofSetLogLevel(OF_LOG_ERROR);
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    animationController.setup();
    
    // by default, cursor is hidden
    ofHideCursor();
    
	osc.setup( 9000 );
    
    // jump into fullscreen
    keyPressed('f');
    
}


void AppController::exit() {
    
    //photobooth.exit();
    
}



// MARK: Loop

void AppController::update() {
    
    updateOsc();
    
    animationController.update();
    
}


void AppController::updateOsc() {
    
    while( osc.hasWaitingMessages() ) {
        
		// get the next message
		ofxOscMessage m;
		osc.getNextMessage( &m );
        
        if (m.getAddress() == "/play") {
            
            string selectName = m.getArgAsString(0);
            cout << selectName << endl;
            animationController.setNextName(selectName);
            
        }
        
        if ( m.getAddress() == "/select" ) {
            
            string type = m.getArgAsString(0);
			// both the arguments are int32's
			string identifier = m.getArgAsString(1);
            
            cout << "/select\t" << type << "\t" << identifier << endl;
            
		}
    }
    
}



// MARK: Draw

void AppController::draw() {
	
    animationController.draw();
    
}




// MARK: interaction 

void AppController::keyPressed(int key) {

    switch (key) {
            
        case 'f':
            
            ofToggleFullscreen();
            windowResized(ofGetWidth(), ofGetHeight());
            break;
            
        default:
            
            animationController.keyPressed(key);
            break;
    }
    
}

void AppController::keyReleased(int key) {

}

void AppController::mouseMoved(int x, int y ) {
    animationController.mouseMoved(x,y);
}

void AppController::mouseDragged(int x, int y, int button) {
    animationController.mouseDragged(x,y,button);
}

void AppController::mousePressed(int x, int y, int button) {
    animationController.mousePressed(x,y,button);
}

void AppController::mouseReleased(int x, int y, int button) {
    animationController.mouseReleased(x,y,button);
}




// MARK: Window
void AppController::windowResized(int w, int h) {
    animationController.windowResized(w,h);
}

void AppController::dragEvent(ofDragInfo dragInfo) { 
    
}



// MARK: System notification

void AppController::gotMessage(ofMessage msg) {
    

}
