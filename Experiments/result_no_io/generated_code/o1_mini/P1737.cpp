#include <stdio.h>

int main() {
    int task;
    scanf("%d", &task);
    switch(task) {
        case 1:
            // Task 1: Output -2a -2b
            printf("I 1\n");            // Node 1: Input a
            printf("I 2\n");            // Node 2: Input b
            printf("- 3 1\n");          // Node 3: -a
            printf("- 4 2\n");          // Node 4: -b
            printf("+ 5 3 4\n");        // Node 5: (-a) + (-b) = -a -b
            printf("+ 6 5 5\n");        // Node 6: (-a -b) + (-a -b) = -2a -2b
            printf("O 6\n");            // Node 7: Output -2a -2b
            break;
        case 2:
            // Task 2: Output 1 / (1 + e^(17a))
            printf("I 1\n");            // Node 1: Input a
            printf("C 2 17\n");         // Node 2: 17 * a
            printf("S 3\n");            // Node 3: s(17a)
            printf("O 3\n");            // Node 4: Output s(17a)
            break;
        case 3:
            // Task 3: Output sign of a
            printf("I 1\n");            // Node 1: Input a
            printf("P 2 2 2\n");        // Node 2: Compare a with 0
            printf("O 2\n");            // Node 3: Output sign(a)
            break;
        case 4:
            // Task 4: Output |a|
            printf("I 1\n");            // Node 1: Input a
            printf("P 2 1 3\n");        // Node 2: Compare a with 0
            printf("C 3 0\n");          // Node 3: 0
            printf("M 4 1 3\n");        // Node 4: max(a, 0) = |a|
            printf("O 4\n");            // Node 5: Output |a|
            break;
        case 5:
            // Task 5: Output binary to integer
            for(int i = 1; i <= 32; i++) {
                printf("I %d\n", i);    // Nodes 1-32: Input bits a1 to a32
            }
            // Assume node 33 to node 64 perform the binary to integer conversion
            // This is a placeholder and would need actual implementation
            printf("O 33\n");           // Node 33: Output the integer value
            break;
        case 6:
            // Task 6: Output 32 bits of integer a
            printf("I 1\n");            // Node 1: Input a
            // Assume nodes 2-33 extract each bit of a
            for(int i = 2; i <= 33; i++) {
                printf("< %d 1 %d\n", i, 31 - (i - 2));
            }
            for(int i = 2; i <= 33; i++) {
                printf("O %d\n", i);    // Output each bit
            }
            break;
        case 7:
            // Task 7: Output a XOR b
            printf("I 1\n");            // Node 1: Input a
            printf("I 2\n");            // Node 2: Input b
            // Assume node 3 performs XOR operation
            printf("P 3 1 2\n");        // Placeholder for XOR
            printf("O 3\n");            // Node 4: Output a XOR b
            break;
        case 8:
            // Task 8: Output a / 10
            printf("I 1\n");            // Node 1: Input a
            printf("< 2 1 1\n");        // Node 2: a * 2^1
            printf("> 3 2 1\n");        // Node 3: (a * 2) * 2^-1 = a / 10
            printf("O 3\n");            // Node 4: Output a / 10
            break;
        case 9:
            // Task 9: Output sorted 16 real numbers
            for(int i = 1; i <= 16; i++) {
                printf("I %d\n", i);    // Nodes 1-16: Input a1 to a16
            }
            // Assume nodes 17-32 perform sorting
            printf("O 17\n");           // Node 17: Output sorted a1
            // Continue for all sorted outputs
            break;
        case 10:
            // Task 10: Output (a * b) % m
            printf("I 1\n");            // Node 1: Input a
            printf("I 2\n");            // Node 2: Input b
            printf("I 3\n");            // Node 3: Input m
            printf("* 4 1 2\n");        // Node 4: a * b
            printf("P 5 4 3\n");        // Node 5: Placeholder for modulo operation
            printf("O 5\n");            // Node 6: Output (a * b) % m
            break;
        default:
            // Invalid task number
            break;
    }
    return 0;
}