
#include <stdio.h>
#include <string.h>

// 1489 - too low, but same as someone else's
int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    char grid[150][150];
    size_t max_x = 0, pos_x = 0, max_y = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        grid[max_y][pos_x++] = (char) character;
        if (character == '\n') {
            max_y++;
            max_x = pos_x-1;
            pos_x = 0;
        }
    }
    fclose(file_handle);

    int removable_rolls = 0;
    int removed_rolls = 0;

    do {
        removed_rolls = 0;
        for (int y = 0; y < max_y; y++) {
            for (int x = 0; x < max_x; x++) {
                if (grid[y][x] == '.') {
                    // printf(".");
                    continue;
                }

                int neighbor_count = 0;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (y + dy < 0 || y + dy >= max_y || x + dx < 0 || x + dx >= max_x) {
                            continue;
                        }
                        if (dx == 0 && dy == 0) {
                            continue;
                        }
                        neighbor_count += grid[y + dy][x + dx] == '@';
                    }
                }

                if (neighbor_count < 4) {
                    removable_rolls++;
                    removed_rolls++;
                    grid[y][x] = '.';
                    // printf("x");
                } else {
                    // printf("@");
                }
            }
            // printf("\n");
        }
    } while (removed_rolls > 0);

    printf("%d\n", removable_rolls);
}
