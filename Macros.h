
#pragma once
#include<exception>
#include<string>
#define _NODISCARD [[nodiscard]]

#define _CONSTEXPR constexpr
#define _PANAGIOTIS_BEGIN namespace panagiotis{
#define _PANAGIOTIS_END }


_PANAGIOTIS_BEGIN
class array_subscript_out_of_range :public std::exception
{
private:
    std::string errorMessage; // To store the error message
public:
    //Constructor to initialize the error message
    explicit array_subscript_out_of_range(const std::string& message)
        : errorMessage(message) {
    }

    // Override the what() method
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};
class tried_to_access_an_empty_iterator_ :public std::exception
{
private:
    std::string errorMessage; // To store the error message
public:
    //Constructor to initialize the error message
    explicit tried_to_access_an_empty_iterator_(const std::string& message)
        : errorMessage(message) {
    }

    // Override the what() method
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};
_PANAGIOTIS_END
