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

- (UIImage *_Nonnull)blobAnalysisFromImage:(UIImage *_Nonnull)image;

@end
