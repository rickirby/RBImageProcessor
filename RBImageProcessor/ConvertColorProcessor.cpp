//
//  ConvertColorProcessor.cpp
//  RBImageProcessor
//
//  Created by Ricki Private on 01/10/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ConvertColorProcessor.hpp"

ConvertColorProcessor::ConvertColorProcessor(Mat image) {
	_image = image;
}

ConvertColorProcessor::~ConvertColorProcessor() {
	
}

Mat ConvertColorProcessor::convertToGRAY() {
	Mat gray;
    cvtColor(_image, gray, COLOR_BGR2GRAY);
    
    return gray;
}

Mat ConvertColorProcessor::convertToHSV() {
	Mat hsv;
    cvtColor(_image, hsv, COLOR_BGR2HSV);
	
    return hsv;
}
