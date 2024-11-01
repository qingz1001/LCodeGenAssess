#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ELEMENTS 200
#define MAX_LENGTH 10
#define MAX_SEQUENCE 200000

bool isPrefix(const char *s, const char *prefix, int length) {
    return strncmp(s, prefix, length) == 0;
}

int main() {
    char elements[MAX_ELEMENTS][MAX_LENGTH + 1];
    int elementCount = 0;
    char sequence[MAX_SEQUENCE + 1];
    int sequenceLength = 0;

    // Read elements
    while (1) {
        char buffer[MAX_LENGTH + 1];
        scanf("%s", buffer);
        if (buffer[0] == '.') {
            break;
        }
        strcpy(elements[elementCount++], buffer);
    }

    // Read sequence
    char ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            continue;
        }
        sequence[sequenceLength++] = ch;
    }
    sequence[sequenceLength] = '\0';

    int maxLength = 0;
    int i = 0;
    while (i < sequenceLength) {
        bool found = false;
        for (int j = 0; j < elementCount; j++) {
            int elementLength = strlen(elements[j]);
            if (i + elementLength <= sequenceLength && isPrefix(sequence + i, elements[j], elementLength)) {
                i += elementLength;
                found = true;
                break;
            }
        }
        if (!found) {
            break;
        }
        maxLength = i;
    }

    printf("%d\n", maxLength);
    return 0;
}