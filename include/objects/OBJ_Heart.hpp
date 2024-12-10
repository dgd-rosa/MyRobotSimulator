#include "super_object.hpp"
#include "exceptions/GameException.hpp"

#ifndef OBJ_HEART_HPP
#define OBJ_HEART_HPP

class OBJ_Heart : public PowerUpObject
{
    private:
        void initShape();
    public:
        OBJ_Heart(int life_boost = 1);
        ~OBJ_Heart() = default;

        void setHeartTexture(std::string string);
        int getLifeBoost();

        
};

#endif