
// MARK: includes
#include "Controller.h"




// MARK: Init

void Controller::setup() {
    
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    animation.setup();
    
    // by default, cursor is hidden
    ofHideCursor();
    
	osc.setup( 9000 );
    
    selectFade = 0.f;
    selectName = "";
    
}


void Controller::exit() {
    
    //photobooth.exit();
    
}



// MARK: Loop

void Controller::update() {
    
    updateFade();
    updateOsc();
    
    animation.update();
    
}


void Controller::updateFade() {

    float fadeSpeed = 0.05f;
    
    // fade in
    if (selectName == "" && selectFade > 0.f) {
        selectFade = MAX(0.f,selectFade-fadeSpeed);
    }
    
    // fade out
    if (selectName != "" && selectFade < 1.f) {
        selectFade = MIN(1.f,selectFade+fadeSpeed);
    }
    
    // fade out complete, change animation
    if (selectName != "" && selectFade == 1.f) {
        animation.select(selectName);
        // ready for next fade out
        selectName = "";
    }

}


void Controller::updateOsc() {
    
    while( osc.hasWaitingMessages() ) {
        
		// get the next message
		ofxOscMessage m;
		osc.getNextMessage( &m );
        
        if (m.getAddress() == "/play") {
            
            selectName = m.getArgAsString(0);
            
        }
        
        if ( m.getAddress() == "/select" ) {
            
            string type = m.getArgAsString(0);
			// both the arguments are int32's
			string identifier = m.getArgAsString(1);
            
            cout << "/select\t" << identifier << endl;
		}
    }
    
}



// MARK: Draw

void Controller::draw() {
	
    animation.draw();
    
    // fade out, if necessary
    if (selectFade > 0.f) {
        
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, selectFade*255);
        ofFill();
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
    }
    
}




// MARK: interaction 

void Controller::keyPressed(int key) {

    switch (key) {
            
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
    animation.mouseMoved(x,y);
}

void Controller::mouseDragged(int x, int y, int button) {
    animation.mouseDragged(x,y,button);
}

void Controller::mousePressed(int x, int y, int button) {
    animation.mousePressed(x,y,button);
}

void Controller::mouseReleased(int x, int y, int button) {
    animation.mouseReleased(x,y,button);
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
