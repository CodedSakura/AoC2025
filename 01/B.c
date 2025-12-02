#include <stdio.h>
#include <stdlib.h>

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
            int amount = atoi(&line[1]);
            times_pointed_at_0 += amount / 100;
            amount %= 100;
            times_pointed_at_0 += direction == 'L' && amount > dial_position;
            times_pointed_at_0 += direction == 'R' && amount + dial_position >= 100;
            dial_position += direction == 'L' ? -amount : amount;
            dial_position = (dial_position + 100) % 100;
        }
    }
    fclose(file_handle);

    printf("%d\n", times_pointed_at_0);
}
