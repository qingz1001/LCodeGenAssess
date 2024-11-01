#include <stdio.h>
#include <string.h>

int main() {
    char code[256];
    int a = 0, b = 0, c = 0;
    
    fgets(code, sizeof(code), stdin);
    
    char *token = strtok(code, ";");
    while (token != NULL) {
        char var = token[0];
        char value = token[3];
        
        int *target;
        switch (var) {
            case 'a': target = &a; break;
            case 'b': target = &b; break;
            case 'c': target = &c; break;
        }
        
        if (value >= '0' && value <= '9') {
            *target = value - '0';
        } else {
            switch (value) {
                case 'a': *target = a; break;
                case 'b': *target = b; break;
                case 'c': *target = c; break;
            }
        }
        
        token = strtok(NULL, ";");
    }
    
    printf("%d %d %d\n", a, b, c);
    
    return 0;
}