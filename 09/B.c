#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} tile_pos_t;

int main() {
    FILE* file_handle = fopen("input.tmp.txt", "r");
    if (file_handle == NULL) {
        printf("Failed to read input\n");
        return 1;
    }

    tile_pos_t red_tiles[512];
    size_t tile_count = 0;
    char data[12];
    size_t data_index = 0;
    int character;
    while ((character = fgetc(file_handle)) != EOF) {
        if (character == '\n') {
            data[data_index] = '\0';
            red_tiles[tile_count++].y = atoi(data);
            data_index = 0;
            continue;
        }
        if (character == ',') {
            data[data_index] = '\0';
            red_tiles[tile_count].x = atoi(data);
            data_index = 0;
            continue;
        }
        data[data_index++] = (char) character;
    }
    fclose(file_handle);

    long long max_area = 0;
    for (int a = 0; a < tile_count; ++a) {
        for (int b = a+1; b < tile_count; ++b) {
            const tile_pos_t tile_a = red_tiles[a];
            const tile_pos_t tile_b = red_tiles[b];
            const int x1 = tile_a.x < tile_b.x ? tile_a.x : tile_b.x;
            const int x2 = tile_a.x > tile_b.x ? tile_a.x : tile_b.x;
            const int y1 = tile_a.y < tile_b.y ? tile_a.y : tile_b.y;
            const int y2 = tile_a.y > tile_b.y ? tile_a.y : tile_b.y;
            for (int c = 0; c < tile_count; ++c) {
                const tile_pos_t tile_c = red_tiles[c];
                if (x1 < tile_c.x && tile_c.x < x2 && y1 < tile_c.y && tile_c.y < y2) {
                    // tile inside area, skipping
                    goto b_loop;
                }
            }
            const long long area = (long long) (x2 - x1 + 1) * (long long) (y2 - y1 + 1);
            if (area > max_area) {
                max_area = area;
            }
b_loop:;
        }
    }

    printf("%lld\n", max_area);
}
