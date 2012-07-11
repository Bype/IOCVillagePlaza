//
//  FaceData.h
//  PhotoBooth
//
//  Created by Douglas Stanley on 06|24|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#pragma once

#include "ofMain.h"

struct FaceDataType {
    
    vector<ofVec2f> original;
    vector<ofVec2f> normalized;
    vector<ofVec2f> current;
    vector<ofVec2f> target;
    vector<ofVec2f> textureCoordinates;
    
    void clear() {
        original.clear();
        normalized.clear();
        current.clear();
        target.clear();
        textureCoordinates.clear();
    }
    
    void push_back(ofVec2f newVector) {
        original.push_back(newVector);
        normalized.push_back(newVector);
        current.push_back(newVector);
        target.push_back(newVector);
        textureCoordinates.push_back(newVector);
    }
    
};


struct FaceData {
    
    string type;
    
    FaceDataType outline;
    FaceDataType features;
    
    void clear() {
        outline.clear();
        features.clear();
    }
	
};



struct FaceVertex {
    int index;
    string type;
    FaceVertex(int _index, string _type) : index(_index), type(_type) {}
};
