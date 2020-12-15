# <big>**UnTUC**</big>

# **USING UnTUC**  

In order to create a Text-based User Interface (TUI), you must first understand a bit of how UnTUC works.  

<br />

***

## <u>**UnTUC structures**</u>

***
### **window_t**  

UnTUC provides a structure for a terminal "window". It is defined in `include/UnTUC.h` like so:  

```c
typedef struct window_s{
    int width;
    int height;
    int num_of_objects;
    void ** window_array;
    unsigned char * object_map;
}window_t;
```

* `width` and `height` are the width and height of the window, respectivley.
* `num_of_objects` is the number of objects (buttons, etc.) stored in the window.
* `window_array` is an array of pointers to the objects in the window.
* `object_map` is an array of the indexes of objects (their indexes in `window_array`) based off of their position in the window. The value 255 marks that no object is at that position on the window. **Therefore, the maximum number of objects that can be added to a window is 255**  
For example, the following object map (written by taking `width` and `height` into account):  
    ```
    255,   0,   0, 255,  
    255,   0,   0, 255,  
    255, 255, 255, 255,  
    255, 255,   1,   1  
    ```
    Corresponds to a window with two objects one on the top center, and one on the bottom right.  

<br />

<br />

***
### **rect_t**  

The rectangle_t structure is an object that corresponds to a rectangle on the GUI. The structure is defined in `include/UnTUC.h` like so:  

```c
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
```  

* `object_type` is the type of object it is (this should always be set to RECTANGLE)
* `x` and `y` are the x and y positions of the rectangle on the window, respectivley.
* `width` and `height` are the width and height of the rectangle, respectivley.
* `r`, `g`, and `b` are the color tints of the rectangle.  

<br />

***
### **button_t**  

The button_t structure is an object that corresponds to a button on the window. The structure is defined in `include/UnTUC.h` like so:  

```c
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

    int (*action)(window_t * window, int index, void * args);
}button_t;
```  

* `object_type` is the type of object it is (this should always be set to BUTTON)
* The next 7 elements are the same as the elements in the **rect_t** structure. (From `x` to `b`)  
* `text` is the text that will be displayed on the button.
* `action` is a function pointer to the function that should be called when the button is clicked. It must take a **window_t** pointer and an index as parameters (in order to manipulate the window). It also must take a void pointer to an array of any other arguments you would like to pass.  

<br />

***
### **tart_t**

The tart_t structure is an object that corresponds to a picture on the window. The structure is defined in `include/UnTUC.h` like so:  

```c
typedef struct tart_s{
    object_type_t object_type;
    int x;
    int y;
    int width;
    int height;
    node_t * canvas;
}tart_t;
```

Tart pictures are pixel art drawings created by the TermiArt System. It can be found here at [the TermiArt repository on GitHub](https://github.com/ari-feiglin/Termi-Art).

* `object_type` is the type of object it is (this should always be set to TART)
* The next 4 elements are the same as the same elements in the **rect_t** and **button_t** structures.
* `canvas` is an array of nodes in the pixel art (more details below in **get_canvas**)

<br />

***

## <u>**UnTUC Functions**</u>  

The following functions are all declared in `include/UnTUC.h` and defined in `src/UnTUC.c`.

<br />

***
### **create_window**
This function initializes a window_t object given a desired width and height.

```c
error_code_t create_window(window_t * window, int width, int height)
```

* `window`: a pointer to the window object to initialize
* `width` and `height`: the desired width and height of the window, respectivley.

<br />

***
### **add_raw**
This function adds a shape object structure to a window.

```c
error_code_t add_raw(window_t * window, void * shape)
```
* `window`: the window to add the object to
* `shape`: a pointer to the object to add to the window

This function updates window's arrays according to the object added.

<br />

***
### **add_button**
This function initializes a `button_t` object and passes it to **add_raw**

```c
error_code_t add_button(window_t * window, int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b, char * text, int (*action)(window_t * window, button_t button, void * arguments))
```
* `window`: A pointer to the window to add the object to.
* `x` and `y`: the x and y coordinates, respectivley, to add the button to.
* `width` and `height`: The width and height of the button, respectivley.
* `r`, `g`, and `b`: The red, green, and blue tints of the button.
* `text`: The text to add to the button.
* `action`: A function pointer to the function to call after the button is clicked.  

<br />

***
### **add_rectangle**
This function initializes a `rect_t` object and passes it to **add_raw**

```c
error_code_t add_rectangle(window_t * window, int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b)
```
* `window`: A pointer to the window to add the object to.
* `x` and `y`: the x and y coordinates, respectivley, to add the rectangle to.
* `width` and `height`: The width and height of the rectangle, respectivley.
* `r`, `g`, and `b`: The red, green, and blue tints of the rectangle.

<br />

***
### **add_tart**
This function initializes a `tart_t` object and passes it to **add_raw**

```c
error_code_t add_tart(window_t * window, int x, int y, char * file_name, bool compressed)
``` 
* `window`: A pointer to the window to add the object to.
* `x` and `y`: the x and y coordinates, respectivley, to add the pixel art to.
* `file_name`: The path to the file that has the pixel art.

<br />

***
### **get_button**
This function gets a button from a window based on an index provided.
```c
error_code_t get_button(window_t * window, int index, button_t * button);
```
* `window`: A pointer to the window to get the button from.
* `index`: The index of the button in the window's window_array.
* `button`: A (non-NULL) pointer to a button struct to fill

<br />

***
### **get_canvas**
This function extracts a canvas (node_t array) from a termiArt file.

```c
error_code_t get_canvas(char * file_name, node_t ** canvas, int * width, int * height, bool compressed);
```
* `file_name`: The file path to the TermiArt pixel art file.
* `canvas`: A pointer to a canvas (a pointer to a node_t array). A node is a structure of 3 bytes that holds the rgb of a pixel on the canvas. For more information, visit [the TermiArt repository on GitHub](https://github.com/ari-feiglin/Termi-Art).
* `width` and `height`: Pointers to integers that will hold the width and height of the canvas.
* `compressed`: If the TermiArt file is compressed or not (if the file was made with TermiArt v0.0.1 or earlier, it won't be compressed)

<br />

***
### **print_window**
This function prints the window to STDOUT.

```c
void print_window(window_t window)
```
* `window`: The window to print.

<br />

***
### **print_map**
This function prints the `object_map` of a window. This is pretty unnecessary and was only made for debugging purposes.

```c
void print_map(window_t window)
```
* `window`: The window whose map you wish to print.

<br />

***
### **free_window**
This function frees all memory taken up by the terminal (save the `window_t` structure itself if it was dynamically allocated).

```c
error_code_t free_window(window_t * window)
```
* `window`: A pointer to the window to free.

<br />

***
### **resize_terminal**
This function resizes the terminal based on the given parameters.

```c
void resize_terminal(int x, int y)
```
* `x` and `y`: The width and height of the terminal, respectivley.

<br />

***
### **run_window**
This function prints and manages a window. Because I wrote it, it isn't customizable, and should only be used if you don't require too much customization. Because of this, you cannot pass arguments to actions (`window` and `index` are passed, but not `args`). Use wasd to move the cursor, enter to click, and q to exit.

```c
void run_window(window_t * window)
```
* `window`: A pointer to the window to print.

<br />

***
## <u>**IMPORTANT NOTES**<u>
Manipulating a button's (that is in the window's window_array) position will not update the window's object_map!

***
## <u>**EXAMPLE PROGRAM**</u>  
The following is a program for a simple cookie clicker game. (There are seperate buttons for gaining cookies and printing them just to demonstrate how UnTUC works).

```c
#include "UnTUC.h"

int cookies = 0;

int increase_cookies(window_t * window, int index, void * args){
    cookies++;
}

int print_cookies(window_t * window, int index, void * args){
    printf("\e[%d;0H", window->height+2);
    printf("\e[1mNumber of cookies: %d\n", cookies);
}

int main(int argc, char ** argv){
    window_t window = {0};

    create_window(&window, 10, 10);
    add_rectangle(&window, 0, 0, window.width, window.height, 100, 200, 200);
    add_button(&window, 1, 3, 4, 4, 132, 86, 60, "COOKIE", &increase_cookies);
    add_button(&window, 6, 3, 3, 3, 0, 0, 255, "Print cookies", &print_cookies);

    run_window(&window);

    free_window(&window);
}
```  

**And that's it! I hope this helped, and thanks for using UnTUC!**