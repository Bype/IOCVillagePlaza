
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
    
}


void Controller::exit() {
    
    //photobooth.exit();
    
}



// MARK: Loop

void Controller::update() {
    
    animation.update();
    
    while( osc.hasWaitingMessages() ) {
        
		// get the next message
		ofxOscMessage m;
		osc.getNextMessage( &m );
        
        if ( m.getAddress() == "/select" )
		{
			// both the arguments are int32's
			string identifier = m.getArgAsString( 0 );
            
            cout << "identifier:" << identifier << endl;
		}
    }
    
}

void Controller::draw() {
	
    animation.draw();
    
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
