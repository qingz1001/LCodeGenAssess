#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plate[9];
    scanf("%s", plate);
    
    int is_local = (strncmp(plate, "MDA", 3) == 0);
    
    int tail_number = -1;
    for (int i = 7; i >= 3; i--) {
        if (isdigit(plate[i])) {
            tail_number = plate[i] - '0';
            break;
        }
    }
    
    for (int day = 1; day <= 5; day++) {
        if (!is_local) {
            printf("1");
        } else {
            switch (day) {
                case 1:
                    printf("%d", (tail_number == 1 || tail_number == 9));
                    break;
                case 2:
                    printf("%d", (tail_number == 2 || tail_number == 8));
                    break;
                case 3:
                    printf("%d", (tail_number == 3 || tail_number == 7));
                    break;
                case 4:
                    printf("%d", (tail_number == 4 || tail_number == 6));
                    break;
                case 5:
                    printf("%d", (tail_number == 5 || tail_number == 0));
                    break;
            }
        }
        
        if (day < 5) {
            printf(" ");
        }
    }
    
    printf("\n");
    
    return 0;
}