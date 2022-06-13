#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {

	Mat outpic, mask;
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;

	VideoCapture cam(0);
	Mat pic;


	namedWindow("Setting", (800, 450));
	createTrackbar("Hmin", "Setting", &hmin, 179); // Hue Minimum
	createTrackbar("Hmax", "Setting", &hmax, 179); // Hue Maximum
	createTrackbar("Smin", "Setting", &smin, 255); // Saturation Minimum
	createTrackbar("Smax", "Setting", &smax, 255); // Saturation Maximum
	createTrackbar("Vmin", "Setting", &vmin, 255); // Vignette Minimum
	createTrackbar("Vmax", "Setting", &vmax, 255); // Vignette Maximum
	while (1) {

		while (true) {
			cam.read(pic);
			cvtColor(pic, outpic, COLOR_BGR2HSV);
			Scalar min(hmin, smin, vmin);
			Scalar max(hmax, smax, vmax);

			inRange(outpic, min, max, mask);
			
			imshow("IMAGE", pic);
			imshow("IMAGE_MASK", mask);
			waitKey(1);
		}
	}
}