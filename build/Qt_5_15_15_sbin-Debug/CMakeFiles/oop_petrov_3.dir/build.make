# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/s1ash2k/oop_petrov_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug

# Include any dependencies generated for this target.
include CMakeFiles/oop_petrov_3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/oop_petrov_3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/oop_petrov_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/oop_petrov_3.dir/flags.make

oop_petrov_3_autogen/timestamp: /usr/bin/moc
oop_petrov_3_autogen/timestamp: /usr/bin/uic
oop_petrov_3_autogen/timestamp: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target oop_petrov_3"
	/usr/bin/cmake -E cmake_autogen /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles/oop_petrov_3_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/oop_petrov_3_autogen/timestamp

CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o: CMakeFiles/oop_petrov_3.dir/flags.make
CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o: oop_petrov_3_autogen/mocs_compilation.cpp
CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o -MF CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o -c /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/oop_petrov_3_autogen/mocs_compilation.cpp

CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.i"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/oop_petrov_3_autogen/mocs_compilation.cpp > CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.i

CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.s"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/oop_petrov_3_autogen/mocs_compilation.cpp -o CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.s

CMakeFiles/oop_petrov_3.dir/main.cpp.o: CMakeFiles/oop_petrov_3.dir/flags.make
CMakeFiles/oop_petrov_3.dir/main.cpp.o: /home/s1ash2k/oop_petrov_3/main.cpp
CMakeFiles/oop_petrov_3.dir/main.cpp.o: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/oop_petrov_3.dir/main.cpp.o"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oop_petrov_3.dir/main.cpp.o -MF CMakeFiles/oop_petrov_3.dir/main.cpp.o.d -o CMakeFiles/oop_petrov_3.dir/main.cpp.o -c /home/s1ash2k/oop_petrov_3/main.cpp

CMakeFiles/oop_petrov_3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oop_petrov_3.dir/main.cpp.i"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s1ash2k/oop_petrov_3/main.cpp > CMakeFiles/oop_petrov_3.dir/main.cpp.i

CMakeFiles/oop_petrov_3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oop_petrov_3.dir/main.cpp.s"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s1ash2k/oop_petrov_3/main.cpp -o CMakeFiles/oop_petrov_3.dir/main.cpp.s

CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o: CMakeFiles/oop_petrov_3.dir/flags.make
CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o: /home/s1ash2k/oop_petrov_3/mainwindow.cpp
CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o -MF CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o.d -o CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o -c /home/s1ash2k/oop_petrov_3/mainwindow.cpp

CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.i"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s1ash2k/oop_petrov_3/mainwindow.cpp > CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.i

CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.s"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s1ash2k/oop_petrov_3/mainwindow.cpp -o CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.s

CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o: CMakeFiles/oop_petrov_3.dir/flags.make
CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o: /home/s1ash2k/oop_petrov_3/petrov_item.cpp
CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o -MF CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o.d -o CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o -c /home/s1ash2k/oop_petrov_3/petrov_item.cpp

CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.i"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s1ash2k/oop_petrov_3/petrov_item.cpp > CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.i

CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.s"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s1ash2k/oop_petrov_3/petrov_item.cpp -o CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.s

CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o: CMakeFiles/oop_petrov_3.dir/flags.make
CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o: /home/s1ash2k/oop_petrov_3/petrov_used_item.cpp
CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o -MF CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o.d -o CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o -c /home/s1ash2k/oop_petrov_3/petrov_used_item.cpp

CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.i"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s1ash2k/oop_petrov_3/petrov_used_item.cpp > CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.i

CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.s"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s1ash2k/oop_petrov_3/petrov_used_item.cpp -o CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.s

CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o: CMakeFiles/oop_petrov_3.dir/flags.make
CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o: /home/s1ash2k/oop_petrov_3/petrov_shop.cpp
CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o: CMakeFiles/oop_petrov_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o -MF CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o.d -o CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o -c /home/s1ash2k/oop_petrov_3/petrov_shop.cpp

CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.i"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/s1ash2k/oop_petrov_3/petrov_shop.cpp > CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.i

CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.s"
	/usr/lib/ccache/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/s1ash2k/oop_petrov_3/petrov_shop.cpp -o CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.s

# Object files for target oop_petrov_3
oop_petrov_3_OBJECTS = \
"CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/oop_petrov_3.dir/main.cpp.o" \
"CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o" \
"CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o" \
"CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o" \
"CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o"

# External object files for target oop_petrov_3
oop_petrov_3_EXTERNAL_OBJECTS =

oop_petrov_3: CMakeFiles/oop_petrov_3.dir/oop_petrov_3_autogen/mocs_compilation.cpp.o
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/main.cpp.o
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/mainwindow.cpp.o
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/petrov_item.cpp.o
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/petrov_used_item.cpp.o
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/petrov_shop.cpp.o
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/build.make
oop_petrov_3: /usr/lib/libQt5Widgets.so.5.15.15
oop_petrov_3: /usr/lib/libboost_serialization.so.1.86.0
oop_petrov_3: /usr/lib/libQt5Gui.so.5.15.15
oop_petrov_3: /usr/lib/libQt5Core.so.5.15.15
oop_petrov_3: CMakeFiles/oop_petrov_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable oop_petrov_3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/oop_petrov_3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/oop_petrov_3.dir/build: oop_petrov_3
.PHONY : CMakeFiles/oop_petrov_3.dir/build

CMakeFiles/oop_petrov_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/oop_petrov_3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/oop_petrov_3.dir/clean

CMakeFiles/oop_petrov_3.dir/depend: oop_petrov_3_autogen/timestamp
	cd /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/s1ash2k/oop_petrov_3 /home/s1ash2k/oop_petrov_3 /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug /home/s1ash2k/oop_petrov_3/build/Qt_5_15_15_sbin-Debug/CMakeFiles/oop_petrov_3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/oop_petrov_3.dir/depend

