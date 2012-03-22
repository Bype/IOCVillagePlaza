//
//  Personae.h
//  IOC
//
//  Created by Douglas Stanley on 03|10|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "Face.h"

class Persona {
    
public:
    
    Face face;
    ofImage body;
    
};


class Personae {
    
public:
    
    // create a singleton
	static Personae& Instance() {
		static Personae instance;
		return instance;
	}
    
    void load();
    void reload();
	void addFace(Face &face);
	
    int size() { return faces.size(); }
    Face& getFace(int index) { return faces[index]; }
    Face& back() { return (faces.back()); }
	
private:
	
	Personae();
	Personae(Personae const&) {} // copy constructor hidden
	Personae& operator=(Personae const&) {} // assignment operator hidden
	~Personae();
	
	static vector<Face> faces;
    
};