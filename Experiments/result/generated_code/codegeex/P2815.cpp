#include <stdio.h>
#include <string.h>

void compressIPv6(char *ipv6) {
    int len = strlen(ipv6);
    int i, j, k;
    int longestZeroSeqStart = -1, longestZeroSeqLen = 0;
    int currentZeroSeqStart = -1, currentZeroSeqLen = 0;
    int doubleColonUsed = 0;

    for (i = 0; i < len; i += 5) {
        if (ipv6[i] == '0' && ipv6[i+1] == '0' && ipv6[i+2] == '0' && ipv6[i+3] == '0') {
            if (currentZeroSeqStart == -1) {
                currentZeroSeqStart = i;
            }
            currentZeroSeqLen++;
        } else {
            if (currentZeroSeqLen > longestZeroSeqLen) {
                longestZeroSeqStart = currentZeroSeqStart;
                longestZeroSeqLen = currentZeroSeqLen;
            }
            currentZeroSeqStart = -1;
            currentZeroSeqLen = 0;
        }
    }

    if (currentZeroSeqLen > longestZeroSeqLen) {
        longestZeroSeqStart = currentZeroSeqStart;
        longestZeroSeqLen = currentZeroSeqLen;
    }

    if (longestZeroSeqLen > 0) {
        doubleColonUsed = 1;
        for (i = 0; i < len; i += 5) {
            if (i >= longestZeroSeqStart && i < longestZeroSeqStart + longestZeroSeqLen * 5) {
                if (i == longestZeroSeqStart) {
                    ipv6[i] = ':';
                    ipv6[i+1] = ':';
                }
                for (j = i; j < i + 5; j++) {
                    ipv6[j] = '0';
                }
            }
        }
    }

    for (i = 0, j = 0; i < len; i++) {
        if (ipv6[i] != '0') {
            ipv6[j++] = ipv6[i];
        }
    }
    while (j < len) {
        ipv6[j++] = ':';
    }

    for (i = 0; i < len; i++) {
        if (ipv6[i] == ':') {
            for (j = i + 1; j < len; j++) {
                if (ipv6[j] != ':') {
                    ipv6[i] = ipv6[j];
                    ipv6[j] = ':';
                    break;
                }
            }
        }
    }

    for (i = 0; i < len; i++) {
        if (ipv6[i] == ':') {
            for (j = i + 1; j < len; j++) {
                if (ipv6[j] != ':') {
                    ipv6[i] = ipv6[j];
                    ipv6[j] = ':';
                    break;
                }
            }
        }
    }

    if (doubleColonUsed) {
        for (i = 0; i < len; i++) {
            if (ipv6[i] == ':') {
                for (j = i + 1; j < len; j++) {
                    if (ipv6[j] != ':') {
                        ipv6[i] = ipv6[j];
                        ipv6[j] = ':';
                        break;
                    }
                }
            }
        }
    }

    for (i = 0; i < len; i++) {
        if (ipv6[i] == ':') {
            for (j = i + 1; j < len; j++) {
                if (ipv6[j] != ':') {
                    ipv6[i] = ipv6[j];
                    ipv6[j] = ':';
                    break;
                }
            }
        }
    }

    ipv6[len] = '\0';
}

int main() {
    char ipv6[40];
    scanf("%s", ipv6);
    compressIPv6(ipv6);
    printf("%s\n", ipv6);
    return 0;
}