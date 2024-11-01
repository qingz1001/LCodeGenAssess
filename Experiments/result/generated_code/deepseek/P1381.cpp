#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_M 100000
#define MAX_WORD_LEN 10

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return strcmp(((WordCount *)a)->word, ((WordCount *)b)->word);
}

int binarySearch(WordCount *words, int n, const char *target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(words[mid].word, target);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    int n, m;
    char wordsToLearn[MAX_N][MAX_WORD_LEN + 1];
    char article[MAX_M][MAX_WORD_LEN + 1];
    WordCount wordCounts[MAX_N];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", wordsToLearn[i]);
        strcpy(wordCounts[i].word, wordsToLearn[i]);
        wordCounts[i].count = 0;
    }

    qsort(wordCounts, n, sizeof(WordCount), compare);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%s", article[i]);
    }

    int maxCount = 0, minLength = m + 1;
    int left = 0, right = 0;
    int currentCount = 0;
    int seen[MAX_N] = {0};

    while (right < m) {
        int index = binarySearch(wordCounts, n, article[right]);
        if (index != -1) {
            if (seen[index] == 0) {
                currentCount++;
            }
            seen[index]++;
        }

        while (currentCount == n) {
            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                maxCount = currentCount;
            }
            int leftIndex = binarySearch(wordCounts, n, article[left]);
            if (leftIndex != -1) {
                seen[leftIndex]--;
                if (seen[leftIndex] == 0) {
                    currentCount--;
                }
            }
            left++;
        }
        right++;
    }

    printf("%d\n%d\n", maxCount, minLength);

    return 0;
}