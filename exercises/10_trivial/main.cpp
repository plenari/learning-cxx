#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 检查边界条件
    if (i < 0) return 0;
    if (i == 0) return 0;
    if (i == 1) return 1;
    
    // 初始化基础情况，如果尚未初始化
    if (cache.cached == 0) {
        cache.cache[0] = 0;
        cache.cache[1] = 1;
        cache.cached = 2;
    }
    
    int cached = cache.cached;
    // 确保我们至少有前两个值来计算后续值
    if (cached <= i && cached >= 2) {
        for (; cached <= i && cached < 16; ++cached) {
            cache.cache[cached] = cache.cache[cached - 1] + cache.cache[cached - 2];
        }
    }
    
    // 更新已缓存的索引
    if (i >= cache.cached) {
        cache.cached = i + 1;
    }
    
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    // NOTICE: C/C++ 中，读取未初始化的变量（包括结构体变量）是未定义行为
    // READ: 初始化的各种写法 <https://zh.cppreference.com/w/cpp/language/initialization>
    FibonacciCache fib = {};  // 初始化所有成员为0
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
