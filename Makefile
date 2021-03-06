# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ari/git_repositories/window_system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ari/git_repositories/window_system

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ari/git_repositories/window_system/CMakeFiles /home/ari/git_repositories/window_system/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/ari/git_repositories/window_system/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named UnTUC

# Build rule for target.
UnTUC: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 UnTUC
.PHONY : UnTUC

# fast build rule for target.
UnTUC/fast:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/build
.PHONY : UnTUC/fast

src/standard.o: src/standard.c.o

.PHONY : src/standard.o

# target to build an object file
src/standard.c.o:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/src/standard.c.o
.PHONY : src/standard.c.o

src/standard.i: src/standard.c.i

.PHONY : src/standard.i

# target to preprocess a source file
src/standard.c.i:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/src/standard.c.i
.PHONY : src/standard.c.i

src/standard.s: src/standard.c.s

.PHONY : src/standard.s

# target to generate assembly for a file
src/standard.c.s:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/src/standard.c.s
.PHONY : src/standard.c.s

src/windows.o: src/windows.c.o

.PHONY : src/windows.o

# target to build an object file
src/windows.c.o:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/src/windows.c.o
.PHONY : src/windows.c.o

src/windows.i: src/windows.c.i

.PHONY : src/windows.i

# target to preprocess a source file
src/windows.c.i:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/src/windows.c.i
.PHONY : src/windows.c.i

src/windows.s: src/windows.c.s

.PHONY : src/windows.s

# target to generate assembly for a file
src/windows.c.s:
	$(MAKE) -f CMakeFiles/UnTUC.dir/build.make CMakeFiles/UnTUC.dir/src/windows.c.s
.PHONY : src/windows.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... UnTUC"
	@echo "... edit_cache"
	@echo "... src/standard.o"
	@echo "... src/standard.i"
	@echo "... src/standard.s"
	@echo "... src/windows.o"
	@echo "... src/windows.i"
	@echo "... src/windows.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

