# **UnTUC**

UnTUC (Unnamed Text-based User Interafce Creator) provides a simple method for creating pseudo-GUIs in your terminal. All GUIs are totally made out of text, and therefore UnTUC requires no external libraries, and provides and all around terrible experience.  

**A tutorial is provided in `Usage.md`.**  

## <u>**VERSION 0.1.1**</u>  
Version 0.1.1 (v0.1.1) was released on December 15, 2020.  
UnTUC v0.1.1 provides the basic essentials for creating a semi-working pseudo-GUI. It does not provide support for mouse input.  

### <u>**DEPENDENCIES**</u>  
* A terminal that supports ANSI escape sequences (especially the ones for cursor movement and rgb colors).  
To test this, go on your terminal and run the following commands (for bash):
    ```
    $ echo -e "\e[31m\e[1mThis text should be red and bold!\e[0m"

    $ echo -e "\e[38;2;0;255;255mThis text should be turqouise\e[0m"

    # the following two commands should be run in order, one after another

    $ clear

    $ echo -e "\e[5;1H\e[31mThis text should be red and some lines down\e[0m"
    ```
* Cmake

### <u>**MAKING AND RUNNING**</u>  
To create a shared object file for UnTUC, on the terminal navigate to the UnTUC directory and run:
```
$ cd /path/to/UnTUC/directory
$ cmake .
$ make
```
Programs that use this library should include UnTUC.h

If you would like to create an executable for UnTUC, run:
```
$ cd /path/to/UnTUC/directory
$ make -f Makefile.bin
```

### **WHAT'S NEW IN VERSION 0.1.1?**
* Button actions now get the index of the button object instead of a button object, allowing for easier manipulation of the button. Because of this, a new simple function was added:
    * The `get_button` function was added to get a button from a window based on an index
* Created a signal handler for in `run_window` sigint (rendering it useless) in order to make sure that all memory can be properly free'd and echo returned to normal. To quit `run_window`, you must now hit q.

### <u>**POSSIBLE UPCOMING FEATURES**</u>  
- [x] Window overflow prevention
- [x] TermiArt compatibility
- [ ] Simplify adding objects
- [ ] Update object_map when a button or other object is moved

**Thank you for visiting UnTUC!**
