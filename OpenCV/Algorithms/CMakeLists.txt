cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( compareAlgVid )
add_executable( compareAlgVid compareAlgVid.cc )
target_link_libraries( compareAlgVid ${OpenCV_LIBS} )
