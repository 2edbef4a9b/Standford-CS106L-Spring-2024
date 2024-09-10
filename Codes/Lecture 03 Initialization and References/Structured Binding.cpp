#include <iostream>
#include <tuple>
#include <string>

std::tuple<std::string, std::string, std::string> getClassInfo()
{
    std::string className = "CS 106L";
    std::string buildingName = "Turing Auditorium";
    std::string language = "C++";
    return {className, buildingName, language};
}

int main()
{
    auto [className, buildingName, language] = getClassInfo();
    std::cout << "Class Name: " << className << std::endl;
    std::cout << "Building Name: " << buildingName << std::endl;
    std::cout << "Language: " << language << std::endl;
    return 0;
}