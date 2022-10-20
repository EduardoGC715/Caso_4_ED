# pragma once
# include "Character.h"

struct Freighter: public Character {
    public:
        Freighter() : Character(40, 10) {
            name = "Freighter";
        }

        Character* clone() {
            return new Freighter;
        }
};
