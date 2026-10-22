// 【本题说明开始】
// CV-L04：Mat 共享、clone、ROI 与行步长（中文自编配套）
// 题目：用给定小矩阵观察共享像素、独立复制与按值传参。
// 只补全下方 3 个 BEGIN / END 区；删除各区占位 throw，再写实现。
// 1：给 shared、independent 赋值；2：逐行求像素和；3：按值 Mat 的 setTo。
// 无键盘输入、图片或图形窗口；main 的建图、调用与输出已给好。
// 默认预期：99 0；7 0；5 3 0 1；42；55 7；9 3（完整标签见 README）。
// VS Code：本题：运行作答。人工核验，没有独立自动评分器。
// 完整题目、格式与解析：../README.md、../solution.md。
// 【本题说明结束】

#include <opencv2/core.hpp>
#include <exception>
#include <iostream>
#include <stdexcept>

// 函数声明：main 先使用函数，具体实现留在文件后半部分。
int sumPixels(const cv::Mat& image);
void paintSharedPixels(cv::Mat image);

int main() {
    try {
        // 实验一：复制发生在 source 被修改之前。
        cv::Mat source = cv::Mat::zeros(4, 5, CV_8UC1);
        cv::Mat shared;
        cv::Mat independent;
        /* BEGIN 1：让 shared 共享 source，让 independent 独立复制 source */
        // 两个对象都需赋值；哪个用普通赋值，哪个用 clone()？
        throw std::runtime_error("补全区 1 尚未完成：共享与独立复制");
        /* END 1 */

        if (shared.empty() || independent.empty()) {
            throw std::runtime_error("补全区 1：两个 Mat 都需要有效数据");
        }
        source.at<uchar>(0, 0) = 99;
        std::cout << "share_clone="
                  << static_cast<int>(shared.at<uchar>(0, 0)) << ' '
                  << static_cast<int>(independent.at<uchar>(0, 0)) << '\n';

        // 实验二：Rect(x,y,宽,高)，at(行,列)。ROI 是原图的窗口。
        cv::Mat roi = source(cv::Rect(1, 1, 3, 2));
        const uchar roiValue{7};  // 完成后可改为 3，重新预测输出。
        roi.setTo(roiValue);
        std::cout << "roi_map="
                  << static_cast<int>(source.at<uchar>(1, 1)) << ' '
                  << static_cast<int>(source.at<uchar>(1, 4)) << '\n';

        cv::Mat packed = roi.clone();
        std::cout << "roi_layout=" << roi.step[0] << ' '
                  << roi.cols * roi.elemSize() << ' '
                  << roi.isContinuous() << ' ' << packed.isContinuous() << '\n';
        std::cout << "roi_sum=" << sumPixels(roi) << '\n';
        packed.at<uchar>(0, 0) = 55;
        std::cout << "roi_clone="
                  << static_cast<int>(packed.at<uchar>(0, 0)) << ' '
                  << static_cast<int>(roi.at<uchar>(0, 0)) << '\n';

        // 实验三：复制参数对象，是否也复制了它所指向的像素？
        cv::Mat input = cv::Mat::zeros(2, 2, CV_8UC1);
        paintSharedPixels(input);
        cv::Mat safeInput = input.clone();
        paintSharedPixels(safeInput);
        safeInput.setTo(3);
        std::cout << "value_parameter="
                  << static_cast<int>(input.at<uchar>(0, 0)) << ' '
                  << static_cast<int>(safeInput.at<uchar>(0, 0)) << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 2;
    }
}

// 本练习约定：image 是二维 CV_8UC1；只读取，不修改像素。
int sumPixels(const cv::Mat& image) {
    /* BEGIN 2：按行、再按列累加真实像素，返回整数总和 */
    // 提示：第 row 行从 image.ptr<uchar>(row) 开始，有 image.cols 列。
    // 用 image.rows 控制外层循环；不要假定 ROI 所有像素紧密连续。
    (void)image;  // 补全后删去这行；当前只用于避免未使用参数警告。
    throw std::runtime_error("补全区 2 尚未完成：逐行求像素和");
    /* END 2 */
}

void paintSharedPixels(cv::Mat image) {
    /* BEGIN 3：调用 setTo，将参数矩阵像素统一改成 9 */
    // 这里故意按值传 Mat：观察改像素与改参数对象本身的区别。
    (void)image;  // 补全后删去这行。
    throw std::runtime_error("补全区 3 尚未完成：按值 Mat 修改像素");
    /* END 3 */
}
