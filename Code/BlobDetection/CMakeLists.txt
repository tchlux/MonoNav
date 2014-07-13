# rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile 
# ^^ Removes all cmake files in order to rebuild (or clean)
cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( blobFinder )
add_executable( blobFinder blobFinder.cc )
target_link_libraries( blobFinder ${OpenCV_LIBS} )

project( cvBlobFinder )
add_executable( cvBlobFinder cvBlobFinder.cc )
target_link_libraries( cvBlobFinder ${OpenCV_LIBS} )