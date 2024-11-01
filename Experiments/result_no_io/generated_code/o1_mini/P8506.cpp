#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int n, count=0;
    scanf("%d", &n);
    getchar(); // consume newline after number
    char line[105];
    while(n--){
        if(fgets(line, sizeof(line), stdin) == NULL){
            break;
        }
        int len = strlen(line);
        if(len >0 && line[len-1]=='\n'){
            line[len-1] = '\0';
            len--;
        }
        int i=0;
        // Skip leading spaces
        while(i<len && line[i]==' ') i++;
        if(i < len && line[i] == '#'){
            i++;
            // Must have at least one space after '#'
            if(i < len && line[i] == ' '){
                // Skip all spaces after '#'
                while(i < len && line[i] == ' ') i++;
                // Check if there's at least one non-space character
                if(i < len && line[i] != ' '){
                    count++;
                }
            }
        }
    }
    printf("%d\n", count);
    return 0;
}