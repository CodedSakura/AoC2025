#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} tile_pos_t;

// 4572898800 - too high
// 334806930 - too low
int main() {
    FILE* file_handle = fopen("input.txt", "r");
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
            for (int n = 0; n < tile_count; ++n) {
                const tile_pos_t tile_n = red_tiles[n];
                if (x1 < tile_n.x && tile_n.x < x2 && y1 < tile_n.y && tile_n.y < y2) {
                    // tile inside area, skipping
                    goto b_loop;
                }
            }
            for (int n = 0; n < tile_count; ++n) {
                const tile_pos_t tile_l1 = red_tiles[n];
                const tile_pos_t tile_l2 = red_tiles[(n+1) % tile_count];
                const int lx1 = tile_l1.x < tile_l2.x ? tile_l1.x : tile_l2.x;
                const int lx2 = tile_l1.x > tile_l2.x ? tile_l1.x : tile_l2.x;
                const int ly1 = tile_l1.y < tile_l2.y ? tile_l1.y : tile_l2.y;
                const int ly2 = tile_l1.y > tile_l2.y ? tile_l1.y : tile_l2.y;
                if (lx1 == lx2 && x1 < lx1 && lx1 < x2) {
                    // vertical line
                    if (ly1 <= y1 && ly2 >= y2) {
                        // split
                        goto b_loop;
                    }
                }
                if (ly1 == ly2 && y1 < ly1 && ly1 < y2) {
                    // horizontal line
                    if (lx1 <= x1 && lx2 >= x2) {
                        // split
                        goto b_loop;
                    }
                }
            }


            const long long area = (long long) (x2 - x1 + 1) * (long long) (y2 - y1 + 1);
            if (area > max_area) {
                // printf("%d;%d - %d;%d (%lld)\n", tile_a.x, tile_a.y, tile_b.x, tile_b.y, area);
                max_area = area;
            }
b_loop:;
        }
    }

    printf("%lld\n", max_area);
}
