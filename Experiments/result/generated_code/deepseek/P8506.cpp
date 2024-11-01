#include <stdio.h>
#include <string.h>

int is_title(char *line) {
    int i = 0;
    // Skip leading whitespace
    while (line[i] == ' ') i++;
    // Check if the first non-whitespace character is '#'
    if (line[i] != '#') return 0;
    i++;
    // Check if the next character is a space
    if (line[i] != ' ') return 0;
    // Skip spaces after '#'
    while (line[i] == ' ') i++;
    // Check if there is non-whitespace content after the spaces
    if (line[i] == '\0' || line[i] == '\n') return 0;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // Consume the newline character after the integer

    int count = 0;
    char line[101];
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);
        if (is_title(line)) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}