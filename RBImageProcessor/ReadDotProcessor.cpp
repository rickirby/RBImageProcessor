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

Mat ReadDotProcessor::rawContours(Mat image) {
	Mat gray, adaptiveImage, dilateImage, erodeImage;
	
	// Image Pre Processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	vector<vector<Point>> contours;
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	// Drawing Contours
	
	Mat result = Mat::zeros(erodeImage.rows, erodeImage.cols, CV_8UC1);
	drawContours(result, contours, -1, Scalar::all(255));
	
	return result;
}

Mat ReadDotProcessor::filteredContours(Mat image) {
	Mat gray, adaptiveImage, dilateImage, erodeImage;

	// Image Pre Processing

	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);

	// Blob Analysis

	vector<vector<Point>> contours;

	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);

	// Filtering Contours

	vector<vector<Point>> filteredContours;

	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
	}
	
	// Drawing Contours
	
	Mat result = Mat::zeros(erodeImage.rows, erodeImage.cols, CV_8UC1);
	drawContours(result, filteredContours, -1, Scalar::all(255));
	
	return result;
}

Mat ReadDotProcessor::redraw(Mat image) {
	Mat gray, adaptiveImage, dilateImage, erodeImage;
	
	// Image Pre Processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	vector<vector<Point>> contours;
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	// Filtering Contours
	
	vector<vector<Point>> filteredContours;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
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
	
	// Drawing Circle on center point got
	
	Mat result = Mat::zeros(erodeImage.rows, erodeImage.cols, CV_8UC1);
	
	for (unsigned int i = 0; i < centerContoursPoint.size(); i++) {
		circle(result, centerContoursPoint[i], 10, Scalar::all(255), -1);
	}
	
	return result;
}

Mat ReadDotProcessor::lineCoordinate(Mat image) {
	Mat gray, adaptiveImage, dilateImage, erodeImage;
	
	// Image Pre Processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	vector<vector<Point>> contours;
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	// Filtering Contours
	
	vector<vector<Point>> filteredContours;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
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
	
	// Grouping centerContoursPoint with same row position and col position, to get the number and coordinate of row and col
	
	vector<Point> coordinatePoint = centerContoursPoint;
	vector<vector<int>> colsGroup;
	vector<vector<int>> rowsGroup;
	vector<int> colsGroupAvg;
	vector<int> rowsGroupAvg;
	
	for (unsigned int i = 0; i < coordinatePoint.size(); i++) {
		
		vector<int> gotCols;
		vector<int> gotRows;
		
		int avgX = 0;
		int avgY = 0;
		
		if (coordinatePoint[i].x != -1) {
			for (unsigned int j = i; j < coordinatePoint.size(); j++) {
				if (coordinatePoint[j].x != -1) {
					if (j == i) {
						gotCols.push_back(coordinatePoint[j].x);
						avgX = coordinatePoint[j].x;
						coordinatePoint[j].x = -1;
					} else {
						if (abs(avgX - coordinatePoint[j].x) < 20) {
							gotCols.push_back(coordinatePoint[j].x);
							avgX = (avgX + coordinatePoint[j].x)/2;
							coordinatePoint[j].x = -1;
						}
					}
				}
			}
			
			colsGroup.push_back(gotCols);
			colsGroupAvg.push_back(avgX);
		}
		
		if (coordinatePoint[i].y != -1) {
			for (unsigned int j = i; j < coordinatePoint.size(); j++) {
				if (coordinatePoint[j].y != -1) {
					if (j == i) {
						gotRows.push_back(coordinatePoint[j].y);
						avgY = coordinatePoint[j].y;
						coordinatePoint[j].y = -1;
					} else {
						if (abs(avgY - coordinatePoint[j].y) < 20) {
							gotRows.push_back(coordinatePoint[j].y);
							avgY = (avgY + coordinatePoint[j].y)/2;
							coordinatePoint[j].y = -1;
						}
					}
				}
			}
			
			rowsGroup.push_back(gotRows);
			rowsGroupAvg.push_back(avgY);
		}
		
	}
	
	// Sorting colsGroupAvg and rowsGroupAvg
	
	sort(colsGroupAvg.begin(), colsGroupAvg.end());
	sort(rowsGroupAvg.begin(), rowsGroupAvg.end());
	
	// Drawing circle and lines
	
	Mat result = Mat::zeros(erodeImage.rows, erodeImage.cols, CV_8UC1);
	
	for (unsigned int i = 0; i < centerContoursPoint.size(); i++) {
		circle(result, centerContoursPoint[i], 10, Scalar::all(255), -1);
	}
	
	for (unsigned int i = 0; i < colsGroupAvg.size(); i++) {
		
		Point2i startPointCol(colsGroupAvg[i], 0);
		Point2i endPointCol(colsGroupAvg[i], erodeImage.rows);
		
		line(result, startPointCol, endPointCol, Scalar::all(128));
	}
	
	for (unsigned int i = 0; i < rowsGroupAvg.size(); i++) {
		
		Point2i startPointRow(0, rowsGroupAvg[i]);
		Point2i endPointRow(erodeImage.cols, rowsGroupAvg[i]);
		
		line(result, startPointRow, endPointRow, Scalar::all(128));
	}
	
	return result;
}

Mat ReadDotProcessor::segmentation(Mat image) {
	Mat gray, adaptiveImage, dilateImage, erodeImage;
	
	// Image Pre Processing
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, adaptiveImage, 255, _adaptiveType ? ADAPTIVE_THRESH_GAUSSIAN_C : ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, _adaptiveBlockSize, _adaptiveConstant);
	dilate(adaptiveImage, dilateImage, Mat(), Point(-1, -1), _dilateIteration);
	erode(dilateImage, erodeImage, Mat(), Point(-1, -1), _erodeIteration);
	
	// Blob Analysis
	
	vector<vector<Point>> contours;
	
	findContours(erodeImage, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	
	// Filtering Contours
	cout << "===*** Filtering contours by area" << endl;
	
	vector<vector<Point>> filteredContours;
	
	for (int i = 0; i < contours.size(); i++) {
		double currentArea = contourArea(contours[i]);
		if ((currentArea > 200.0) && (currentArea < 500.0)) {
			filteredContours.push_back(contours[i]);
		}
	}
	
	cout << "===*** Eliminating " << contours.size() - filteredContours.size() << " contours" << endl;
	
	cout << "===*** Find Contours debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j = 0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y) =" << filteredContours[i][j] << endl;
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
	
	cout << "===*** Center Point debugging" << endl;
	
	for (unsigned int i = 0;  i < filteredContours.size();  i++) {
		cout << "# Index: " << i << ", points count: " << filteredContours[i].size() << endl;
		for (unsigned int j = 0;  j < filteredContours[i].size();  j++) {
			cout << "Point(x,y) =" << filteredContours[i][j] << endl;
		}
		
		cout << " Center: " << centerContoursPoint[i] << endl;
		cout << " Area: " << contourArea(filteredContours[i]) << endl;
	}
	
	// Grouping centerContoursPoint with same row position and col position, to get the number and coordinate of row and col
	
	vector<Point> coordinatePoint = centerContoursPoint;
	vector<vector<int>> colsGroup;
	vector<vector<int>> rowsGroup;
	vector<int> colsGroupAvg;
	vector<int> rowsGroupAvg;
	
	for (unsigned int i = 0; i < coordinatePoint.size(); i++) {
		
		vector<int> gotCols;
		vector<int> gotRows;
		
		int avgX = 0;
		int avgY = 0;
		
		if (coordinatePoint[i].x != -1) {
			for (unsigned int j = i; j < coordinatePoint.size(); j++) {
				if (coordinatePoint[j].x != -1) {
					if (j == i) {
						gotCols.push_back(coordinatePoint[j].x);
						avgX = coordinatePoint[j].x;
						coordinatePoint[j].x = -1;
					} else {
						if (abs(avgX - coordinatePoint[j].x) < 20) {
							gotCols.push_back(coordinatePoint[j].x);
							avgX = (avgX + coordinatePoint[j].x)/2;
							coordinatePoint[j].x = -1;
						}
					}
				}
			}
			
			colsGroup.push_back(gotCols);
			colsGroupAvg.push_back(avgX);
		}
		
		if (coordinatePoint[i].y != -1) {
			for (unsigned int j = i; j < coordinatePoint.size(); j++) {
				if (coordinatePoint[j].y != -1) {
					if (j == i) {
						gotRows.push_back(coordinatePoint[j].y);
						avgY = coordinatePoint[j].y;
						coordinatePoint[j].y = -1;
					} else {
						if (abs(avgY - coordinatePoint[j].y) < 20) {
							gotRows.push_back(coordinatePoint[j].y);
							avgY = (avgY + coordinatePoint[j].y)/2;
							coordinatePoint[j].y = -1;
						}
					}
				}
			}
			
			rowsGroup.push_back(gotRows);
			rowsGroupAvg.push_back(avgY);
		}
		
	}
	
	// Sorting colsGroupAvg and rowsGroupAvg
	
	sort(colsGroupAvg.begin(), colsGroupAvg.end());
	sort(rowsGroupAvg.begin(), rowsGroupAvg.end());
	
	cout << "===*** colsGroup and rowsGroup debugging" << endl;
	
	for (unsigned int i = 0; i < coordinatePoint.size(); i++) {
		cout << "coordinatePoint index " << i << " = " << coordinatePoint[i] << endl;
	}
	
	for (unsigned int i = 0; i < colsGroup.size(); i++) {
		for (unsigned j = 0; j < colsGroup[i].size(); j++) {
			cout << "colsGroup index " << i << "," << j << " = " << colsGroup[i][j] << endl;
		}
	}
	
	for (unsigned int i = 0; i < rowsGroup.size(); i++) {
		for (unsigned j = 0; j < rowsGroup[i].size(); j++) {
			cout << "rowsGroup index " << i << "," << j << " = " << rowsGroup[i][j] << endl;
		}
	}
	
	cout << "===*** colsGroupAvg and rowsGroupAvg debugging" << endl;
	
	for (unsigned int i = 0; i < colsGroupAvg.size(); i++) {
		cout << "colsGroupAvg index: " << i << " = " << colsGroupAvg[i] << endl;
	}
	
	for (unsigned int i = 0; i < rowsGroupAvg.size(); i++) {
		cout << "rowsGroupAvg index: " << i << " = " << rowsGroupAvg[i] << endl;
	}
	
	cout << "===*** colsGroupSize = " << colsGroup.size() << endl;
	cout << "===*** rowsGroupSize = " << rowsGroup.size() << endl;
	
	// Getting coloumn pairs (2) and row pairs (3)
	
	vector<vector<int>> colsPairs;
	vector<vector<int>> rowsPairs;
	
	bool shouldSkip = false;
	int shouldSkipCount = 0;
	
	for (unsigned int i = 0; i < colsGroupAvg.size(); i++) {
		vector<int> colPair;
		
		if (!shouldSkip) {
			if ((abs(colsGroupAvg[i] - colsGroupAvg[i + 1]) < 40) && (i < colsGroupAvg.size() - 1)) {
				colPair.push_back(colsGroupAvg[i]);
				colPair.push_back(colsGroupAvg[i + 1]);
				
				shouldSkip = true;
				colsPairs.push_back(colPair);
			} else {
				if (i == 0) {
					// case for single coordinate found on very first document
					colPair.push_back(colsGroupAvg[i] - 30);
					colPair.push_back(colsGroupAvg[i]);
					
					shouldSkip = true;
					colsPairs.push_back(colPair);
				} else if (i == colsGroupAvg.size() - 1) {
					// case for single coordinate found on very end of document
					colPair.push_back(colsGroupAvg[i]);
					colPair.push_back(colsGroupAvg[i] + 30);
					
					colsPairs.push_back(colPair);
				} else {
					// case for single line found beetween the other pairs
					cout << "not found " << i << endl;
				}
			}
		} else {
			shouldSkip = false;
		}
	}
	
	shouldSkip = false;
	
	for (unsigned int i = 0; i < rowsGroupAvg.size(); i++) {
		vector<int> rowPair;
		
		if (shouldSkipCount == 0) {
			if ((abs(rowsGroupAvg[i] - rowsGroupAvg[i + 1]) < 40) && (i < rowsGroupAvg.size() - 2)) {
				rowPair.push_back(rowsGroupAvg[i]);
				rowPair.push_back(rowsGroupAvg[i + 1]);
				rowPair.push_back(rowsGroupAvg[i + 2]);
				
				shouldSkipCount++;
				rowsPairs.push_back(rowPair);
			} else {
				if (i == 0) {
					// case for single coordinate found on very first document
					rowPair.push_back(rowsGroupAvg[i] - 60);
					rowPair.push_back(rowsGroupAvg[i] - 30);
					rowPair.push_back(rowsGroupAvg[i]);
					
					shouldSkipCount++;
					rowsPairs.push_back(rowPair);
				} else if (i == rowsGroupAvg.size() - 1) {
					// case for single coordinate found on very end of document
					rowPair.push_back(rowsGroupAvg[i]);
					rowPair.push_back(rowsGroupAvg[i] + 30);
					rowPair.push_back(rowsGroupAvg[i] + 60);
					
					rowsPairs.push_back(rowPair);
				} else {
					// case for single line found beetween the other pairs
					cout << "not found " << i << endl;
				}
			}
		} else {
			if (shouldSkipCount > 1) {
				shouldSkipCount = 0;
			} else {
				shouldSkipCount++;
			}
		}
	}
	
	cout << "===*** colsPairs and rowsPairs debugging" << endl;
	
	for (unsigned int i = 0; i < colsPairs.size(); i++) {
		cout << "colsPairs " << i << " = ";
		for (unsigned int j = 0; j < colsPairs[i].size(); j++) {
			cout << colsPairs[i][j] << " ";
		}
		cout << endl;
	}
	
	for (unsigned int i = 0; i < rowsPairs.size(); i++) {
		cout << "rowsPairs " << i << " = ";
		for (unsigned int j = 0; j < rowsPairs[i].size(); j++) {
			cout << rowsPairs[i][j] << " ";
		}
		cout << endl;
	}
	
	// Drawing circle, lines, and rectangle
	
	Mat result = Mat::zeros(erodeImage.rows, erodeImage.cols, CV_8UC1);
	
	for (unsigned int i = 0; i < centerContoursPoint.size(); i++) {
		circle(result, centerContoursPoint[i], 10, Scalar::all(255), -1);
	}
	
	for (unsigned int i = 0; i < colsGroupAvg.size(); i++) {
		
		Point2i startPointCol(colsGroupAvg[i], 0);
		Point2i endPointCol(colsGroupAvg[i], erodeImage.rows);
		
		line(result, startPointCol, endPointCol, Scalar::all(128));
	}
	
	for (unsigned int i = 0; i < rowsGroupAvg.size(); i++) {
		
		Point2i startPointRow(0, rowsGroupAvg[i]);
		Point2i endPointRow(erodeImage.cols, rowsGroupAvg[i]);
		
		line(result, startPointRow, endPointRow, Scalar::all(128));
	}
	
	for (unsigned int i = 0; i < colsPairs.size(); i++) {
		for (unsigned int j = 0; j < rowsPairs.size(); j++) {
			Point2i startPoint(colsPairs[i][0] - 15, rowsPairs[j][0] - 15);
			Point2i endPoint(colsPairs[i][1] + 15, rowsPairs[j][2] + 15);
			
			rectangle(result, startPoint, endPoint, Scalar(255,0,0), 1, 8, 0);
		}
	}
	
	return result;
}
