#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include "opencv2/features2d/features2d.hpp" // On Vaio
//#include "opencv2/nonfree/features2d.hpp" //On HP

#define SIFT_WINDOW "SIFT"

int g_sift_numFeatures		= 0; 
int g_sift_octaveLayers		= 3; 
int g_sift_contrastThresh	= 4; 
int g_sift_edgeThresh		= 10;

std::vector<cv::KeyPoint> g_sift_keypoints;

// Pre:  origImg is defined
// Post: Keypoints are calculated and drawn to a new image
void siftDetector(cv::Mat &origImg){
  cv::SIFT detector(g_sift_numFeatures, g_sift_octaveLayers, 
		    ((float) g_sift_contrastThresh) / 100,
		    g_sift_edgeThresh );

  detector.detect( origImg , g_sift_keypoints );
  cv::Mat img_keypoints;
  drawKeypoints( origImg, g_sift_keypoints, img_keypoints,
		 cv::Scalar::all(-1), 
		 cv::DrawMatchesFlags::DEFAULT );
  imshow( SIFT_WINDOW , img_keypoints );  
}
