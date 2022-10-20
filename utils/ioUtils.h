# pragma once
# include <iostream>
# include <string>
# include <mutex>

using namespace std;

mutex io_mutex;

int inputInt(int min, int max) {
    int result;
    while (true) {
        printf("Input: ");
        scanf("%d", &result);
        if (result < min || result > max) {
            printf("Error - Invalid option\n");
        } else {
            break;
        }
    }
    return result;
}

int optionMenu(string& pMessage, string* pOptions, int pSize) {
    int result;
    printf("%s\n", pMessage.c_str());
    for (int index = 0; index < pSize; ++index) {
        printf("    %d) %s\n", index+1, pOptions[index].c_str());
    }
    return inputInt(1, pSize);
}