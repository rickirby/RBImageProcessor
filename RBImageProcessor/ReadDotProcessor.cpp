//
//  ReadDotProcessor.cpp
//  RBImageProcessor
//
//  Created by Ricki Bin Yamin on 07/12/20.
//  Copyright © 2020 Ricki Bin Yamin. All rights reserved.
//

#include "ReadDotProcessor.hpp"

// MARK: - Life Cycles

ReadDotProcessor::ReadDotProcessor(bool adaptiveType, int adaptiveBlockSize, double adaptiveConstant, int dilateIteration, int erodeIteration) {
	_adaptiveType = adaptiveType;
	_adaptiveBlockSize = adaptiveBlockSize;
	_adaptiveConstant = adaptiveConstant;
	_dilateIteration = dilateIteration;
	_erodeIteration = erodeIteration;
}

ReadDotProcessor::~ReadDotProcessor() {
	_adaptiveType = NULL;
	_adaptiveBlockSize = NULL;
	_adaptiveConstant = NULL;
	_dilateIteration = NULL;
	_erodeIteration = NULL;
}

Mat ReadDotProcessor::blobAnalysis(Mat image) {
	
	Mat gray, adaptiveImage, dilateImage, erodeImage, result;
	vector<vector<Point>> contours;
	
	// Image Pre processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> filteredContours;

	cout << "=== filtering contours" << endl;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
	}
	
	cout << "=== eliminating " << contours.size() - filteredContours.size() << " contours" << endl;
	
	cout << "=== findContours debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j=0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y)=" << filteredContours[i][j] << endl;
		}
		
		cout << " Area: " << contourArea(filteredContours[i]) << std::endl;
	}
	
	erodeImage = Scalar::all(0);
	drawContours(erodeImage, filteredContours, -1, Scalar::all(255));
	
	return erodeImage;
}

Mat ReadDotProcessor::dotCircle(Mat image) {
	
	Mat gray, adaptiveImage, dilateImage, erodeImage, result;
	vector<vector<Point>> contours;
	
	// Image Pre processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> filteredContours;
	
	cout << "=== filtering contours" << endl;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
	}
	
	cout << "=== eliminating " << contours.size() - filteredContours.size() << " contours" << endl;
	
	cout << "=== findContours debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j = 0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y)=" << filteredContours[i][j] << endl;
		}
		
		cout << " Area: " << contourArea(filteredContours[i]) << endl;
	}
	
	// Finding min max coordinate per dot and average them to get center point
	
	vector<Point> centerContoursPoint;
	
	for (unsigned int i = 0; i < filteredContours.size(); i++) {
		
		int minX = filteredContours[i][0].x, minY = filteredContours[i][0].y, maxX = filteredContours[i][0].x, maxY = filteredContours[i][0].y;
		
		for (unsigned int j = 0; j < filteredContours[i].size(); j++) {
			
			int currentX = filteredContours[i][j].x;
			int currentY = filteredContours[i][j].y;
			
			minX = min(minX, currentX);
			minY = min(minY, currentY);
			maxX = max(maxX, currentX);
			maxY = max(maxY, currentY);
		}
		
		int centerX = (minX + maxX) / 2;
		int centerY = (minY + maxY) / 2;
		
		Point2i centerPoint(centerX, centerY);
		centerContoursPoint.push_back(centerPoint);
	}
	
	cout << "=== centerPoint debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j = 0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y)=" << filteredContours[i][j] << endl;
		}
		
		cout << " Center: " << centerContoursPoint[i] << endl;
		cout << " Area: " << contourArea(filteredContours[i]) << endl;
	}
	
	erodeImage = Scalar::all(0);
	
	for (unsigned int i = 0; i < centerContoursPoint.size(); i++) {
		circle(erodeImage, centerContoursPoint[i], 10, Scalar::all(255), -1);
	}
	
	return erodeImage;
}

Mat ReadDotProcessor::lineCoordinate(Mat image) {
	
	Mat gray, adaptiveImage, dilateImage, erodeImage, result;
	vector<vector<Point>> contours;
	
	// Image Pre processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	vector<vector<Point>> filteredContours;
	
	cout << "=== filtering contours" << endl;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
	}
	
	cout << "=== eliminating " << contours.size() - filteredContours.size() << " contours" << endl;
	
	cout << "=== findContours debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j = 0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y)=" << filteredContours[i][j] << endl;
		}
		
		cout << " Area: " << contourArea(filteredContours[i]) << endl;
	}
	
	// Finding min max coordinate per dot and average them to get center point
	
	vector<Point> centerContoursPoint;
	
	for (unsigned int i = 0; i < filteredContours.size(); i++) {
		
		int minX = filteredContours[i][0].x, minY = filteredContours[i][0].y, maxX = filteredContours[i][0].x, maxY = filteredContours[i][0].y;
		
		for (unsigned int j = 0; j < filteredContours[i].size(); j++) {
			
			int currentX = filteredContours[i][j].x;
			int currentY = filteredContours[i][j].y;
			
			minX = min(minX, currentX);
			minY = min(minY, currentY);
			maxX = max(maxX, currentX);
			maxY = max(maxY, currentY);
		}
		
		int centerX = (minX + maxX) / 2;
		int centerY = (minY + maxY) / 2;
		
		Point2i centerPoint(centerX, centerY);
		centerContoursPoint.push_back(centerPoint);
	}
	
	cout << "=== centerPoint debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j = 0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y)=" << filteredContours[i][j] << endl;
		}
		
		cout << " Center: " << centerContoursPoint[i] << endl;
		cout << " Area: " << contourArea(filteredContours[i]) << endl;
	}
	
	vector<Point> coordinatePoint = centerContoursPoint;
	vector<vector<int>> colsGroup;
	vector<vector<int>> rowsGroup;
	
	for (unsigned int i = 0; i < coordinatePoint.size(); i++) {
		
		vector<int> gotCols;
		vector<int> gotRows;
		
		if (coordinatePoint[i].x != -1) {
			for (unsigned int j = i; j < coordinatePoint.size(); j++) {
				cout << i << "," << j << "=" << coordinatePoint[j] << endl;
				if (coordinatePoint[j].x != -1) {
					if (j == i) {
						cout << "asign new value " << coordinatePoint[j] << endl;
						gotCols.push_back(coordinatePoint[j].x);
						coordinatePoint[j].x = -1;
					} else {
						cout << "comparing value " << endl;
						if (abs(gotCols[0] - coordinatePoint[j].x) < 20) {
							gotCols.push_back(coordinatePoint[j].x);
							coordinatePoint[j].x = -1;
						}
					}
				}
			}
			
			colsGroup.push_back(gotCols);
		}
		
		if (coordinatePoint[i].y != -1) {
			for (unsigned int j = i; j < coordinatePoint.size(); j++) {
				cout << i << "," << j << "=" << coordinatePoint[j] << endl;
				if (coordinatePoint[j].y != -1) {
					if (j == i) {
						cout << "asign new value " << coordinatePoint[j] << endl;
						gotRows.push_back(coordinatePoint[j].y);
						coordinatePoint[j].y = -1;
					} else {
						cout << "comparing value " << endl;
						// TODO: try to compare with average value that has got, not first item, also on cols
						if (abs(gotRows[0] - coordinatePoint[j].y) < 20) {
							gotRows.push_back(coordinatePoint[j].y);
							coordinatePoint[j].y = -1;
						}
					}
				}
			}
			
			rowsGroup.push_back(gotRows);
		}
		
	}
	
	cout << "=== colsGroup and rowsGroup debugging" << endl;
	
	for (unsigned int i = 0; i < coordinatePoint.size(); i++) {
		cout << "coordinatePoint index " << i << " = " << coordinatePoint[i] << endl;
	}
	
	cout << "=== colsGroupSize = " << colsGroup.size() << endl;
	cout << "=== rowsGroupSize = " << rowsGroup.size() << endl;
	
	// Getting average value of every coloumns and rows
	
	vector<int> colsGroupAverage;
	vector<int> rowsGroupAverage;
	
	for (unsigned int i = 0; i < colsGroup.size(); i++) {
		int sum = 0;
		for (unsigned int j = 0; j < colsGroup.size(); j++) {
			sum += colsGroup[i][j];
		}
		
		colsGroupAverage.push_back(sum / colsGroup.size());
	}
	
	for (unsigned int i = 0; i < rowsGroup.size(); i++) {
		int sum = 0;
		for (unsigned int j = 0; j < rowsGroup.size(); j++) {
			sum += rowsGroup[i][j];
		}
		
		rowsGroupAverage.push_back(sum / colsGroup.size());
	}
	
	erodeImage = Scalar::all(0);
	
	for (unsigned int i = 0; i < centerContoursPoint.size(); i++) {
		circle(erodeImage, centerContoursPoint[i], 10, Scalar::all(255), -1);
	}
	
	// Drawing line
	
	for (unsigned int i = 0; i < colsGroupAverage.size(); i++) {

		Point2i startPointCol(colsGroupAverage[i], 0);
		Point2i endPointCol(colsGroupAverage[i], erodeImage.rows);
		
		line(erodeImage, startPointCol, endPointCol, Scalar::all(128));
	}
	
	for (unsigned int i = 0; i < rowsGroupAverage.size(); i++) {
		
		Point2i startPointRow(0, rowsGroupAverage[i]);
		Point2i endPointRow(erodeImage.cols, rowsGroupAverage[i]);
		
		line(erodeImage, startPointRow, endPointRow, Scalar::all(128));
	}
	
	return erodeImage;
}
