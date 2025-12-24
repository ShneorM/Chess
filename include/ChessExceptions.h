#pragma once
#include <exception>
#include <string>
using namespace std;

class InvalidMoveException : public exception 
{
    string message;
public:
    InvalidMoveException(const string& msg) : message(msg) {}
    const char* what() const noexcept override 
    {
        return message.c_str();
    }
};

class CheckException : public exception 
{
    string message;
public:
    CheckException(const string& msg) : message(msg) {}
    const char* what() const noexcept override 
    {
        return message.c_str();
    }
};

