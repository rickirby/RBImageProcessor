//
//  ReadDotProcessor.hpp
//  RBImageProcessor
//
//  Created by Ricki Bin Yamin on 07/12/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#ifndef ReadDotProcessor_hpp
#define ReadDotProcessor_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class ReadDotProcessor {
public:
	
	// MARK: - Life Cycles
	
	ReadDotProcessor(bool adaptiveType, int adaptiveBlockSize, double adaptiveConstant, int dilateIteration, int erodeIteration);
	~ReadDotProcessor();
	
	// MARK: - Public Methods
	
	void blobAnalysis();
	
private:
	
	// MARK: - Private Properties
	bool _adaptiveType;
	int _adaptiveBlockSize;
	double _adaptiveConstant;
	int _dilateIteration;
	int _erodeIteration;
	
};

#endif /* ReadDotProcessor_hpp */
