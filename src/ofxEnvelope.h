#pragma once

#include "ofMain.h"

struct ofxEnvelopeOptions{
    int curveHeight;
    float curveCutoff;
    float curvature;
    int nVertices;
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
};
