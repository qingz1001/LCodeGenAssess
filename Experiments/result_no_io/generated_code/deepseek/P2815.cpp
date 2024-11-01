#include <stdio.h>
#include <string.h>

void compressIPv6(char *ipv6) {
    char result[40];
    char *parts[8];
    int i, j, zero_start = -1, zero_len = 0;

    // Split the IPv6 address into 8 parts
    parts[0] = strtok(ipv6, ":");
    for (i = 1; i < 8; i++) {
        parts[i] = strtok(NULL, ":");
    }

    // Remove leading zeros from each part
    for (i = 0; i < 8; i++) {
        for (j = 0; parts[i][j] == '0' && parts[i][j + 1] != '\0'; j++) {
            memmove(&parts[i][j], &parts[i][j + 1], strlen(parts[i]) - j);
        }
    }

    // Find the longest sequence of zero parts
    for (i = 0; i < 8; i++) {
        if (strcmp(parts[i], "0") == 0) {
            int len = 0;
            while (i + len < 8 && strcmp(parts[i + len], "0") == 0) {
                len++;
            }
            if (len > zero_len) {
                zero_len = len;
                zero_start = i;
            }
            i += len;
        }
    }

    // Construct the compressed IPv6 address
    result[0] = '\0';
    for (i = 0; i < 8; i++) {
        if (i == zero_start) {
            strcat(result, "::");
            i += zero_len - 1;
        } else {
            if (strlen(result) > 0 && strcmp(result + strlen(result) - 2, "::") != 0) {
                strcat(result, ":");
            }
            strcat(result, parts[i]);
        }
    }

    printf("%s\n", result);
}

int main() {
    char ipv6[40];
    scanf("%s", ipv6);
    compressIPv6(ipv6);
    return 0;
}