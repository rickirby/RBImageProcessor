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

+ (UIImage *_Nonnull)convertToGRAYwithImage:(UIImage *_Nonnull)image;
+ (UIImage *_Nonnull)convertToHSVwithImage:(UIImage *_Nonnull)image;

@end
