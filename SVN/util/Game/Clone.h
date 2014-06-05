#ifndef DEFINED_CLONE
#define DEFINED_CLONE

#include "iostream"
#include "Matrix.h"
#include "Vertex.h"
#include "Link.h"
#include "Model.h"
#include "Camera.h"

// Pre:  bBox is a bounding box for an object to test overlap on. 
//       n (normal) is the normal that bBox will be projected onto
// Post: min and max are set for this bBox being projected onto normal
void boxToLine(Vertex * bBox, Vertex & n, float &min, float &max);
class Clone{
  // CI:  This class will hold the data necessary for one occurance
  //      of a model in an environment
protected:
  Model * Maker; // This will be the model that the clone is built
  //  off of
  Matrix<float> * modelMatrix;
  // This matrix will hold the
  //   transformations for this clone
  Camera * Cam; // The camera for the view and projection

public:
  Vertex Center; // The center of this clone
  float Radius;  // The radius of this clone
  float Momentum; // The momentum of this clone object

  // Pre:  Maker is a well defined Model object, similare of camera
  // Post: This clone is initialized
  Clone(Model * model, Camera * cam);

  // Pre:  N/a
  // Post: if modelMatrix has been initialized then it will be deleted
  ~Clone();

  // Post: Returns the vertex that represents this clone's position
  Vertex & pos();
  Vertex & position();

  // Pre:  x,y,z are defined valid coordinates
  // Post: The model matrix is set to this location
  void move(float x, float y, float z);

  // Pre:  x, y, and z are defined
  // Post: The current matrix for 
  void translate(float x, float y, float z);

  // Pre:  amount, x, y, and z are defined
  // Post: The current matrix for 
  void rotate(float amount, float x, float y, float z);

  // Pre:  x,y,z are all positive scalar factors
  // Post: The model is scaled by the amount given
  void scale(float x, float y, float z);

  // Pre:  The modelMatrix is initilaized, view and projection are
  //       from camera
  // Post: The model is drawn to this location
  void draw(const Matrix<float> * view, 
	    const Matrix<float> * projection);

  // Pre:  The modelMatrix is initialized, cam is stored in this
  // Post: This model instance is drawn
  void draw();

  // Pre:  dot is s clone that should be drawn at each vertex of bBox
  // Post: All of the bBox corners of this clone are
  //       highlighted with the 'dot' clone
  void drawBBox(Clone & dot);

  // Pre:  bBox is defined
  // Post: bBox is filled with Vertices transformed by mat
  void genBox(Vertex * bBox) const;

  // Pre:  nBox is empty and ready to be initialized, bBox has been
  //       constructed with the "genBox" static method
  // Post: The normals for this bounding box are generated
  static void genNorm(Vertex * nBox, Vertex * bBox);

  // Pre:  nBox1 and nBox2 are of length NORMAL_BOX_SIZE and initialized
  // Post: All of the extra normals are generated for the special case
  static void genExtraNorm(Vertex * extraN, Vertex * nBox1, 
			   Vertex * nBox2);

  // Pre:  (eject, ejectAmount, c1Min, c2Min) need to be initialized
  //       c1 and c2 should be constructed and in use with valid
  //       bounding boxes and Model's as "Maker"s
  // Post: The default collision on the 6 normals of the two clones is
  //       performed, if that collisions produces true, then the extra
  //       special case for collision on the all of the cross products
  //       of the normal pairs is run (9 extra normals).  true if the
  //       two bounding boxes for these clones are colliding
  static bool standardCollision(Vertex & eject, float & ejectAmount,
				float & c1Min, float & c2Min, 
				Clone & c1, Clone & c2);

  // Pre:  bBox1 & bBox2 are both initialized by Clone::genBox,
  //       (eject, ejectAmount, c1Min, c2Min) need to be initialized
  // Post: The two boxes given are projected to norm and then tested for
  //       oeverlap, if there is overlap and it is the smallest overlap
  //       that has been seen (smaller ejectAmount) then the information
  //       about this check is recored in c1Min, c2Min, eject, and
  //       ejectAmount 
  static void CheckBoxesAndNormal(Vertex * bBox1, Vertex * bBox2,
				  Vertex & norm, float & olap,
				  Vertex & eject, float & ejectAmount,
				  float & c1Min, float & c2Min);

  // Pre:  c1 and c2 are well defined, eject is either true or false
  // Post: Handles collision, true if there was a collision, if eject
  //       is true then the clones are ejected according to their
  //       momentum values, if false no ejection is performed
  static bool Collides(Clone & c1, Clone & c2, bool e);

  // Pre:  out and clone are defined properly
  // Post: The information in clone is sent to this ostream
  friend std::ostream & operator<<(std::ostream & out, Clone & clone);
};


#endif
