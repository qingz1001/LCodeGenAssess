#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MAX_NUMS 20

int square_mod(int num) {
    return (num * num) % 100;
}

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    char sentence[MAX_LEN];
    char *words[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                     "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                     "eighteen", "nineteen", "twenty", "a", "both", "another", "first", "second", "third"};
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 1, 1, 2, 3};
    int nums[MAX_NUMS] = {0}, num_count = 0;

    fgets(sentence, MAX_LEN, stdin);
    sentence[strcspn(sentence, ".")] = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        sentence[i] = tolower(sentence[i]);
    }

    char *token = strtok(sentence, " ");
    while (token != NULL) {
        for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
            if (strcmp(token, words[i]) == 0) {
                nums[num_count++] = square_mod(values[i]);
                break;
            }
        }
        token = strtok(NULL, " ");
    }

    if (num_count == 0) {
        printf("0\n");
        return 0;
    }

    qsort(nums, num_count, sizeof(int), cmp);

    long long result = 0;
    for (int i = 0; i < num_count; i++) {
        result = result * 100 + nums[i];
    }

    printf("%lld\n", result);
    return 0;
}