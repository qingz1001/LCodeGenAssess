#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORDS 20
#define MAX_LEN 20

int is_number(char *word) {
    char *numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                       "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                       "eighteen", "nineteen", "twenty", "a", "both", "another", "first", "second", "third"};
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 1, 1, 2, 3};
    
    for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
        if (strcmp(word, numbers[i]) == 0) {
            return values[i];
        }
    }
    return 0;
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, int l, int r, long long *min) {
    if (l == r) {
        long long num = atoll(str);
        if (num < *min) {
            *min = num;
        }
    } else {
        for (int i = l; i <= r; i++) {
            swap((str + l), (str + i));
            permute(str, l + 1, r, min);
            swap((str + l), (str + i));
        }
    }
}

int main() {
    char word[MAX_LEN];
    char result[MAX_WORDS * 2 + 1] = {0};
    int count = 0;

    for (int i = 0; i < 6; i++) {
        scanf("%s", word);
        for (int j = 0; word[j]; j++) {
            word[j] = tolower(word[j]);
        }
        
        int num = is_number(word);
        if (num > 0) {
            int squared = (num * num) % 100;
            sprintf(result + count * 2, "%02d", squared);
            count++;
        }
    }

    if (count == 0) {
        printf("0\n");
        return 0;
    }

    while (result[0] == '0') {
        memmove(result, result + 1, strlen(result));
    }

    long long min = 9223372036854775807LL;  // Max value of long long
    permute(result, 0, strlen(result) - 1, &min);

    printf("%lld\n", min);

    return 0;
}