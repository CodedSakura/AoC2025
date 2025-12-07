#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 123349426806 - too low
int main() {
    FILE* file_handle = fopen("input.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    long long active_beams[256] = {0};
    size_t pos_x = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        pos_x++;
        if (character == '\n') {
            pos_x = 0;
            // for (int i = 0; i < 256; i++) {
            //     printf("%2d ", active_beams[i]);
            // }
            // printf("\n");
        } else if (character == 'S') {
            active_beams[pos_x] = 1;
        } else if (character == '^' && active_beams[pos_x] > 0) {
            active_beams[pos_x - 1] += active_beams[pos_x];
            active_beams[pos_x + 1] += active_beams[pos_x];
            active_beams[pos_x] = 0;
        }
    }
    fclose(file_handle);

    long long sum = 0;
    for (int i = 0; i < 256; i++) {
        sum += active_beams[i];
    }

    printf("%lld\n", sum);
}
