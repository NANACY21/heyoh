# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\allproject\personal\heyoh

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\allproject\personal\heyoh\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/heyoh.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/heyoh.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/heyoh.dir/flags.make

CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.obj: CMakeFiles/heyoh.dir/flags.make
CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.obj: ../algorithm/stackqueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\allproject\personal\heyoh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\heyoh.dir\algorithm\stackqueue.cpp.obj -c D:\allproject\personal\heyoh\algorithm\stackqueue.cpp

CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\allproject\personal\heyoh\algorithm\stackqueue.cpp > CMakeFiles\heyoh.dir\algorithm\stackqueue.cpp.i

CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\allproject\personal\heyoh\algorithm\stackqueue.cpp -o CMakeFiles\heyoh.dir\algorithm\stackqueue.cpp.s

# Object files for target heyoh
heyoh_OBJECTS = \
"CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.obj"

# External object files for target heyoh
heyoh_EXTERNAL_OBJECTS =

heyoh.exe: CMakeFiles/heyoh.dir/algorithm/stackqueue.cpp.obj
heyoh.exe: CMakeFiles/heyoh.dir/build.make
heyoh.exe: CMakeFiles/heyoh.dir/linklibs.rsp
heyoh.exe: CMakeFiles/heyoh.dir/objects1.rsp
heyoh.exe: CMakeFiles/heyoh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\allproject\personal\heyoh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable heyoh.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\heyoh.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/heyoh.dir/build: heyoh.exe

.PHONY : CMakeFiles/heyoh.dir/build

CMakeFiles/heyoh.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\heyoh.dir\cmake_clean.cmake
.PHONY : CMakeFiles/heyoh.dir/clean

CMakeFiles/heyoh.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\allproject\personal\heyoh D:\allproject\personal\heyoh D:\allproject\personal\heyoh\cmake-build-debug D:\allproject\personal\heyoh\cmake-build-debug D:\allproject\personal\heyoh\cmake-build-debug\CMakeFiles\heyoh.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/heyoh.dir/depend

