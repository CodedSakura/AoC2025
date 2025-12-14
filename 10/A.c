#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char indicator_count;
    char indicators;
    char button_count;
    char buttons[16];
    short joltage[10];
} machine_t;

// 385 - too low
int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    int total = 0;
    machine_t current = {};
    char data[12];
    size_t data_index = 0;
    char step = 1; // 1 = indicators, 2 = schematics, 3 = joltage
    short current_joltage = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == '\n') {
            // process
            // printf("%08b (%08b %08b %08b %08b %08b %08b %08b)\n", current.indicators,
            //     current.buttons[0], current.buttons[1], current.buttons[2], current.buttons[3],
            //     current.buttons[4], current.buttons[5], current.buttons[6], current.buttons[7]);
            char fewest = 16;
            const int possible_combos = 1 << current.button_count;
            for (int i = 0; i < possible_combos; i++) {
                char pressed_button_count = 0;
                char indicator_state = 0;
                for (int bit = 0; bit < current.button_count; bit++) {
                    if (!(i & 1 << bit)) continue;
                    pressed_button_count++;
                    indicator_state ^= current.buttons[bit];
                    // if (i == 10) {
                    //     printf("> %08b (^ %08b)\n", indicator_state, current.buttons[bit]);
                    // }
                }
                if (indicator_state == current.indicators) {
                    printf("%08b (%d)\n", i, i);
                    if (fewest > pressed_button_count) {
                        fewest = pressed_button_count;
                    }
                }
            }
            total += fewest;
            printf("[%d]\n", fewest);
            // restart
            memset(&current, 0, sizeof(machine_t));
            current_joltage = 0;
            data_index = 0;
            continue;
        }
        if (character == '[' || character == ']') {
            step = 1;
            continue;
        }
        if (character == '(' || character == ')') {
            step = 2;
            continue;
        }
        if (character == '{') {
            step = 3;
            continue;
        }
        if (character == '}') {
            data[data_index] = '\0';
            current.joltage[current_joltage] = (short) atoi(data);
            data_index = 0;
            continue;
        }
        if (character == ' ') {
            if (step == 2) {
                current.button_count++;
            }
            continue;
        }
        if (character == ',') {
            if (step == 3) {
                data[data_index] = '\0';
                current.joltage[current_joltage++] = (short) atoi(data);
                data_index = 0;
            }
            continue;
        }
        if (step == 1) {
            if (character == '#') {
                current.indicators |= 1 << current.indicator_count;
            }
            current.indicator_count++;
        }
        if (step == 2) {
            current.buttons[current.button_count] |= (1 << ((char) character - '0'));
        }
        if (step == 3) {
            data[data_index++] = (char) character;
        }
    }
    fclose(file_handle);

    printf("%d\n", total);
}
