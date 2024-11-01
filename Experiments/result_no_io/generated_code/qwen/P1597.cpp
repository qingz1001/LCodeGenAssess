#include <stdio.h>
#include <string.h>

int main() {
    char code[256];
    int a = 0, b = 0, c = 0;
    
    fgets(code, sizeof(code), stdin);
    
    for (int i = 0; i < strlen(code); ++i) {
        if (code[i] == 'a') a = 1;
        else if (code[i] == 'b') b = 1;
        else if (code[i] == 'c') c = 1;
        
        if (code[i + 3] >= '0' && code[i + 3] <= '9') {
            switch (code[i]) {
                case 'a': a = code[i + 3] - '0'; break;
                case 'b': b = code[i + 3] - '0'; break;
                case 'c': c = code[i + 3] - '0'; break;
            }
            i += 4; // Skip the rest of the assignment statement
        } else {
            switch (code[i + 3]) {
                case 'a': 
                    switch (code[i]) {
                        case 'a': a = a; break;
                        case 'b': a = b; break;
                        case 'c': a = c; break;
                    }
                    break;
                case 'b': 
                    switch (code[i]) {
                        case 'a': b = a; break;
                        case 'b': b = b; break;
                        case 'c': b = c; break;
                    }
                    break;
                case 'c': 
                    switch (code[i]) {
                        case 'a': c = a; break;
                        case 'b': c = b; break;
                        case 'c': c = c; break;
                    }
                    break;
            }
            i += 4; // Skip the rest of the assignment statement
        }
    }
    
    printf("%d %d %d\n", a, b, c);
    
    return 0;
}