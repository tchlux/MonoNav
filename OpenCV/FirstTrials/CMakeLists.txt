cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )

project( compareAlgVid )
add_executable( compareAlgVid compareAlgVid.cc )
target_link_libraries( compareAlgVid ${OpenCV_LIBS} )

#harris corner detector
project( cornerHarrisDemo )
add_executable( cornerHarrisDemo cornerHarrisDemo.cc )
target_link_libraries( cornerHarrisDemo ${OpenCV_LIBS} )

project( cornerHarrisVid )
add_executable( cornerHarrisVid cornerHarrisVid.cc )
target_link_libraries( cornerHarrisVid ${OpenCV_LIBS} )

#Lucas Kanade
project( lkdemo )
add_executable( lkdemo lkdemo.cpp )
target_link_libraries( lkdemo ${OpenCV_LIBS} )

#Farneback
project( myfback )
add_executable( myfback myfback.cc )
target_link_libraries( myfback ${OpenCV_LIBS} )

project( sparseRegionFback )
add_executable( sparseRegionFback sparseRegionFback.cc )
target_link_libraries( sparseRegionFback ${OpenCV_LIBS} )

#Feature detectors
project( siftFeatureDetector )
add_executable( siftFeatureDetector siftFeatureDetector.cc )
target_link_libraries( siftFeatureDetector ${OpenCV_LIBS} )

project( siftFeatureDetectorVideo )
add_executable( siftFeatureDetectorVideo siftFeatureDetectorVideo.cc )
target_link_libraries( siftFeatureDetectorVideo ${OpenCV_LIBS} )

project( surfFeatureDetector )
add_executable( surfFeatureDetector surfFeatureDetector.cc )
target_link_libraries( surfFeatureDetector ${OpenCV_LIBS} )

project( surfFeatureDetectorVideo )
add_executable( surfFeatureDetectorVideo surfFeatureDetectorVideo.cc )
target_link_libraries( surfFeatureDetectorVideo ${OpenCV_LIBS} )

#Lower level tests
project( sobelDerrivVid )
add_executable( sobelDerrivVid sobelDerrivVid.cc )
target_link_libraries( sobelDerrivVid ${OpenCV_LIBS} )

project( sparseRegionImg )
add_executable( sparseRegionImg sparseRegionImg.cc )
target_link_libraries( sparseRegionImg ${OpenCV_LIBS} )

project( sparseRegionVid )
add_executable( sparseRegionVid sparseRegionVid.cc )
target_link_libraries( sparseRegionVid ${OpenCV_LIBS} )
