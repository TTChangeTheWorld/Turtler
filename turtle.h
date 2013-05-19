#ifndef TURTLE_H
#define TURTLE_H
//#include <errorclass.h>
#include <QImage>
class Turtle
{
private:
    QImage *object_image;
    int x;
    int y;
    int id;
public:
    Turtle(int _id, int _x, int _y);
    int getX();
    int getY();
    int getId();
    //ErrorClass setX(int _x);
    //ErrorClass setY(int _y);
};

#endif // TURTLE_H
