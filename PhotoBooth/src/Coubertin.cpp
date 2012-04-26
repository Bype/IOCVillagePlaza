//
//  Coubertin.cpp
//  DeCoubertin
//
//  Created by Douglas Stanley on 04|05|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "Coubertin.h"
//#include <iterator>

// MARK: Init

void Coubertin::setup() {
    
    speechFont.loadFont("fonts/GothamRnd-Bold.otf", 24, true, true);
    
    // these are the names of the movies we need to load
    string names[7] = {"poireauter", "hello", "bulle", "remove", "smile", "flash", "select"};
    for(int i=0; i<7; i++) {
        // load movie
        coubertin[names[i]] = ofVideoPlayer();
        coubertin[names[i]].loadMovie("personae/decoubertin/" + names[i] + ".mov");
        coubertin[names[i]].setLoopState(OF_LOOP_NONE);
        coubertin[names[i]].setPosition(0.f);
        coubertin[names[i]].setSpeed(0.f);
        coubertin[names[i]].play();
    }
    
    w = coubertin.begin()->second.getWidth();
    h = coubertin.begin()->second.getHeight();
    
    target = "poireauter";
    setCurrent(target);
    
    speechText = "";
    
}



// MARK: Loop

void Coubertin::update() {
    
    // go through all the movies
    for(map<string,ofVideoPlayer>::iterator it = coubertin.begin(); it != coubertin.end(); it++) {
        (*it).second.idleMovie();
    }
    
    if ("poireauter" == current) {
        
        updatePoireauter();
        
    } else if ("hello" == current) {
        
        updateHello();
        
    } else if ("bulle" == current) {
        
        updateBulle();
        
    } else if ("remove" == current) {
        
        updateRemove();
        
    } else if ("smile" == current) {
        
        updateSmile();
        
    } else if ("flash" == current) {
        
        updateFlash();
        
    } else if ("select" == current) {
        
        updateSelect();
        
    }
    
}


void Coubertin::updatePoireauter() {
    
    // this loop can be interrupted at any time
    ready = true;
    triggered = true;
    
    // do we have a new target?
    if (current != target) {
        // are we done with this one?
        if (atBeginning("poireauter") || atEnd("poireauter")) {
            
            if (target == "flash" || target == "smile") setCurrent("remove");
            else setCurrent(target);
            return;
        }
        // should we just reverse to beginning
        if (getPosition("poireauter") < 0.5 && getSpeed("poireauter") > -1.5) {
            reverse("poireauter",-1.5);
            return;
        } // or is the end closer
        else if (getPosition("poireauter") > 0.5 && getSpeed("poireauter") < 1.5) {
            forward("poireauter",1.5);
            return;
        } // still not done, just wait until we're done
        else return;
    }
    
    // are we at the beginning/end of the movie?
    if ((atBeginning("poireauter") || atEnd("poireauter")) && (ofRandom(1000) < 1) ) {
        
        if (ofRandom(2) < 1) { // sometimes forward
            reverse("poireauter",ofRandom(0.75,1.5));
        } else { // sometimes backward
            forward("poireauter",ofRandom(0.75,1.5));
        }
        
    }
    
}


void Coubertin::updateHello() {
    
    // have we said hello?
    if (triggered && atEnd("hello")) {
        ready = true;
    }
    
    // do we have a new target?
    if (current != target) {
        
        if (atEnd("hello")) {
            if (target == "flash" || target == "smile") setCurrent("remove");
            else setCurrent(target);
            return;
        }
        
    }
    
    // if we haven't played yet, play
    if (!triggered) {
        // if we have to, rewind
        if (atEnd("hello") || atBeginning("hello")) rewind("hello");
        // play this puppy
        forward("hello");  
        triggered = true;      
    }
    
}


void Coubertin::updateBulle() {
    
    // have we said hello?
    if (triggered && atEnd("bulle")) {
        ready = true;
    }
    
    if (current != target) {
        
        // if we've rewinded all the way back to the beginning
        if (atBeginning("bulle")) {
            if (target == "flash" || target == "smile") setCurrent("remove");
            else setCurrent(target);
            return;
        }
        
        // if we need to, rewind
        if (atEnd("bulle")) reverse("bulle");
        
    }
    
    //if (!triggered) {
    if (atBeginning("bulle")) {
        
        //if (atEnd("bulle")) rewind("bulle");
        forward("bulle");
        triggered = true;
        
    }
    
}


void Coubertin::updateRemove() {
    
    // have we said hello?
    if (triggered && atEnd("remove")) {
        ready = true;
    }
    
    if (current != target) {
        
        // ok, we're back at the beginning
        if (atBeginning("remove") && target != "flash" && target != "smile") {
            setCurrent(target);
            return;
        }
        
        if (atEnd("remove") && (target == "flash" || target == "smile")) {
            setCurrent("smile");
            return;
        }
        
        // if we need to, rewind
        if (atEnd("remove") && target != "flash" && target != "smile") reverse("remove");
        
        // if we need to, advance
        if (atBeginning("remove") && (target == "flash" || target == "smile")) forward("remove");
        
    }
    
    //if (!triggered) {
    if (atBeginning("remove")) {
        forward("remove");
        triggered = true;
    }
    
}


void Coubertin::updateSmile() {
    
    // have we said hello?
    if (triggered && atEnd("smile")) {
        ready = true;
    }
    
    if (current != target) {
        
        if (atBeginning("smile") && target != "flash") {
            setCurrent("remove");
            return;
        }
        
        if (atEnd("smile") && target == "flash") {
            setCurrent("flash");
            return;
        }
        
        // do we need to get to the flash?
        if (atBeginning("smile") && target == "flash") forward("smile");
        
        // if we need to rewind
        if (atEnd("smile") && target != "flash") reverse("smile");
        
    }
    
    // if for whatever reason we haven't played this yet
    if (atBeginning("smile")) {
        forward("smile");
        triggered = true;
    }
    
}


void Coubertin::updateFlash() {
    
    // have we said hello?
    if (triggered && atEnd("flash")) {
        ready = true;
    }
    
    // do we have a new target?
    if (current != target) {
        
        if (atEnd("flash")) {
            setCurrent("smile");
            return;
        }
        
    }
    
    // if we haven't played yet, play
    if (!triggered) {
        // if we have to, rewind
        if (atEnd("flash") || atBeginning("flash")) rewind("flash");
        // play this puppy
        forward("flash");  
        triggered = true;      
    }
    
}


void Coubertin::updateSelect() {
    
    // have we said hello?
    if (triggered && atEnd("select")) {
        ready = true;
    }
    
    if (current != target) {
        
        // if we've rewinded all the way back to the beginning
        if (atBeginning("select")) {
            if (target == "flash" || target == "smile") setCurrent("remove");
            else setCurrent(target);
            return;
        }
        
        // if we need to, rewind
        if (atEnd("select")) reverse("select");
        
    }
    
    //if (!triggered) {
    if (atBeginning("select")) {
        
        forward("select");
        triggered = true;
        
    }
    
    
}





// MARK: Draw

void Coubertin::draw() {
    
    // draw video center screen
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofTranslate(0,50);
	ofSetColor(255,255,255);
    coubertin[current].draw( -w/2 , -h/2);
    
    // draw text, if there is any
    if ("bulle" == current && "" != speechText && triggered && atEnd("bulle")) {
        drawBulle();
    }
    
    if (("flash" == current || ("smile" == current && atEnd("smile"))) && "" != speechText) {
        drawSmile();
    }
    
    if ("select" == current && "" !=speechText && triggered && atEnd("select")) {
        drawSelect();
    }
    
    ofPopMatrix();
    
    // draw playback head
    // DEBUG
    /*ofSetColor(0,0,0);
     ofDrawBitmapString("current:" + current, ofPoint(100,100));
     ofDrawBitmapString(ofToString(coubertin[current].getSpeed(),0), ofPoint(100,115));
     ofDrawBitmapString(ofToString(getPosition(current),2), ofPoint(100,130));
     ofDrawBitmapString("atBeginning:" + ofToString(atBeginning(current)), ofPoint(100,145));
     ofDrawBitmapString("atEnd:" + ofToString(atEnd(current)), ofPoint(100,160));    
     */
    
}


void Coubertin::drawSmile() {
    
    ofPushMatrix();
    ofTranslate(-156,-282);
    drawText();
    ofPopMatrix();
    
}


void Coubertin::drawBulle() {
    
    ofPushMatrix();
    ofTranslate(106,-282);
    drawText();
    ofPopMatrix();
    
}


void Coubertin::drawSelect() {
    
    ofPushMatrix();
    ofTranslate(-256,-282);
    drawText();
    ofPopMatrix();
    
}


void Coubertin::drawText() {
    
    ofRectangle rectangle = speechFont.getStringBoundingBox(speechText, 0, 0);
    ofTranslate(-rectangle.width/2, (-rectangle.height/2) + speechFont.getLineHeight()/2);
    
    ofSetColor(255,255,255);
    speechFont.drawString(speechText,0,0);
    
    
}


// MARK: Controls


void Coubertin::forward(string name, float speed) {
    
    coubertin[name].setSpeed(ABS(speed));
    coubertin[name].play();
    
}


void Coubertin::reverse(string name, float speed) {
    
    coubertin[name].setSpeed(-ABS(speed));
    coubertin[name].play(); 
    
}

bool Coubertin::atBeginning(string name) {
    
    if (coubertin[name].getPosition() <= 0.f) return true;
    else return false;
    
}


bool Coubertin::atEnd(string name) {
    
    if (coubertin[name].getPosition() >= 1.f) return true;
    else return false;
    
}


void Coubertin::rewind(string name) {
    
    coubertin[name].setPosition(0.f);
    
}


float Coubertin::getPosition(string name) {
    
    return coubertin[name].getPosition();
    
}


float Coubertin::getSpeed(string name) {
    
    return coubertin[name].getSpeed();
    
}


void Coubertin::setCurrent(string newState) {
    
    current = newState;
    
    triggered = false;
    ready = false;
    
}


void Coubertin::setState(string newState, string text) {
    
    speechText = "";
    
    if      ("poireauter" == newState) {
        
    } else if ("hello"    == newState) {
        
    } else if ("bulle"    == newState) {
        setSpeech("  Hello!\nWelcome...");
    } else if ("remove"   == newState) {
        
    } else if ("smile"    == newState) {
        setSpeech("  May I\ntake your\n picture?");
    } else if ("flash"    == newState) {
        setSpeech("Cheese!");
        
    } else if ("select"   == newState) {
        setSpeech("Please\nselect a\nfavorite");
    }
    
    target = newState;
    triggered = false;
    ready = false;
    
}


void Coubertin::setSpeech(string text) {
    
    speechText = text;
    
}
