#include <stdio.h>
#include <string.h>

void compressIPv6(char *ipv6) {
    char parts[8][5];
    int i, j;
    int zero_start = -1, zero_length = 0, max_zero_start = -1, max_zero_length = 0;

    // Split the IPv6 address into 8 parts
    for (i = 0, j = 0; i < 8; i++, j += 5) {
        strncpy(parts[i], ipv6 + j, 4);
        parts[i][4] = '\0';
    }

    // Remove leading zeros and find the longest sequence of zeros
    for (i = 0; i < 8; i++) {
        char *part = parts[i];
        while (*part == '0' && *(part + 1) == '0') {
            memmove(part, part + 1, strlen(part));
        }
        if (*part == '0') {
            memmove(part, part + 1, strlen(part));
        }

        if (strcmp(parts[i], "0") == 0) {
            if (zero_start == -1) {
                zero_start = i;
            }
            zero_length++;
        } else {
            if (zero_length > max_zero_length) {
                max_zero_length = zero_length;
                max_zero_start = zero_start;
            }
            zero_start = -1;
            zero_length = 0;
        }
    }

    // Check the last sequence of zeros
    if (zero_length > max_zero_length) {
        max_zero_length = zero_length;
        max_zero_start = zero_start;
    }

    // Print the compressed IPv6 address
    for (i = 0; i < 8; i++) {
        if (i == max_zero_start && max_zero_length > 1) {
            if (i == 0) {
                printf("::");
            } else {
                printf(":");
            }
            i += max_zero_length - 1;
        } else {
            printf("%s", parts[i]);
            if (i < 7 && !(max_zero_start == 7 && max_zero_length > 1)) {
                printf(":");
            }
        }
    }
    printf("\n");
}

int main() {
    char ipv6[40];
    scanf("%s", ipv6);
    compressIPv6(ipv6);
    return 0;
}