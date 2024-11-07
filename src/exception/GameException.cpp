#include "exceptions/GameException.hpp"

GameException::GameException(const char* err) : message(err)
{
    
}

GameException::GameException(const std::string err) : message(err)
{

}

GameException::~GameException()
{
}