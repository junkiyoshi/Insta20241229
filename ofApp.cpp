#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 2);
	this->base_mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->draw_mesh.clear();

	if (ofGetFrameNum() % 50 < 20) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 20, 0.2, 0);
	}

	vector<ofColor> color_list = { ofColor(239) };

	auto noise_seed = ofRandom(1000);
	for (int k = 0; k < color_list.size(); k++) {

		noise_seed += ofRandom(1000);
		for (auto v : this->base_mesh.getVertices()) {

			for (int i = 0; i < 1; i++) {

				auto radius = ofMap(ofNoise(glm::vec4(v.x * 0.0085, v.y * 0.0085, v.z * 0.0085, this->noise_step)), 0, 1, 50, 350);
				v = glm::normalize(v) * radius;
			}

			this->draw_mesh.addVertex(v);
			this->draw_mesh.addColor(color_list[k]);
		}

		for (int i = 0; i < this->base_mesh.getNumIndices(); i++) {

			this->draw_mesh.addIndex(this->base_mesh.getIndex(i));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(5);
	ofRotateY(ofGetFrameNum() * 0.72);

	ofFill();
	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		ofDrawSphere(this->draw_mesh.getVertex(i), 2);
		ofDrawLine(glm::vec3(), this->draw_mesh.getVertex(i));
	}

	this->cam.end();

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}