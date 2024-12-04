#include "super_object.hpp"
#include "exceptions/GameException.hpp"

#ifndef OBJ_HEART_HPP
#define OBJ_HEART_HPP

class OBJ_Heart : public SuperObject
{
    private:
        void initShape();
    public:
        OBJ_Heart();
        ~OBJ_Heart() = default;

        void setHeartTexture(std::string string);

        
};

#endif