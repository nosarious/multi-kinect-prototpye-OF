#pragma once

#include "ofConstants.h"
#include "ofTexture.h"
#include "ofGraphics.h"
#include "ofTypes.h"

#include "ofxBase3DVideo.h"

#include "ofxThread.h"
	//new start
#ifndef _MSC_VER
#include <libusb.h> //old was by itself
#endif
	//new end
#include "libfreenect.h"
#include "ofxKinectCalibration.h"
#include "ofxKinectPlayer.h"//new
#include "ofxKinectRecorder.h"//new

class ofxKinect : public ofxBase3DVideo, protected ofThread{

	public :

		ofxKinect();
		virtual ~ofxKinect();

		/// are the current frames new?
		bool isFrameNew();
        
		/// open the connection and start grabbing images
		bool open(int id);
        
		/// close the connection and stop grabbing images
		void close();
        
		/// initialize resources, must be called before open()
		//		bool init(bool infrared=false, bool bTexture=true); //old
	//new start
		/// initialize resources, must be called before open()
		/// infrared controls whether the video image is rgb or IR
		/// set vdeo to false to disabel vidoe image grabbing (saves bandwidth)
		/// set texture to false if you don't need to use the internal textures
		///
		/// naturally, if you disable the video image the video pixels and
		/// RGB color will be 0
		///
		bool init(bool infrared=false, bool video=true, bool texture=true);
	//new end
		/// updates the pixel buffers and textures - make sure to call this to update to the latetst incoming frames
		void update(); 
		
		/// clear resources
		void clear();
	//new start
		/// is the connection currently open?
		bool isConnected();
	
		/// set tilt angle of the camera in degrees
		/// 0 is flat, the range is -30 to 30
		bool setCameraTiltAngle(float angleInDegrees);
	
		//get camera angle
		float getCurrentCameraTiltAngle(); 
		float getTargetCameraTiltAngle();
	//new end
		float getDistanceAt(int x, int y);
		float getDistanceAt(const ofPoint & p);
		
		/// calculates the coordinate in the world for the pixel (perspective calculation). Center  of image is (0.0) 
		ofVec3f getWorldCoordinateFor(int x, int y);

		ofColor	getColorAt(int x, int y);
		ofColor getColorAt(const ofPoint & p);

		ofColor getCalibratedColorAt(int x, int y);
		ofColor getCalibratedColorAt(const ofPoint & p);		
		
		float 			getHeight();
		float 			getWidth();

		ofPoint			getRawAccel();
		ofPoint			getMksAccel();		
		
		/// get the pixels of the most recent rgb frame
		unsigned char	* getPixels();
		
		/// get the pixels of the most recent depth frame
		unsigned char 	* getDepthPixels();		// grey scale values
		unsigned short	* getRawDepthPixels();	// raw 11 bit values
		
		// get the rgb pixels corrected to match the depth frame
		unsigned char * getCalibratedRGBPixels();

		/// get the distance in centimeters to a given point
		float* getDistancePixels();
		
		/// get the rgb texture
		ofTexture &		getTextureReference();
		
		/// get the greyscale depth texture
	ofTexture &		getDepthTextureReference();
		
		/// for 007 compatibility
	ofPixels & getPixelsRef();
	
		
		/**
			set the near value of the pixels in the greyscale depth image to white?
			
			bEnabled = true : pixels close to the camera are brighter
			bEnabled = false: pixels closer to the camera are darker (default)
		**/
		void enableDepthNearValueWhite(bool bEnabled=true);
		bool isDepthNearValueWhite();
		
		void 			setVerbose(bool bTalkToMe);
        
		void 			setUseTexture(bool bUse);
		void 			draw(float x, float y, float w, float h);
		void 			draw(float x, float y);
		void			draw(const ofPoint & point);
		void			draw(const ofRectangle & rect);
		
		void 			drawDepth(float x, float y, float w, float h);
		void 			drawDepth(float x, float y);
		void			drawDepth(const ofPoint & point);
		void			drawDepth(const ofRectangle & rect);
	
	ofxKinectCalibration& getCalibration();//new

		const static int	width = 640;
		const static int	height = 480;

	protected:

		bool					bUseTexture;
		ofTexture				depthTex;			// the depth texture
		ofTexture 				videoTex;				// the RGB texture
		bool 					bVerbose;
		bool 					bGrabberInited;
		
		ofPixels pixels; //new
	
		unsigned char *			videoPixels;
		unsigned short *		depthPixelsRaw;
		
		ofPoint rawAccel;
		ofPoint mksAccel;
        
		float targetTiltAngleDeg;
		float currentTiltAngleDeg;
		bool bTiltNeedsApplying;
		

    private:

		freenect_context *	kinectContext;	// kinect context handle
		freenect_device * 	kinectDevice;	// kinect device handle
		
		unsigned short *	depthPixelsBack;	// depth back
		unsigned char *		videoPixelsBack;		// rgb back
		
	bool bIsFrameNew;//new
	bool bNeedsUpdate;
	bool bUpdateTex;
	bool bGrabVideo;//new
	
		bool				bInfrared;
		int					bytespp;

		// libfreenect callbacks
		static void grabDepthFrame(freenect_device *dev, void *depth, uint32_t timestamp);
		static void grabRgbFrame(freenect_device *dev, void *rgb, uint32_t timestamp);
    
		// thread function
		void threadedFunction();

		ofxKinectCalibration calibration;
};

