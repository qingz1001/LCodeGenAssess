#include <stdio.h>
#include <string.h>

int main() {
    char str[256];
    scanf("%s", str);
    
    int len = strlen(str);
    int boy_count = 0, girl_count = 0;
    
    for (int i = len - 1; i >= 0; i--) {
        if (i >= 2 && str[i] == 'y' && str[i-1] == 'o' && str[i-2] == 'b') {
            boy_count++;
            i -= 2;
        } else if (i >= 3 && str[i] == 'l' && str[i-1] == 'r' && str[i-2] == 'i' && str[i-3] == 'g') {
            girl_count++;
            i -= 3;
        }
    }
    
    printf("%d\n%d\n", boy_count, girl_count);
    
    return 0;
}