#include <stdio.h>

int main() {
    int notes[8];
    for (int i = 0; i < 8; i++) {
        scanf("%d", &notes[i]);
    }

    int ascending = 1;
    int descending = 1;

    for (int i = 1; i < 8; i++) {
        if (notes[i] > notes[i - 1]) {
            descending = 0;
        } else if (notes[i] < notes[i - 1]) {
            ascending = 0;
        }
    }

    if (ascending) {
        printf("ascending\n");
    } else if (descending) {
        printf("descending\n");
    } else {
        printf("mixed\n");
    }

    return 0;
}