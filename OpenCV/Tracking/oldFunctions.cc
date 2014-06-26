// =========================================
//      FUNCTIONS I'M NOT USING ANYMORE     
// =========================================

// USED TO COMBINE TWO IMAGES

// TODO:  This function will add img1 and img2 placing the results in 2
void addImages( const cv::Mat &img1, cv::Mat &img2 ){
  for (int row(0); row < img1.rows; row++){
    for (int col(0); col < img1.cols; col++){
      img2.at<px>(row,col) = img1.at<px>(row,col) + img2.at<px>(row,col);
    }
  }    
}


// This function returns a matrix whose contents are only those that
//  were in both images provided and above "threshold"

// Pre:  img1 and img2 are defined and of the same dimensions
// Post: A cv::Mat that has the bright spots from both images
cv::Mat andThresh(cv::Mat img1, cv::Mat img2){
  int rows(img1.rows);
  int cols(img1.cols);
  cv::Mat combo(rows, cols, CV_8UC3);

  for (int row(0); row < rows; row ++){
    for (int col(0); col < cols; col ++){
      combo.at<cv::Vec3b>( row, col ) =
      	(img1.at<cv::Vec3b>(row, col) + img2.at<cv::Vec3b>(row, col))
      	/ 2;
    }
  }
  return(combo);
}
