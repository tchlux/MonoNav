cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( edgeVectorPic )
add_executable( edgeVectorPic edgeVectorPic.cc )
target_link_libraries( edgeVectorPic ${OpenCV_LIBS} )

project( edgeVectorPicAuto )
add_executable( edgeVectorPicAuto edgeVectorPicAuto.cc )
target_link_libraries( edgeVectorPicAuto ${OpenCV_LIBS} )

project( edgeVectorVid )
add_executable( edgeVectorVid edgeVectorVid.cc )
target_link_libraries( edgeVectorVid ${OpenCV_LIBS} )

project( blobTutorial )
add_executable( blobTutorial blobTutorial.cc )
target_link_libraries( blobTutorial ${OpenCV_LIBS} )

project( testImageTree )
add_executable( testImageTree testImageTree.cc )
target_link_libraries( testImageTree ${OpenCV_LIBS} )
