cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( testBlobFinder )
add_executable( testBlobFinder testBlobFinder.cc )
target_link_libraries( testBlobFinder ${OpenCV_LIBS} )
