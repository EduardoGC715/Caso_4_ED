# pragma once
# include <mutex>

class PlayerScore {
    private:
        std::mutex mtx;
        int ID;
        int score;

    public:
        PlayerScore() : mtx(), ID(0), score(0)
        {}

        void setID(int pID) {
            ID = pID;
        }

        void add(int pValue) {
            mtx.lock();
            score += pValue;
            mtx.unlock();
        }

        int player() {
            return ID;
        }

        int get() {
            return score;
        }
};