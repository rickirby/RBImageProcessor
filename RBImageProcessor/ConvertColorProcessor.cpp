//
//  ConvertColorProcessor.cpp
//  RBImageProcessor
//
//  Created by Ricki Private on 01/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ConvertColorProcessor.hpp"

Mat ConvertColorProcessor::convertToGRAY(Mat image) {
	Mat gray;
	cv::cvtColor(image, gray, COLOR_BGR2GRAY);
	
	return gray;
}

Mat ConvertColorProcessor::convertToHSV(Mat image) {
	Mat hsv;
	cv::cvtColor(image, hsv, COLOR_BGR2HSV);
	
	return hsv;
}

Mat ConvertColorProcessor::convertToBW(Mat image) {
	Mat gray, bw;
	cv::cvtColor(image, gray, COLOR_BGR2GRAY);
	cv::threshold(gray, bw, 0, 255, THRESH_OTSU);
	
	return bw;
}

Mat ConvertColorProcessor::adaptiveThreshold(Mat image, bool isGaussian, int blockSize, double constant) {
	Mat gray, result;
	cv::cvtColor(image, gray, COLOR_BGR2GRAY);
	cv::adaptiveThreshold(gray, result, 255, isGaussian ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, constant);
	
	return result;
}

Mat ConvertColorProcessor::dilate(Mat image, int iteration, bool isGaussian, int blockSize, double constant) {
	Mat gray, adaptiveImage, result;
	cv::cvtColor(image, gray, COLOR_BGR2GRAY);
	cv::adaptiveThreshold(gray, adaptiveImage, 255, isGaussian ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, constant);
	cv::dilate(adaptiveImage, result, Mat(), Point(-1, -1), iteration);
	
	return result;
}

Mat ConvertColorProcessor::erode(Mat image, int erodeIteration, int dilateIteration, bool isGaussian, int blockSize, double constant) {
	Mat gray, adaptiveImage, dilateImage, result;
	cv::cvtColor(image, gray, COLOR_BGR2GRAY);
	cv::adaptiveThreshold(gray, adaptiveImage, 255, isGaussian ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, constant);
	cv::dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), dilateIteration);
	cv::erode(dilateImage, result, Mat(), Point(-1, -1), erodeIteration);
	
	return result;
}
