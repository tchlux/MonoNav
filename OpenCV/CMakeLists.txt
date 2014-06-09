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

project( sobelDerrivVid )
add_executable( sobelDerrivVid sobelDerrivVid.cc )
target_link_libraries( sobelDerrivVid ${OpenCV_LIBS} )

project( testFeatureDetectImg )
add_executable( testFeatureDetectImg testFeatureDetectImg.cc )
target_link_libraries( testFeatureDetectImg ${OpenCV_LIBS} )

project( surfFeatureDetector )
add_executable( surfFeatureDetector surfFeatureDetector.cc )
target_link_libraries( surfFeatureDetector ${OpenCV_LIBS} )

project( surfFeatureDetectorVideo )
add_executable( surfFeatureDetectorVideo surfFeatureDetectorVideo.cc )
target_link_libraries( surfFeatureDetectorVideo ${OpenCV_LIBS} )

project( siftFeatureDetector )
add_executable( siftFeatureDetector siftFeatureDetector.cc )
target_link_libraries( siftFeatureDetector ${OpenCV_LIBS} )
