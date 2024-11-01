#include <stdio.h>
#include <string.h>

#define MAX_BUFFER 100000

void represent(int x, char *buffer, int *pos) {
    if(x == 0){
        buffer[*pos] = '0';
        (*pos)++;
        return;
    }
    
    int exponents[32], count = 0;
    for(int i = 31; i >= 0; i--){
        if(x & (1 << i)){
            exponents[count++] = i;
        }
    }
    
    for(int j = 0; j < count; j++){
        buffer[*pos] = '2';
        (*pos)++;
        buffer[*pos] = '(';
        (*pos)++;
        
        if(exponents[j] > 0){
            represent(exponents[j], buffer, pos);
        }
        else{
            buffer[*pos] = '0';
            (*pos)++;
        }
        
        buffer[*pos] = ')';
        (*pos)++;
        
        if(j < count - 1){
            buffer[*pos] = '+';
            (*pos)++;
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    
    char buffer[MAX_BUFFER];
    int pos = 0;
    
    represent(n, buffer, &pos);
    buffer[pos] = '\0';
    
    printf("%s\n", buffer);
    return 0;
}