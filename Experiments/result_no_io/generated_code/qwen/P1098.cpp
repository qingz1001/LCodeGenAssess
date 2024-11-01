#include <stdio.h>
#include <string.h>

void expand(char *str, int p1, int p2, int p3) {
    char temp[100];
    int len = strlen(str);
    int j = 0;
    
    for (int i = 0; i < len; ) {
        if (i + 2 < len && str[i + 2] == '-' && 
            ((str[i] >= 'a' && str[i] <= 'z' && str[i + 2] > str[i]) || 
             (str[i] >= 'A' && str[i] <= 'Z' && str[i + 2] > str[i]))) {
            
            int start = str[i];
            int end = str[i + 2];
            i += 3;
            
            if (p3 == 2) {
                while (end > start) {
                    for (int k = 0; k < p2; k++) {
                        temp[j++] = end--;
                    }
                }
            } else {
                for (char c = start + 1; c < end; c++) {
                    for (int k = 0; k < p2; k++) {
                        temp[j++] = c;
                    }
                }
            }
        } else {
            temp[j++] = str[i++];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

int main() {
    int p1, p2, p3;
    scanf("%d %d %d", &p1, &p2, &p3);
    getchar(); // consume newline character
    
    char str[101];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // remove newline character at the end
    
    expand(str, p1, p2, p3);
    
    printf("%s\n", str);
    return 0;
}