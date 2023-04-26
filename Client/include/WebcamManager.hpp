#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <SDL.h>

#include "headCalibration.hpp"
#include "headCorrelationTracking.hpp"
#include "handTracking.hpp"

class WebcamManager
{
    public:
    WebcamManager(SDL_Renderer* renderer);
	~WebcamManager();

    inline bool isCameraOpened() const { return cap.isOpened(); };

    inline cv::Point getHeadCenter() const { return headCenter; };
    inline cv::Point getRightHandCenter() const { return rightHandCenter; };
    inline cv::Point getLeftHandCenter() const { return leftHandCenter; };

    bool calibrate(SDL_Renderer* renderer);
    bool nextAction();
    void SDL_renderCalibration(SDL_Renderer* renderer);
    void CV_render();

    private:
    void startCalibration();

    SDL_Texture* frameTexture;

    cv::Mat frame, croppedHead, screenshotCalibration;
	cv::Mat gCroppedHead, gScreenshot, gFrame;
	cv::Mat rgbFrame, rgbScreenshotCalibration;
	cv::Vec3f handRgbCalibration;
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    bool firstCalibration;
	bool duringCalibration;
	bool endCalibrationTimer;

	float rThreshold, gThreshold, bThreshold;
    
	cv::VideoCapture cap;
	
	cv::Point headCenter;
	cv::Point rightHandCenter;
	cv::Point leftHandCenter;

	cv::Point oldLHCenter, oldRHCenter;
    
    // Calibration ellipse's constants
	const cv::Point imageCenter;
	const cv::Size ellipseSize;
	const cv::Scalar ellipseColor;
	const int handSquareSize;

    // Hand calibration data
	const cv::Point topLeftLhandCorner;
	const cv::Point bottomRightLhandCorner;
	const cv::Point topLeftRhandCorner;
	const cv::Point bottomRightRhandCorner;

    static constexpr double THRESHOLD_RATIO = 0.1;
};