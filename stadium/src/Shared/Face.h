//
//  Face.h
//  IOC
//
//  Created by Douglas Stanley on 03|10|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"

class Face {
    
public:
    
    string type;
    string identifier;
    ofImage image;
    ofMesh  mesh;
    
    void draw();
    
};
