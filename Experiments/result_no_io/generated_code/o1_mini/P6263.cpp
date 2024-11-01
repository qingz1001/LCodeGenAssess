#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    char s[55];
    scanf("%s", s);
    
    int mapping[256];
    for(int i=0;i<256;i++) mapping[i]=-1;
    
    // Left Hand
    // Little finger
    mapping['1'] = 0; mapping['Q'] = 0; mapping['A'] = 0; mapping['Z'] = 0;
    // Ring finger
    mapping['2'] = 1; mapping['W'] = 1; mapping['S'] = 1; mapping['X'] = 1;
    // Middle finger
    mapping['3'] = 2; mapping['E'] = 2; mapping['D'] = 2; mapping['C'] = 2;
    // Index finger
    mapping['4'] = 3; mapping['5'] = 3; mapping['R'] = 3; mapping['T'] = 3;
    mapping['F'] = 3; mapping['G'] = 3; mapping['V'] = 3; mapping['B'] = 3;
    
    // Right Hand
    // Index finger
    mapping['6'] = 4; mapping['7'] = 4; mapping['Y'] = 4; mapping['U'] = 4;
    mapping['H'] = 4; mapping['J'] = 4; mapping['N'] = 4; mapping['M'] = 4;
    // Middle finger
    mapping['8'] = 5; mapping['I'] = 5; mapping['K'] = 5;
    // Ring finger
    mapping['9'] = 6; mapping['O'] = 6; mapping['L'] = 6;
    // Little finger
    mapping['0'] = 7; mapping['P'] = 7;
    
    // Handle lowercase letters
    for(int i=0;i<256;i++){
        if(mapping[i] != -1 && 'a' <= i && i <= 'z'){
            mapping[toupper(i)] = mapping[i];
        }
    }
    
    int counts[8] = {0};
    int len = strlen(s);
    for(int i=0;i<len;i++){
        char c = toupper(s[i]);
        if(mapping[c] != -1){
            counts[mapping[c]]++;
        }
    }
    
    for(int i=0;i<8;i++){
        printf("%d\n", counts[i]);
    }
}