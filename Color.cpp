#include "Color.h"

const GLfloat Color::Black[] = { 0.0, 0.0, 0.0 };
const GLfloat Color::White[] = { 1.0, 1.0, 1.0 };
const GLfloat Color::Red[] = { 1.0, 0.0, 0.0 };
const GLfloat Color::Green[] = { 0.0, 1.0, 0.0 };
const GLfloat Color::Blue[] = { 0.0, 0.0, 1.0 };
const GLfloat Color::Yellow[] = { 1.0, 1.0, 0.0 };
const GLfloat Color::Purple[] = { 0.5, 0, 0.5 };
const GLfloat Color::Grey[] = { 0.5, 0.5, 0.5 };
const GLfloat Color::Brown[] = { 0.6, 0.3, 0 };
const GLfloat Color::DarkBlue[] = { 15/255.0, 30/255.0, 53/255.0 };

const GLfloat Color::Leg[] = { 73 / 255.0, 67 / 255.0, 40 / 255.0 , 1.0 };
const GLfloat Color::Tail[] = { 0.3, 0.25, 0.05 , 1.0 };
const GLfloat Color::Torso[] = { 0.5, 0.35, 0.05, 1.0 };
const GLfloat Color::TorsoDiffuse[] = { 0.4, 0.3, 0.02, 1.0 };
const GLfloat Color::Face[] = { 0.5, 0.35, 0.05, 1.0 };
const GLfloat Color::Neck[] = { 0.5, 0.35, 0.05, 1.0 };
const GLfloat Color::Head[] = { 0.5, 0.35, 0.05, 1.0 };
const GLfloat Color::Ear[] = { 0.4, 0.35, 0.05, 1.0 };
const GLfloat Color::Eye[] = { 0.05, 0.05, 0.05, 1.0 };
const GLfloat Color::Mouth[] = { 0.3176, 0, 0, 1.0 };
const GLfloat Color::Nose[] = { 0.3176, 0.20392, 0.01568, 1.0 };

const GLfloat Color::TableLeg[] = { 0.26666, 0.1372, 0, 1.0 };
const GLfloat Color::TableSurface[] = { 0.316, 0.184, 0.04, 1.0 };

const GLfloat Color::FloorPlate1[] = { 234 / 255.0, 154 / 201.0, 97 / 156.0, 1.0 };
const GLfloat Color::FloorPlate2[] = { 206 / 255.0, 154/255.0, 97/255.0, 1.0 };


/*
Materials light settings:
http://devernay.free.fr/cours/opengl/materials.html
*/
//Silver:
//const GLfloat Color::TeapotAmbient[] = { 0.19225, 0.19225, 0.19225 };
//const GLfloat Color::TeapotDiffuse[] = { 0.50754, 0.50754, 0.50754 };
//const GLfloat Color::TeapotSpecular[] = { 0.508273, 0.508273, 0.508273 };

//Gold:
const GLfloat Color::TeapotAmbient[] = { 0.24725, 0.1995, 0.0745 };
const GLfloat Color::TeapotDiffuse[] = { 0.75164, 0.60648, 0.22648 };
const GLfloat Color::TeapotSpecular[] = { 0.628281, 0.555802, 0.366065 };