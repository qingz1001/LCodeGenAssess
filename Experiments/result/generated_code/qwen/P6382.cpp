#include <stdio.h>
#include <string.h>

int main() {
    char license_plate[9];
    scanf("%s", license_plate);

    int is_local = (license_plate[0] == 'M' && license_plate[1] == 'D' && license_plate[2] == 'A');
    int last_digit = license_plate[7] - '0';

    int result[5] = {0, 0, 0, 0, 0};

    if (!is_local) {
        for (int i = 0; i < 5; i++) {
            result[i] = 1;
        }
    } else {
        switch (last_digit % 10) {
            case 1:
                result[0] = 1;
                result[4] = 1;
                break;
            case 2:
                result[1] = 1;
                result[3] = 1;
                break;
            case 3:
                result[2] = 1;
                result[3] = 1;
                break;
            case 4:
                result[1] = 1;
                result[4] = 1;
                break;
            case 5:
                result[4] = 1;
                break;
            case 6:
                result[1] = 1;
                break;
            case 7:
                result[2] = 1;
                result[3] = 1;
                break;
            case 8:
                result[1] = 1;
                result[3] = 1;
                break;
            case 9:
                result[0] = 1;
                result[4] = 1;
                break;
        }
    }

    for (int i = 0; i < 5; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}