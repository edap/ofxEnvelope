#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    angle.addListener(this, &ofApp::angleChanghed);
    xDev.addListener(this, &ofApp::deviationOnXChanghed);
    yDev.addListener(this, &ofApp::deviationOnYChanghed);
    cutTop.addListener(this, &ofApp::cutTopChanghed);
    height.addListener(this, &ofApp::heightChanghed);
    nVertices.addListener(this, &ofApp::nVerticesChanghed);
    yOffset.addListener(this, &ofApp::yOffsetChanghed);
    gui.setup();
    gui.add(angle.setup("angle", 0.002, 0.001, 0.02));
    gui.add(xDev.setup("xDev %", 0.2, 0.0, 0.4));
    gui.add(yDev.setup("yDev %", 0.2, 0.0, 0.4));
    gui.add(cutTop.setup("cutTop %", 0.0, 0.0, 0.9));
    gui.add(height.setup("height", 600, 10, 900));
    gui.add(nVertices.setup("nVertices", 400, 10, 4000));
    //gui.add(yOffset.setup("yOffset", 0, -400, 400));
    light.setup();
    mat.setDiffuseColor(ofFloatColor::red);
}

//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
    ofDrawAxis(400);
    mat.begin();
    env.draw();
    mat.end();
    cam.end();
    ofDisableDepthTest();
    maybeDrawGui();
}

void ofApp::angleChanghed(float & _angle){
    env.options.curvature = _angle;
    env.clear();
    env.setupPoints();
}

void ofApp::deviationOnYChanghed(float & _devY){
    env.options.deviationOnY = _devY;
    env.clear();
    env.setupPoints();
}

void ofApp::deviationOnXChanghed(float & _devX){
    env.options.deviationOnX = _devX;
    env.clear();
    env.setupPoints();
}

void ofApp::cutTopChanghed(float & _cutTop){

    env.options.curveCutoffTop = _cutTop;
    cout << env.options.curveCutoffTop << endl;
    env.clear();
    env.setupPoints();
}

void ofApp::yOffsetChanghed(int & _yOffset){
    auto pos = glm::vec3(0.0f, float(_yOffset), 0.0f);
    env.moveTo(pos);
}

void ofApp::heightChanghed(int & _height){
    env.options.curveHeight = _height;
    env.clear();
    env.setupPoints();
};

void ofApp::nVerticesChanghed(int & _nVertices){
    env.options.nVertices = _nVertices;
    env.clear();
    env.setupPoints();
};

void ofApp::keyPressed(int key){
    if(key == 'g'){
        drawGui = !drawGui;
    }
}

void ofApp::maybeDrawGui(){
    if (drawGui) {
        ofPushStyle();
        //fps
        string msg = "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
        ofDrawBitmapStringHighlight(msg, 10, 10);
        //gui
        gui.draw();
        ofPopStyle();
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//------------- -------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
