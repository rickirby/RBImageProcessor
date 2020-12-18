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

- (UIImage *_Nonnull)blobAnalysisFromImage:(UIImage *_Nonnull)image {
	Mat opencvImage;
	UIImageToMat(image, opencvImage);
	
	return MatToUIImage(_readDotProcessor->segmentation(opencvImage));
}

@end
