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
CMAKE_COMMAND = "/Applications/CMake 2.8-2.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-2.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-2.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/asher/Projects/rp/cerialize

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/asher/Projects/rp/cerialize/install

# Include any dependencies generated for this target.
include cspec/CMakeFiles/cerialize_spec.dir/depend.make

# Include the progress variables for this target.
include cspec/CMakeFiles/cerialize_spec.dir/progress.make

# Include the compile flags for this target's objects.
include cspec/CMakeFiles/cerialize_spec.dir/flags.make

cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o: cspec/CMakeFiles/cerialize_spec.dir/flags.make
cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o: ../cspec/cerialize_internal_spec.c
  $(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/cerialize/install/CMakeFiles $(CMAKE_PROGRESS_1)
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o   -c /Users/asher/Projects/rp/cerialize/cspec/cerialize_internal_spec.c

cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.i: cmake_force
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.i"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/cerialize/cspec/cerialize_internal_spec.c > CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.i

cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.s: cmake_force
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.s"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/cerialize/cspec/cerialize_internal_spec.c -o CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.s

cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.requires:
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.requires

cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.provides: cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.requires
  $(MAKE) -f cspec/CMakeFiles/cerialize_spec.dir/build.make cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.provides.build
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.provides

cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.provides.build: cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.provides.build

cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o: cspec/CMakeFiles/cerialize_spec.dir/flags.make
cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o: ../cspec/cerialize_spec.c
  $(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/cerialize/install/CMakeFiles $(CMAKE_PROGRESS_2)
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o   -c /Users/asher/Projects/rp/cerialize/cspec/cerialize_spec.c

cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.i: cmake_force
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cerialize_spec.dir/cerialize_spec.c.i"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/cerialize/cspec/cerialize_spec.c > CMakeFiles/cerialize_spec.dir/cerialize_spec.c.i

cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.s: cmake_force
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cerialize_spec.dir/cerialize_spec.c.s"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/cerialize/cspec/cerialize_spec.c -o CMakeFiles/cerialize_spec.dir/cerialize_spec.c.s

cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.requires:
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.requires

cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.provides: cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.requires
  $(MAKE) -f cspec/CMakeFiles/cerialize_spec.dir/build.make cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.provides.build
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.provides

cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.provides.build: cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.provides.build

cspec/CMakeFiles/cerialize_spec.dir/main.c.o: cspec/CMakeFiles/cerialize_spec.dir/flags.make
cspec/CMakeFiles/cerialize_spec.dir/main.c.o: ../cspec/main.c
  $(CMAKE_COMMAND) -E cmake_progress_report /Users/asher/Projects/rp/cerialize/install/CMakeFiles $(CMAKE_PROGRESS_3)
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cspec/CMakeFiles/cerialize_spec.dir/main.c.o"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/cerialize_spec.dir/main.c.o   -c /Users/asher/Projects/rp/cerialize/cspec/main.c

cspec/CMakeFiles/cerialize_spec.dir/main.c.i: cmake_force
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cerialize_spec.dir/main.c.i"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -E /Users/asher/Projects/rp/cerialize/cspec/main.c > CMakeFiles/cerialize_spec.dir/main.c.i

cspec/CMakeFiles/cerialize_spec.dir/main.c.s: cmake_force
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cerialize_spec.dir/main.c.s"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && /usr/bin/clang  $(C_DEFINES) $(C_FLAGS) -S /Users/asher/Projects/rp/cerialize/cspec/main.c -o CMakeFiles/cerialize_spec.dir/main.c.s

cspec/CMakeFiles/cerialize_spec.dir/main.c.o.requires:
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/main.c.o.requires

cspec/CMakeFiles/cerialize_spec.dir/main.c.o.provides: cspec/CMakeFiles/cerialize_spec.dir/main.c.o.requires
  $(MAKE) -f cspec/CMakeFiles/cerialize_spec.dir/build.make cspec/CMakeFiles/cerialize_spec.dir/main.c.o.provides.build
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/main.c.o.provides

cspec/CMakeFiles/cerialize_spec.dir/main.c.o.provides.build: cspec/CMakeFiles/cerialize_spec.dir/main.c.o
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/main.c.o.provides.build

# Object files for target cerialize_spec
cerialize_spec_OBJECTS = \
"CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o" \
"CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o" \
"CMakeFiles/cerialize_spec.dir/main.c.o"

# External object files for target cerialize_spec
cerialize_spec_EXTERNAL_OBJECTS =

cspec/../cerialize_spec: cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o
cspec/../cerialize_spec: cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o
cspec/../cerialize_spec: cspec/CMakeFiles/cerialize_spec.dir/main.c.o
cspec/../cerialize_spec: /usr/local/lib/libcspec.a
cspec/../cerialize_spec: src/../libcerialize.dylib
cspec/../cerialize_spec: cspec/CMakeFiles/cerialize_spec.dir/build.make
cspec/../cerialize_spec: cspec/CMakeFiles/cerialize_spec.dir/link.txt
  @$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../cerialize_spec"
  cd /Users/asher/Projects/rp/cerialize/install/cspec && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cerialize_spec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cspec/CMakeFiles/cerialize_spec.dir/build: cspec/../cerialize_spec
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/build

cspec/CMakeFiles/cerialize_spec.dir/requires: cspec/CMakeFiles/cerialize_spec.dir/cerialize_internal_spec.c.o.requires
cspec/CMakeFiles/cerialize_spec.dir/requires: cspec/CMakeFiles/cerialize_spec.dir/cerialize_spec.c.o.requires
cspec/CMakeFiles/cerialize_spec.dir/requires: cspec/CMakeFiles/cerialize_spec.dir/main.c.o.requires
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/requires

cspec/CMakeFiles/cerialize_spec.dir/clean:
  cd /Users/asher/Projects/rp/cerialize/install/cspec && $(CMAKE_COMMAND) -P CMakeFiles/cerialize_spec.dir/cmake_clean.cmake
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/clean

cspec/CMakeFiles/cerialize_spec.dir/depend:
  cd /Users/asher/Projects/rp/cerialize/install && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/asher/Projects/rp/cerialize /Users/asher/Projects/rp/cerialize/cspec /Users/asher/Projects/rp/cerialize/install /Users/asher/Projects/rp/cerialize/install/cspec /Users/asher/Projects/rp/cerialize/install/cspec/CMakeFiles/cerialize_spec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cspec/CMakeFiles/cerialize_spec.dir/depend

