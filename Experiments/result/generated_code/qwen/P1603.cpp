#include <stdio.h>
#include <string.h>

int main() {
    char sentence[100];
    scanf("%s %s %s %s %s %s .", sentence, sentence + 7, sentence + 14, sentence + 21, sentence + 28, sentence + 35);
    
    int numbers[6] = {0};
    int count = 0;
    
    for (int i = 0; i < 6; i++) {
        if (strcmp(sentence + 7 * i, "one") == 0) numbers[count++] = 1;
        else if (strcmp(sentence + 7 * i, "two") == 0) numbers[count++] = 2;
        else if (strcmp(sentence + 7 * i, "three") == 0) numbers[count++] = 3;
        else if (strcmp(sentence + 7 * i, "four") == 0) numbers[count++] = 4;
        else if (strcmp(sentence + 7 * i, "five") == 0) numbers[count++] = 5;
        else if (strcmp(sentence + 7 * i, "six") == 0) numbers[count++] = 6;
        else if (strcmp(sentence + 7 * i, "seven") == 0) numbers[count++] = 7;
        else if (strcmp(sentence + 7 * i, "eight") == 0) numbers[count++] = 8;
        else if (strcmp(sentence + 7 * i, "nine") == 0) numbers[count++] = 9;
        else if (strcmp(sentence + 7 * i, "ten") == 0) numbers[count++] = 10;
        else if (strcmp(sentence + 7 * i, "eleven") == 0) numbers[count++] = 11;
        else if (strcmp(sentence + 7 * i, "twelve") == 0) numbers[count++] = 12;
        else if (strcmp(sentence + 7 * i, "thirteen") == 0) numbers[count++] = 13;
        else if (strcmp(sentence + 7 * i, "fourteen") == 0) numbers[count++] = 14;
        else if (strcmp(sentence + 7 * i, "fifteen") == 0) numbers[count++] = 15;
        else if (strcmp(sentence + 7 * i, "sixteen") == 0) numbers[count++] = 16;
        else if (strcmp(sentence + 7 * i, "seventeen") == 0) numbers[count++] = 17;
        else if (strcmp(sentence + 7 * i, "eighteen") == 0) numbers[count++] = 18;
        else if (strcmp(sentence + 7 * i, "nineteen") == 0) numbers[count++] = 19;
        else if (strcmp(sentence + 7 * i, "twenty") == 0) numbers[count++] = 20;
        else if (strcmp(sentence + 7 * i, "a") == 0 || strcmp(sentence + 7 * i, "both") == 0 || strcmp(sentence + 7 * i, "another") == 0 || strcmp(sentence + 7 * i, "first") == 0 || strcmp(sentence + 7 * i, "second") == 0 || strcmp(sentence + 7 * i, "third") == 0) numbers[count++] = 1;
    }
    
    if (count == 0) {
        printf("0\n");
        return 0;
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (numbers[i] > numbers[j]) {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }
    
    int password = 0;
    for (int i = 0; i < count; i++) {
        password = password * 100 + (numbers[i] * numbers[i]) % 100;
    }
    
    while (password >= 10 && password % 10 == 0) {
        password /= 10;
    }
    
    printf("%d\n", password);
    
    return 0;
}