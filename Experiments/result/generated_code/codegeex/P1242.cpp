#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 45

int main() {
    int n;
    scanf("%d", &n);

    int initial[MAX_DISKS + 1], target[MAX_DISKS + 1];
    int initial_heights[3], target_heights[3];
    char columns[3] = {'A', 'B', 'C'};

    // Read initial state
    for (int i = 0; i < 3; i++) {
        int disk;
        initial_heights[i] = 0;
        while (scanf("%d", &disk) && disk != 0) {
            initial[initial_heights[i]++] = disk;
        }
    }

    // Read target state
    for (int i = 0; i < 3; i++) {
        int disk;
        target_heights[i] = 0;
        while (scanf("%d", &disk) && disk != 0) {
            target[target_heights[i]++] = disk;
        }
    }

    // Function to find the column index for a given disk in the target state
    int find_target_column(int disk) {
        for (int i = 0; i < 3; i++) {
            if (target_heights[i] > 0 && target[target_heights[i] - 1] == disk) {
                return i;
            }
        }
        return -1; // Should not happen
    }

    // Function to move a disk from one column to another
    void move_disk(int disk, int from, int to) {
        printf("move %d from %c to %c\n", disk, columns[from], columns[to]);
    }

    // Function to solve the Tower of Hanoi problem
    void solve_hanoi(int n, int from, int to, int aux) {
        if (n == 0) return;

        solve_hanoi(n - 1, from, aux, to);

        int disk = initial[--initial_heights[from]];
        move_disk(disk, from, to);
        target_heights[to]++;

        solve_hanoi(n - 1, aux, to, from);
    }

    // Find the column with the largest disk in the initial state
    int find_largest_disk_column() {
        int max_disk = 0, max_column = -1;
        for (int i = 0; i < 3; i++) {
            if (initial_heights[i] > 0 && initial[initial_heights[i] - 1] > max_disk) {
                max_disk = initial[initial_heights[i] - 1];
                max_column = i;
            }
        }
        return max_column;
    }

    // Main logic to solve the problem
    int main() {
        int largest_disk_column = find_largest_disk_column();
        int target_column = find_target_column(initial[initial_heights[largest_disk_column] - 1]);

        // Move the largest disk to the target column
        solve_hanoi(initial_heights[largest_disk_column] - 1, largest_disk_column, target_column, 3 - largest_disk_column - target_column);

        // Move the largest disk to its final position
        move_disk(initial[--initial_heights[largest_disk_column]], largest_disk_column, target_column);

        // Move the remaining disks to the target column
        solve_hanoi(initial_heights[largest_disk_column], largest_disk_column, target_column, 3 - largest_disk_column - target_column);

        printf("%d\n", initial_heights[largest_disk_column] + initial_heights[target_column]);

        return 0;
    }
}