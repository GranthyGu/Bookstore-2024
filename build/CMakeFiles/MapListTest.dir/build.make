# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build

# Include any dependencies generated for this target.
include CMakeFiles/MapListTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MapListTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MapListTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MapListTest.dir/flags.make

CMakeFiles/MapListTest.dir/codegen:
.PHONY : CMakeFiles/MapListTest.dir/codegen

CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o: CMakeFiles/MapListTest.dir/flags.make
CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o: /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/error.cpp
CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o: CMakeFiles/MapListTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o -MF CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o.d -o CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o -c /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/error.cpp

CMakeFiles/MapListTest.dir/src/Headers/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MapListTest.dir/src/Headers/error.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/error.cpp > CMakeFiles/MapListTest.dir/src/Headers/error.cpp.i

CMakeFiles/MapListTest.dir/src/Headers/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MapListTest.dir/src/Headers/error.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/error.cpp -o CMakeFiles/MapListTest.dir/src/Headers/error.cpp.s

CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o: CMakeFiles/MapListTest.dir/flags.make
CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o: /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/BookManager.cpp
CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o: CMakeFiles/MapListTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o -MF CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o.d -o CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o -c /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/BookManager.cpp

CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/BookManager.cpp > CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.i

CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/BookManager.cpp -o CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.s

CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o: CMakeFiles/MapListTest.dir/flags.make
CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o: /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/LogManager.cpp
CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o: CMakeFiles/MapListTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o -MF CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o.d -o CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o -c /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/LogManager.cpp

CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/LogManager.cpp > CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.i

CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/LogManager.cpp -o CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.s

CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o: CMakeFiles/MapListTest.dir/flags.make
CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o: /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/tokenscanner.cpp
CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o: CMakeFiles/MapListTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o -MF CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o.d -o CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o -c /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/tokenscanner.cpp

CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/tokenscanner.cpp > CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.i

CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/tokenscanner.cpp -o CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.s

CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o: CMakeFiles/MapListTest.dir/flags.make
CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o: /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/AccountManager.cpp
CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o: CMakeFiles/MapListTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o -MF CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o.d -o CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o -c /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/AccountManager.cpp

CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/AccountManager.cpp > CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.i

CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/Headers/AccountManager.cpp -o CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.s

CMakeFiles/MapListTest.dir/src/main.cpp.o: CMakeFiles/MapListTest.dir/flags.make
CMakeFiles/MapListTest.dir/src/main.cpp.o: /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/main.cpp
CMakeFiles/MapListTest.dir/src/main.cpp.o: CMakeFiles/MapListTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MapListTest.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MapListTest.dir/src/main.cpp.o -MF CMakeFiles/MapListTest.dir/src/main.cpp.o.d -o CMakeFiles/MapListTest.dir/src/main.cpp.o -c /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/main.cpp

CMakeFiles/MapListTest.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MapListTest.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/main.cpp > CMakeFiles/MapListTest.dir/src/main.cpp.i

CMakeFiles/MapListTest.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MapListTest.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/src/main.cpp -o CMakeFiles/MapListTest.dir/src/main.cpp.s

# Object files for target MapListTest
MapListTest_OBJECTS = \
"CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o" \
"CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o" \
"CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o" \
"CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o" \
"CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o" \
"CMakeFiles/MapListTest.dir/src/main.cpp.o"

# External object files for target MapListTest
MapListTest_EXTERNAL_OBJECTS =

MapListTest: CMakeFiles/MapListTest.dir/src/Headers/error.cpp.o
MapListTest: CMakeFiles/MapListTest.dir/src/Headers/BookManager.cpp.o
MapListTest: CMakeFiles/MapListTest.dir/src/Headers/LogManager.cpp.o
MapListTest: CMakeFiles/MapListTest.dir/src/Headers/tokenscanner.cpp.o
MapListTest: CMakeFiles/MapListTest.dir/src/Headers/AccountManager.cpp.o
MapListTest: CMakeFiles/MapListTest.dir/src/main.cpp.o
MapListTest: CMakeFiles/MapListTest.dir/build.make
MapListTest: CMakeFiles/MapListTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable MapListTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MapListTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MapListTest.dir/build: MapListTest
.PHONY : CMakeFiles/MapListTest.dir/build

CMakeFiles/MapListTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MapListTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MapListTest.dir/clean

CMakeFiles/MapListTest.dir/depend:
	cd /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024 /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024 /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build /Users/guyuanxi/Desktop/C++/Bookstore-Management-2024/Bookstore-2024/build/CMakeFiles/MapListTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MapListTest.dir/depend

