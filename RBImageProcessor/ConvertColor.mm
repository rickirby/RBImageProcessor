//
//  ConvertColor.m
//  RBImageProcessor
//
//  Created by Ricki Private on 29/09/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>
#import <Foundation/Foundation.h>
#import "ConvertColor.h"
#import "ConvertColorProcessor.hpp"

using namespace std;
using namespace cv;

@implementation ConvertColor {
	ConvertColorProcessor *_convertColorProcessor;
}

- (instancetype)initWithImage:(UIImage*)image {
	if ((self = [super init])) {
		Mat opencvImage;
		UIImageToMat(image, opencvImage);
		_convertColorProcessor = new ConvertColorProcessor(opencvImage);
	}
	
	return self;
}

- (UIImage *)convertToGRAY {
	return MatToUIImage(_convertColorProcessor->convertToGRAY());
}

- (UIImage *)convertToHSV {
	return MatToUIImage(_convertColorProcessor->convertToHSV());
}

@end
