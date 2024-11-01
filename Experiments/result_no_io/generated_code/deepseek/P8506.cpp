#include <stdio.h>
#include <string.h>

int is_title(char *line) {
    int i = 0;
    // Skip leading spaces
    while (line[i] == ' ') i++;
    // Check if the first non-space character is '#'
    if (line[i] != '#') return 0;
    i++;
    // Check if there is a space after '#'
    if (line[i] != ' ') return 0;
    // Skip spaces after '#'
    while (line[i] == ' ') i++;
    // Check if there is non-space content after the spaces
    if (line[i] == '\0' || line[i] == '\n') return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d\n", &n);
    char lines[10][101];
    int title_count = 0;

    for (int i = 0; i < n; i++) {
        fgets(lines[i], 101, stdin);
        if (is_title(lines[i])) {
            title_count++;
        }
    }

    printf("%d\n", title_count);
    return 0;
}