# pragma once
# include <iostream>
# include <string>

using namespace std;

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
    result = inputInt(1, pSize);
    return result;
}