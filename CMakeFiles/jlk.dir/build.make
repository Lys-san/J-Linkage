# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lysandre/Documents/tests/JLinkage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lysandre/Documents/tests/JLinkage

# Include any dependencies generated for this target.
include CMakeFiles/jlk.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/jlk.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jlk.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jlk.dir/flags.make

CMakeFiles/jlk.dir/JLinkage.cpp.o: CMakeFiles/jlk.dir/flags.make
CMakeFiles/jlk.dir/JLinkage.cpp.o: JLinkage.cpp
CMakeFiles/jlk.dir/JLinkage.cpp.o: CMakeFiles/jlk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jlk.dir/JLinkage.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jlk.dir/JLinkage.cpp.o -MF CMakeFiles/jlk.dir/JLinkage.cpp.o.d -o CMakeFiles/jlk.dir/JLinkage.cpp.o -c /home/lysandre/Documents/tests/JLinkage/JLinkage.cpp

CMakeFiles/jlk.dir/JLinkage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlk.dir/JLinkage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lysandre/Documents/tests/JLinkage/JLinkage.cpp > CMakeFiles/jlk.dir/JLinkage.cpp.i

CMakeFiles/jlk.dir/JLinkage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlk.dir/JLinkage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lysandre/Documents/tests/JLinkage/JLinkage.cpp -o CMakeFiles/jlk.dir/JLinkage.cpp.s

CMakeFiles/jlk.dir/point.cpp.o: CMakeFiles/jlk.dir/flags.make
CMakeFiles/jlk.dir/point.cpp.o: point.cpp
CMakeFiles/jlk.dir/point.cpp.o: CMakeFiles/jlk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jlk.dir/point.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jlk.dir/point.cpp.o -MF CMakeFiles/jlk.dir/point.cpp.o.d -o CMakeFiles/jlk.dir/point.cpp.o -c /home/lysandre/Documents/tests/JLinkage/point.cpp

CMakeFiles/jlk.dir/point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlk.dir/point.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lysandre/Documents/tests/JLinkage/point.cpp > CMakeFiles/jlk.dir/point.cpp.i

CMakeFiles/jlk.dir/point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlk.dir/point.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lysandre/Documents/tests/JLinkage/point.cpp -o CMakeFiles/jlk.dir/point.cpp.s

CMakeFiles/jlk.dir/line.cpp.o: CMakeFiles/jlk.dir/flags.make
CMakeFiles/jlk.dir/line.cpp.o: line.cpp
CMakeFiles/jlk.dir/line.cpp.o: CMakeFiles/jlk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jlk.dir/line.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jlk.dir/line.cpp.o -MF CMakeFiles/jlk.dir/line.cpp.o.d -o CMakeFiles/jlk.dir/line.cpp.o -c /home/lysandre/Documents/tests/JLinkage/line.cpp

CMakeFiles/jlk.dir/line.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlk.dir/line.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lysandre/Documents/tests/JLinkage/line.cpp > CMakeFiles/jlk.dir/line.cpp.i

CMakeFiles/jlk.dir/line.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlk.dir/line.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lysandre/Documents/tests/JLinkage/line.cpp -o CMakeFiles/jlk.dir/line.cpp.s

CMakeFiles/jlk.dir/window.cpp.o: CMakeFiles/jlk.dir/flags.make
CMakeFiles/jlk.dir/window.cpp.o: window.cpp
CMakeFiles/jlk.dir/window.cpp.o: CMakeFiles/jlk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/jlk.dir/window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jlk.dir/window.cpp.o -MF CMakeFiles/jlk.dir/window.cpp.o.d -o CMakeFiles/jlk.dir/window.cpp.o -c /home/lysandre/Documents/tests/JLinkage/window.cpp

CMakeFiles/jlk.dir/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlk.dir/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lysandre/Documents/tests/JLinkage/window.cpp > CMakeFiles/jlk.dir/window.cpp.i

CMakeFiles/jlk.dir/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlk.dir/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lysandre/Documents/tests/JLinkage/window.cpp -o CMakeFiles/jlk.dir/window.cpp.s

CMakeFiles/jlk.dir/cluster.cpp.o: CMakeFiles/jlk.dir/flags.make
CMakeFiles/jlk.dir/cluster.cpp.o: cluster.cpp
CMakeFiles/jlk.dir/cluster.cpp.o: CMakeFiles/jlk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/jlk.dir/cluster.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jlk.dir/cluster.cpp.o -MF CMakeFiles/jlk.dir/cluster.cpp.o.d -o CMakeFiles/jlk.dir/cluster.cpp.o -c /home/lysandre/Documents/tests/JLinkage/cluster.cpp

CMakeFiles/jlk.dir/cluster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlk.dir/cluster.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lysandre/Documents/tests/JLinkage/cluster.cpp > CMakeFiles/jlk.dir/cluster.cpp.i

CMakeFiles/jlk.dir/cluster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlk.dir/cluster.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lysandre/Documents/tests/JLinkage/cluster.cpp -o CMakeFiles/jlk.dir/cluster.cpp.s

CMakeFiles/jlk.dir/model.cpp.o: CMakeFiles/jlk.dir/flags.make
CMakeFiles/jlk.dir/model.cpp.o: model.cpp
CMakeFiles/jlk.dir/model.cpp.o: CMakeFiles/jlk.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/jlk.dir/model.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jlk.dir/model.cpp.o -MF CMakeFiles/jlk.dir/model.cpp.o.d -o CMakeFiles/jlk.dir/model.cpp.o -c /home/lysandre/Documents/tests/JLinkage/model.cpp

CMakeFiles/jlk.dir/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jlk.dir/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lysandre/Documents/tests/JLinkage/model.cpp > CMakeFiles/jlk.dir/model.cpp.i

CMakeFiles/jlk.dir/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jlk.dir/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lysandre/Documents/tests/JLinkage/model.cpp -o CMakeFiles/jlk.dir/model.cpp.s

# Object files for target jlk
jlk_OBJECTS = \
"CMakeFiles/jlk.dir/JLinkage.cpp.o" \
"CMakeFiles/jlk.dir/point.cpp.o" \
"CMakeFiles/jlk.dir/line.cpp.o" \
"CMakeFiles/jlk.dir/window.cpp.o" \
"CMakeFiles/jlk.dir/cluster.cpp.o" \
"CMakeFiles/jlk.dir/model.cpp.o"

# External object files for target jlk
jlk_EXTERNAL_OBJECTS =

jlk: CMakeFiles/jlk.dir/JLinkage.cpp.o
jlk: CMakeFiles/jlk.dir/point.cpp.o
jlk: CMakeFiles/jlk.dir/line.cpp.o
jlk: CMakeFiles/jlk.dir/window.cpp.o
jlk: CMakeFiles/jlk.dir/cluster.cpp.o
jlk: CMakeFiles/jlk.dir/model.cpp.o
jlk: CMakeFiles/jlk.dir/build.make
jlk: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.15.3
jlk: /usr/lib/x86_64-linux-gnu/libGL.so
jlk: /usr/lib/x86_64-linux-gnu/libGLU.so
jlk: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
jlk: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
jlk: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
jlk: CMakeFiles/jlk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lysandre/Documents/tests/JLinkage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable jlk"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jlk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jlk.dir/build: jlk
.PHONY : CMakeFiles/jlk.dir/build

CMakeFiles/jlk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jlk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jlk.dir/clean

CMakeFiles/jlk.dir/depend:
	cd /home/lysandre/Documents/tests/JLinkage && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lysandre/Documents/tests/JLinkage /home/lysandre/Documents/tests/JLinkage /home/lysandre/Documents/tests/JLinkage /home/lysandre/Documents/tests/JLinkage /home/lysandre/Documents/tests/JLinkage/CMakeFiles/jlk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jlk.dir/depend

