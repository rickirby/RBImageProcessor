//
//  ReadDotProcessor.hpp
//  RBImageProcessor
//
//  Created by Ricki Bin Yamin on 07/12/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef ReadDotProcessor_hpp
#define ReadDotProcessor_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ReadDotProcessor {
public:
	
	// MARK: - Life Cycles
	
	ReadDotProcessor(bool adaptiveType, int adaptiveBlockSize, double adaptiveConstant, int dilateIteration, int erodeIteration, double minAreaContourFilter_, double maxAreaContourFilter_, double redrawCircleSize_, double maxSpaceForGroupingSameRowAndCols_, double maxDotSpaceInterDot_, double defaultDotSpaceInterDot_, int cropOffsideX_, int cropOffsideY_);
	~ReadDotProcessor();
	
	// MARK: - Public Properties
	
	double minAreaContourFilter;
	double maxAreaContourFilter;
	double redrawCircleSize;
	double maxSpaceForGroupingSameRowAndCols;
	double maxDotSpaceInterDot;
	double defaultDotSpaceInterDot;
	int cropOffsideX;
	int cropOffsideY;
	
	// MARK: - Public Methods
	
	Mat rawContours(Mat image);
	Mat filteredContours(Mat image);
	Mat redraw(Mat image);
	Mat lineCoordinate(Mat image);
	Mat segmentation(Mat image);
	vector<vector<string>> decodeBraille(Mat image);
	
private:
	
	// MARK: - Private Properties
	bool _adaptiveType;
	int _adaptiveBlockSize;
	double _adaptiveConstant;
	int _dilateIteration;
	int _erodeIteration;
	
	// MARK: - Private Methods
	double _proportionalValue(int imageWidth, double value);
	
};

#endif /* ReadDotProcessor_hpp */
