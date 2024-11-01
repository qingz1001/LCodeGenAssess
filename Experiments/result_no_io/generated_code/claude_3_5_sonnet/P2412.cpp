#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_LENGTH 16

char words[MAX_WORDS][MAX_LENGTH];
int N, M;

int compare_words(const char *a, const char *b) {
    int i = 0;
    while (a[i] && b[i]) {
        char ca = tolower(a[i]);
        char cb = tolower(b[i]);
        if (ca != cb) return ca - cb;
        i++;
    }
    return a[i] - b[i];
}

void find_max_word(int x, int y) {
    int max_index = x - 1;
    for (int i = x; i < y; i++) {
        if (compare_words(words[i], words[max_index]) >= 0) {
            max_index = i;
        }
    }
    printf("%s\n", words[max_index]);
}

int main() {
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < N; i++) {
        scanf("%s", words[i]);
    }
    
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        find_max_word(x - 1, y);
    }
    
    return 0;
}