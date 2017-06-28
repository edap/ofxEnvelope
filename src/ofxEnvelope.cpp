#include "ofxEnvelope.h"

static const ofxEnvelopeOptions defaultEnvelopeOptions = {
    400, // curveHeight
    1.0, // curveCutoff
    0.002, // curvature
    600 // nVertices
};

int curveHeight;
float curveCutoff;
float curvature;
int nVertices;

ofxEnvelope::ofxEnvelope(){
    setup(defaultEnvelopeOptions);
};

ofxEnvelope::ofxEnvelope(ofxEnvelopeOptions opt){
    setup(opt);


};

ofxEnvelope::~ofxEnvelope(){
    //cleanup allocation
}

void ofxEnvelope::setup(ofxEnvelopeOptions opt){
    this->options = opt;
    setupPoints();
};

void ofxEnvelope::setupPoints(){
    points.reserve(options.nVertices);
    float x_zero = getPointZero(options.curvature, options.curveHeight);



    for (int i =0; i< options.nVertices; i++) {
        float randomY = ofRandom(options.curveHeight);
        float xOnCurve = getVauleOnParabola(options.curvature, randomY, options.curveHeight/2, x_zero);
        float negativeXOnCurve = xOnCurve * -1;

        float zOnCurve = xOnCurve;
        float negativeZOnCurve = zOnCurve * -1;
        glm::vec3 pos = glm::vec3(ofRandom(xOnCurve, negativeXOnCurve),
                                  randomY,
                                  ofRandom(negativeZOnCurve, zOnCurve));
        points.push_back(pos);
    }

};


const vector<glm::vec3> ofxEnvelope::getPoints() {
};


void ofxEnvelope::draw(){


    ofSetColor(ofFloatColor::red);
    ofDrawCircle(0, options.curveHeight, 0, 20);
    ofSetColor(ofFloatColor::blue);
    for (auto v:points) {
        ofDrawSphere(v.x, v.y, v.z, 2);
    }
};


void ofxEnvelope::moveTo(glm::vec3 _pos){
    for(auto &v:points){
        v.x += _pos.x;
        v.y += _pos.y;
        v.z += _pos.z;
    }
}

const float ofxEnvelope::getPointZero(float a, float _height) const{
    return (-1 * a) * ((_height/2.0)*(_height/2.0));

}

const float ofxEnvelope::getVauleOnParabola(float a, float y, float y_0, float x_0) const{
    return a * ((y - y_0)*(y - y_0)) + x_0;

}

void ofxEnvelope::clear(){
    points.clear();
}



