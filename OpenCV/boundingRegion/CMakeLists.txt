cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( edgeVectorPic )
add_executable( edgeVectorPic edgeVectorPic.cc )
target_link_libraries( edgeVectorPic ${OpenCV_LIBS} )

project( edgeVectorVid )
add_executable( edgeVectorVid edgeVectorVid.cc )
target_link_libraries( edgeVectorVid ${OpenCV_LIBS} )
