# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Nibbler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Nibbler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Nibbler.dir/flags.make

CMakeFiles/Nibbler.dir/main.cpp.o: CMakeFiles/Nibbler.dir/flags.make
CMakeFiles/Nibbler.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Nibbler.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Nibbler.dir/main.cpp.o -c /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/main.cpp

CMakeFiles/Nibbler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Nibbler.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/main.cpp > CMakeFiles/Nibbler.dir/main.cpp.i

CMakeFiles/Nibbler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Nibbler.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/main.cpp -o CMakeFiles/Nibbler.dir/main.cpp.s

CMakeFiles/Nibbler.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Nibbler.dir/main.cpp.o.requires

CMakeFiles/Nibbler.dir/main.cpp.o.provides: CMakeFiles/Nibbler.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Nibbler.dir/build.make CMakeFiles/Nibbler.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Nibbler.dir/main.cpp.o.provides

CMakeFiles/Nibbler.dir/main.cpp.o.provides.build: CMakeFiles/Nibbler.dir/main.cpp.o


# Object files for target Nibbler
Nibbler_OBJECTS = \
"CMakeFiles/Nibbler.dir/main.cpp.o"

# External object files for target Nibbler
Nibbler_EXTERNAL_OBJECTS =

Nibbler: CMakeFiles/Nibbler.dir/main.cpp.o
Nibbler: CMakeFiles/Nibbler.dir/build.make
Nibbler: CMakeFiles/Nibbler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Nibbler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Nibbler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Nibbler.dir/build: Nibbler

.PHONY : CMakeFiles/Nibbler.dir/build

CMakeFiles/Nibbler.dir/requires: CMakeFiles/Nibbler.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Nibbler.dir/requires

CMakeFiles/Nibbler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Nibbler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Nibbler.dir/clean

CMakeFiles/Nibbler.dir/depend:
	cd /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug /nfs/zfs-student-6/users/julekgwa/ClionProjects/Nibbler/cmake-build-debug/CMakeFiles/Nibbler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Nibbler.dir/depend
