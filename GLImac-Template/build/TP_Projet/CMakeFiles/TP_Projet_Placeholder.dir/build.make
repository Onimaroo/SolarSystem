# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build

# Include any dependencies generated for this target.
include TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/depend.make

# Include the progress variables for this target.
include TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/progress.make

# Include the compile flags for this target's objects.
include TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/flags.make

TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.o: TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/flags.make
TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.o: ../TP_Projet/Placeholder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.o"
	cd /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.o -c /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet/Placeholder.cpp

TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.i"
	cd /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet/Placeholder.cpp > CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.i

TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.s"
	cd /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet/Placeholder.cpp -o CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.s

# Object files for target TP_Projet_Placeholder
TP_Projet_Placeholder_OBJECTS = \
"CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.o"

# External object files for target TP_Projet_Placeholder
TP_Projet_Placeholder_EXTERNAL_OBJECTS =

TP_Projet/TP_Projet_Placeholder: TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/Placeholder.cpp.o
TP_Projet/TP_Projet_Placeholder: TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/build.make
TP_Projet/TP_Projet_Placeholder: glimac/libglimac.a
TP_Projet/TP_Projet_Placeholder: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP_Projet/TP_Projet_Placeholder: /usr/lib/x86_64-linux-gnu/libSDL.so
TP_Projet/TP_Projet_Placeholder: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP_Projet/TP_Projet_Placeholder: ../third-party/libGLEW.a
TP_Projet/TP_Projet_Placeholder: TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP_Projet_Placeholder"
	cd /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP_Projet_Placeholder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/build: TP_Projet/TP_Projet_Placeholder

.PHONY : TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/build

TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/clean:
	cd /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet && $(CMAKE_COMMAND) -P CMakeFiles/TP_Projet_Placeholder.dir/cmake_clean.cmake
.PHONY : TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/clean

TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/depend:
	cd /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/TP_Projet /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet /home/padawan/Téléchargements/GLImac-Template-GLEW_inside/GLImac-Template/build/TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP_Projet/CMakeFiles/TP_Projet_Placeholder.dir/depend

