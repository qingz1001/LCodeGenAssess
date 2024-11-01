#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char input[100];
    scanf("%s", input);
    
    int numbers[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
    int mod_values[20] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 1, 4, 9, 16, 25, 36, 49, 64, 81, 0};
    int result = 0;
    
    while (strcmp(input, ".") != 0) {
        if (strcmp(input, "one") == 0 || strcmp(input, "a") == 0 || strcmp(input, "another") == 0) {
            result = (result * 100) + mod_values[1];
        } else if (strcmp(input, "two") == 0 || strcmp(input, "both") == 0) {
            result = (result * 100) + mod_values[2];
        } else if (strcmp(input, "three") == 0) {
            result = (result * 100) + mod_values[3];
        } else if (strcmp(input, "four") == 0) {
            result = (result * 100) + mod_values[4];
        } else if (strcmp(input, "five") == 0) {
            result = (result * 100) + mod_values[5];
        } else if (strcmp(input, "six") == 0) {
            result = (result * 100) + mod_values[6];
        } else if (strcmp(input, "seven") == 0) {
            result = (result * 100) + mod_values[7];
        } else if (strcmp(input, "eight") == 0) {
            result = (result * 100) + mod_values[8];
        } else if (strcmp(input, "nine") == 0) {
            result = (result * 100) + mod_values[9];
        } else if (strcmp(input, "ten") == 0) {
            result = (result * 100) + mod_values[10];
        } else if (strcmp(input, "eleven") == 0) {
            result = (result * 100) + mod_values[11];
        } else if (strcmp(input, "twelve") == 0) {
            result = (result * 100) + mod_values[12];
        } else if (strcmp(input, "thirteen") == 0) {
            result = (result * 100) + mod_values[13];
        } else if (strcmp(input, "fourteen") == 0) {
            result = (result * 100) + mod_values[14];
        } else if (strcmp(input, "fifteen") == 0) {
            result = (result * 100) + mod_values[15];
        } else if (strcmp(input, "sixteen") == 0) {
            result = (result * 100) + mod_values[16];
        } else if (strcmp(input, "seventeen") == 0) {
            result = (result * 100) + mod_values[17];
        } else if (strcmp(input, "eighteen") == 0) {
            result = (result * 100) + mod_values[18];
        } else if (strcmp(input, "nineteen") == 0) {
            result = (result * 100) + mod_values[19];
        } else if (strcmp(input, "twenty") == 0) {
            result = (result * 100) + mod_values[20];
        }
        
        scanf("%s", input);
    }
    
    // 去掉前导零
    while (result >= 100 && result % 10 == 0) {
        result /= 10;
    }
    
    printf("%d\n", result);
    
    return 0;
}