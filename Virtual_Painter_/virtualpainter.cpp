#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/objdetect.hpp>


using namespace cv;
using namespace std;

Mat camvid;
vector<vector<int>> newPoints;

vector<vector<int>> colorseen{ {0,92,114,179,255,255} };// Color it detects (brown)
vector<Scalar> coloroutput{ {182,106,80} }; // Color it produces (Blue)

float area;

Point cofunction(Mat dilatepic) {
	
	vector<vector<Point>> colet;
	vector<Vec4i> neon;

	findContours(dilatepic, colet, neon, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	Point centre(0, 0); // Pre-defining  the Centre

	for (int i = 0; i < colet.size(); i++) {

		vector<vector<Point>> arr(colet.size());
		vector<Rect> faces(colet.size());

		area = contourArea(colet[i]);
		float perimeter = arcLength(colet[i], true);

		approxPolyDP(colet[i], arr[i], 0.02 * perimeter, true); // In this if we change the value with perimeter then the no. of arc length will increase 
		cout << area << endl;
		faces[i] = boundingRect(arr[i]);
		
		centre.x = faces[i].x + faces[i].width / 2;
		centre.y = faces[i].y;
		
		circle(camvid, { centre.x,centre.y }, sqrt(area / 3.14), Scalar(0, 0, 255), FILLED);
	}
	return centre;
}


Mat outpic;

//  color() Used to Display color on the screen

vector<vector<int>> color(Mat pic) {

	cvtColor(pic, outpic, COLOR_BGR2HSV);
	for (int i = 0; i < colorseen.size(); i++) {
		Mat mask;

		Scalar min(colorseen[i][0], colorseen[i][1], colorseen[i][2]);
		Scalar max(colorseen[i][3], colorseen[i][4], colorseen[i][5]);
		
		inRange(outpic, min, max, mask);
		Point centre = cofunction(mask);
		newPoints.push_back({ centre.x,centre.y,i });
	}
	return newPoints;
}

// draw() Used to draw Circle for the identified object (sky blue)

void draw(vector<vector<int>> newPoints, vector<Scalar> coloroutput) {

	for (int i = 0; i < newPoints.size(); i++) {
		circle(camvid, Point(newPoints[i][0], newPoints[i][1]), 12, coloroutput[0], FILLED);
	}

}

void main() {

	VideoCapture cam(0);

	while (1) {

		cam.read(camvid); // Used for reading
		newPoints = color(camvid);
		draw(newPoints, coloroutput);


		imshow("Video", camvid); // Used to display
		waitKey(1);
	}
}