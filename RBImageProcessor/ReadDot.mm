//
//  ReadDot.m
//  RBImageProcessor
//
//  Created by Ricki Bin Yamin on 08/12/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>
#import <Foundation/Foundation.h>
#import "ReadDot.h"
#import "ReadDotProcessor.hpp"

using namespace std;
using namespace cv;

@implementation ReadDot {
	ReadDotProcessor* _readDotProcessor;
}

- (instancetype _Nonnull)initWithAdaptiveType:(BOOL)adaptiveType adaptiveBlockSize:(NSInteger)adaptiveBlockSize adaptiveConstant:(double)adaptiveConstant dilateIteration:(NSInteger)dilateIteration erodeIteration:(NSInteger)erodeIteration {
	if ((self = [super init])) {
		_readDotProcessor = new ReadDotProcessor(adaptiveType, (int) adaptiveBlockSize, adaptiveConstant, (int) dilateIteration, (int) erodeIteration);
	}
	
	return self;
}

- (void)setMinAreaContourFilter:(double)minAreaContourFilter {
	_readDotProcessor->minAreaContourFilter = minAreaContourFilter;
}

- (void)setMaxAreaContourFilter:(double)maxAreaContourFilter {
	_readDotProcessor->maxAreaContourFilter = maxAreaContourFilter;
}

- (void)setMaxSpaceForGroupingSameRowAndCols:(double)maxSpaceForGroupingSameRowAndCols {
	_readDotProcessor->maxSpaceForGroupingSameRowAndCols = maxSpaceForGroupingSameRowAndCols;
}

- (void)setMaxDotSpaceInterDot:(double)maxDotSpaceInterDot {
	_readDotProcessor->maxDotSpaceInterDot = maxDotSpaceInterDot;
}

- (void)setDefaultDotSpaceInterDot:(double)defaultDotSpaceInterDot {
	
}

- (UIImage *_Nonnull)rawContoursFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_readDotProcessor->rawContours(opencvImage));
}

- (UIImage *_Nonnull)filteredContoursFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_readDotProcessor->filteredContours(opencvImage));
}

- (UIImage *_Nonnull)redrawFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_readDotProcessor->redraw(opencvImage));
}

- (UIImage *_Nonnull)lineCoordinateFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_readDotProcessor->lineCoordinate(opencvImage));
}

- (UIImage *_Nonnull)segmentationFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_readDotProcessor->segmentation(opencvImage));
}

@end
