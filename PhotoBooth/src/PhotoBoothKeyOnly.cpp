#include "PhotoBoothKeyOnly.h"

//--------------------------------------------------------------
void PhotoBoothKeyOnly::setup(){
    
	ofBackground(255,255,255);
    
    coubertin.setup();
    
}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::update(){
    
    coubertin.update();

}

//--------------------------------------------------------------
void PhotoBoothKeyOnly::draw(){
    
    coubertin.draw();
    
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
