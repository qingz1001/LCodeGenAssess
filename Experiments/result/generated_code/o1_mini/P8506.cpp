#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int n, count=0;
    scanf("%d", &n);
    getchar(); // consume newline after number
    char line[105];
    for(int i=0;i<n;i++){
        if(!fgets(line, sizeof(line), stdin)){
            break;
        }
        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;
        int j=0;
        // Skip leading spaces
        while(line[j] && isspace(line[j])) j++;
        if(line[j] != '#') continue;
        j++;
        // There must be at least one space after '#'
        if(!isspace(line[j])) continue;
        // Skip spaces after '#'
        while(line[j] && isspace(line[j])) j++;
        // There must be at least one non-space character
        if(line[j] == '\0') continue;
        count++;
    }
    printf("%d\n", count);
    return 0;
}