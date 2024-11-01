#include <stdio.h>
#include <string.h>

char frame[5][80];

void add_peter_pan(int pos) {
    frame[0][pos] = '.';
    frame[1][pos] = '.';
    frame[2][pos] = '#';
    frame[3][pos] = '.';
    frame[4][pos] = '.';
    
    frame[0][pos+1] = '.';
    frame[1][pos+1] = '#';
    frame[2][pos+1] = '.';
    frame[3][pos+1] = '#';
    frame[4][pos+1] = '.';
    
    frame[0][pos+2] = '#';
    frame[1][pos+2] = '.';
    frame[2][pos+2] = '.';
    frame[3][pos+2] = '.';
    frame[4][pos+2] = '#';
}

void add_wendy(int pos) {
    frame[0][pos] = '.';
    frame[1][pos] = '.';
    frame[2][pos] = '*';
    frame[3][pos] = '.';
    frame[4][pos] = '.';
    
    frame[0][pos+1] = '.';
    frame[1][pos+1] = '*';
    frame[2][pos+1] = '.';
    frame[3][pos+1] = '*';
    frame[4][pos+1] = '.';
    
    frame[0][pos+2] = '*';
    frame[1][pos+2] = '.';
    frame[2][pos+2] = '.';
    frame[3][pos+2] = '.';
    frame[4][pos+2] = '*';
}

int main() {
    char word[16];
    scanf("%s", word);
    int len = strlen(word);
    
    memset(frame, '.', sizeof(frame));
    
    for(int i = 0; i < len; i++) {
        int pos = 4*i;
        if((i+1) % 3 == 0) {
            add_wendy(pos);
        } else {
            add_peter_pan(pos);
        }
        frame[2][pos+2] = word[i];
    }
    
    for(int i = 0; i < 5; i++) {
        frame[i][4*len+1] = '\0';
        printf("%s\n", frame[i]);
    }
    
    return 0;
}