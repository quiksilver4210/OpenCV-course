#include "opencv2/opencv.hpp"
#include <string>

const std::string file_directory = "../../examples/1_capture/";

const std::string trackbar_name = "timeline";
int slider_position = 0;
cv::VideoCapture capture(file_directory + "dog.mp4");

void onTrackbarSlide(int new_pos, void *) {
  capture.set(cv::CAP_PROP_POS_FRAMES, new_pos);
}

int showVideo(const std::string &win_name) {

  if (!capture.isOpened()) {
    std::cerr << "Can't open video file" << std::endl;
    return 1;
  }

  cv::Mat frame;
  int position = (int) capture.get(cv::CAP_PROP_FRAME_COUNT);
  cv::createTrackbar(trackbar_name, win_name, &slider_position, position, onTrackbarSlide);
  while (capture >> frame, !frame.empty()) {
    cv::imshow(win_name, frame);
    cvSetTrackbarPos(trackbar_name.c_str(), win_name.c_str(), (int) capture.get(cv::CAP_PROP_POS_FRAMES));
    if (cv::waitKey(5) >= 0) {
      std::cout << "You stopped playing video" << std::endl;
      break;
    }
  }
  std::cout << "Video is ended" << std::endl;
  return 0;
}
void createWindow(const std::string &win_name) {
  cv::namedWindow(win_name, cv::WINDOW_FULLSCREEN);
}

int showImage(const std::string &win_name) {
  cv::Mat img = cv::imread(file_directory + "apples.jpeg");
  if (img.empty()) {
    std::cerr << "Can't open image" << std::endl;
    return 1;
  }
  cv::imshow(win_name, img);
  cv::waitKey(0);
  return 0;
}

int main() {
  std::string win_name = "new window";
  createWindow(win_name);
  showImage(win_name);
  showVideo(win_name);
  cv::destroyAllWindows();
  return 0;
}