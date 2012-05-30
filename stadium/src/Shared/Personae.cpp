//
//  Personae.cpp
//  IOC
//
//  Created by Douglas Stanley on 03|10|2012.
//  Copyright (c) 2012 www.abstractmachine.net. All rights reserved.
//

#include "Personae.h"
#include "ofxXmlSettings.h"

vector<Face> Personae::faces;


Personae::Personae(){
    
    
}

Personae::~Personae() {
    
    
}


void Personae::load() {
    
    load("athlete");
    load("fan");
    load("ioc");
    load("press");
    
}


void Personae::load(string type, string identifier) {
    
    
    
}


void Personae::load(string type) {
    
    // go into folder to get saved faces
    string filepath = ofToDataPath("players/" + type + "/");
    string filename = "";
    
    ofDirectory dir;
    
    int howMany = dir.listDir(filepath);
    
    //you can now iterate through the files as you like
    for(int i = 0; i < howMany; i++){
        string filename = dir.getPath(i);
        
        // load the image
        faces.push_back(Face());
        faces.back().image.loadImage(filename + "/image.png");
        
        ofxXmlSettings xml;
        xml.loadFile(filename + "/mesh.xml");
        
        // load the mesh
        
        xml.pushTag("mesh");

        // vertices
        
        xml.pushTag("vertices");
        int howManyVertices = xml.getNumTags("vertex");
        for(int i=0; i<howManyVertices; i++) {
            
            xml.pushTag("vertex", i);
            
            float x = xml.getValue("x", 0.f);
            float y = xml.getValue("y", 0.f);
            float z = xml.getValue("z", 0.f);
            
            // ok, we've extracted this vertex from the xml file, add it to mesh
            faces.back().mesh.addVertex( ofVec3f(x,y,z) );
            
            xml.popTag(); // vertex #i
        }
        
        xml.popTag(); // vertices
        
        // texture coordinates
        
        xml.pushTag("textureCoordinates");
        
        int howManyTextureCoordinates = xml.getNumTags("coordinate");
        for(int i=0; i<howManyTextureCoordinates; i++) {
            
            xml.pushTag("coordinate", i);
            
            float x = xml.getValue("x", 0.f);
            float y = xml.getValue("y", 0.f);
            
            // ok, we've extracted this texture coordinate from the xml file, add it to mesh
            faces.back().mesh.addTexCoord( ofVec2f(x,y) );
            
            xml.popTag(); // coordinate #i
            
        }
        
        xml.popTag(); // textureCoordinates
        
        xml.popTag(); // mesh
        
    }

    
}


void Personae::reload() {
    
    
    
}


void Personae::addFace(Face &face) {
    
    // first, create a folder to hold this persona
    
    string folder = face.type;
    
    //string filepath = ofToDataPath("players/athlete/");
    string filepath = ofToDataPath("players/" + folder + "/");
    //string filename = "";
    string identifier = face.identifier;
    
    /*
    int year = ofGetYear();
    int mon  = ofGetMonth();
    int day  = ofGetDay();
    int hour = ofGetHours();
    int min  = ofGetMinutes();
    int sec  = ofGetSeconds();
    int mil  = ofGetElapsedTimeMillis() % 1000;
    
    filename += ((year < 10) ? "0" : "") + ofToString(year);
    filename += ((mon < 10) ? "_0" : "_") + ofToString(mon);
    filename += ((day < 10) ? "_0" : "_") + ofToString(day);
    filename += ((hour < 10) ? "_0" : "_") + ofToString(hour);
    filename += ((min < 10) ? "_0" : "_") + ofToString(min);
    filename += ((sec < 10) ? "_0" : "_") + ofToString(sec);
    
    if (mil < 10) filename += "_00";
    else if (mil < 100) filename += "_0";
    else filename += "_";
    filename += ofToString(mil);
     
     */
    
    // create a directory with this name
    
    ofDirectory dir(filepath + identifier);
    if(!dir.exists()){
        dir.create(true);
    }
    
    // now, add to the list
    
    faces.push_back(Face());
    faces.back().image = face.image;
    faces.back().mesh  = face.mesh;
    
    // save the image
    face.image.saveImage(filepath + identifier + "image.png");
    
    // save the mesh as an xml file (vertices + textureCoordinates)
    
    ofxXmlSettings xml;
    xml.addTag("mesh");
    xml.pushTag("mesh");
    
    // save the mesh as an xml file
    int howManyVertices = face.mesh.getNumVertices();
    int howManyNormals  = face.mesh.getNumNormals();
    int howManyTextureCoordinates = face.mesh.getNumTexCoords();
    
    xml.addTag("vertices");
    xml.pushTag("vertices");
    
    for(int i=0; i<howManyVertices; i++) {
        
        ofVec3f vertex = face.mesh.getVertex(i);
        
		xml.addTag("vertex");
		xml.pushTag("vertex", i);
        
		xml.setValue("x", vertex.x);
		xml.setValue("y", vertex.y);
		xml.setValue("z", vertex.z);
        
        xml.popTag(); // vertex #i
        
    }
    
    xml.popTag(); // vertices
    
    xml.addTag("textureCoordinates");
    xml.pushTag("textureCoordinates");
    
    for(int i=0; i<howManyTextureCoordinates; i++) {
        
        ofVec2f textureCoordinate = face.mesh.getTexCoord(i);
        
        xml.addTag("coordinate");
        xml.pushTag("coordinate", i);
        
        xml.setValue("x", textureCoordinate.x);
        xml.setValue("y", textureCoordinate.y);
        
        xml.popTag(); // texture coordinate #i
        
    }
    
    xml.popTag(); // textureCoordinates
    xml.popTag(); // mesh
    
    // save file
    xml.saveFile(filepath + identifier + "mesh.xml");
    
    // tell Animation that there's a new sherrif in town
        
}
