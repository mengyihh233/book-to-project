// 【本题说明开始】
// 教材strlib五接口调用练习
// 题目与要求：
// 在main调用已有适配头里的integerToString、stringToInteger、realToString、stringToReal、
// toUpperCase。
// 不用先实现库。核对42→文本42、文本 +007 →7、-1.25e2→-125、cpp-17→CPP-17，
// 再检查空串、尾随杂字和越界异常。
//
// 写在哪里：本文件main中的自己的调用；不要include参考答案代替实现。
// 怎么检查：本组没有独立自动判分，按题目边界自测；参考核对只验证参考。
// 输入输出：没有统一标准输入/输出协议，先预测类型与值，再实际调用核对。
// 详细题目：../stanford-strings.md。
// 【本题说明结束】
//
#include "../兼容头文件/strlib.hpp"
#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

// Call the shared teaching adapter; do not reimplement these five functions.
// This is not the original Stanford strlib library.
int main() {
    namespace rc = roberts_compat;
    // TODO 1: predict and call rc::integerToString(42),
    //         rc::stringToInteger(" +007 "), rc::realToString(23.45),
    //         rc::stringToReal("-1.25e2") and rc::toUpperCase("cpp-17").
    //         Check returned types and whether the original string changes.
    // TODO 2: use numeric_limits<int>::min()/max() in an integer round trip.
    // TODO 3: try "12px", blank text and "1e9999"; catch the expected
    //         invalid_argument or out_of_range without pretending success.
    // TODO 4: pick an ASCII boundary and one unchanged non-ASCII byte sequence.
    // Remove this placeholder only after adding your own calls and checks.
    std::cerr << "stanford-strings: not implemented yet\n";
    return 2;
}
