#include <iostream>

#define TRANS_ARRAY_LEN 9 // Length of a transormation array
#define ESCAPE_NUMBER 2 // Number that signals the end of a while loop

// Pre:  t1 and t2 are of length 9, time is between 0 and 1
// Post: The transformation array that is interpolated between those
//       points
float * interpolate_transformation(const float *t1, const float *t2,
				   float time){
  float * res = new float[TRANS_ARRAY_LEN];
  for (int i=0; i<TRANS_ARRAY_LEN; i++){
    res[i] = t1[i]*(1.0-time) + t2[i]*(time);
  }
  return(res);
}

// Pre:  res is of length TRANS_ARRAY_LEN allocated with new
// Post: res is couted and then deleted
void cout_result(float * res){
  std::cout << "[";
  for (int i=0; i<TRANS_ARRAY_LEN; i++){
    std::cout << res[i] << ", ";
  }
  std::cout << "\b\b ]" << std::endl;
  delete(res);
}

// Testing the interpolate funtion
int main(int argc, char * argv[]){
  // float trans1[TRANS_ARRAY_LEN], trans2[TRANS_ARRAY_LEN];
  float trans1[TRANS_ARRAY_LEN] = {1, 1, 1,  1, 1, 1,  1, 1, 1};
  float trans2[TRANS_ARRAY_LEN] = {0, 0, 0,  0, 0, 0,  0, 0, 0};
  float * result;
  float time = 0.5;
  std::cout << "Type " << ESCAPE_NUMBER << " to exit" << std::endl;
  while (time != ESCAPE_NUMBER){
    std::cin >> time;
    std::cout << std::endl;
    cout_result(interpolate_transformation(trans1, trans2, time));
  }
}
