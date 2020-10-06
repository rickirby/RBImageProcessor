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
