#include "UnTUC.h"

/**
 * @brief: Resizes the terminal
 * @param[IN] x: Width of terminal
 * @param[IN] y: height of terminal
 */
void resize_terminal(IN int x, IN int y){
    printf("X: %d\nY: %d\n\n", x, y);
    printf("\e[8;%d;%dt", y, x);
}

/**
 * @brief: Prints a window's object map
 * @param[IN] window: The target window
 */
void print_map(IN window_t window){
    int i = 0;
    int j = 0;

    for(i=0; i<window.height; i++){
        for(j=0; j<window.width; j++){
            printf("%-4d", window.object_map[i * window.width + j]);
        }
        puts("");
    }
}

/**
 * @brief: Adds a shape to the window
 * @param[OUT] window: The target window
 * @param[IN] shape: A pointer to a shape structure
 * 
 * @returns: ERROR_CODE_SUCCESS on success, else an indicative error code
 */
error_code_t add_raw(OUT window_t * window, IN void * shape){
    error_code_t return_value = ERROR_CODE_UNINITIALIZED;
    int i = 0;
    int j = 0;
    int object_index = 0;
    int object_size = 0;
    button_t * button = NULL;
    rect_t * rectangle = NULL;
    object_type_t object_type = 0;

    object_type = ((rect_t *)shape)->object_type;
    switch(object_type){
        case BUTTON: button = (button_t *)shape; object_size = sizeof(button_t); break;
        case RECTANGLE: rectangle = (rect_t *)shape; object_size = sizeof(rect_t); break;
        default: return_value = ERROR_CODE_INVALID_INPUT; goto cleanup; break;
    }

    object_index = window->num_of_objects;
    if(object_index >= 255){
        puts("\e[31m\e[1mERROR: MAXIMUM OF 255 OBJECTS\e[0m");
        return_value = ERROR_CODE_OVERLOAD;
        goto cleanup;
    }
    window->num_of_objects++;

    window->window_array = realloc(window->window_array, window->num_of_objects * sizeof(void *));
    if(NULL == window->window_array){
        return_value = print_error("ADD_RAW: Realloc error", ERROR_CODE_COULDNT_ALLOCATE_MEMORY);
        goto cleanup;
    }

    window->window_array[object_index] = malloc(object_size);
    if(NULL == window->window_array[window->num_of_objects-1]){
        return_value = print_error("ADD_RAW: Malloc error", ERROR_CODE_COULDNT_ALLOCATE_MEMORY);
        goto cleanup;
    }

    memcpy(window->window_array[object_index], shape, object_size);

    if(BUTTON == object_type){
        for(i=button->y; i<button->y + button->height; i++){
            for(j=button->x; j<button->x + button->width; j++){
                window->object_map[i * window->width + j] = (unsigned char)object_index;
            }
        }
    }

    return_value = ERROR_CODE_SUCCESS;

cleanup:
    return return_value;
}

/**
 * @brief: Adds a button to the window
 * @param[OUT] window: The target window
 * @param[IN] x: The x position of the button
 * @param[IN] y: The y position of the button
 * @param[IN] width: The width of the button
 * @param[IN] height: The height of the button
 * @param[IN] r: The red tint of the button
 * @param[IN] g: The green tint of the button
 * @param[IN] b: The blue tint of the button
 * @param[IN] text: The text to be displayed on the button (in white)
 * @param[IN] action: A function pointer to the function to be called when the button is clicked
 * 
 * @returns: ERROR_CODE_SUCCESS on success, else an indicative error code
 * @notes: This is just a shell for add_raw. It initializes the structure with the input parameters and calls add_raw.
 */
error_code_t add_button(OUT window_t * window, IN int x, IN int y, IN int width, IN int height, IN unsigned char r, IN unsigned char g, IN unsigned char b, IN char * text, IN int (*action)(window_t * window, button_t button, void * arguments)){
    error_code_t return_value = ERROR_CODE_UNINITIALIZED;
    button_t button = {0};
    
    button.object_type = BUTTON;
    button.x = x;
    button.y = y;
    button.width = width;
    button.height = height;
    button.r = r;
    button.g = g;
    button.b = b;

    button.text = malloc(strnlen(text, BUFFER_SIZE)+1);
    if(NULL == button.text){
        return_value = print_error("ADD_BUTTON: Malloc error", ERROR_CODE_COULDNT_ALLOCATE_MEMORY);
        goto cleanup;
    }
    memcpy(button.text, text, strnlen(text, BUFFER_SIZE)+1);

    button.action = action;

    return_value = add_raw(window, &button);

cleanup:
    return return_value;
}

/**
 * @brief: Adds a rectangle to the window
 * @param[OUT] window: The target window
 * @param[IN] x: The x position of the button
 * @param[IN] y: The y position of the button
 * @param[IN] width: The width of the button
 * @param[IN] height: The height of the button
 * @param[IN] r: The red tint of the button
 * @param[IN] g: The green tint of the button
 * @param[IN] b: The blue tint of the button
 * 
 * @returns: ERROR_CODE_SUCCESS on success, else an indicative error code
 * @notes: This is just a shell for add_raw. It initializes the structure with the input parameters and calls add_raw.
 */
error_code_t add_rectangle(OUT window_t * window, IN int x, IN int y, IN int width, IN int height, IN unsigned char r, IN unsigned char g, IN unsigned char b){
    error_code_t return_value = ERROR_CODE_UNINITIALIZED;
    rect_t rectangle = {0};

    rectangle.object_type = RECTANGLE;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.width = width;
    rectangle.height = height;
    rectangle.r = r;
    rectangle.g = g;
    rectangle.b = b;
    
    return_value = add_raw(window, &rectangle);

    return return_value;
}

/**
 * @brief: Creates a window
 * @param[OUT] window: The window to initialize
 * @param[IN] width: the desired width of the window
 * @param[IN] height: The desired height of the window
 * 
 * @returns: ERROR_CODE_SUCCESS on success, else an indicative error code
 */
error_code_t create_window(OUT window_t * window, IN int width, IN int height){
    error_code_t return_value = ERROR_CODE_UNINITIALIZED;

    window->width = width;
    window->height = height;
    window->num_of_objects = 0;

    window->object_map = malloc(width * height);
    if(NULL == window->object_map){
        return_value = print_error("CREATE_WINDOW: Malloc error", ERROR_CODE_COULDNT_ALLOCATE_MEMORY);
        goto cleanup;
    }
    memset(window->object_map, 255, width * height);

    return_value = ERROR_CODE_SUCCESS;

cleanup:
    return return_value;
}

/**
 * @brief: Prints a window
 * @param[IN] window: The window to print
 */
void print_window(IN window_t window){
    int row = 0;
    int column = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int text_pointer = 0;
    button_t * button = NULL;
    rect_t * rectangle = NULL;

    //system("clear");
    printf("\e[0;0H");

    for(row=0; row<window.height; row++){
        for(column=0; column<window.width; column++){
            fputs(". ", stdout);
        }
        puts("");
    }

    for(k=0; k<window.num_of_objects; k++){
        if(NULL != window.window_array[k] && BUTTON == ((button_t *)window.window_array[k])->object_type){
            text_pointer = 0;
            button = (button_t *)window.window_array[k];
            printf("\e[%d;%dH", (button->y+1), button->x * 2 + 1);

            for(j=0; j<button->height; j++){
                for(i=0; i<button->width; i++){
                    if(button->text[text_pointer] != 0){
                        printf("\e[48;2;%d;%d;%dm%c%c\e[0m", button->r, button->g, button->b, button->text[text_pointer], (button->text[text_pointer+1] != 0) ? button->text[text_pointer+1] : ' ');
                        text_pointer += 2;
                    }
                    else{
                        printf("\e[48;2;%d;%d;%dm  \e[0m", button->r, button->g, button->b);
                    }
                }
                printf("\e[%d;%dH", button->y + j + 2, button->x * 2 + 1);
            }
        }
        else if(NULL != window.window_array[k] && RECTANGLE == ((rect_t *)window.window_array[k])->object_type){
            rectangle = (rect_t *)window.window_array[k];
            printf("\e[%d;%dH", (rectangle->y+1), rectangle->x * 2 + 1);

            for(j=0; j<rectangle->height; j++){
                for(i=0; i<rectangle->width; i++){
                    printf("\e[48;2;%d;%d;%dm  \e[0m", rectangle->r, rectangle->g, rectangle->b);
                }
                printf("\e[%d;%dH", rectangle->y + j + 2, rectangle->x * 2 + 1);
            }
        }
    }

    printf("\e[%d;%dH", window.height+2, 0);
}

/**
 * @brief: Gets user input and prints window accordingly
 * @param[IN] window: The window to print
 * 
 * @returns: ERROR_CODE_SUCCESS on success, else an indicative error code
 * @notes: This is really just a simple function that can be used if you don't want too much customization.
 */
void run_window(IN window_t * window){
    int cursor_x = 0;
    int cursor_y = 0;
    int prev_cursor_x = 0;
    int prev_cursor_y = 0;
    unsigned char button_index = 0;
    char input = 0;
    button_t * button = NULL;
    bool run = true;

    system("clear");
    change_cursor(true);

    change_echo(false);

    print_window(*window);
    printf("\e[%d;%dH", cursor_y+1, cursor_x * 2 + 1);

    while(run){
        input = getchar();

        switch(input){
            case 'w': cursor_y--; break;
            case 'a': cursor_x--; break;
            case 's': cursor_y++; break;
            case 'd': cursor_x++; break;
            case ' ':
                button_index = window->object_map[cursor_y * window->width + cursor_x];
                if( 255 != button_index) {
                    button = (button_t *)window->window_array[button_index];

                    if(BUTTON == button->object_type && NULL != button->action ){
                        button->action(window, *button, NULL);
                    }
                }

                print_window(*window);
                break;
            case 'q': run = false; break;
        }

        if(cursor_x >= 0){
            cursor_x %= window->width;
        }
        else{
            cursor_x = (window->width + cursor_x) % window->width;
        }
        if(cursor_y >= 0){
            cursor_y %= window->height;
        }
        else{
            cursor_y = (window->height + cursor_y) % window->height;
        }

        printf("\e[%d;%dH", cursor_y+1, cursor_x * 2 + 1);
    }

    change_echo(true);
}

/**
 * @brief: Frees all memory taken up by a window
 * @param[OUT] window: The target window
 * 
 * @returns: ERROR_CODE_SUCCESS on success, else an indicative error code
 * @notes: This doesn't free the window structure if it was dynamically allocated.
 */
error_code_t free_window(window_t * window){
    int i = 0;
    int j = 0;
    int freed_ptr = 0;
    button_t * button = NULL;
    void * freed[255] = {0};
    bool can_free = true;

    system("clear");
    printf("\e[0;0H");

    for(i=0; i<window->num_of_objects; i++){
        can_free = true;

        if(BUTTON == ((button_t *)window->window_array[i])->object_type && NULL != ((button_t *)window->window_array[i])->text){
            button = (button_t *)(window->window_array[i]);
            for(j=0; j<sizeof(freed) && freed[j] != NULL; j++){
                if(freed[j] == button->text){
                    can_free = false;
                }
            }
            if(can_free){
                free(button->text);
                freed[freed_ptr] = button->text;
                freed_ptr++;
            }
        }
        if(NULL != window->window_array[i]){
            free(window->window_array[i]);
            window->window_array[i] = NULL;
        }
    }

    free(window->window_array);
    free(window->object_map);
}
