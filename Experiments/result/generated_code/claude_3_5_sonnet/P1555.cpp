#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 32

long long bin_to_dec(char* bin) {
    long long result = 0;
    for (int i = 0; bin[i]; i++) {
        result = result * 2 + (bin[i] - '0');
    }
    return result;
}

long long tri_to_dec(char* tri) {
    long long result = 0;
    for (int i = 0; tri[i]; i++) {
        result = result * 3 + (tri[i] - '0');
    }
    return result;
}

void dec_to_bin(long long num, char* bin) {
    int i = 0;
    while (num > 0) {
        bin[i++] = (num % 2) + '0';
        num /= 2;
    }
    bin[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = bin[j];
        bin[j] = bin[i - j - 1];
        bin[i - j - 1] = temp;
    }
}

void dec_to_tri(long long num, char* tri) {
    int i = 0;
    while (num > 0) {
        tri[i++] = (num % 3) + '0';
        num /= 3;
    }
    tri[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = tri[j];
        tri[j] = tri[i - j - 1];
        tri[i - j - 1] = temp;
    }
}

int main() {
    char bin[MAX_LEN], tri[MAX_LEN];
    scanf("%s", bin);
    scanf("%s", tri);

    int bin_len = strlen(bin);
    int tri_len = strlen(tri);

    for (long long i = 0; i <= 1000000000; i++) {
        char test_bin[MAX_LEN], test_tri[MAX_LEN];
        dec_to_bin(i, test_bin);
        dec_to_tri(i, test_tri);

        int bin_diff = 0, tri_diff = 0;
        if (strlen(test_bin) == bin_len) {
            for (int j = 0; j < bin_len; j++) {
                if (test_bin[j] != bin[j]) bin_diff++;
            }
        }
        if (strlen(test_tri) == tri_len) {
            for (int j = 0; j < tri_len; j++) {
                if (test_tri[j] != tri[j]) tri_diff++;
            }
        }

        if (bin_diff <= 1 && tri_diff <= 1) {
            printf("%lld\n", i);
            return 0;
        }
    }

    return 0;
}