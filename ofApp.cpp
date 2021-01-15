#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	
	int deg_span = 6;
	ofColor color;
	for (int deg = 0; deg < 360; deg += deg_span * 2) {

		for (int radius = 50; radius < 720; radius += 15) {

			int hue = ((int)ofMap(deg, 0, 360, 0, 255) + radius / 2 - ofGetFrameNum()) % 255;
			color.setHsb(hue, 255, 255);

			this->mesh.addVertex(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), 0));
			this->mesh.addVertex(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), 0));
			this->mesh.addColor(color);
			this->mesh.addColor(color);

			if (radius > 50) {

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
			}

		}
	}


	this->mesh.addVertex(glm::vec3());
	this->mesh.addColor(ofColor(255));
	int center_index = this->mesh.getNumVertices() - 1;
	for (int deg = 0; deg < 360; deg += deg_span) {

		int hue = ((int)ofMap(deg, 0, 360, 0, 255) - ofGetFrameNum()) % 255;
		color.setHsb(hue, 255, 255);

		this->mesh.addVertex(glm::vec3(35 * cos((deg + deg_span) * DEG_TO_RAD), 35 * sin((deg + deg_span) * DEG_TO_RAD), 0));
		this->mesh.addVertex(glm::vec3(35 * cos((deg - deg_span) * DEG_TO_RAD), 35 * sin((deg - deg_span) * DEG_TO_RAD), 0));

		this->mesh.addColor(color);
		this->mesh.addColor(color);

		this->mesh.addIndex(center_index);
		this->mesh.addIndex(this->mesh.getNumVertices() - 2);
		this->mesh.addIndex(this->mesh.getNumVertices() - 1);

		
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.draw();

	ofSetColor(239);
	ofFill();
	ofDrawRectangle(glm::vec2(ofGetWidth() * -0.5, ofGetHeight() * -0.5), ofGetWidth(), 30);
	ofDrawRectangle(glm::vec2(ofGetWidth() * -0.5, ofGetHeight() *  0.5), ofGetWidth(), -30);
	ofDrawRectangle(glm::vec2(ofGetWidth() * -0.5, ofGetHeight() * -0.5), 30, ofGetHeight());
	ofDrawRectangle(glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * -0.5), -30, ofGetHeight());
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}