
#ifndef COMPONENT2D_H
#define COMPONENT2D_H

#include "mvc/Component.h"
#include "mvc/Projection2D.h"
#include "mvc/DisplayDevice.h"
#include "Image/Raster.h"

class Component2D : public Component
{
   private:

   protected:
      int mycolorid;        // Color cookie of Component color.
      long _layer;          // Layer this component is to be drawn on.
      bool _selectable;     // Whether or not the component is selectable.
      bool _drawselected;   // Whether or not we should draw the "selected"
                            // representation of the component.
      bool _visible;        // Whether or not the component can be seen.
      int _linewidth;
      double bb_x1,bb_y1;   // Corners of a bounding box (Minimum Bounding
      double bb_x2,bb_y2;   // Rectangle) for the component in world coords.

   public:

      Component2D(void);

      //
      // Attributes
      //
      virtual void setLayer(long layernum);
      virtual long getLayer(void);
         // The concept of a layer allows some control over the order
         // in which Components are drawn by views. Most views draw
         // objects to their DisplayDevice sorted in ascending order on
         // layer number. A special optimization is available in some views;
         // components with negative layer numbers (layer < 0) are 
         // drawn in a special "buffer" so that DisplayDevice expose events
         // are handled more efficiently. Default layer is zero (0).

      virtual void setSelectable(bool flag);
         // 'true' means that a component is a candidate for selection
         // by the model in response to a 'select' operation. 'false' means
         // that the component can not be selected. Default is 'true'.
      virtual bool isSelectable(void);
         // Queries the components select status (set by setSelectable).
      virtual void setDrawSelected(bool flag);
         // When true, causes the component to draw its "selected" mode
         // representation. The component draws this representation in
         // XOR mode on the DisplayDevice.

      virtual void setVisible(bool flag);
         // Controls whether or not a component is drawn. Default true.
      virtual bool isVisible(void);

      virtual void setLineWidth(int width);
      virtual void setLineColor(int colorcookie);



      //
      // Bounding Box
      //
      virtual void getBoundingBox(double& x1, double& y1,
                                  double& x2, double& y2);
         // Returns world coordinates for opposite corners of a 
         // minimum bounding box for the component.

      virtual void computeBoundingBox(void);
         // Causes component to recompute its bounding box. Normally,
         // the component uses this method automatically whenever 
         // something changes that would affect the MBR. Subclasses
         // with methods that are not defined in the Component2D class
         // and that could affect the MBR should call this method.

      virtual bool intersectsBox(double x1, double y1, double x2, double y2);
         // (x1,y1) (x2,y2) are opposite corners of a box. This method
         // returns 'true' if this component's bounding box is partially
         // or completely contained in the given box.

      //
      // Misc.
      //         
      virtual double getDistance(double x, double y);
         // Returns distance (in world coordinates) from component
         // to the point (x,y). Each component is expected to provide
         // this method (especially non-pointlike components).

      virtual void draw(Projection2D* proj, DisplayDevice* dd);
         // Draw Component on Display Device dd using projection proj.

      //
      // Transformations
      //
      virtual void rotate(double x, double y, double theta);
         // Rotate Component by theta radians around point (x,y).

      virtual void translate(double delta_x, double delta_y);
         // Translate Component.

      virtual void moveTo(double x, double y);
         // Move component to (x,y).

      virtual void scale(double sx, double sy);
	// Scale Component by sx in x and sy in y.



};

class PointComponent2D : public Component2D
{
   private:

   protected:
      double myx, myy;

   public:

      PointComponent2D(double x, double y, int colorid);

      void computeBoundingBox(void);

      double getDistance(double x, double y);

      void draw(Projection2D* proj, DisplayDevice* dd);

      void moveTo(double x, double y);

      virtual double getX(void);
      virtual double getY(void);
};

class SymbolComponent2D : public PointComponent2D
{
   private:
   protected:
      int mysize;
   public:
      SymbolComponent2D(double x, double y, int colorid);
      
      void setSize(int s);
      int getSize(void);
};

class PlusSymbolComponent2D : public SymbolComponent2D
{
   private:
   protected:
   public:
      PlusSymbolComponent2D(double x, double y, int colorid);
      void draw(Projection2D* proj, DisplayDevice* dd);
};

class LineComponent2D : public Component2D
{
   private:

   protected:

      double lx1,ly1;    // World Coordinates of line start point.
      double lx2,ly2;    // World Coordinates of line end point.


   public:

      LineComponent2D(double x1, double y1, double x2, double y2, int colorid);

      void draw(Projection2D* proj, DisplayDevice* dd);
         // Draw Component on Display Device dd using projection proj.

      void rotate(double x, double y, double theta);
         // Rotate Component by theta radians around point (x,y).

      void translate(double delta_x, double delta_y);
         // Translate Component.

      void scale(double sx, double sy);
	// Scale Component by sx in x and sy in y.

      void computeBoundingBox(void);

};

class PolyLineComponent2D : public Component2D
{
   private:

   protected:

      double *_x;   // Coordinates of points in polyline.
      double *_y;
      int _numpoints;

   public:
      
      PolyLineComponent2D(void);
      PolyLineComponent2D(double x[], double y[], int numpoints, int colorid);
      ~PolyLineComponent2D(void);

      void draw(Projection2D* proj, DisplayDevice* dd);

      void setPoints(double x[], double y[], int numpoints);

      void computeBoundingBox(void);

};

class RasterComponent2D : public Component2D, public Raster
{
   private:

   protected:

   public:

      RasterComponent2D(Image* theimage, double xres, double yres,
                        double wx, double wy, int wx_offset, int wy_offset);
         // theimage -- pointer to an Image that has already been init.
         // xres,yres -- resolution of an image pixel in world units.
         // wx,wy -- World coods of a pixel within the image.
         // wx_offset, wy_offset -- location of the (wx,wy) pixel in
         //    the image.

      void draw(Projection2D* proj, DisplayDevice* dd);
         // Draw Component on Display Device dd using projection proj.
};

#endif // COMPONENT2D_H
