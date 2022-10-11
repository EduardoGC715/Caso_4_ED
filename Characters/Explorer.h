# pragma once
# include "Character.h"

struct Explorer: public Character {
    public:
        Explorer()
        : Character(8, 20) {
            name = "Explorer";
        }

        Character* clone() {
            return new Explorer;
        }
};
