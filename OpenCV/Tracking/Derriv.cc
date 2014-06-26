
typedef cv::Vec3b px; // "px" for pixel 
// (blue, green, red)  is OpenCV default

// Returns the sum of a BGR pixel's channels
int sum(const px &pixel){
  return(pixel.val[0]+pixel.val[1]+pixel.val[2]);
}

// Pre:  pix1 and pix2 are defined with a ">" operator
// Post: The absolute value of the difference between them found using
//        a comparison check
px absDifference(const px &pix1, const px &pix2){
  px result(pix1 - pix2);
  if (sum(pix2) > sum(pix1))
     result = pix2 - pix1;  
  return result;
}

// Pre:  img defined
//       row-neighboorhood >= 0, row+neighboorhood < img.rows
//       col-neighboorhood >= 0, col+neighboorhood < img.cols
// Post: The derrivative at the given point (the positive difference
//       in pixel values "neighboorhood" distance from (row,col))
px pixelDerriv(const cv::Mat &img, const int &row,
	       const int &col, const int &neighboorhood){
  px leftX( img.at<px>(row,col-neighboorhood));
  px rightX(img.at<px>(row,col+neighboorhood));
  px xDiff( absDifference(leftX, rightX));

  px topY(   img.at<px>(row-neighboorhood,col));
  px bottomY(img.at<px>(row+neighboorhood,col));
  px yDiff(  absDifference(topY, bottomY));

  px diff(xDiff+yDiff);
  return ( diff);//  / neighboorhood );
}
// TODO:  This function is not optimized, there are many improvements
//        that can be made but I am leaving it as accurate as possible
//        until algorithm development is done

  // diff.val[0] /= neighboorhood;
  // diff.val[1] /= neighboorhood;
  // diff.val[2] /= neighboorhood;

// Pre:  img is defined, rows > 0, cols > 0, neighboorhood defined
// Post: Each pixel's value in the derrivative is the difference of
//       the pixels "neighboorhood" distance on either side of that
//       pixel both vertically and horizontally
void derriv(const const cv::Mat &inImg, cv::Mat &outImg,
	       const int &neighboorhood=1){
  for (int row(neighboorhood); 
       row < (inImg.rows - neighboorhood); row ++){
    for (int col(neighboorhood); 
	 col < (inImg.cols - neighboorhood); col ++){
      outImg.at<px>( row, col ) = 
	pixelDerriv(inImg,row,col,neighboorhood);
    }
  }  
  return derrivImg;
}
