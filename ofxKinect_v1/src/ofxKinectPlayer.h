/*
 * KinectPlayer.h
 *
 *  Created on: 14/12/2010
 *      Author: arturo
 */

#pragma once

#include "ofMain.h"
#include "ofxBase3DVideo.h"
#include "ofVectorMath.h"
#include "ofxKinectCalibration.h"

class ofxKinectPlayer: public ofxBase3DVideo {
public:
	ofxKinectPlayer();
	virtual ~ofxKinectPlayer();

		/// setup the recording to read,
		/// set video to true to enable the video (infrared/RGB) image
		/// make sure you recorded the video frames or reading them will fail big time!
		//void setup(const string & file, bool video=false);
	void setup(const string & file, bool color=false);//new
	void update();
	
	void draw(float x, float y);
	void draw(float , float y, float w, float h);
	void draw(const ofPoint & point);
	void draw(const ofRectangle & rect);
		//new start
	void drawDepth(float x, float y, float w, float h);
	void drawDepth(float x, float y);
	void drawDepth(const ofPoint & point);
	void drawDepth(const ofRectangle & rect);
		//new end
	ofTexture & getTextureReference();
	ofTexture & getDepthTextureReference();
	void setUseTexture(bool bUseTexture);

	float getHeight();
	float getWidth();

	void setAnchorPercent(float xPct, float yPct){};
    void setAnchorPoint(float x, float y){};
	void resetAnchor(){};

	bool isFrameNew();
	void close();
		//new start
	void loop()				{bLoop = true;}
	void noLoop()			{bLoop = false;}
	void setLoop(bool loop)	{bLoop = loop;}
	bool isLooping()		{return bLoop;}
		//new end

	unsigned char * getPixels();
	unsigned char * getDepthPixels();
	float * getDistancePixels();
	unsigned char * getCalibratedRGBPixels();
		//new start
	/// for 007 compatibility
	ofPixelsRef getPixelsRef();
		//new end

	float getDistanceAt(int x, int y) ;
	ofVec3f getWorldCoordinateFor(int x, int y);

	int fps;
	
	const static int	width = 640;//new
	const static int	height = 480;//new
private:
	FILE * f;
	string filename;//new
	unsigned short *buf;
	ofTexture depthTex,videoTex;
	bool bUseTexture;
	unsigned char *rgb;
		//new start
	ofPixels pixels;
	
	bool bVideo;
	bool bLoop;
		//new end
	bool readColor;

	int lastFrameTime;

	ofxKinectCalibration calibration;
};

