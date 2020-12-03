# **UnTUC**

UnTUC (Unnamed Text-based User Interafce Creator) provides a simple method for creating pseudo-GUIs in your terminal. All GUIs are totally made out of text, and therefore UnTUC requires no external libraries, and provides and all around terrible experience.  

**A tutorial is provided in `Usage.md`.**  

## <u>**VERSION 0.1.0**</u>  
Version 0.1.0 (v0.1.0) was released on December 4, 2020.  
UnTUC v0.1.0 provides the basic essentials for creating a semi-working pseudo-GUI. It does not provide support for mouse input.  

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

### <u>**POSSIBLE UPCOMING FEATURES**</u>  
- [x] Window overflow prevention
- [x] TermiArt compatibility
- [ ] Simplify adding objects

**Thank you for visiting UnTUC!**
