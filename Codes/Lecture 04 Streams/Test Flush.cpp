#include <iostream>
#include <sstream>

void doSomething() {
    int sum = 0;
    for (int i = 0; i < 1000000000; ++i) {
        sum += i;
    }
}

int main() {

    // Test whether '\n' flushes the output buffer
    std::cout << "Hello, World!" << '\n';
    doSomething();
    std::cout << "Hello, World!" << '\n';
    doSomething();
    std::cout << "Hello, World!" << '\n';
    std::cout << std::endl;

    std::ostringstream oss;
    oss << "Hello, World!" << '\n';
    doSomething();
    oss << "Hello, World!" << '\n';
    doSomething();
    oss << "Hello, World!" << '\n';
    oss << std::endl;
    
    return 0;
}