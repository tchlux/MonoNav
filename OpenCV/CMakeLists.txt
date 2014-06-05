cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )
#project( firstProgram )
#add_executable( firstProgram firstProgram.cc )
#target_link_libraries( firstProgram ${OpenCV_LIBS} )

project( displayVideo )
add_executable( displayVideo displayVideo.cc )
target_link_libraries( displayVideo ${OpenCV_LIBS} )
