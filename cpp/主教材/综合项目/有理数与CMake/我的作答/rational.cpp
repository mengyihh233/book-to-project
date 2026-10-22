#include "rational.hpp"
#include <stdexcept>

// 原书定位：第6章6.3，PDF206—211；以下为自编中文概括，不是原文代码。
// 1. 用户关心“这个类型能做什么”，私有表示由类负责维护。
// 2. 同一个数可能有多种分子/分母写法；构造后应统一成唯一表示。
// 3. 本练习约定：分母为正、分子分母互质、零统一为0/1。
// 4. 构造函数先建立不变量；成功的四则运算也必须保持它。
// 先手算2/-4与0/-7，再写代码；接口中的const表示原对象保持不变。
// 本适配用标准异常和有限int32存储，和历史教材库的报错机制有区别。

// 核心作答只修改本文件。接口、调用示例和检查程序已经提供。
// 先实现规范化与构造，再实现四则运算；不会的先看README分步提示。
namespace roberts_lab {
Rational Rational::normalized(std::int64_t /*numerator*/, std::int64_t /*denominator*/) {
    // TODO：拒绝零分母、统一符号、约分，再检查int32存储范围。
    throw std::logic_error("NOT_IMPLEMENTED: normalization");
}
// 构造是对象的入口：调用者不必自己先约分，也不能得到分母为零的对象。
Rational::Rational(std::int32_t numerator, std::int32_t denominator) {
    *this = normalized(numerator, denominator);
}
// 操作符重载让用户用熟悉的+；返回新值，不把左边对象偷偷改掉。
// 先在纸上写出a/b+c/d，比较中间乘积的类型与最终存储类型。
Rational Rational::operator+(const Rational& /*other*/) const {
    // TODO：先提升到int64再乘，最后交给normalized统一表示。
    throw std::logic_error("NOT_IMPLEMENTED: addition");
}
// 减法复用同一不变量；不要为每个运算分别设计一套约分规则。
Rational Rational::operator-(const Rational& /*other*/) const {
    throw std::logic_error("NOT_IMPLEMENTED: subtraction");
}
// 乘法的数学公式简单，但固定宽度整数的范围仍需要检查。
Rational Rational::operator*(const Rational& /*other*/) const {
    throw std::logic_error("NOT_IMPLEMENTED: multiplication");
}
Rational Rational::operator/(const Rational& /*other*/) const {
    // TODO：先判断右操作数是否为0，再使用倒数公式。
    throw std::logic_error("NOT_IMPLEMENTED: division");
}
} // namespace roberts_lab
