# pragma once
# include "Character.h"

typedef unordered_map<int, bool> tunnelID_hash;

struct Mole: public Character, public iSkill {
    private:
        tunnelID_hash* skill_usage;
        bool random_use;

    public:
        Mole() : Character(15, 7) {
            name = "Mole";
            skill_usage = new tunnelID_hash;
            random_use = false;
        }

        Character* clone() {
            return new Mole;
        }

        void executeStrategy() {
            switch (strategy->getState()) {
                case SEARCH:
                    strategy->searchTunnel();
                    if (strategy->getState() == UNDERGROUND) {
                        add_tunnel();
                    }
                    break;

                case UNDERGROUND:
                    strategy->searchChamber();
                    set_random_usage();
                    break;

                case MINING:
                    strategy->mineChamber();
                    break;

                case RETRIEVE:
                    strategy->retrieveMineral();
                    set_random_usage();
                    break;
                
                case SCORE:
                    strategy->score_minerals();
                    break;

                case UNAVAILABLE:
                    executeSkill();
                    if (strategy->state == UNDERGROUND) { // If succesful, save Mole
                        display_action();
                        sleep(1);
                        return;
                    }
                case DONE:
                    *isDone = true;
                    return;
            }
            display_action();
            if (random_use) {
                executeSkill();
                display_action();
                sleep(1);
            }
        }

        void set_random_usage() {
            if (strategy->tunnelEntrance != nullptr) {
                random_use = !(random(0, 19)); // 5% random skill usage
            } else {
                random_use = false;
            }
        }

        void executeSkill() {
            if (is_consumed() || strategy->currentChamber == nullptr) {
                strategy->message = ("Skill unavailable for this tunnel...");
                return;
            }

            ChamberNode* currentParent = strategy->currentChamber->get_parent();
            ChamberNode* nextChamber = nullptr;
            // Busca chamber heramano de current
            if (currentParent->get_left() == strategy->currentChamber) {
                nextChamber = currentParent->get_right();
            } else {
                nextChamber = currentParent->get_left();
            }

            if (nextChamber != nullptr && nextChamber->get_data()->is_transitable()) {
                delete strategy->tunnelOptions->pop();
                strategy->currentChamber = nextChamber;
                strategy->tunnelOptions->add(new RandOption(2));
                int chamberID = strategy->currentChamber->get_data()->get_ID();
                strategy->message = ("Skill succesful! Dug into chamber #" + to_string(chamberID));
                update_usage();
            } else {
                int chamberID = strategy->currentChamber->get_data()->get_ID();
                strategy->message = ("Skill failed... Chamber #" + to_string(chamberID) + " has no brother chamber");
            }

            if (strategy->state == UNAVAILABLE) {
                strategy->state = UNDERGROUND;
            }
        }

        void add_tunnel() {
            int tunnelID = strategy->tunnelEntrance->get_data()->get_ID() / 100;
            if (! skill_usage->count(tunnelID)) {
                skill_usage->emplace(tunnelID, false);
            }
        }

        bool is_consumed() {
            int tunnelID = strategy->tunnelEntrance->get_data()->get_ID() / 100;
            bool usage = skill_usage->at(tunnelID);
            return usage;
        }

        void update_usage() {
            int tunnelID = strategy->tunnelEntrance->get_data()->get_ID() / 100;
            skill_usage->at(tunnelID) = true;
        }

};
