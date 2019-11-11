
#include "opencv2/opencv.hpp"
const std::string file_directory = "../../examples/4_contours/";

int contourIdx = 0;
int level = 0;

void createWindowForCont(const std::string &win_name, int max_con_id) {
  cv::namedWindow(win_name, CV_WINDOW_NORMAL);
  cv::resizeWindow(win_name, 550, 550);
  cv::createTrackbar("contourIdx", win_name, &contourIdx, max_con_id);
  cv::createTrackbar("level", win_name, &level, 10);
}

void drawContours(const cv::Mat &img,
                  const std::vector<std::vector<cv::Point>> &contours,
                  const std::vector<cv::Vec4i> &hier) {
  createWindowForCont("figures", contours.size() - 1);
  while (true) {
    cv::Mat temp;
    img.copyTo(temp);
    cv::drawContours(temp, contours, contourIdx, cv::Scalar(0, 0, 0), 5,
                     cv::LINE_8, hier, level);
    cv::imshow("figures", temp);
    if (cv::waitKey(10) >= 0) {
      break;
    };
  }
}
void detectContours() {
  cv::Mat src = cv::imread(file_directory + "figures.png");
  cv::Mat proccesed;
  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hier;
  cv::cvtColor(src, proccesed, cv::COLOR_BGR2GRAY);
  cv::threshold(proccesed, proccesed, 200, 255, cv::THRESH_BINARY_INV);
  cv::findContours(proccesed, contours, hier, cv::RETR_TREE,
                   cv::CHAIN_APPROX_SIMPLE);
  drawContours(src, contours, hier);
}
void drawLine(const cv::Mat &src, double angle) {
  int length = 150;
  cv::Point P1(src.cols / 2, src.cols - 1);
  cv::Point P2;

  P2.x = (int)round(P1.x - length * cos(angle * CV_PI / 180.0));
  P2.y = (int)round(P1.y - length * sin(angle * CV_PI / 180.0));
  cv::line(src, P1, P2, cv::Scalar(0, 0, 255), 5);
}
void detectLineAngle() {
  cv::Mat src = cv::imread(file_directory + "lines.png");
  cv::Mat proccesed;
  std::vector<std::vector<cv::Point>> contours;
  cv::cvtColor(src, proccesed, cv::COLOR_BGR2GRAY);
  cv::threshold(proccesed, proccesed, 200, 255, cv::THRESH_BINARY_INV);
  cv::findContours(proccesed, contours, cv::noArray(), cv::RETR_TREE,
                   cv::CHAIN_APPROX_SIMPLE);

  double angles = 0;
  for (int i = 0; i < contours.size(); ++i) {
    int line_length = 100;
    cv::Vec4f line;
    cv::fitLine(contours[i], line, CV_DIST_L2, 0, 0.01, 0.01);

    cv::Point p1 = cv::Point(line.val[2], line.val[3]);
    cv::Point p2 = cv::Point(line.val[2] + line[0] * line_length,
                             line.val[3] + line[1] * line_length);

    cv::line(src, p1, p2, cv::Scalar(255, 0, 0), 5);

    cv::RotatedRect rect = cv::minAreaRect(contours[i]);

    if (rect.size.width > rect.size.height) {
      angles += rect.angle + 180;
    } else {
      angles += rect.angle + 90;
    }
  }
  drawLine(src, angles / contours.size());
  cv::imshow("lines", src);
  cv::waitKey(0);
}
int main() {
  detectContours();
  cv::destroyAllWindows();
  detectLineAngle();
  return 0;
}