/**
 * @file   main.cpp
 * @author Bruno Jobard
 * @author Author1
 * @author Author2
 * @date   Sep 2012
 *
 * @brief  Declares an application, a main window and a 3D scene
 *
 *
 */
#include <QApplication>
#include "my_main_window.h"


#include "my_object3d.h"
#include "objects/cube.h"
#include "objects/pyramid.h"
#include "objects/cube_corner.h"
#include "objects/cylindre.h"
#include "objects/cone.h"
#include "objects/disk.h"
#include "objects/sphere.h"
#include "objects/tore.h"
#include "objects/func_surface.h"
#include "objects/off_loader.h"

/**
* Program usage
* Should be handled with the tclap library
*/
void usage(char* name){
    cout<< "usage: " << name << " [options]" <<endl;
    cout<< "options:" <<endl;
    cout<< "  -h, --help                 shows this message" <<endl;
    cout<< "  --off file                 loads OFF file" <<endl;
}

float func_expcos(float x, float y)
{
    return exp(-(x*x/2+y*y/2))*cos(2*x*x+2*y*y);
}

float func_cossin(float x, float y)
{
    return  cos(x)*sin(y);
}

float func_bumps(float x, float y)
{
    return sin(10*(x*x+y*y))/10;
}

float func_pyramid(float x,float y)
{
    return (1-abs(x+y))-abs(y-x);
}

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    // Parse program arguments here
    // with the tclap library
    // http://tclap.sourceforge.net/manual.html
    //

    // initialize my custom 3D scene
    float objectRadius = 1.;
    QPointer<MyScene> myScene = new MyScene(objectRadius);

    //simple objects
    myScene->addObject(new Cube());
    myScene->addObject(new Pyramid());
    myScene->addObject(new Cube_corner());
    myScene->addObject(new Disk(20));
    myScene->addObject(new Cylindre(20));
    myScene->addObject(new Cone(20));
    myScene->addObject(new Sphere(20));
    myScene->addObject(new Tore(20));

    // surface functions
    myScene->addObject(new FuncSurface(50,50,-PI,PI,-PI,PI,&func_expcos));
    myScene->addObject(new FuncSurface(50,50,-PI,PI,-PI,PI,&func_cossin));
    myScene->addObject(new FuncSurface(50,50,-1,1,-1,1,&func_bumps));
    myScene->addObject(new FuncSurface(50,50,-1,1,-1,1,&func_pyramid));

    // add user defined OFF files
    myScene->addObject(new OffLoader("data/aircraft.off"));

    // initialize my custom main window
    QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
    // display the window
    myMainWindow->show();
    // enter in the main loop
    return app.exec();
}

