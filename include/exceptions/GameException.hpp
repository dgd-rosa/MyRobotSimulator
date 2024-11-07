#include <exception>
#include <iostream>

#ifndef GAMEEXCEPTION_HPP
#define GAMEEXCEPTION_HPP

class GameException : std::exception
{
    private:
        std::string message;
    public:
        GameException(const char* err);
        GameException(const std::string err);
        ~GameException();

        const char* what() const noexcept override {
            return message.c_str();
        }
};



#endif