#include <iostream> // For "cerr"
#include <opencv2/opencv.hpp> // Defines the namespace "cv" and all
                              //  the cv functions and types used
#include <assert.h>
#include "tetraMedian.cc"
#include "objectManagement.cc"

#define BLOBS_WINDOW "Detected Blobs"
#define ORIGINAL_IMAGE "Original Image"

#define HP_ESC_KEY 1048603
#define VAIO_ESC_KEY 27


// TODO:  Retrieves one video frame or image depending on command line args
void getImage(const int &argc, char *argv[], 
	      cv::VideoCapture &vid, cv::Mat &img);

// TODO: Initializes all images for the blob detector
void initializeImages(const int &argc, char *argv[],
		      cv::VideoCapture &vid, cv::Mat &img,
		      cv::Mat &blobImg);

// TODO:  This function initializes the cv windows for displaying
void initializeCV(RecursiveMedian &detector, const int &maxSamples);


// TODO:  This function will provide testing ground for the vector
//        based image derrivative
int main(int argc, char *argv[]){
  RecursiveMedian detector;
  BlobVec blobs; // This is the list of blobs in the image
  ObjVec groups; // This is where tracking is done
  // Initialize variables, the video from the webcam needs to be flipped
  cv::Mat img, temp, blobImg;;
  cv::VideoCapture vid(0);

  initializeImages(argc, argv, vid, img, blobImg);
  initializeCV(detector, (img.rows*img.cols) / 512);

  int keyPressed(-1);
  // Main test runs until user presses escape key
  while ((keyPressed != HP_ESC_KEY) && (keyPressed != VAIO_ESC_KEY)){
    getImage(argc, argv, vid, img);

    // Reset the blob image to black
    blobImg.setTo(cv::Scalar(0,0,0));

    detector.detect(img, blobs); // Fill the vector of blobs
    drawBlobs(img, blobs); // Draw blob boundaries on original image

    trackGroups(blobs, groups);
    drawGroups(blobImg, groups, 2); // Draw the high level blobs
    // drawBlobs(cv::Mat outImage, BlobVec blobs, 
    //           int minLife, float minVelocity)

    cv::imshow(ORIGINAL_IMAGE, img);
    cv::imshow(BLOBS_WINDOW, blobImg);

    blobs.clear();
    resetGroups(groups);

    keyPressed = cv::waitKey(1);
    if (keyPressed == 1048608){
      blobs.clear();
      groups.clear();
    }
  }

  return 0;
}

// TODO:  Retrieves one video frame or image depending on command line args
void getImage(const int &argc, char *argv[], 
	      cv::VideoCapture &vid, cv::Mat &img){
  if (argc == 1){
    cv::Mat temp;
    vid >> temp;
    cv::flip(temp, img, 1); 
  } else if (argc == 2){
    vid >> img;
    if (img.empty()){
      vid.release();
      vid.open(argv[1]);
      vid >> img; 
    }
  } 
  else{
    img = cv::imread(argv[1]); 
  }
}

// TODO: Initializes all images for the blob detector
void initializeImages(const int &argc, char *argv[],
		      cv::VideoCapture &vid, cv::Mat &img,
		      cv::Mat &blobImg){
  cv::Mat temp;
  vid >> temp;  
  cv::flip(temp, img, 1);

  if (argc == 2){     // Video provided as command line argument
    vid.open(argv[1]);      
    vid >> img;
  }
  if (argc >= 3)      // Image file provided along with flag
    img = cv::imread(argv[1]);

  img.copyTo(blobImg);
}

// TODO:  This function initializes the cv windows for displaying
void initializeCV(RecursiveMedian &detector, const int &maxSamples){
  cv::namedWindow(ORIGINAL_IMAGE, CV_WINDOW_NORMAL);
  cv::waitKey(50); // To ensure windows do not overlap
  cv::namedWindow(BLOBS_WINDOW, CV_WINDOW_NORMAL);
  cv::createTrackbar("Samples", BLOBS_WINDOW, &detector.samples, 
		     maxSamples);
}
