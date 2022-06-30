#include "Person.hpp"


std::ostream &operator<<(std::ostream &stream, PhoneType phoneType)
{
    std::string namePhoneType[] = {"MOBILE", "HOME", "WORK"};
    return stream << namePhoneType[phoneType];
}