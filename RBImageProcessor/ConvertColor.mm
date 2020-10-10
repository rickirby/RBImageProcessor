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

+ (UIImage *)makeGrayFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::convertToGRAY(opencvImage));
}

+ (UIImage *)makeHSVFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::convertToHSV(opencvImage));
}

+ (UIImage *)makeBWFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::convertToBW(opencvImage));
}

+ (UIImage *)adaptiveThresholdFromImage:(UIImage *)image isGaussian:(BOOL)isGaussian blockSize:(NSInteger)blockSize constant:(double)constant {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::adaptiveThreshold(opencvImage, isGaussian, (int) blockSize, constant));
}

+ (UIImage *)dilateFromImage:(UIImage *)image iteration:(NSInteger)iteration isGaussian:(BOOL)isGaussian adaptiveBlockSize:(NSInteger)blockSize adaptiveConstant:(double)constant {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(ConvertColorProcessor::dilate(opencvImage, (int) iteration, isGaussian, (int) blockSize, constant));
}

@end
