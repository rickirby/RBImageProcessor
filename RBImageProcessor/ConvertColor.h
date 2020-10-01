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

- (instancetype)initWithImage:(UIImage*)image;
- (UIImage*)convertToGRAY;
- (UIImage*)convertToHSV;

@end
