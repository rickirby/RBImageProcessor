//
//  ConvertColor.h
//  RBImageProcessor
//
//  Created by Ricki Private on 29/09/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


@interface ConvertColor : NSObject

- (instancetype _Nonnull)initWithAdaptiveType:(BOOL)adaptiveType adaptiveBlockSize:(NSInteger)adaptiveBlockSize adaptiveConstant:(double)adaptiveConstant dilateIteration:(NSInteger)dilateIteration erodeIteration:(NSInteger)erodeIteration;

- (void)setAdaptiveType:(BOOL)adaptiveType;
- (void)setAdaptiveBlockSize:(NSInteger)adaptiveBlockSize;
- (void)setAdaptiveConstant:(double)adaptiveConstant;
- (void)setDilateIteration:(NSInteger)dilateIteration;
- (void)setErodeIteration:(NSInteger)erodeIteration;

- (UIImage *_Nonnull)makeGrayFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)makeHSVFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)makeBWFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)adaptiveThresholdFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)dilateFromImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)erodeFromImage:(UIImage *_Nonnull)image;

@end
