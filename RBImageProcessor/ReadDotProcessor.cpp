//
//  ReadDotProcessor.cpp
//  RBImageProcessor
//
//  Created by Ricki Bin Yamin on 07/12/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ReadDotProcessor.hpp"

// MARK: - Life Cycles

ReadDotProcessor::ReadDotProcessor(bool adaptiveType, int adaptiveBlockSize, double adaptiveConstant, int dilateIteration, int erodeIteration) {
	_adaptiveType = adaptiveType;
	_adaptiveBlockSize = adaptiveBlockSize;
	_adaptiveConstant = adaptiveConstant;
	_dilateIteration = dilateIteration;
	_erodeIteration = erodeIteration;
}

ReadDotProcessor::~ReadDotProcessor() {
	_adaptiveType = NULL;
	_adaptiveBlockSize = NULL;
	_adaptiveConstant = NULL;
	_dilateIteration = NULL;
	_erodeIteration = NULL;
}

Mat ReadDotProcessor::blobAnalysis(Mat image) {
	
	Mat gray, adaptiveImage, dilateImage, erodeImage, result;
	vector<vector<Point>> contours;
	
	// Image Pre processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> filteredContours;

	cout << "=== filtering contours" << endl;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
	}
	
	cout << "=== eliminating " << contours.size() - filteredContours.size() << " contours" << endl;
	
	cout << "=== findContours debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j=0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y)=" << filteredContours[i][j] << endl;
		}
		
		cout << " Area: " << contourArea(filteredContours[i]) << std::endl;
	}
	
	erodeImage = Scalar::all(0);
	drawContours(erodeImage, filteredContours, -1, Scalar::all(255));
	
	return erodeImage;
}
