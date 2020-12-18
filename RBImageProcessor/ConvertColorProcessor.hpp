//
//  ConvertColorProcessor.hpp
//  RBImageProcessor
//
//  Created by Ricki Private on 01/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef ConvertColorProcessor_hpp
#define ConvertColorProcessor_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class ConvertColorProcessor {
public:
	
	// MARK: - Life Cycles
	
	ConvertColorProcessor(bool adaptiveType_, int adaptiveBlockSize_, double adaptiveConstant_, int dilateIteration_, int erodeIteration_);
	~ConvertColorProcessor();
	
	// MARK: - Public Properties

	bool adaptiveType;
	int adaptiveBlockSize;
	double adaptiveConstant;
	int dilateIteration;
	int erodeIteration;
	
	// MARK: - Public Methods
	
	Mat convertToGRAY(Mat image);
	Mat convertToHSV(Mat image);
	Mat convertToBW(Mat image);
	Mat adaptiveThreshold(Mat image);
	Mat dilate(Mat image);
	Mat erode(Mat image);

};

#endif /* ConvertColorProcessor_hpp */
