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
	NSDictionary *_brailleDictionary;
}

- (instancetype _Nonnull)initWithAdaptiveType:(BOOL)adaptiveType
							adaptiveBlockSize:(NSInteger)adaptiveBlockSize
							 adaptiveConstant:(double)adaptiveConstant
							  dilateIteration:(NSInteger)dilateIteration
							   erodeIteration:(NSInteger)erodeIteration
						 minAreaContourFilter:(double)minAreaContourFilter
						 maxAreaContourFilter:(double)maxAreaContourFilter
							 redrawCircleSize:(double)redrawCircleSize
			maxSpaceForGroupingSameRowAndCols:(double)maxSpaceForGroupingSameRowAndCols
						  maxDotSpaceInterDot:(double)maxDotSpaceInterDot
					  defaultDotSpaceInterDot:(double)defaultDotSpaceInterDot
								 cropOffsideX:(NSInteger)cropOffsideX
								 cropOffsideY:(NSInteger)cropOffsideY {
	if ((self = [super init])) {
		_readDotProcessor = new ReadDotProcessor(adaptiveType, (int) adaptiveBlockSize, adaptiveConstant, (int) dilateIteration, (int) erodeIteration, minAreaContourFilter, maxAreaContourFilter, redrawCircleSize, maxSpaceForGroupingSameRowAndCols, maxDotSpaceInterDot, defaultDotSpaceInterDot, (int) cropOffsideX, (int) cropOffsideY);
		
		NSString *brailleCharFile = [[NSBundle mainBundle] pathForResource:@"RBImageProcessor.bundle/Braille-Char" ofType:@"plist"];
		_brailleDictionary = [NSDictionary dictionaryWithContentsOfFile:brailleCharFile];
	}
	
	return self;
}

- (void)setMinAreaContourFilter:(double)minAreaContourFilter {
	_readDotProcessor->minAreaContourFilter = minAreaContourFilter;
}

- (void)setMaxAreaContourFilter:(double)maxAreaContourFilter {
	_readDotProcessor->maxAreaContourFilter = maxAreaContourFilter;
}

- (void)setRedrawCircleSize:(double)redrawCircleSize {
	_readDotProcessor->redrawCircleSize = redrawCircleSize;
}

- (void)setMaxSpaceForGroupingSameRowAndCols:(double)maxSpaceForGroupingSameRowAndCols {
	_readDotProcessor->maxSpaceForGroupingSameRowAndCols = maxSpaceForGroupingSameRowAndCols;
}

- (void)setMaxDotSpaceInterDot:(double)maxDotSpaceInterDot {
	_readDotProcessor->maxDotSpaceInterDot = maxDotSpaceInterDot;
}

- (void)setDefaultDotSpaceInterDot:(double)defaultDotSpaceInterDot {
	_readDotProcessor->defaultDotSpaceInterDot = defaultDotSpaceInterDot;
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

- (NSString *_Nonnull)translateBrailleFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	NSString *result = @"";
	vector<vector<string>> decodedBraille = _readDotProcessor->decodeBraille(opencvImage);
	
	for (unsigned int i = 0; i < decodedBraille.size(); i++) {
		for (unsigned int j = 0; j < decodedBraille[i].size(); j++) {
			NSString *value = _brailleDictionary[@(decodedBraille[i][j].c_str())];
			if (value != NULL) {
				result = [result stringByAppendingString:value];
			} else {
				result = [result stringByAppendingString:@"#"];
			}
			int colSize = (int)decodedBraille[0].size();
			if (colSize <= 15) {
				result = [result stringByAppendingString:@"  "];
			} else if (colSize > 15 && colSize < 20) {
				result = [result stringByAppendingString:@" "];
			}
		}
		result = [result stringByAppendingString:@"\r\n"];
	}
	
	return result;
}

@end
