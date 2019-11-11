
#include "opencv2/opencv.hpp"

const std::string file_directory = "../../examples/3_filters/";

std::vector<int> low = {30, 0, 201};
std::vector<int> high = {180, 18, 255};
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

void showImage(const std::string &win_name, const cv::Mat &img) {
  cv::namedWindow(win_name, CV_WINDOW_NORMAL);
  cv::resizeWindow(win_name, 550, 550);
  cv::imshow(win_name, img);
}
void threshOps() {
  cv::Mat src = cv::imread(file_directory + "text.jpg");
  cv::Mat processed;
  cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);

  cv::threshold(src, processed, 130, 255, cv::THRESH_BINARY);
  showImage("THRESH_BIN", processed);
  cv::threshold(src, processed, 130, 255, cv::THRESH_OTSU);
  showImage("THRESH_OTSU", processed);

  cv::adaptiveThreshold(src, processed, 255, cv::ADAPTIVE_THRESH_MEAN_C,
                        cv::THRESH_BINARY, 131, 10);
  showImage("ADAPTIVE_MEAN_C", processed);
  cv::adaptiveThreshold(src, processed, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                        cv::THRESH_BINARY, 131, 10);
  showImage("ADAPTIVE_GAUSSIAN_C", processed);
  cv::waitKey(0);
}

void blurOps() {
  cv::Size ker(31, 31);
  cv::Mat src = cv::imread(file_directory + "text.jpg");
  showImage("Def", src);
  cv::Mat processed;
  //  cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);

  cv::blur(src, processed, ker);
  showImage("Blur", processed);
  cv::medianBlur(src, processed, 31);
  showImage("medianBlur", processed);
  cv::GaussianBlur(src, processed, ker, 100.0);
  showImage("GaussianBlur", processed);
  cv::bilateralFilter(src, processed, 31, 100.0, 10);
  showImage("bilateralBlur", processed);
  cv::waitKey(0);
}

void morphOps() {
  cv::Mat src = cv::imread(file_directory + "road.jpeg");
  cv::Mat processed;
  createWindow("DEF");
  cv::cvtColor(src, src, CV_BGR2HSV);
  while (true) {
    cv::inRange(src, low, high, processed);
    cv::imshow("DEF", processed);
    if (cv::waitKey(10) >= 0) {
      break;
    }
  }

  cv::erode(processed, processed, cv::Mat(3, 3, CV_8UC1));
  cv::erode(processed, processed, cv::Mat(2, 2, CV_8UC1), cv::Point(-1, -1), 1,
            CV_HAL_BORDER_REFLECT);
  cv::erode(processed, processed, cv::Mat(1, 1, CV_8UC1), cv::Point(-1, -1), 3,
            CV_HAL_BORDER_REFLECT);
  showImage("ERODE", processed);

  cv::dilate(processed, processed, cv::Mat(3, 3, CV_8UC1), cv::Point(-1, -1),
             2);
  showImage("DILATE", processed);
  cv::waitKey(0);
}
int main() {
  threshOps();
  cv::destroyAllWindows();
  blurOps();
  cv::destroyAllWindows();
  morphOps();
  cv::destroyAllWindows();

  return 0;
}