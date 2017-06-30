#pragma once

#include "ofMain.h"
#include <random>

struct ofxEnvelopeOptions{
    int curveHeight;
    float curveCutoffTop;
    float curvature;
    int nVertices;
    float deviationOnY;
    float deviationOnX;
};

class ofxEnvelope{
public:
    ofxEnvelope();
    ~ofxEnvelope();
    ofxEnvelope(ofxEnvelopeOptions opt);

    void setup(ofxEnvelopeOptions opt);
    void draw();
    void setupPoints();
    void moveTo(glm::vec3 pos);
    void clear();


    ofxEnvelopeOptions options;
    const vector<glm::vec3> getPoints();
private:
    vector<glm::vec3> points;
    ofPolyline line;
    const float getPointZero(float a, float _height) const;
    const float getVauleOnParabola(float a, float x, float x_0, float y_0) const;

    float getRandomY();
    float getRandomRadius(float _avgRay);
    float ofRandomGaussian(float mean, float stddev);
    float ofRandomGaussian();

    std::default_random_engine generator;
    std::normal_distribution<float> distribution;
    bool pointInTopCutOffArea(float y);
};
