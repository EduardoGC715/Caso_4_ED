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
            switch (strategy->getState()) {
                case SEARCH:
                    strategy->searchTunnel();
                    break;

                case UNDERGROUND:
                    strategy->searchChamber();
                    break;

                case MINING:
                    strategy->mineChamber(); break;

                case RETRIEVE:
                    strategy->retrieveMineral(); break;
                
                case SCORE:
                    strategy->score_minerals();
                    break;

                case UNAVAILABLE:
                    //executeSkill()
                case DONE:
                    *isDone = true;
                    return;
            }
            display_action();
        }

        void executeSkill() {
            // Revisar si ya consumio habilidad de cambiar camaras en el tunel
            // Ejecutar habilidad segun resultado
        }

};
