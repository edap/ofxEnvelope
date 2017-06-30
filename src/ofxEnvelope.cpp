#include "ofxEnvelope.h"

static const ofxEnvelopeOptions defaultEnvelopeOptions = {
    400,   // curveHeight
    0.0,   // curveCutoffTop (percent of the top area that will not be considered)
    0.002, // curvature
    600,   // nVertices
    0.3,   //deviationOnY (percent on the height)
    0.3,    //deviationOnX (percent on the ray)
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
    points.clear();
    line.clear();
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
        float randomY = getRandomY();
        // do not add points that are not in the range of the interested section
        if(randomY < options.curveHeight && randomY > 0 &&
           !pointInTopCutOffArea(randomY)
           ) {
            float xOnCurve = getVauleOnParabola(options.curvature, randomY, options.curveHeight/2, x_zero);
            float radiusLength = abs(xOnCurve);
            float radius = getRandomRadius(radiusLength);
            float randomTheta = 2.0f * 3.1415926f * ofRandom(1.0);

            float x = radius * cosf(randomTheta);
            float z = radius * sinf(randomTheta);

            glm::vec3 pos = glm::vec3(x,
                                      randomY,
                                      z);

            points.push_back(pos);
        };
    }
};

bool ofxEnvelope::pointInTopCutOffArea(float y){
    float lengthToRemove = options.curveCutoffTop * options.curveHeight;
    bool isIt =  y > (float(options.curveHeight) - lengthToRemove);
    cout << lengthToRemove << endl;
    return isIt;
};

float ofxEnvelope::getRandomY(){
    if(options.deviationOnY < 0.01){
        return ofRandom(options.curveHeight);
    } else {
        float deviation = options.curveHeight * options.deviationOnY;
        float rY = abs(ofRandomGaussian(options.curveHeight, deviation));
        // we take just the bottom part of the curve
        float bottomPart;
        if (rY >= options.curveHeight) {
            float diff = rY = options.curveHeight;
            bottomPart = options.curveHeight - diff;
        } else {
            bottomPart = rY;
        }
        return bottomPart;
    }
}

float ofxEnvelope::getRandomRadius(float _avgRay){
    if(options.deviationOnX < 0.01){
        return _avgRay;
    } else {
        float deviation = _avgRay * options.deviationOnX;
        float radius = abs(ofRandomGaussian(_avgRay, deviation));
        // we take just the bottom part of the curve
        float bottomPart;
        if (radius >= _avgRay) {
            float diff = radius - _avgRay;
            bottomPart = _avgRay - diff;
        } else {
            bottomPart = radius;
        }
        return bottomPart;
    }
}


const vector<glm::vec3> ofxEnvelope::getPoints() {
    return this->points;
};


void ofxEnvelope::draw(){
    ofPushStyle();
    ofSetColor(ofFloatColor::red);
    line.draw();
    ofSetColor(ofFloatColor::blue);
    for (auto v:points) {
        ofDrawSphere(v.x, v.y, v.z, 4);
    }
    ofPopStyle();
};


void ofxEnvelope::moveTo(glm::vec3 _pos){
    for(auto &v:points){
        v.x += _pos.x;
        v.y += _pos.y;
        v.z += _pos.z;
    }

    line.clear();
    float x_zero = getPointZero(options.curvature, options.curveHeight);
    for(int y = 0; y< options.curveHeight; y+= 10){
        float x = getVauleOnParabola(options.curvature, y, options.curveHeight/2, x_zero);
        line.addVertex(x+_pos.x, y+_pos.y);
    }
}

const float ofxEnvelope::getPointZero(float a, float _height) const{
    return (-1 * a) * ((_height/2.0)*(_height/2.0));

}

const float ofxEnvelope::getVauleOnParabola(float a, float y, float y_0, float x_0) const{
    return a * ((y - y_0)*(y - y_0)) + x_0;

}

// https://github.com/openframeworks/openFrameworks/issues/224
float ofxEnvelope::ofRandomGaussian(float mean, float stddev) {
    std::normal_distribution<float>::param_type _param(mean, stddev);
    distribution.param(_param);
    return distribution(generator);
}

float ofRandomGaussian() {
    //this assumes the parameters dont change just get another number from the distribution
    //return distribution(generator);
}

void ofxEnvelope::clear(){
    line.clear();
    points.clear();
}



