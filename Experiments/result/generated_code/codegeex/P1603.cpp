#include <stdio.h>
#include <string.h>

int is_number(char *word) {
    if (strcmp(word, "one") == 0) return 1;
    if (strcmp(word, "two") == 0) return 2;
    if (strcmp(word, "three") == 0) return 3;
    if (strcmp(word, "four") == 0) return 4;
    if (strcmp(word, "five") == 0) return 5;
    if (strcmp(word, "six") == 0) return 6;
    if (strcmp(word, "seven") == 0) return 7;
    if (strcmp(word, "eight") == 0) return 8;
    if (strcmp(word, "nine") == 0) return 9;
    if (strcmp(word, "ten") == 0) return 10;
    if (strcmp(word, "eleven") == 0) return 11;
    if (strcmp(word, "twelve") == 0) return 12;
    if (strcmp(word, "thirteen") == 0) return 13;
    if (strcmp(word, "fourteen") == 0) return 14;
    if (strcmp(word, "fifteen") == 0) return 15;
    if (strcmp(word, "sixteen") == 0) return 16;
    if (strcmp(word, "seventeen") == 0) return 17;
    if (strcmp(word, "eighteen") == 0) return 18;
    if (strcmp(word, "nineteen") == 0) return 19;
    if (strcmp(word, "twenty") == 0) return 20;
    if (strcmp(word, "a") == 0) return 1;
    if (strcmp(word, "both") == 0) return 2;
    if (strcmp(word, "another") == 0) return 1;
    if (strcmp(word, "first") == 0) return 1;
    if (strcmp(word, "second") == 0) return 2;
    if (strcmp(word, "third") == 0) return 3;
    return 0;
}

int main() {
    char sentence[100];
    scanf("%[^\n]", sentence); // 读取整行输入
    char *token = strtok(sentence, " ");
    int numbers[5];
    int count = 0;
    
    while (token != NULL) {
        int num = is_number(token);
        if (num > 0) {
            numbers[count++] = num;
        }
        token = strtok(NULL, " ");
    }
    
    int squared[5];
    for (int i = 0; i < count; i++) {
        squared[i] = (numbers[i] * numbers[i]) % 100;
    }
    
    // 按数位排序
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (squared[i] > squared[j]) {
                int temp = squared[i];
                squared[i] = squared[j];
                squared[j] = temp;
            }
        }
    }
    
    // 组合成一个新数
    int new_number = 0;
    for (int i = 0; i < count; i++) {
        new_number = new_number * 10 + squared[i] % 10;
        new_number = new_number * 10 + squared[i] / 10;
    }
    
    // 去除前导0
    while (new_number % 10 == 0 && new_number > 0) {
        new_number /= 10;
    }
    
    printf("%d\n", new_number);
    return 0;
}