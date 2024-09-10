#include <iostream>

int main()
{
    int intergerOne = 5.0;
    int intergerTwo(5.0);
    // Error
    // int intergerThree{5.0};
    // int intergerFour = {5.0};
    // Uniform initialization
    // safe and recommended
    int intergerThree{5};
    int intergerFour = {5};

    std::cout << "intergerOne: " << intergerOne << std::endl;
    std::cout << "intergerTwo: " << intergerTwo << std::endl;
    std::cout << "intergerThree: " << intergerThree << std::endl;
    std::cout << "intergerFour: " << intergerFour << std::endl;

    return 0;
}