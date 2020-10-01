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

- (instancetype _Nonnull)initWithImage:(UIImage *_Nonnull)image;
- (UIImage *_Nonnull)convertToGRAY;
- (UIImage *_Nonnull)convertToHSV;

@end
