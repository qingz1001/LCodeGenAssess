#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void addNumbers(char *num1, char *num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 > len2 ? len1 : len2;
    int carry = 0;
    char result[MAX_LEN] = {0};
    int resultIndex = 0;

    for (int i = 0; i < maxLen || carry; i++) {
        int digit1 = i < len1 ? num1[i] - '0' : 0;
        int digit2 = i < len2 ? num2[i] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / primes[i];
        result[resultIndex++] = (sum % primes[i]) + '0';
    }

    reverse(result);
    printf("%s\n", result);
}

void parseInput(char *input) {
    char num1[MAX_LEN] = {0};
    char num2[MAX_LEN] = {0};
    int num1Index = 0, num2Index = 0;
    int i = 0;

    while (input[i] != '+') {
        if (input[i] == ',') {
            num1Index++;
        } else {
            num1[num1Index] = input[i];
        }
        i++;
    }
    i++; // skip '+'

    while (input[i] != '\0') {
        if (input[i] == ',') {
            num2Index++;
        } else {
            num2[num2Index] = input[i];
        }
        i++;
    }

    reverse(num1);
    reverse(num2);
    addNumbers(num1, num2);
}

int main() {
    char input[MAX_LEN];
    scanf("%s", input);
    parseInput(input);
    return 0;
}