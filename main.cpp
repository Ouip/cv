#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#define LOCAL

#define RedL Scalar(0, 100, 46)
#define RedH Scalar(10, 255, 255)
#define BlueL Scalar(100, 43, 46)
#define BlueH Scalar(124, 255, 255)
#define YellowL Scalar(26, 43, 46)
#define YellowH Scalar(34, 255, 255)

class Signal {
   public:
    Mat Image;
    Signal(string image_path) {
        _img = imread(image_path);
        Image = _img.clone();
    }

   public:
    void GetSignal() {
        // Three Color Mask
        ColorMask(_img);
        // Get boundRect Point
        Printer(DrawBound());
    }

    void ColorMask(Mat& img) {
        GaussianBlur(img, img, Size(9, 9), 2, 2);
        cvtColor(img, img, COLOR_BGR2HSV);

        Mat temp[2];
        inRange(img, Scalar(156, 50, 60), Scalar(180, 255, 255), temp[0]);
        inRange(img, RedL, RedH, temp[1]);
        mask[0] = temp[0] | temp[1];

        inRange(img, BlueL, BlueH, mask[1]);

        inRange(img, YellowL, YellowH, mask[2]);
    }

    vector<Point> DrawBound() {
        vector<Point> result;
        for (int i = 0; i < 3; ++i) {
            vector<vector<Point>> contours;
            findContours(mask[i], contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

            for (auto& s : contours) {
                if (contourArea(s) < 1000)
                    continue;
                Rect boundRect = boundingRect(s);
                // TEST
                rectangle(Image, boundRect.tl(), boundRect.br(), 255, 1);
                circle(Image, boundRect.tl(), 3, 100, -1);
                circle(Image, boundRect.br(), 3, 100, -1);
                result.emplace_back(boundRect.tl());
                result.emplace_back(boundRect.br());
            }
        }
        return result;
    }

    void Printer(vector<Point> v) {
        for (int i = 0; i < v.size(); ++i) {
            cout << v[i].x << " " << v[i].y << " ";
            if (!(i + 1 % 2))
                cout << endl;
        }
        vector<Point>(v).swap(v);  // release vector
    }

   protected:
    Mat mask[3];
    Mat _img;
};

int main(int argc, char* argv[]) {
    String image_path;
#ifdef LOCAL
    for (int i = 0; i < 10; ++i) {
        image_path = "C:\\cv\\tes" + to_string(i) + ".png";
        image_path = "C:\\cv\\tes.png";
        Signal solution(image_path);
        solution.GetSignal();
        imshow("test", solution.Image);
        waitKey(0);
    }
#else
    image_path = argv[1];
    Signal solution(image_path);
    solution.GetSignal();
#endif
}
