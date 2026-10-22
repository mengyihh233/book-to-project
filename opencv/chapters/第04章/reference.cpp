// 第4章自编配套：Mat共享、clone、ROI与行步长，不是原书官方答案。
#include <opencv2/core.hpp>
#include <cassert>
#include <iostream>

// 参数对象按值复制，像素缓冲区仍可能共享。
void paint_shared_pixels(cv::Mat image) {
    image.setTo(9);
}

int main() {
    cv::setNumThreads(1);
    cv::Mat source = cv::Mat::zeros(4, 5, CV_8UC1);
    cv::Mat shared = source;         // 复制矩阵头，像素共享
    cv::Mat independent = source.clone();
    source.at<uchar>(0, 0) = 99;
    assert(shared.at<uchar>(0, 0) == 99);
    assert(independent.at<uchar>(0, 0) == 0);
    std::cout << "share_clone=" << int(shared.at<uchar>(0, 0)) << ' '
              << int(independent.at<uchar>(0, 0)) << '\n';

    // Rect(x,y,width,height)，at(row,col)：两种坐标顺序不要混用。
    cv::Mat roi = source(cv::Rect(1, 1, 3, 2));
    roi.setTo(7);
    assert(source.at<uchar>(1, 1) == 7);
    assert(source.at<uchar>(2, 3) == 7);
    assert(source.at<uchar>(1, 4) == 0); // ROI外未变
    assert(roi.at<uchar>(0, 0) == source.at<uchar>(1, 1));
    std::cout << "roi_map=" << int(source.at<uchar>(1, 1)) << ' '
              << int(source.at<uchar>(1, 4)) << '\n';

    // 本例一行原图5字节，ROI每行有效3字节，共2行，中间有间隔。
    assert(source.isContinuous());
    assert(!roi.isContinuous());
    assert(roi.step[0] == source.step[0]);
    assert(roi.step[0] > roi.cols * roi.elemSize());
    int sum = 0;
    for (int row = 0; row < roi.rows; ++row) {
        const uchar* pixels = roi.ptr<uchar>(row);
        for (int col = 0; col < roi.cols; ++col) sum += pixels[col];
    }
    assert(sum == 42);
    std::cout << "roi_sum=" << sum << '\n';

    cv::Mat packed = roi.clone();
    assert(packed.isContinuous());
    packed.at<uchar>(0, 0) = 55;
    assert(roi.at<uchar>(0, 0) == 7);
    std::cout << "roi_clone=" << int(packed.at<uchar>(0, 0)) << ' '
              << int(roi.at<uchar>(0, 0)) << '\n';

    cv::Mat input = cv::Mat::zeros(2, 2, CV_8UC1);
    paint_shared_pixels(input);
    assert(input.at<uchar>(0, 0) == 9); // 按值传Mat并不隔离像素
    cv::Mat safe_input = input.clone();
    paint_shared_pixels(safe_input);
    safe_input.setTo(3);
    assert(input.at<uchar>(0, 0) == 9);
    assert(safe_input.at<uchar>(0, 0) == 3);
    std::cout << "value_parameter=" << int(input.at<uchar>(0, 0)) << ' '
              << int(safe_input.at<uchar>(0, 0)) << '\n';
    std::cout << "本章自检通过。\n";
}
