//
//  ConvertColorProcessor.cpp
//  RBImageProcessor
//
//  Created by Ricki Private on 01/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ConvertColorProcessor.hpp"

ConvertColorProcessor::ConvertColorProcessor(bool adaptiveType_, int adaptiveBlockSize_, double adaptiveConstant_, int dilateIteration_, int erodeIteration_, int cropOffsideX_, int cropOffsideY_) {
	adaptiveType = adaptiveType_;
	adaptiveBlockSize = adaptiveBlockSize_;
	adaptiveConstant = adaptiveConstant_;
	dilateIteration = dilateIteration_;
	erodeIteration = erodeIteration_;
	cropOffsideX = cropOffsideX_;
	cropOffsideY = cropOffsideY_;
}

Mat ConvertColorProcessor::convertToGRAY(Mat image) {
	Mat croppedImage, gray;
	
	// Cropping Border
	
	int croppedAreaWidth = image.cols - (2 * cropOffsideX);
	int croppedAreaHeight = image.rows - (2 * cropOffsideY);
	Rect croppedArea(cropOffsideX, cropOffsideY, croppedAreaWidth, croppedAreaHeight);
	
	croppedImage = image(croppedArea);
	
	cv::cvtColor(croppedImage, gray, COLOR_BGR2GRAY);
	
	return gray;
}

Mat ConvertColorProcessor::convertToHSV(Mat image) {
	Mat croppedImage, hsv;
	
	// Cropping Border
	
	int croppedAreaWidth = image.cols - (2 * cropOffsideX);
	int croppedAreaHeight = image.rows - (2 * cropOffsideY);
	Rect croppedArea(cropOffsideX, cropOffsideY, croppedAreaWidth, croppedAreaHeight);
	
	croppedImage = image(croppedArea);
	
	cv::cvtColor(croppedImage, hsv, COLOR_BGR2HSV);
	
	return hsv;
}

Mat ConvertColorProcessor::convertToBW(Mat image) {
	Mat croppedImage, gray, bw;
	
	// Cropping Border
	
	int croppedAreaWidth = image.cols - (2 * cropOffsideX);
	int croppedAreaHeight = image.rows - (2 * cropOffsideY);
	Rect croppedArea(cropOffsideX, cropOffsideY, croppedAreaWidth, croppedAreaHeight);
	
	croppedImage = image(croppedArea);
	
	cv::cvtColor(croppedImage, gray, COLOR_BGR2GRAY);
	cv::threshold(gray, bw, 0, 255, THRESH_OTSU);
	
	return bw;
}

Mat ConvertColorProcessor::adaptiveThreshold(Mat image) {
	Mat croppedImage, gray, result;
	
	// Cropping Border
	
	int croppedAreaWidth = image.cols - (2 * cropOffsideX);
	int croppedAreaHeight = image.rows - (2 * cropOffsideY);
	Rect croppedArea(cropOffsideX, cropOffsideY, croppedAreaWidth, croppedAreaHeight);
	
	croppedImage = image(croppedArea);
	
	cv::cvtColor(croppedImage, gray, COLOR_BGR2GRAY);
	cv::adaptiveThreshold(gray, result, 255, adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, adaptiveBlockSize, adaptiveConstant);
	
	return result;
}

Mat ConvertColorProcessor::dilate(Mat image) {
	Mat croppedImage, gray, adaptiveImage, result;
	
	// Cropping Border
	
	int croppedAreaWidth = image.cols - (2 * cropOffsideX);
	int croppedAreaHeight = image.rows - (2 * cropOffsideY);
	Rect croppedArea(cropOffsideX, cropOffsideY, croppedAreaWidth, croppedAreaHeight);
	
	croppedImage = image(croppedArea);
	
	cv::cvtColor(croppedImage, gray, COLOR_BGR2GRAY);
	cv::adaptiveThreshold(gray, adaptiveImage, 255, adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, adaptiveBlockSize, adaptiveConstant);
	cv::dilate(adaptiveImage, result, Mat(), Point(-1, -1), dilateIteration);
	
	return result;
}

Mat ConvertColorProcessor::erode(Mat image) {
	Mat croppedImage, gray, adaptiveImage, dilateImage, result;
	
	// Cropping Border
	
	int croppedAreaWidth = image.cols - (2 * cropOffsideX);
	int croppedAreaHeight = image.rows - (2 * cropOffsideY);
	Rect croppedArea(cropOffsideX, cropOffsideY, croppedAreaWidth, croppedAreaHeight);
	
	croppedImage = image(croppedArea);
	
	cv::cvtColor(croppedImage, gray, COLOR_BGR2GRAY);
	cv::adaptiveThreshold(gray, adaptiveImage, 255, adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, adaptiveBlockSize, adaptiveConstant);
	cv::dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), dilateIteration);
	cv::erode(dilateImage, result, Mat(), Point(-1, -1), erodeIteration);
	
	return result;
}
