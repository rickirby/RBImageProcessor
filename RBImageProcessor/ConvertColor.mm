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
	ConvertColorProcessor* _convertColorProcessor;
}

- (instancetype _Nonnull)initWithAdaptiveType:(BOOL)adaptiveType
							adaptiveBlockSize:(NSInteger)adaptiveBlockSize
							 adaptiveConstant:(double)adaptiveConstant
							  dilateIteration:(NSInteger)dilateIteration
							   erodeIteration:(NSInteger)erodeIteration
								 cropOffsideX:(NSInteger)cropOffsideX
								 cropOffsideY:(NSInteger)cropOffsideY {
	if ((self = [super init])) {
		_convertColorProcessor = new ConvertColorProcessor(adaptiveType, (int) adaptiveBlockSize, adaptiveConstant, (int) dilateIteration, (int) erodeIteration, (int) cropOffsideX, (int) cropOffsideY);
	}
	
	return self;
}

- (void)setAdaptiveType:(BOOL)adaptiveType {
	_convertColorProcessor->adaptiveType = adaptiveType;
}

- (void)setAdaptiveBlockSize:(NSInteger)adaptiveBlockSize {
	_convertColorProcessor->adaptiveBlockSize = (int) adaptiveBlockSize;
}

- (void)setAdaptiveConstant:(double)adaptiveConstant {
	_convertColorProcessor->adaptiveConstant = adaptiveConstant;
}

- (void)setDilateIteration:(NSInteger)dilateIteration {
	_convertColorProcessor->dilateIteration = (int) dilateIteration;
}

- (void)setErodeIteration:(NSInteger)erodeIteration {
	_convertColorProcessor->erodeIteration = (int) erodeIteration;
}

- (UIImage *)makeGrayFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_convertColorProcessor->convertToGRAY(opencvImage));
}

- (UIImage *)makeHSVFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_convertColorProcessor->convertToHSV(opencvImage));
}

- (UIImage *)makeBWFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_convertColorProcessor->convertToBW(opencvImage));
}

- (UIImage *)adaptiveThresholdFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_convertColorProcessor->adaptiveThreshold(opencvImage));
}

- (UIImage *)dilateFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_convertColorProcessor->dilate(opencvImage));
}

- (UIImage *)erodeFromImage:(UIImage *)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_convertColorProcessor->erode(opencvImage));
}

@end
