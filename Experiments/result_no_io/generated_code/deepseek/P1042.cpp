#include <stdio.h>
#include <string.h>

#define MAX_LEN 2500 * 25 + 1

void process_scores(char *record, int score_limit) {
    int w_score = 0, l_score = 0;
    for (int i = 0; record[i] != '\0' && record[i] != 'E'; i++) {
        if (record[i] == 'W') w_score++;
        else if (record[i] == 'L') l_score++;

        if ((w_score >= score_limit || l_score >= score_limit) && abs(w_score - l_score) >= 2) {
            printf("%d:%d\n", w_score, l_score);
            w_score = 0;
            l_score = 0;
        }
    }
    printf("%d:%d\n", w_score, l_score);
}

int main() {
    char record[MAX_LEN];
    char line[26];
    int len = 0;

    while (fgets(line, sizeof(line), stdin)) {
        int line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') line[line_len - 1] = '\0';
        strcpy(record + len, line);
        len += line_len - 1;
        if (strstr(line, "E") != NULL) break;
    }

    process_scores(record, 11);
    printf("\n");
    process_scores(record, 21);

    return 0;
}