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
include CMakeFiles/stackqueue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stackqueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stackqueue.dir/flags.make

CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.obj: CMakeFiles/stackqueue.dir/flags.make
CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.obj: ../algorithm/stackqueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\allproject\personal\heyoh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.obj"
	D:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\stackqueue.dir\algorithm\stackqueue.cpp.obj -c D:\allproject\personal\heyoh\algorithm\stackqueue.cpp

CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\allproject\personal\heyoh\algorithm\stackqueue.cpp > CMakeFiles\stackqueue.dir\algorithm\stackqueue.cpp.i

CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\allproject\personal\heyoh\algorithm\stackqueue.cpp -o CMakeFiles\stackqueue.dir\algorithm\stackqueue.cpp.s

# Object files for target stackqueue
stackqueue_OBJECTS = \
"CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.obj"

# External object files for target stackqueue
stackqueue_EXTERNAL_OBJECTS =

stackqueue.exe: CMakeFiles/stackqueue.dir/algorithm/stackqueue.cpp.obj
stackqueue.exe: CMakeFiles/stackqueue.dir/build.make
stackqueue.exe: CMakeFiles/stackqueue.dir/linklibs.rsp
stackqueue.exe: CMakeFiles/stackqueue.dir/objects1.rsp
stackqueue.exe: CMakeFiles/stackqueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\allproject\personal\heyoh\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stackqueue.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\stackqueue.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stackqueue.dir/build: stackqueue.exe

.PHONY : CMakeFiles/stackqueue.dir/build

CMakeFiles/stackqueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\stackqueue.dir\cmake_clean.cmake
.PHONY : CMakeFiles/stackqueue.dir/clean

CMakeFiles/stackqueue.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\allproject\personal\heyoh D:\allproject\personal\heyoh D:\allproject\personal\heyoh\cmake-build-debug D:\allproject\personal\heyoh\cmake-build-debug D:\allproject\personal\heyoh\cmake-build-debug\CMakeFiles\stackqueue.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stackqueue.dir/depend

