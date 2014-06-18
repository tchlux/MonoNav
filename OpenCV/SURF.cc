#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used

#define SURF_WINDOW "SURF"

int g_surf_minHessian = 2000; // The hessian value for the detector
int g_surf_numOctaves = 3; // Number of gaussian pyramid octaves,
			   // bigger numbers detect bigger features
int g_surf_octaveLayers = 2; // Number of images within each octave
int g_surf_extended = 1; // True if extended descriptors should
			       // be computed 
int g_surf_upright = 0;  // True if orientation does not need to be
			    // computed 
std::vector<cv::KeyPoint> g_surf_keypoints;

// Pre:  origImg is defined
// Post: Keypoints are calculated and drawn to a new image
void surfDetector(cv::Mat &origImg){
  cv::SURF detector(g_surf_minHessian, g_surf_numOctaves, 
  		    g_surf_octaveLayers, g_surf_extended,
  		    g_surf_upright);
  detector.detect( origImg , g_surf_keypoints );
  //-- Draw keypoints
  cv::Mat img_keypoints;
  drawKeypoints( origImg, g_surf_keypoints, img_keypoints,
		 cv::Scalar::all(-1), 
		 cv::DrawMatchesFlags::DEFAULT );

   imshow( SURF_WINDOW , img_keypoints );  
}
