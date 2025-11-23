#define _CRT_SECURE_NO_WARNINGS
#include <iostream>


//
//// 1. 递归终止函数（处理 0 个参数的情况）
//void print() {
//    std::cout << "--------------------------" << std::endl;
//}
//
//// 2. 可变参数递归函数
//template <typename T, typename... Args>
//void print(T first_arg, Args... remaining_args) {
//    // 打印第一个参数
//    std::cout << first_arg << std::endl;
//
//    // 递归调用，将剩余的参数包传递下去
//    // 每次递归，参数包都会“剥离”掉第一个参数
//    print(remaining_args...);
//}
//
//int main() {
//    print(10, 3.14, "Hello", 'A');
//    return 0;
//}
//#include <map>
//#include <string>
//#include <iostream>
//
//struct Value {
//    std::string data;
//    Value(std::string d) : data(std::move(d)) {
//        std::cout << "Value Constructor: " << data << std::endl;
//    }
//    Value(const Value& other) : data(other.data) {
//        std::cout << "Value Copy Constructor: " << data << std::endl;
//    }
//};
//
//int main() {
//    std::map<int, Value> my_map;
//
//    std::cout << "--- Using emplace on map ---" << std::endl;
//    // emplace 会将参数完美转发给 std::pair 的构造函数
//    // std::pair 的构造函数在这里会用 10 作为 key，并用 "apple" 构造 Value 对象
//    my_map.emplace(10, "apple");
//
//    std::cout << "\n--- Using insert on map (for comparison) ---" << std::endl;
//    // insert 需要一个已经构造好的 pair 对象
//    my_map.insert(std::make_pair(20, Value("banana")));
//
//    return 0;
//}
//#include <iostream>
//
//int main() {
//    int x = 10;
//    int y = 20;
//
//    // 按值捕获 x 和 y
//    auto add = [x, y]() {
//        return x + y;
//    };
//    std::cout << "Sum: " << add() << std::endl; // 输出 30
//
//    // 按引用捕获 x
//    auto increment = [&x]() {
//        x++;
//    };
//    increment();
//    std::cout << "x after increment: " << x << std::endl; // 输出 11
//
//    // 按值捕获 y，并尝试修改 (需要 mutable)
//    auto try_modify_y = [y]() mutable {
//        y = 100; // 只修改副本
//        std::cout << "y inside lambda: " << y << std::endl; // 输出 100
//    };
//    try_modify_y();
//    std::cout << "y outside lambda: " << y << std::endl; // 仍然是 20
//
//    return 0;
//}
#include <iostream>
#include <functional>

int main() {
    // 包装 Lambda（捕获外部变量）
    int x = 10;
    std::function<int(int)> func = [x](int y) {
        return x + y;
    };

    std::cout << func(5) << std::endl; // 输出 15

    return 0;
}