#include <stdio.h>
#include <stdlib.h>
#include "standard.h"

typedef enum object_type_s {BUTTON=1, RECTANGLE, TART}object_type_t;

typedef struct node_s{
    unsigned char r;
    unsigned char g;
    unsigned char b;
}node_t;

typedef struct window_s{
    int width;
    int height;
    int num_of_objects;
    void ** window_array;
    unsigned char * object_map;
}window_t;

typedef struct button_s{
    object_type_t object_type;
    int x;
    int y;
    int width;
    int height;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char * text;

    int (*action)(window_t * window, struct button_s button, void * args);
}button_t;

typedef struct rect_s{
    object_type_t object_type;
    int x;
    int y;
    int width;
    int height;
    unsigned char r;
    unsigned char g;
    unsigned char b;
}rect_t;

typedef struct tart_s{
    object_type_t object_type;
    int x;
    int y;
    int width;
    int height;
    node_t * canvas;
}tart_t;

error_code_t create_window(window_t * window, int width, int height);
error_code_t get_canvas(char * file_name, node_t ** canvas, int * width, int * height, bool compressed);
error_code_t add_raw(window_t * window, void * shape);
error_code_t add_button(window_t * window, int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b, char * text, int (*action)(window_t * window, button_t button, void * arguments));
error_code_t add_rectangle(window_t * window, int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b);
error_code_t add_tart(window_t * window, int x, int y, char * file_name, bool compressed);
void print_window(window_t window);
void print_map(window_t window);
error_code_t free_window(window_t * window);
void resize_terminal(int x, int y);
void run_window(IN window_t * window);
