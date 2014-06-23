# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thomas/MonoNav/OpenCV/boundingRegion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/MonoNav/OpenCV/boundingRegion

# Include any dependencies generated for this target.
include CMakeFiles/edgeVectorPic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/edgeVectorPic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/edgeVectorPic.dir/flags.make

CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o: CMakeFiles/edgeVectorPic.dir/flags.make
CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o: edgeVectorPic.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/thomas/MonoNav/OpenCV/boundingRegion/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o -c /home/thomas/MonoNav/OpenCV/boundingRegion/edgeVectorPic.cc

CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/thomas/MonoNav/OpenCV/boundingRegion/edgeVectorPic.cc > CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.i

CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/thomas/MonoNav/OpenCV/boundingRegion/edgeVectorPic.cc -o CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.s

CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.requires:
.PHONY : CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.requires

CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.provides: CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.requires
	$(MAKE) -f CMakeFiles/edgeVectorPic.dir/build.make CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.provides.build
.PHONY : CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.provides

CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.provides.build: CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o

# Object files for target edgeVectorPic
edgeVectorPic_OBJECTS = \
"CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o"

# External object files for target edgeVectorPic
edgeVectorPic_EXTERNAL_OBJECTS =

edgeVectorPic: CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o
edgeVectorPic: /usr/local/lib/libopencv_videostab.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_video.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_ts.a
edgeVectorPic: /usr/local/lib/libopencv_superres.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_stitching.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_photo.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_ocl.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_objdetect.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_nonfree.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_ml.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_legacy.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_imgproc.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_highgui.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_gpu.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_flann.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_features2d.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_core.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_contrib.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_calib3d.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_nonfree.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_ocl.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_gpu.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_photo.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_objdetect.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_legacy.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_video.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_ml.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_calib3d.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_features2d.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_highgui.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_imgproc.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_flann.so.2.4.9
edgeVectorPic: /usr/local/lib/libopencv_core.so.2.4.9
edgeVectorPic: CMakeFiles/edgeVectorPic.dir/build.make
edgeVectorPic: CMakeFiles/edgeVectorPic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable edgeVectorPic"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/edgeVectorPic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/edgeVectorPic.dir/build: edgeVectorPic
.PHONY : CMakeFiles/edgeVectorPic.dir/build

CMakeFiles/edgeVectorPic.dir/requires: CMakeFiles/edgeVectorPic.dir/edgeVectorPic.cc.o.requires
.PHONY : CMakeFiles/edgeVectorPic.dir/requires

CMakeFiles/edgeVectorPic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/edgeVectorPic.dir/cmake_clean.cmake
.PHONY : CMakeFiles/edgeVectorPic.dir/clean

CMakeFiles/edgeVectorPic.dir/depend:
	cd /home/thomas/MonoNav/OpenCV/boundingRegion && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomas/MonoNav/OpenCV/boundingRegion /home/thomas/MonoNav/OpenCV/boundingRegion /home/thomas/MonoNav/OpenCV/boundingRegion /home/thomas/MonoNav/OpenCV/boundingRegion /home/thomas/MonoNav/OpenCV/boundingRegion/CMakeFiles/edgeVectorPic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/edgeVectorPic.dir/depend

