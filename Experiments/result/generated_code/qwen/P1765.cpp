#include <stdio.h>
#include <string.h>

int main() {
    char sentence[201];
    int count = 0;

    scanf("%s", sentence);

    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ' ') {
            count++;
        } else {
            switch (sentence[i]) {
                case 'a': case 'b': case 'c':
                    count += 1;
                    break;
                case 'd': case 'e': case 'f':
                    count += 2;
                    break;
                case 'g': case 'h': case 'i':
                    count += 3;
                    break;
                case 'j': case 'k': case 'l':
                    count += 4;
                    break;
                case 'm': case 'n': case 'o':
                    count += 5;
                    break;
                case 'p': case 'q': case 'r': case 's':
                    count += 6;
                    break;
                case 't': case 'u': case 'v':
                    count += 7;
                    break;
                case 'w': case 'x': case 'y': case 'z':
                    count += 8;
                    break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}