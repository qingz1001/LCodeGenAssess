#include <stdio.h>
#include <string.h>

int main() {
    char sentence[100];
    scanf("%s", sentence);

    int numbers[6] = {0};
    int count = 0;

    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] >= '0' && sentence[i] <= '9') {
            numbers[count++] = sentence[i] - '0';
        } else if ((sentence[i] == 'o' || sentence[i] == 'O') && (sentence[i + 1] == 'n' || sentence[i + 1] == 'N')) {
            numbers[count++] = 1;
        } else if ((sentence[i] == 't' || sentence[i] == 'T') && (sentence[i + 1] == 'w' || sentence[i + 1] == 'W') && (sentence[i + 2] == 'o' || sentence[i + 2] == 'O')) {
            numbers[count++] = 2;
        }
        // Add more conditions for other numbers...
    }

    if (count == 0) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        numbers[i] = (numbers[i] * numbers[i]) % 100;
    }

    // Sort the array to find the smallest number
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (numbers[j] < numbers[i]) {
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
            }
        }
    }

    // Print the result
    printf("%d\n", numbers[0]);

    return 0;
}