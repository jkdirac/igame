# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liaochen/workspace/IGEM/git-hub/igame/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD

# Include any dependencies generated for this target.
include BdInterface/CMakeFiles/test_bdbinterface.dir/depend.make

# Include the progress variables for this target.
include BdInterface/CMakeFiles/test_bdbinterface.dir/progress.make

# Include the compile flags for this target's objects.
include BdInterface/CMakeFiles/test_bdbinterface.dir/flags.make

BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o: BdInterface/CMakeFiles/test_bdbinterface.dir/flags.make
BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o: ../BdInterface/test/bdbInterfaceTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o"
	cd /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o -c /home/liaochen/workspace/IGEM/git-hub/igame/src/BdInterface/test/bdbInterfaceTest.cpp

BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.i"
	cd /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/liaochen/workspace/IGEM/git-hub/igame/src/BdInterface/test/bdbInterfaceTest.cpp > CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.i

BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.s"
	cd /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/liaochen/workspace/IGEM/git-hub/igame/src/BdInterface/test/bdbInterfaceTest.cpp -o CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.s

BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.requires:
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.requires

BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.provides: BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.requires
	$(MAKE) -f BdInterface/CMakeFiles/test_bdbinterface.dir/build.make BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.provides.build
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.provides

BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.provides.build: BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.provides.build

# Object files for target test_bdbinterface
test_bdbinterface_OBJECTS = \
"CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o"

# External object files for target test_bdbinterface
test_bdbinterface_EXTERNAL_OBJECTS =

bin/test_bdbinterface: BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o
bin/test_bdbinterface: /usr/lib/libQtOpenGL.so
bin/test_bdbinterface: /usr/lib/libQtSvg.so
bin/test_bdbinterface: /usr/lib/libQtGui.so
bin/test_bdbinterface: /usr/lib/libQtXml.so
bin/test_bdbinterface: /usr/lib/libQtCore.so
bin/test_bdbinterface: bin/libbdinterface.a
bin/test_bdbinterface: BdInterface/CMakeFiles/test_bdbinterface.dir/build.make
bin/test_bdbinterface: BdInterface/CMakeFiles/test_bdbinterface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/test_bdbinterface"
	cd /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bdbinterface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
BdInterface/CMakeFiles/test_bdbinterface.dir/build: bin/test_bdbinterface
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/build

BdInterface/CMakeFiles/test_bdbinterface.dir/requires: BdInterface/CMakeFiles/test_bdbinterface.dir/test/bdbInterfaceTest.cpp.o.requires
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/requires

BdInterface/CMakeFiles/test_bdbinterface.dir/clean:
	cd /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface && $(CMAKE_COMMAND) -P CMakeFiles/test_bdbinterface.dir/cmake_clean.cmake
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/clean

BdInterface/CMakeFiles/test_bdbinterface.dir/depend:
	cd /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liaochen/workspace/IGEM/git-hub/igame/src /home/liaochen/workspace/IGEM/git-hub/igame/src/BdInterface /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface /home/liaochen/workspace/IGEM/git-hub/igame/src/BUILD/BdInterface/CMakeFiles/test_bdbinterface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : BdInterface/CMakeFiles/test_bdbinterface.dir/depend

