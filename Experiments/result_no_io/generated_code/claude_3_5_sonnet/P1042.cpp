#include <stdio.h>
#include <string.h>

#define MAX_LEN 26
#define MAX_LINES 2501

void process_game(int score_limit) {
    int w = 0, l = 0;
    for (int i = 0; i < MAX_LINES; i++) {
        char line[MAX_LEN];
        if (fgets(line, MAX_LEN, stdin) == NULL) break;
        
        for (int j = 0; j < strlen(line); j++) {
            if (line[j] == 'E') return;
            if (line[j] == 'W') w++;
            if (line[j] == 'L') l++;
            
            if ((w >= score_limit || l >= score_limit) && abs(w - l) >= 2) {
                printf("%d:%d\n", w, l);
                w = 0;
                l = 0;
            }
        }
    }
    if (w > 0 || l > 0) {
        printf("%d:%d\n", w, l);
    }
}

int main() {
    process_game(11);
    printf("\n");
    rewind(stdin);
    process_game(21);
    return 0;
}