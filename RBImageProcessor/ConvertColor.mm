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

@implementation ConvertColor

+ (UIImage *)convertToGRAYwithImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::convertToGRAY(opencvImage));
}

+ (UIImage *)convertToHSVwithImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::convertToHSV(opencvImage));
}

@end
