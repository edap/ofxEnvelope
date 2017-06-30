#pragma once

#include "ofMain.h"
#include "ofxEnvelope.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void angleChanghed(float & angle);
    void deviationOnYChanghed(float & yDev);
    void deviationOnXChanghed(float & xDev);
    void cutTopChanghed(float & cutTop);
    void yOffsetChanghed(int & yOffset);
    void maybeDrawGui();
    void heightChanghed(int & height);
    void nVerticesChanghed(int & nVertices);
    bool drawGui = true;

    ofxPanel gui;
    ofxFloatSlider angle;
    ofxFloatSlider yDev;
    ofxFloatSlider xDev;
    ofxFloatSlider cutTop;
    ofxIntSlider yOffset;
    ofxIntSlider height;
    ofxIntSlider nVertices;
    ofMaterial mat;
    ofEasyCam cam;
    ofLight light;

    ofxEnvelope env;
		
};
