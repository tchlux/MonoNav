cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( firstProgram )
add_executable( firstProgram firstProgram.cc )
target_link_libraries( firstProgram ${OpenCV_LIBS} )

project( displayVideo )
add_executable( displayVideo displayVideo.cc )
target_link_libraries( displayVideo ${OpenCV_LIBS} )

# project( bgfg_gmg )
# add_executable( bgfg_gmg bgfg_gmg.cpp )
# target_link_libraries( bgfg_gmg ${OpenCV_LIBS} )

project( cornerHarrisDemo )
add_executable( cornerHarrisDemo cornerHarrisDemo.cc )
target_link_libraries( cornerHarrisDemo ${OpenCV_LIBS} )

project( cornerHarrisVid )
add_executable( cornerHarrisVid cornerHarrisVid.cc )
target_link_libraries( cornerHarrisVid ${OpenCV_LIBS} )
