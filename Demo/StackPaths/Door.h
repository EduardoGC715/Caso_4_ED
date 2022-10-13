# pragma once

class Door {
    private:
        int ID;
        bool tunnel;
    
    public:
        Door(int pID, bool pTunnel)
        : ID(pID), tunnel(pTunnel)
        {}

        int getID() {
            return ID;
        }

        bool hasTunnel() {
            return tunnel;
        }
};