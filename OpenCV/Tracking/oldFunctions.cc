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


// Pre:  img, x, y , xMove, yMove all defined, optional initial
//       jumpScale and maxChannelDiff.
// Post: The farthest point in the (x,y) direction specified that
//       does NOT differ by more than "maxChannelDiff" on any ONE of
//       the channels in the pixel, so color matters. The edge of
//       the image is returned if it is reached.
cv::Point jumpToEdge(const cv::Mat &img, int x, int y,
		     const int &xMove, const int &yMove,
		     const px &blobColor,
		     int jumpScale=DEFAULT_JUMP, 
		     const int &maxChannelDiff=DEFAULT_DIFF_THRESH){
  x += (xMove*jumpScale);  y += (yMove*jumpScale);
  while (jumpScale >= MIN_JUMP_SCALE){
    // If the pixel is in the image and similarly colored, continue to jump
    if (inBounds(img, x, y) &&
	(! channelsDiff(blobColor, img.at<px>(y, x), maxChannelDiff))){
      x += (xMove*jumpScale); y += (yMove*jumpScale);
    }
    else{
      // Subtract out the old jump
      x -= (xMove*jumpScale); y -= (yMove*jumpScale);
      // Divide the jump amount by two
      jumpScale >>= 1;
      // Add the new half jump
      x += (xMove*jumpScale); y += (yMove*jumpScale);      
    }
  }
  return cv::Point(x,y);
}


// Pre:  xDir and yDir defined, only one of them is non-zero
// Post: The next direction to travel (cycles clockwise)
void setUniDirection4(int &xDir, int &yDir){
  if (yDir == -1){
    yDir = 0;  xDir = 1;
  }
  else if (xDir == 1){
    yDir = 1;  xDir = 0;
  }
  else if (yDir == 1){
    yDir = 0;  xDir = -1;
  }
  else{
    yDir = -1; xDir = 0;
  } 
}

// Pre:  inImg and outImg defined and of equal dimensions
//       col and row are the starting point, depth is the max number
//       of "jump to Edge" function calls allowed
// Post: The out image is colored based off the results of performing
//       a single directional search for the boundaries of a blob
void uniDirection4(const cv::Mat &inImg, cv::Mat &outImg,
		   const int &col, const int &row, const int &depth){
  const px blobColor(inImg.at<px>(row, col));
  float ptsFound(0);
  float avgX(col);
  float avgY(row);
  int xDir(0);
  int yDir(-1);
  cv::Point edge(col,row);
  outImg.at<px>(row,col) = px(255,0,0);
  for (int i(0); i<depth; i++){
    edge = jumpToEdge(inImg, edge.x, edge.y, xDir, yDir, blobColor);
    setUniDirection4(xDir, yDir);
    // Dynamically calculate average
    ptsFound++;
    avgX += ((edge.x-avgX)*g_frac)/ptsFound;
    avgY += ((edge.y-avgY)*g_frac)/ptsFound;
    outImg.at<px>(edge.y,edge.x) = px(0,0,255);
  }
  outImg.at<px>(avgY,avgX) = px(0,255,0);
}

// Pre:  xDir and yDir defined, only one of them is non-zero
// Post: The next direction to travel (horizontal / vertical switch)
void setUniDirection8(int &xDir, int &yDir){
  if ((yDir == -1) && (xDir == 0)){
    xDir = 1;
  }
  else if ((xDir ==  1) && (yDir == -1)){
    yDir = 0;
  }
  else if ((yDir ==  0) && (xDir == 1)){
    yDir = 1;
  }
  else if ((yDir ==  1) && (xDir == 1)){
    xDir = 0;
  }
  else if ((xDir ==  0) && (yDir == 1)){
    xDir = -1;
  }
  else if ((xDir == -1) && (yDir == 1)){
    yDir = 0;
  }
  else if ((yDir ==  0) && (xDir == -1)){
    yDir = -1;
  }
  else if ((yDir == -1) && (xDir == -1)){
    xDir = 0;
  } 
  else
    std::cerr << "setUniDirection8 logic crash." 
	      << std::endl;
}

// Pre:  inImg and outImg defined and of equal dimensions
//       col and row are the starting point, depth is the max number
//       of "jump to Edge" function calls allowed
// Post: The out image is colored based off the results of performing
//       a single directional search for the boundaries of a blob
void uniDirection8(const cv::Mat &inImg, cv::Mat &outImg,
		   const int &col, const int &row, const int &depth){
  const px blobColor(inImg.at<px>(row, col));
  float ptsFound(0);
  float avgX(col);
  float avgY(row);
  int xDir(0);
  int yDir(-1);
  cv::Point edge(col,row);
  outImg.at<px>(row,col) = px(255,0,0);
  for (int i(0); i<depth; i++){
    edge = jumpToEdge(inImg, edge.x, edge.y, xDir, yDir, blobColor);
    setUniDirection8(xDir, yDir);
    // Dynamically calculate average
    ptsFound++;
    avgX += ((edge.x-avgX)*g_frac)/ptsFound;
    avgY += ((edge.y-avgY)*g_frac)/ptsFound;
    outImg.at<px>(edge.y,edge.x) = px(0,0,255);
  }
  outImg.at<px>(avgY,avgX) = px(0,255,0);
}

// Pre:  xDir and yDir defined, only one of them is non-zero
// Post: The next direction to travel (cycles clockwise)
void setBiDirection4(int &xDir, int &yDir){
  if (yDir == -1){
    yDir = 1;  xDir = 0;
  }
  else if (yDir == 1){
    yDir = 0;  xDir = 1;
  }
  else if (xDir == 1){
    yDir = 0;  xDir = -1;
  }
  else{
    yDir = -1; xDir = 0;
  } 
}

// Pre:  inImg and outImg of equal dimensions, row and col within
//       the bounds of the image. depth >= 0
// Post: A North/South median followed by a East/West median point,
//       continues until 'depth' is reached.  The starting point is
//       marked blue, the collected dots are marked as red, and the
//       average points are marked as green.
void biDirection4(const cv::Mat &inImg, cv::Mat &outImg,
		  const int &col, const int &row, const int &depth){
  const px blobColor(inImg.at<px>(row, col));
  float avgX(col);
  float avgY(row);
  int xDir(0);
  int yDir(-1);
  cv::Point edge1(col,row);
  cv::Point edge2(col,row);
  outImg.at<px>(row,col) = px(255,0,0);
  for (int i(0); i<depth; i+=2){
    const int x((edge1.x+edge2.x)/2);
    const int y((edge1.y+edge2.y)/2);
    edge1 = jumpToEdge(inImg, x, y, xDir, yDir, blobColor);
    setBiDirection4(xDir, yDir);
    edge2 = jumpToEdge(inImg, x, y, xDir, yDir, blobColor);
    setBiDirection4(xDir, yDir);
    // Dynamically calculate average
    avgX += (x-avgX)/g_frac;
    avgY += (y-avgY)/g_frac;
    outImg.at<px>(edge1.y,edge1.x) = px(0,0,255);
    outImg.at<px>(edge2.y,edge2.x) = px(0,0,255);
  }  
  outImg.at<px>(avgY,avgX) = px(0,255,0);
}


  // int algorithm(3);
  // cv::createTrackbar("Algorithm", TRACKBAR_WINDOW, &algorithm,
  // 		     3, callbackDummy);
  //   	if (algorithm == 0)
  //   	  uniDirection4(img, imgDerriv, col, row, depth);
  //   	else if (algorithm == 1)
  //   	  uniDirection8(img, imgDerriv, col, row, depth);
  //   	else if (algorithm == 2)
  //   	  biDirection4(img, imgDerriv, col, row, depth);
  //   	else if (algorithm == 3)

      //	(! channelsDiff(blobColor, img.at<px>(y, x), maxChannelDiff))){

// // TODO:  This formula will update the average based off the old
// //        average, a new value value, and the number of data points
// //        already contained in the average given
// void updateAverage(float &avg, const int &value, const int &pts){
//   avg += ((value-avg)*g_frac)/pts;
//   // avg += ((value*f)/pts) - ((avg*f)/pts);
//   // avg = avg + (-((avg*f)/pts) + ((value*f)/pts));
//   // avg = avg - ((avg*f)/pts) + ((value*f)/pts);
//   // avg = avg * (1 - f/pts) + ((value*f)/pts);
//   // avg = avg * ((pts-f)/pts) + value * (1/pts);
// }

// // Pre:  px1, px2, maxChannelDiff defined
// // Post: true if the SQUARED difference in pixel values for any ONE
// //       channel exceed "maxChannelDiff"
// bool channelsDiff(const px &px1, const px &px2, 
// 		  const int &maxChannelDiff=DEFAULT_DIFF_THRESH){
//   if ((( (px1[0]+px1[1]+px1[2]) - (px2[0]+px2[1]+px2[2]) ) > maxChannelDiff*3) ||
//       (( (px2[0]+px2[1]+px2[2]) - (px1[0]+px1[1]+px1[2]) ) > maxChannelDiff*3))
//     return true;
//   return false;
// }

