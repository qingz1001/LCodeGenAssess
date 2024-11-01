#include <stdio.h>
#include <string.h>

#define MAX_NUM 18
#define NUM_CODES 10
#define CODE_LENGTH 7

int code[NUM_CODES][CODE_LENGTH] = {
    {1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}
};

int countPossibleValues(char *input) {
    int count = 0;
    for (int i = 0; i <= 9; i++) {
        if (memcmp(input, (char *)code[i], CODE_LENGTH) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    char input[MAX_NUM + 1];
    scanf("%s", input);
    int result = 1;
    for (int i = 0; i < strlen(input); i += CODE_LENGTH) {
        result *= countPossibleValues(&input[i]);
    }
    printf("%d\n", result);
    return 0;
}