# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/joseg/AppData/Local/JetBrains/CLion2021.3/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/joseg/AppData/Local/JetBrains/CLion2021.3/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin

# Include any dependencies generated for this target.
include CMakeFiles/Caso_4_ED.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Caso_4_ED.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Caso_4_ED.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Caso_4_ED.dir/flags.make

CMakeFiles/Caso_4_ED.dir/main.cpp.o: CMakeFiles/Caso_4_ED.dir/flags.make
CMakeFiles/Caso_4_ED.dir/main.cpp.o: ../main.cpp
CMakeFiles/Caso_4_ED.dir/main.cpp.o: CMakeFiles/Caso_4_ED.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Caso_4_ED.dir/main.cpp.o"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Caso_4_ED.dir/main.cpp.o -MF CMakeFiles/Caso_4_ED.dir/main.cpp.o.d -o CMakeFiles/Caso_4_ED.dir/main.cpp.o -c /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/main.cpp

CMakeFiles/Caso_4_ED.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Caso_4_ED.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/main.cpp > CMakeFiles/Caso_4_ED.dir/main.cpp.i

CMakeFiles/Caso_4_ED.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Caso_4_ED.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/main.cpp -o CMakeFiles/Caso_4_ED.dir/main.cpp.s

# Object files for target Caso_4_ED
Caso_4_ED_OBJECTS = \
"CMakeFiles/Caso_4_ED.dir/main.cpp.o"

# External object files for target Caso_4_ED
Caso_4_ED_EXTERNAL_OBJECTS =

Caso_4_ED.exe: CMakeFiles/Caso_4_ED.dir/main.cpp.o
Caso_4_ED.exe: CMakeFiles/Caso_4_ED.dir/build.make
Caso_4_ED.exe: CMakeFiles/Caso_4_ED.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Caso_4_ED.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Caso_4_ED.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Caso_4_ED.dir/build: Caso_4_ED.exe
.PHONY : CMakeFiles/Caso_4_ED.dir/build

CMakeFiles/Caso_4_ED.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Caso_4_ED.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Caso_4_ED.dir/clean

CMakeFiles/Caso_4_ED.dir/depend:
	cd /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin /cygdrive/c/Users/joseg/OneDrive/Desktop/Work/Repositories/Caso_4_ED/cmake-build-debug-cygwin/CMakeFiles/Caso_4_ED.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Caso_4_ED.dir/depend

