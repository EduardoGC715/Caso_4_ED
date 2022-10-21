# pragma once
# include "Character.h"
# include "../Interfaces/iSkill.h"

struct Mole: public Character, public iSkill {
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
                    strategy->searchTunnel(currentRoom, roomOptions, currentPath);
                    break;

                case UNDERGROUND:
                    strategy->searchChamber(currentPath, pathOptions);
                    break;

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
