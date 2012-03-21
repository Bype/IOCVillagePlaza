//
//  Shader.cpp
//  IOCStadium
//
//  Created by Douglas Edric Stanley on 01|24|2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Shader.h"

void Shader::setup() {
    
    // load shaders
	shader.load("shaders/noise.vert", "shaders/noise.frag");
    
}


void Shader::begin() {
    
    shader.begin();
    
}


void Shader::setUniform() {
    
    //we want to pass in some varrying values to animate our type / color 
    shader.setUniform1f("timeValX",  ofGetElapsedTimef() * 0.1 );
    shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.11 );
    
    //we also pass in the mouse position 
    //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped. 
    //shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
    
}


void Shader::end() {
    
    shader.end();
    
}