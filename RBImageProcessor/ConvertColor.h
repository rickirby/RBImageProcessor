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

+ (UIImage *_Nonnull)makeGrayFromImage:(UIImage *_Nonnull)image;
+ (UIImage *_Nonnull)makeHSVFromImage:(UIImage *_Nonnull)image;
+ (UIImage *_Nonnull)makeBWFromImage:(UIImage *_Nonnull)image;
+ (UIImage *_Nonnull)adaptiveThresholdFromImage:(UIImage *_Nonnull)image isGaussian:(BOOL)isGaussian blockSize:(NSInteger)blockSize constant:(double)constant;
+ (UIImage *_Nonnull)dilateFromImage:(UIImage *_Nonnull)image iteration:(NSInteger)iteration isGaussian:(BOOL)isGaussian adaptiveBlockSize:(NSInteger)blockSize adaptiveConstant:(double)constant;

@end
