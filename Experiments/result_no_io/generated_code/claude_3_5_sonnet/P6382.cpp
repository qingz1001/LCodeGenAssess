#include <stdio.h>
#include <string.h>

int main() {
    char plate[9];
    scanf("%s", plate);
    
    int is_local = (strncmp(plate, "MDA", 3) == 0);
    
    int tail_num = -1;
    for(int i = 7; i >= 3; i--) {
        if(plate[i] >= '0' && plate[i] <= '9') {
            tail_num = plate[i] - '0';
            break;
        }
    }
    
    for(int day = 1; day <= 5; day++) {
        if(!is_local) {
            printf("1");
        } else {
            switch(day) {
                case 1:
                    printf("%d", (tail_num == 1 || tail_num == 9));
                    break;
                case 2:
                    printf("%d", (tail_num == 2 || tail_num == 8));
                    break;
                case 3:
                    printf("%d", (tail_num == 3 || tail_num == 7));
                    break;
                case 4:
                    printf("%d", (tail_num == 4 || tail_num == 6));
                    break;
                case 5:
                    printf("%d", (tail_num == 5 || tail_num == 0));
                    break;
            }
        }
    }
    
    return 0;
}