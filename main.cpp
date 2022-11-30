#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define LOCAL

void GetSignal(Mat img) {
    cvtColor(img, img, COLOR_BGR2GRAY);
    vector<vector<int>> contours;
    findContours(img, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    // color check
}

int main(int argc, char* argv[]) {
    String image_path;
#ifdef LOCAL
    image_path = "C:\\cv\\test.jpg";
#else
    image_path = argv[1];
#endif
    Mat img = imread(image_path, IMREAD_COLOR);
}
