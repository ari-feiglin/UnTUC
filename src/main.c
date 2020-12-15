#include "UnTUC.h"

int cookies = 0;

int increase_cookies(window_t * window, int index, void * args){
    cookies++;
}

int print_cookies(window_t * window, int index, void * args){
    printf("\e[%d;0H", window->height+2);
    printf("\e[1m\e[31mNumber of cookies: %d\n", cookies);
    sleep(1);
}

int new_func(window_t * window, int index, void * args){
    int error_check = 0;
    button_t button = {0};

    error_check = get_button(window, index, &button);
    if(ERROR_CODE_SUCCESS != error_check){
        system("clear");
        change_echo(true);
        puts("\n\n\n\n\n\n\n");
        sleep(1);
    }
    button.r += 100;
    puts("\e[31mSEE?\e[0m");
    button.x -= 1;
    ((button_t *)window->window_array[index])->r += 100;
    ((button_t *)window->window_array[index])->y--;

    add_raw(window, &button);

    //free(button.text);
}

int main(int argc, char ** argv){
    window_t window = {0};

    create_window(&window, 10, 10);
    add_tart(&window, 0, 0, "../termiArt/.termiArt.tart", true);
    //add_rectangle(&window, 0, 0, window.width, window.height, 100, 200, 200);
    add_button(&window, 1, 3, 4, 4, 132, 86, 60, "COOKIE", &increase_cookies);
    add_button(&window, 6, 3, 3, 3, 0, 0, 255, "Print cookies", &new_func);

    run_window(&window);

    free_window(&window);
}