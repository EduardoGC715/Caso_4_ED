# pragma once
# include "../utils/Random.h"

class RandOption {
    private:
        int index;
        int size;
        int* options;
    
    public:
        RandOption(int pSize) {
            size = pSize;
            options = new int[size];

            int seed = random(0,size);
            for (index = 0; index < size; ++index) {
                options[index] = seed % size;
                ++seed;
            }
            index = 0; // Reset option index
        }

        ~RandOption() {
            delete[] options;
        }

        bool isCleared() {
            return index == size;
        }

        int getOption() {
            return options[index++];
        }
};