#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1001

bool isValidMessage(char* message, char* target) {
    char* at = strchr(message, '@');
    if (at == NULL) return false;
    
    char* nextAt = strchr(at + 1, '@');
    if (nextAt != NULL) return false;
    
    return strncmp(at + 1, target, strlen(target)) == 0;
}

int main() {
    char line[MAX_LINE_LENGTH];
    char target[MAX_LINE_LENGTH];
    char firstSpeaker[MAX_LINE_LENGTH];
    int lineCount = 0;
    bool queueBroken = false;
    char breaker[MAX_LINE_LENGTH];

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%[^:]: @%s", firstSpeaker, target);

    while (fgets(line, sizeof(line), stdin) && line[0] != '\n') {
        lineCount++;
        char speaker[MAX_LINE_LENGTH];
        char message[MAX_LINE_LENGTH];
        sscanf(line, "%[^:]: %[^\n]", speaker, message);

        if (!queueBroken && !isValidMessage(message, target)) {
            queueBroken = true;
            strcpy(breaker, speaker);
        }

        if (strcmp(speaker, target) == 0) {
            printf("Successful @%s attempt\n", target);
            return 0;
        }
    }

    printf("Unsuccessful @%s attempt\n", target);
    if (queueBroken) {
        printf("%d\n%s\n", lineCount, breaker);
    } else {
        printf("%d\nGood Queue Shape\n", lineCount);
    }

    return 0;
}