//
//  ConvertColor.m
//  RBImageProcessor
//
//  Created by Ricki Private on 29/09/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>
#import <Foundation/Foundation.h>
#import "ConvertColor.h"

using namespace std;
using namespace cv;

@implementation ConvertColor

+ (UIImage *) imageBGRtoGRAY:(UIImage *)image {
    // convert UIImage to Mat
    cv::Mat openCVImage;
    UIImageToMat(image, openCVImage, true);
    
    // Run the c++ code
    cv::Mat resultImage = convertBGRtoGRAY(openCVImage);
    
    // convert Mat to UIImage and return
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoGRAYMagic:(UIImage *)image {
    // convert UIImage to Mat
    cv::Mat openCVImage;
    UIImageToMat(image, openCVImage, true);
    
    // Run the c++ code
    cv::Mat magicImage = convertBGRtoMagic(openCVImage);
    cv::Mat resultImage = convertBGRtoGRAY(magicImage);
    
    // convert Mat to UIImage and return
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoBlackAndWhite:(UIImage *)image {
    cv::Mat openCVImage;
    UIImageToMat(image, openCVImage);
    
    cv::Mat resultImage = convertBGRtoBlackAndWhite(openCVImage);
    
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoNeg:(UIImage *)image {
    // convert UIImage to Mat
    cv::Mat openCVImage;
    UIImageToMat(image, openCVImage);
    
    // Run the c++ code
    cv::Mat resultImage = convertBGRtoNeg(openCVImage);
    
    // convert Mat to UIImage and return
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoNegMagic:(UIImage *)image {
    // convert UIImage to Mat
    cv::Mat openCVImage;
    UIImageToMat(image, openCVImage);
    
    // Run the c++ code
    cv::Mat magicImage = convertBGRtoMagic(openCVImage);
    cv::Mat resultImage = convertBGRtoNeg(magicImage);
    
    // convert Mat to UIImage and return
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoHSV:(UIImage *)image {
    // convert UIImage to Mat
    cv:: Mat openCVImage;
    UIImageToMat(image, openCVImage);
    
    // Run the c++ code
    cv::Mat resultImage = convertBGRtoHSV(openCVImage);
    
    // convert Mat to UIImage and return
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoMagic:(UIImage *)image {
    // convert UIImage to Mat
    cv::Mat openCVImage;
    UIImageToMat(image, openCVImage);
    
    // Run the c++ code
    cv::Mat resultImage = convertBGRtoMagic(openCVImage);
    
    // convert Mat to UIImage and return
    return MatToUIImage(resultImage);
}

+ (UIImage *) imageBGRtoAdaptive:(UIImage *)image {
    cv:: Mat openCVImage;
    UIImageToMat(image, openCVImage);
    
    cv:: Mat resultImage = convertBGRtoAdaptive(openCVImage);
    
    return MatToUIImage(resultImage);
}

Mat convertBGRtoGRAY(Mat frame) {
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    
    return gray;
}

Mat convertBGRtoBlackAndWhite(Mat frame) {
    Mat gray = convertBGRtoGRAY(frame);
    Mat bw;
    threshold(gray, bw, 0, 255, THRESH_OTSU);
    
    return bw;
}

Mat convertBGRtoNeg(Mat frame) {
    Mat gray;
    Mat neg;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    neg.create(gray.rows, gray.cols, CV_8U);
    // then invert the value
    for (int j = 0; j < gray.rows; j++) {
        for (int i = 0; i < gray.cols; i++) {
            uchar intensity = gray.at<uchar>(j, i);
            neg.at<uchar>(j, i) = 255 - intensity;
        }
    }
    
    return neg;
}

Mat convertBGRtoHSV(Mat frame) {
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    return hsv;
}

Mat convertBGRtoMagic(Mat frame) {
    Mat resultImage = cv::Mat::zeros(frame.size(), frame.type());
    frame.convertTo(resultImage, -1, 1.9, -80);
    frame.release();

    return resultImage;
}

Mat convertBGRtoAdaptive(Mat frame) {
    Mat grayImage = convertBGRtoGRAY(frame);
    Mat resultImage = cv::Mat::zeros(grayImage.size(), grayImage.type());
    adaptiveThreshold(grayImage, resultImage, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 57, 10);
    
    return resultImage;
}

@end
