cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( edgeFinderPic )
add_executable( edgeFinderPic edgeFinderPic.cc )
target_link_libraries( edgeFinderPic ${OpenCV_LIBS} )

project( edgeFinderPicAuto )
add_executable( edgeFinderPicAuto edgeFinderPicAuto.cc )
target_link_libraries( edgeFinderPicAuto ${OpenCV_LIBS} )

project( edgeFinderVid )
add_executable( edgeFinderVid edgeFinderVid.cc )
target_link_libraries( edgeFinderVid ${OpenCV_LIBS} )

project( blobTutorial )
add_executable( blobTutorial blobTutorial.cc )
target_link_libraries( blobTutorial ${OpenCV_LIBS} )

project( testImageTree )
add_executable( testImageTree testImageTree.cc )
target_link_libraries( testImageTree ${OpenCV_LIBS} )

project( testDerrivative )
add_executable( testDerrivative testDerrivative.cc )
target_link_libraries( testDerrivative ${OpenCV_LIBS} )

project( derrivativeTree )
add_executable( derrivativeTree derrivativeTree.cc )
target_link_libraries( derrivativeTree ${OpenCV_LIBS} )

project( testSmartDerrivative )
add_executable( testSmartDerrivative testSmartDerrivative.cc )
target_link_libraries( testSmartDerrivative ${OpenCV_LIBS} )

project( testBlobFinder )
add_executable( testBlobFinder testBlobFinder.cc )
target_link_libraries( testBlobFinder ${OpenCV_LIBS} )
