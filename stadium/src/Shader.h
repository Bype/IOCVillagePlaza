//
//  Shader.h
//  IOCStadium
//
//  Created by Douglas Edric Stanley on 01|24|2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofShader.h"

class Shader {
    
public:  
    
    void setup();
    void begin();
    void setUniform();
    void end();
    
    ofShader shader;
    
};
