#include <iostream> //for cout and debugging
#include <complex>  //c++ complex num class
#include <ifstream> //for writing ppm images to file

#define DEPTH_THRESHOLD 4
#define DEFAULT_FILE "temp.ppm"
#define RGB_SIZE 3
#define RED 0
#define BLUE 1
#define GREEN 2


using namespace std;

int main(int argc, char * argv[]){
  int status = 0;

  return(status);
}


template class<T>
class Mandelbrot{
  //CI:  All variables are set at all times after initialization

protected:

  void parentUpdate; //The function to call to update the parent
  byte * lows;        //list of the three low integers for RGB
  byte * mids;        //list of the three mid ints for RGB
  byte * highs;       //list of three high ints for RGB
  int depth;         //Max calculation depth
  int dim;           //width of picture in pixels
  double a;          //complex a coordinate
  double b;          //complex b coordinate
  double hsize;      //half current zoom state
  int counter;       //counter used for status bar updates
  PPM ppm;           //holder for the ppm image class

public:

  // Pre:  
  // Post: Default construction
  Mandelbrot(){};

  // Pre:  newA, newB, size all are valid non-trash values
  //       red, green, and blue are arrays of length three
  //       depth and size are integers > 0
  // Post: These values are set into this class' protected members
  void set(double newA, double newB, double size, int dimensions,
	   int * red, int * green, int * blue, int newDepth){
    a        = newA;
    b        = newB;
    hsize    = size / 2;
    dim      = dimensions;
    depth    = newDepth;
    lows[0]  = red[0];
    mids[0]  = red[1];
    highs[0] = red[2];
    lows[1]  = green[0];
    mids[1]  = green[1];
    highs[1] = green[2];
    lows[2]  = blue[0];
    mids[2]  = blue[1];
    highs[2] = blue[2];
    ppm.set(dimensions);
  };

  // Pre:  x is a defined euclydian coordinate
  // Post: the x_complex coordinate of the given euclydian coord
  double xComplex(int x){
    double min_x  = a - hsize;
    double x_diff = a + hsize - min_x;
    return( ((x/dim)*x_diff) + min_x );
  };

  // Pre:  y is a defined euclydian coordinate
  // Post: the y_complex coordinate of the given euclydian coord
  double yComplex(int y){
    double min_y  = b - hsize;
    double y_diff = b + hsize - min_y;
    return( ((y/dim)*y_diff) + min_y );
  };

  // Pre:  c1, c2, and i are defined
  // Post: the corresponding RGB pixel values
  int * interpolate(byte * color1, byte * color2, float i){
    byte * pixel = new int[3];
    pixel[0]   = (1-i)*color1[0] + i*color2[0];
    pixel[1] = (1-i)*color1[1] + i*color2[1];
    pixel[2]  = (1-i)*color1[2] + i*color2[2];
    return(pixel);
  };

  // Pre:  x and y are euclydian points from the pixel image
  // Post: the integer depth value is returned
  int calculateDepth(int x, int y){
    int currDepth = 0;
    complex<double> init = complex(xComplex(x), yComplex(y));
    complex<double> cnum(init);
    bool maxedOut = false;
    while( (currDepth < depth)&&(!maxedOut) ){
      cnum = cnum*cnum + init;
      if (cnum*cnum > DEPTH_THRESHOLD){
	maxedOut = true;
      }
      currDepth++;
    }
    return(depth);
  };

  // Pre:  
  // Post: The mandelbrot image is calculated and saved
  void mandelbrot(){
    for (int y; y<height; y++){
      counter++;
      for (int x; x<width; x++){
	float currDepth = (float) calculateDepth(x, y);
	float c;
	byte * rgb;
	if (currDepth <= depth/2){
	  c = currDepth / (depth/2);
	  rgb = interpolate(lows, mids, c)
	}
	else{
	  c = (currDepth- (depth/2)) / depth;
	  rgb = interpolate(mids, highs, c)	  
	}
	ppm.setPixel(x,y,rgb);
      }
    }
  }
  ppm.write(); //write the ppm image to a file
}



// ========================================
//             PPM CLASS
// ========================================


class PPM{
  //CI: width / height >= 0, image is NULL or valid, not trash

protected:
  int width;
  int height;
  byte *** image;

public:
  // Pre:  
  // Post: Default constructor
  PPM(){
    width = 0;
    height = 0;
    image = NULL;
  };

  // Pre:  Some dimension is given
  // Post: a sqaure image with that dimension is produced
  PPM(int dimension){
    set(dimension, dimension);
  };

  // Pre:  width and height > 0
  // Post: image with given dimensions produced
  PPM(int w, int h){
    set(w, h);
  };

  // Pre:  dim is >= 0
  // Post: set height and width, DELETES OLD IMAGE, produces a new
  //       image holder with given width and height
  void set(int dim){
    set(dim, dim);
  };

  // Pre:  w and h are >= 0
  // Post: set height and width, DELETES OLD IMAGE, produces a new
  //       image holder with given width and height
  void set(int w, int h){
    if (image != NULL){
      delete(image);
    }
    width  = w;
    height = h;
    image  = new byte[width][height][RGB_SIZE]; //[col][row]
  };

  // Pre:  0 <= x < width, 0 <= y < height, values in rgb > 0
  // Post: The pixel at given (x,y) coord is set to rgb (deleted if
  //       already there)
  void setPixel(int x, int y, byte * rgb){
    if (image[x][y] != NULL){
      delete(image[x][y]);
    }
    image[x][y] = new byte[3];
    image[x][y][RED]   = rgb[RED]
    image[x][y][GREEN] = rgb[GREEN]
    image[x][y][BLUE]  = rgb[BLUE]
  }

  // Pre:  
  // Post: Default filename is used for write
  void write(){
    write(DEFAULT_FILE);
  };

  // Pre:  filename is properly terminated
  // Post: ppm file is produced
  void write(char * filename){
    ofstream out(filename);
    out << "P6 " << width << ' ' << height << ' '
	<< "255\n";
    for (int col; col<w; col++){
      for (int row; row<h; row++){
	for (int pix; pix<RGB_SIZE; pix++){
	  out << image[col][row][pix];
	}
      }
    }
    out.close();
  };

}
