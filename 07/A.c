#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    bool active_beams[256];
    int beam_splits = 0;
    size_t pos_x = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        pos_x++;
        if (character == '\n') {
            pos_x = 0;
        } else if (character == 'S') {
            active_beams[pos_x] = true;
        } else if (character == '^' && active_beams[pos_x]) {
            beam_splits++;
            active_beams[pos_x] = false;
            active_beams[pos_x-1] = true;
            active_beams[pos_x+1] = true;
        }
    }
    fclose(file_handle);

    printf("%d\n", beam_splits);
}
