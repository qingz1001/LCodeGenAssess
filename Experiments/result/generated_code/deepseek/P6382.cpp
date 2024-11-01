#include <stdio.h>
#include <string.h>

int main() {
    char plate[9];
    scanf("%s", plate);

    int isLocal = strncmp(plate, "MDA", 3) == 0;
    int lastDigit = -1;

    for (int i = 7; i >= 3; i--) {
        if (plate[i] >= '0' && plate[i] <= '9') {
            lastDigit = plate[i] - '0';
            break;
        }
    }

    int restrictions[5] = {0};

    if (!isLocal) {
        for (int i = 0; i < 5; i++) {
            restrictions[i] = 1;
        }
    } else {
        switch (lastDigit) {
            case 1:
            case 9:
                restrictions[0] = 1;
                break;
            case 2:
            case 8:
                restrictions[1] = 1;
                break;
            case 3:
            case 7:
                restrictions[2] = 1;
                break;
            case 4:
            case 6:
                restrictions[3] = 1;
                break;
            case 5:
            case 0:
                restrictions[4] = 1;
                break;
        }
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", restrictions[i]);
    }
    printf("\n");

    return 0;
}