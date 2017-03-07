// CV_homeworks.cpp : Defines the entry point for the console application.
// This code is written by Engr. Sander Ali Khowaja Graduate Student,
// Information Systems Lab, HUFS, Korea (sandar.ali@usindh.edu.pk) (sunder.ali@hufs.ac.kr)

#include "stdafx.h"
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>
#include <opencv/highgui.h>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

//// properties, c/c++ C:\opencv\build\include
//// properties, linker general additional directories C:\opencv\build\x64\vc14\lib
//// properties, linker, input, additional dependencies, opencv_world320.lib (release) opencv_world320d.lib(debug)
//// copy opencv_world320.dll file from opencv folder to release exe file
//// copy opencv_world320d.dll file from opencv folder to debug exe file

//Global Variables
int main()
{
	//Defining the variables for images
	cv::Mat img;
	cv::Mat img1;
	cv::Mat img2;
	cv::Mat img3;
	//Defining the variables for average operation
	float sum1;
	float sum2; 
	float sum3;
	//Reading the image file
	img = cv::imread("C:/Users/PC/Desktop/Lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//Printing the statistics of the image
	cout << "The size of the image is :" << endl;
	cout << "Width :" << img.size().width << endl;
	cout << "Height :" << img.size().height << endl;
	cout << "Channels :" << img.channels() << endl;
	cout << "Image Type :" << img.type() << endl;
	cout << "Pixel Intensity values at (10,10) :" << img.at<Vec3b>(10, 10) << endl;

	//showing the original image
	cv::imshow("Original Image", img);
	//defining the 3 kernels i.e. 3x3, 4x4, 5x5
	float kernel1[3][3] = {
						{1 / 9.0, 1 / 9.0, 1 / 9.0},
						{1 / 9.0, 1 / 9.0, 1 / 9.0},
						{1 / 9.0, 1 / 9.0, 1 / 9.0}
						};
	float kernel2[5][5] = {
						{1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0},
						{1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0 },
						{ 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0 },
						{ 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0 },
						{ 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0, 1 / 25.0 },
						};
	float kernel3[4][4] = {
						{ 1 / 16.0, 1 / 16.0, 1 / 16.0, 1/16.0 },
						{ 1 / 16.0, 1 / 16.0, 1 / 16.0, 1/16.0 },
						{ 1 / 16.0, 1 / 16.0, 1 / 16.0, 1/16.0 }
						};
	//Creating the same image for applying mean filters on the noisy image
	img1 = img.clone();
	img2 = img.clone();
	img3 = img.clone();
	//Filtering image with varying kernels
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			img1.at<uchar>(y, x) = 0.0;
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
	img2.at<uchar>(y, x) = 0.0;
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			img3.at<uchar>(y, x) = 0.0;

	//convolution operation for filtering the image by varying the kernel size
	for (int y = 1; y < img.rows - 1; y++) {
		for (int x = 1; x < img.cols - 1; x++) {
			sum1 = 0.0;
			sum2 = 0.0;
			sum3 = 0.0;
			for (int k = -1; k <= 1; k++) {
				for (int j = -1; j <= 1; j++) {
					sum1 = sum1 + kernel1[j + 1][k + 1] * img.at<uchar>(y - j, x - k);
					sum2 = sum2 + kernel2[j + 1][k + 1] * img.at<uchar>(y - j, x - k);
					sum3 = sum3 + kernel3[j + 1][k + 1] * img.at<uchar>(y - j, x - k);
				}
			}
			//Enhancing the intensity levels of image
			//sum3 = sum3 * 2.2;
			//sum2 = sum2 * 3.5;
			//As the upper limit of the image in uint8 is 255, 
			//therefore limiting the intensity levels to 255
			//for filtered image2 and image3
					if (sum3 > 255) 
					sum3 = 255;
					if (sum2 > 255)
						sum2 = 255;
			
			img1.at<uchar>(y, x) = sum1;
			img2.at<uchar>(y, x) = sum2;
			img3.at<uchar>(y, x) = sum3;
		}
	}
	//Visualizing the images
	namedWindow("Filtered Image 3x3", CV_WINDOW_AUTOSIZE);
	imshow("Filtered Image 3x3", img1);

	namedWindow("Filtered Image 4x4", CV_WINDOW_AUTOSIZE);
	imshow("Filtered Image 4x4", img3);

	namedWindow("Filtered Image 5x5", CV_WINDOW_AUTOSIZE);
	imshow("Filtered Image 5x5", img2);

	cv::waitKey();
	return 0;

	//saving the images 
	imwrite("C:/Users/PC/Desktop/Lena3x3.jpg", img1);
	imwrite("C:/Users/PC/Desktop/Lena4x4.jpg", img3);
	imwrite("C:/Users/PC/Desktop/Lena5x5.jpg", img2);

}