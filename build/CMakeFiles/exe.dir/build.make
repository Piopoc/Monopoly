# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/piopo/Documenti/C++/monopoli

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piopo/Documenti/C++/monopoli/build

# Include any dependencies generated for this target.
include CMakeFiles/exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exe.dir/flags.make

CMakeFiles/exe.dir/src/main.cpp.o: CMakeFiles/exe.dir/flags.make
CMakeFiles/exe.dir/src/main.cpp.o: /home/piopo/Documenti/C++/monopoli/src/main.cpp
CMakeFiles/exe.dir/src/main.cpp.o: CMakeFiles/exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/piopo/Documenti/C++/monopoli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exe.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exe.dir/src/main.cpp.o -MF CMakeFiles/exe.dir/src/main.cpp.o.d -o CMakeFiles/exe.dir/src/main.cpp.o -c /home/piopo/Documenti/C++/monopoli/src/main.cpp

CMakeFiles/exe.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/exe.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/piopo/Documenti/C++/monopoli/src/main.cpp > CMakeFiles/exe.dir/src/main.cpp.i

CMakeFiles/exe.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/exe.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/piopo/Documenti/C++/monopoli/src/main.cpp -o CMakeFiles/exe.dir/src/main.cpp.s

CMakeFiles/exe.dir/src/tabellone.cpp.o: CMakeFiles/exe.dir/flags.make
CMakeFiles/exe.dir/src/tabellone.cpp.o: /home/piopo/Documenti/C++/monopoli/src/tabellone.cpp
CMakeFiles/exe.dir/src/tabellone.cpp.o: CMakeFiles/exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/piopo/Documenti/C++/monopoli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/exe.dir/src/tabellone.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exe.dir/src/tabellone.cpp.o -MF CMakeFiles/exe.dir/src/tabellone.cpp.o.d -o CMakeFiles/exe.dir/src/tabellone.cpp.o -c /home/piopo/Documenti/C++/monopoli/src/tabellone.cpp

CMakeFiles/exe.dir/src/tabellone.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/exe.dir/src/tabellone.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/piopo/Documenti/C++/monopoli/src/tabellone.cpp > CMakeFiles/exe.dir/src/tabellone.cpp.i

CMakeFiles/exe.dir/src/tabellone.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/exe.dir/src/tabellone.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/piopo/Documenti/C++/monopoli/src/tabellone.cpp -o CMakeFiles/exe.dir/src/tabellone.cpp.s

CMakeFiles/exe.dir/src/player.cpp.o: CMakeFiles/exe.dir/flags.make
CMakeFiles/exe.dir/src/player.cpp.o: /home/piopo/Documenti/C++/monopoli/src/player.cpp
CMakeFiles/exe.dir/src/player.cpp.o: CMakeFiles/exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/piopo/Documenti/C++/monopoli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/exe.dir/src/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exe.dir/src/player.cpp.o -MF CMakeFiles/exe.dir/src/player.cpp.o.d -o CMakeFiles/exe.dir/src/player.cpp.o -c /home/piopo/Documenti/C++/monopoli/src/player.cpp

CMakeFiles/exe.dir/src/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/exe.dir/src/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/piopo/Documenti/C++/monopoli/src/player.cpp > CMakeFiles/exe.dir/src/player.cpp.i

CMakeFiles/exe.dir/src/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/exe.dir/src/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/piopo/Documenti/C++/monopoli/src/player.cpp -o CMakeFiles/exe.dir/src/player.cpp.s

# Object files for target exe
exe_OBJECTS = \
"CMakeFiles/exe.dir/src/main.cpp.o" \
"CMakeFiles/exe.dir/src/tabellone.cpp.o" \
"CMakeFiles/exe.dir/src/player.cpp.o"

# External object files for target exe
exe_EXTERNAL_OBJECTS =

exe: CMakeFiles/exe.dir/src/main.cpp.o
exe: CMakeFiles/exe.dir/src/tabellone.cpp.o
exe: CMakeFiles/exe.dir/src/player.cpp.o
exe: CMakeFiles/exe.dir/build.make
exe: CMakeFiles/exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/piopo/Documenti/C++/monopoli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exe.dir/build: exe
.PHONY : CMakeFiles/exe.dir/build

CMakeFiles/exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exe.dir/clean

CMakeFiles/exe.dir/depend:
	cd /home/piopo/Documenti/C++/monopoli/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piopo/Documenti/C++/monopoli /home/piopo/Documenti/C++/monopoli /home/piopo/Documenti/C++/monopoli/build /home/piopo/Documenti/C++/monopoli/build /home/piopo/Documenti/C++/monopoli/build/CMakeFiles/exe.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/exe.dir/depend

