# pragma once
# include "Character.h"

struct Mole: public Character {
    public:
        Mole()
        : Character(15, 7)
        {}
};
