#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_X 10000001

char flags[MAX_X];
unsigned long long sum = 0;

// Fast input buffer
#define BUFFER_SIZE 1 << 24
char buffer[BUFFER_SIZE];
size_t data_size, data_pos;

// Function to load data into buffer
void load_buffer() {
    data_size = fread(buffer, 1, BUFFER_SIZE, stdin);
    data_pos = 0;
}

// Function to get next character
char next_char() {
    if (data_pos >= data_size) {
        load_buffer();
        if (data_size == 0) return EOF;
    }
    return buffer[data_pos++];
}

// Function to read next integer
int read_int(int *number) {
    int c;
    *number = 0;
    // Skip non-digit characters
    do {
        c = next_char();
        if (c == EOF) return 0;
    } while (!isdigit(c));
    // Read number
    while (isdigit(c)) {
        *number = (*number) * 10 + (c - '0');
        c = next_char();
    }
    return 1;
}

int main(){
    load_buffer();
    int n;
    if(!read_int(&n)) return 0;
    int x, t;
    for(int i=0;i<n;i++){
        if(!read_int(&x)) break;
        if(!read_int(&t)) break;
        if(t >1 && !flags[x]){
            sum += t;
            flags[x] = 1;
        }
    }
    printf("%llu\n", sum);
    return 0;
}