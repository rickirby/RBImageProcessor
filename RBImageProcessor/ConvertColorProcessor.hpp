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
	
	static Mat convertToGRAY(Mat image);
	static Mat convertToHSV(Mat image);

};

#endif /* ConvertColorProcessor_hpp */
