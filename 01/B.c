#include <stdio.h>
#include <stdlib.h>

// 8009 - too high
// 2774 - too low
// 6819 - right, but gotten with brute force
int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    int dial_position = 50;
    int times_pointed_at_0 = 0;

    char line[5];
    unsigned char line_index = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        line[line_index++] = (char) character;
        if (character == '\n') {
            line[line_index - 1] = '\0';
            line_index = 0;

            const char direction = line[0];
            const char sign = direction == 'L' ? -1 : 1;
            const int amount = atoi(&line[1]);
            // printf("%+2d", direction, amount, dial_position);
            // times_pointed_at_0 += direction == 'L' && amount > dial_position;
            // times_pointed_at_0 += direction == 'R' && 100 - amount <= dial_position;
            for (int i = 0; i < amount; i++) {
                dial_position = (dial_position + sign + 100) % 100;
                if (dial_position == 0) {
                    times_pointed_at_0++;
                    // printf("%s %d\n", line, times_pointed_at_0);
                }
            }
            // dial_position += amount;
            // printf(" -> %+4d (%2d) %d\n", dial_position, (dial_position + 100) % 100, times_pointed_at_0);
            dial_position = (dial_position + 100) % 100;
        }
    }
    fclose(file_handle);

    printf("%d\n", times_pointed_at_0);
}
