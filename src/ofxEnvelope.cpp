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

    //this line it is used just as debugging purpose
    for(int y = 0; y< options.curveHeight; y+= 10){
       float x = getVauleOnParabola(options.curvature, y, options.curveHeight/2, x_zero);
       line.addVertex(x,y);
    }

    for (int i =0; i< options.nVertices; i++) {
        float randomY = ofRandom(options.curveHeight);
        float xOnCurve = getVauleOnParabola(options.curvature, randomY, options.curveHeight/2, x_zero);
        float radiusLength = abs(xOnCurve);
        float randomTheta = 2.0f * 3.1415926f * ofRandom(1.0);

        float x = radiusLength * cosf(randomTheta);
        float z = radiusLength * sinf(randomTheta);

        glm::vec3 pos = glm::vec3(x,
                                  randomY,
                                  z);

        points.push_back(pos);
    }
};


const vector<glm::vec3> ofxEnvelope::getPoints() {
};


void ofxEnvelope::draw(){
    ofSetColor(ofFloatColor::red);
    line.draw();
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
    line.clear();
    points.clear();
}



