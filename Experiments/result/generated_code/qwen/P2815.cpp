#include <stdio.h>
#include <string.h>

void compressIPv6(char *input, char *output) {
    int groups[8];
    int count = 0;
    char temp[5];

    // Split the input string into groups of 4 characters
    for (int i = 0; i < 32; i += 4) {
        strncpy(temp, input + i, 4);
        temp[4] = '\0';
        groups[count++] = atoi(temp, 16);
    }

    int maxZeroGroup = -1;
    int zeroCount = 0;

    // Find the longest sequence of zeros
    for (int i = 0; i < 8; i++) {
        if (groups[i] == 0) {
            zeroCount++;
            if (zeroCount > maxZeroGroup) {
                maxZeroGroup = zeroCount;
                zeroCount = 0;
            }
        } else {
            zeroCount = 0;
        }
    }

    // Construct the output string
    int pos = 0;
    for (int i = 0; i < 8; i++) {
        if (groups[i] != 0 || maxZeroGroup == 0) {
            if (pos > 0 && pos < strlen(output)) {
                output[pos++] = ':';
            }
            sprintf(temp, "%x", groups[i]);
            strcpy(output + pos, temp);
            pos += strlen(temp);
        } else {
            if (maxZeroGroup == 1) {
                if (pos > 0 && pos < strlen(output)) {
                    output[pos++] = ':';
                }
                output[pos++] = '0';
            }
            maxZeroGroup--;
        }
    }
}

int main() {
    char input[40], output[40];
    scanf("%s", input);
    compressIPv6(input, output);
    printf("%s\n", output);
    return 0;
}