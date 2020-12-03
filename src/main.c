#include "UnTUC.h"

int cookies = 0;

int increase_cookies(window_t * window, button_t button, void * args){
    cookies++;
}

int print_cookies(window_t * window, button_t button, void * args){
    printf("\e[%d;0H", window->height+2);
    printf("\e[1m\e[31mNumber of cookies: %d\n", cookies);
    sleep(1);
}

int main(int argc, char ** argv){
    window_t window = {0};

    create_window(&window, 10, 10);
    add_tart(&window, 0, 0, "../termiArt/.termiArt.tart", true);
    //add_rectangle(&window, 0, 0, window.width, window.height, 100, 200, 200);
    add_button(&window, 1, 3, 4, 4, 132, 86, 60, "COOKIE", &increase_cookies);
    add_button(&window, 6, 3, 3, 3, 0, 0, 255, "Print cookies", &print_cookies);

    run_window(&window);

    free_window(&window);
}