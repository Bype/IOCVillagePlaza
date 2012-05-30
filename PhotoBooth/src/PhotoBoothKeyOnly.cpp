#include "PhotoBoothKeyOnly.h"

//--------------------------------------------------------------
void PhotoBoothKeyOnly::setup(){
    
	ofBackground(255,255,255);
    
    coubertin.setup();
    
    setupOsc();
    
}


void PhotoBoothKeyOnly::setupOsc() {
    
    ofxXmlSettings xml;
    xml.loadFile("osc.xml");
    
    xml.pushTag("osc");
    string address = xml.getAttribute("ip", "address", "127.0.0.1");
    int port = xml.getAttribute("port", "value", 9000);
    
	// open an outgoing connection to HOST:PORT
	osc.setup( address, port );
    
    xml.popTag(); // osc
    
}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::update(){
    
    coubertin.update();

}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::draw(){
    
    coubertin.draw();
    
}


// MARK: State


void PhotoBoothKeyOnly::toggleCameraVisibility() {
    
    
}


void PhotoBoothKeyOnly::toggleStateVisibility() {
    
    
    
}


void PhotoBoothKeyOnly::toggleRotation() {
    
    
}


void PhotoBoothKeyOnly::setTag(string newTag) {
    
    string identifier = newTag;
    string type = "athlete";
    
    string sub = newTag.substr(0,3);
    if ("ATH" == sub) type = "athlete";
    if ("PRS" == sub) type = "press";
    if ("IOC" == sub) type = "ioc";
    if ("FAN" == sub) type = "fan";
    
    Face face;
    face.type = type;
    face.identifier = identifier;
    
    sendOsc(face);
    
}





void PhotoBoothKeyOnly::sendOsc(Face &face) {
    
    ofxOscMessage m;
    m.setAddress( "/select" );
    m.addStringArg( face.type );
    m.addStringArg( face.identifier );
    osc.sendMessage( m );
    
}



//--------------------------------------------------------------
void PhotoBoothKeyOnly::keyPressed(int key){
    
    switch(key) {
            
        case 'a':
            coubertin.setState("poireauter");
            break;
            
        case 'b':
            coubertin.setState("hello");
            break;
            
        case 'c':
            coubertin.setState("bulle");
            break;
            
        case 'd':
            coubertin.setState("remove");
            break;
            
        case 'e':
            coubertin.setState("smile");
            break;
            
        case 'f':
            coubertin.setState("flash");
            break;
            
        case 'g':
            coubertin.setState("select");
            break;

        default:
            break;
            
    }
    
}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::keyReleased(int key){

}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::mousePressed(int x, int y, int button){
	
}


//--------------------------------------------------------------
void PhotoBoothKeyOnly::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::windowResized(int w, int h){

}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::dragEvent(ofDragInfo dragInfo){ 

}
