//
//  ReadDot.h
//  RBImageProcessor
//
//  Created by Ricki Bin Yamin on 08/12/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface ReadDot : NSObject

- (instancetype _Nonnull)initWithAdaptiveType:(BOOL)adaptiveType adaptiveBlockSize:(NSInteger)adaptiveBlockSize adaptiveConstant:(double)adaptiveConstant dilateIteration:(NSInteger)dilateIteration erodeIteration:(NSInteger)erodeIteration;

- (void)setMinAreaContourFilter:(double)minAreaContourFilter;
- (void)setMaxAreaContourFilter:(double)maxAreaContourFilter;
- (void)setRedrawCircleSize:(double)redrawCircleSize;
- (void)setMaxSpaceForGroupingSameRowAndCols:(double)maxSpaceForGroupingSameRowAndCols;
- (void)setMaxDotSpaceInterDot:(double)maxDotSpaceInterDot;
- (void)setDefaultDotSpaceInterDot:(double)defaultDotSpaceInterDot;

- (UIImage *_Nonnull)rawContoursFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)filteredContoursFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)redrawFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)lineCoordinateFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)segmentationFromImage:(UIImage *_Nonnull)image;

@end
