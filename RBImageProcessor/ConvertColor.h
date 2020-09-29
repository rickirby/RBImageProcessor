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

+ (UIImage *) imageBGRtoGRAY: (UIImage *) image;
+ (UIImage *) imageBGRtoGRAYMagic: (UIImage *) image;
+ (UIImage *) imageBGRtoBlackAndWhite: (UIImage *) image;
+ (UIImage *) imageBGRtoNeg: (UIImage *) image;
+ (UIImage *) imageBGRtoNegMagic: (UIImage *) image;
+ (UIImage *) imageBGRtoHSV: (UIImage *) image;
+ (UIImage *) imageBGRtoMagic: (UIImage *) image;
+ (UIImage *) imageBGRtoAdaptive: (UIImage *) image;

@end
