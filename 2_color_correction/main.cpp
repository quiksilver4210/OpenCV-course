#include <opencv2/opencv.hpp>
#include <string>

const std::string file_directory = "../../examples/2_color_correction/";

std::vector<int> low = {0, 0, 0};
std::vector<int> high = {180, 255, 255};
int createWindow(const std::string &win_name) {
  cv::namedWindow(win_name, cv::WINDOW_NORMAL);
  cv::resizeWindow(win_name, 450, 450);
  cv::createTrackbar("l_HUE", win_name, &low[0], 180);
  cv::createTrackbar("l_SAT", win_name, &low[1], 255);
  cv::createTrackbar("l_VAL", win_name, &low[2], 255);
  cv::createTrackbar("h_HUE", win_name, &high[0], 180);
  cv::createTrackbar("h_SAT", win_name, &high[1], 255);
  cv::createTrackbar("h_VAL", win_name, &high[2], 255);
}

int showImage(const std::string &win_name, int color_space_val) {
  cv::namedWindow(win_name, cv::WINDOW_NORMAL);
  cv::resizeWindow(win_name, 450, 450);
  cv::Mat img = cv::imread(file_directory + "rainbow.png");
  if (img.empty()) {
    std::cerr << "Can't open image" << std::endl;
    return 1;
  }
  cv::cvtColor(img, img, color_space_val);
  cv::imshow(win_name, img);

  return 0;
}
int main() {
  showImage("DEFAULT", 0);
  showImage("RGB", cv::COLOR_BGR2RGB);
  showImage("GRAY", cv::COLOR_BGR2GRAY);
  showImage("HSV", cv::COLOR_BGR2HSV);
  showImage("XYZ", cv::COLOR_BGR2XYZ);
  showImage("LAB", cv::COLOR_BGR2Lab);
  cv::waitKey(0);

  cv::destroyAllWindows();

  createWindow("HSV");
  while (true) {
    cv::Mat img = cv::imread(file_directory + "rainbow.png");
    cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
    cv::inRange(img, low, high, img);
    cv::imshow("HSV", img);
    if (cv::waitKey(10) >= 0) {
      break;
    }
  }

  return 0;
}