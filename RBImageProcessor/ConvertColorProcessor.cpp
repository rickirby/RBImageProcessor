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
	cvtColor(image, gray, COLOR_BGR2GRAY);
	
	return gray;
}

Mat ConvertColorProcessor::convertToHSV(Mat image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	
	return hsv;
}

Mat ConvertColorProcessor::convertToBW(Mat image) {
	Mat bw;
	Mat gray = convertToGRAY(image);
	threshold(gray, bw, 0, 255, THRESH_OTSU);
	
	return bw;
}

Mat ConvertColorProcessor::adaptiveThreshold(Mat image, bool isGaussian, int blockSize, double constant) {
	Mat gray = convertToGRAY(image), result;
	cv::adaptiveThreshold(gray, result, 255, isGaussian ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, constant);
	
	return result;
}
