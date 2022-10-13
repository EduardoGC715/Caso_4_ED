# pragma once
# include "Character.h"
# include "../Strategy/Skill.h"

struct Mole: public Character, public Skill {
    public:
        Mole() : Character(15, 7) {
            name = "Mole";
        }

        Character* clone() {
            return new Mole;
        }

        void executeStrategy() {
            switch (state) {
                case SEARCH:
                    strategy->searchTunnel(); break;

                case UNDERGROUND:
                    strategy->searchChamber(); break;

                case MINING:
                    strategy->mineChamber(); break;

                case RETRIEVE:
                    strategy->retrieveMineral(); break;

                case UNAVAILABLE:
                default:
                    //executeSkill()
                    break;
            }
        }

        void executeSkill() {
            // Revisar si ya consumio habilidad de cambiar camaras en el tunel
            // Ejecutar habilidad segun resultado
        }

};
