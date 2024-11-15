#include "super_object.hpp"
#include "exceptions/GameException.hpp"

#ifndef OBJ_SCREW_HPP
#define OBJ_SCREW_HPP

class OBJ_Screw : public PointObject
{
    public:
        OBJ_Screw();
        ~OBJ_Screw() = default;
};

#endif