#include "scene.h"

#include <GL/gl.h>
#include <math.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
}


// ez a függvény rajzolja ki a koordináta rendszer tengelyeit
void draw_origin()
{

    glBegin(GL_LINES);
    
    // increse draw distance
    
    
    // ez a függvény beállítja a színt, amivel a következő vertexeket rajzoljuk
    glColor3f(1, 0, 0);
    // ez a függvény beállítja a következő vertexeket
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    // ez a függvény rajzol egy háromszöget a vertexekből hát ez gyönyörű
    // glColor3f(1, 0, 1); 
    // glVertex3f(0, 0, 0);
    // glVertex3f(1, 1, 0);
    // glVertex3f(1, 1, 0);
    // glVertex3f(0.5, 0.5, 1);
    // glVertex3f(0.5, 0.5, 1);
    // glVertex3f(0, 0, 0);

    // ez a függvény egy kört rajzol
    // glColor3f(1, 1, 0);
    // for (int i = 0; i < 360; i += 10) {
    //     glVertex3f(0, 0, 0);
    //     glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
    // }

    //ez a függvény egy mandarint rajzol
    // glColor3f(1, 0.6, 0);
    // for (int i = 0; i < 360; i += 10) {
    //     for (int j = 0; j < 360; j += 10) {
    //         glVertex3f(cos(i * M_PI / 180) * sin(j * M_PI / 180), sin(i * M_PI / 180) * sin(j * M_PI / 180), cos(j * M_PI / 180));
    //         glVertex3f(cos(i * M_PI / 180) * sin((j + 10) * M_PI / 180), sin(i * M_PI / 180) * sin((j + 10) * M_PI / 180), cos((j + 10) * M_PI / 180));
    //         glVertex3f(cos((i + 10) * M_PI / 180) * sin(j * M_PI / 180), sin((i + 10) * M_PI / 180) * sin(j * M_PI / 180), cos(j * M_PI / 180));
    //         glVertex3f(cos((i + 10) * M_PI / 180) * sin((j + 10) * M_PI / 180), sin((i + 10) * M_PI / 180) * sin((j + 10) * M_PI / 180), cos((j + 10) * M_PI / 180));
    //     }
    // }

    // ez a függvény egy piramist rajzol
    // glColor3f(0, 1, 1);
    // for (int i = 0; i < 360; i += 10) {
    //     glVertex3f(0, 0, 0);
    //     glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
    //     glVertex3f(cos((i + 10) * M_PI / 180), sin((i + 10) * M_PI / 180), 0);
    //     glVertex3f(0, 0, 1);
    // }

    // ez a függvény egy szivet rajzol
    

    glColor3f(1, 0, 1);
    glLineWidth(50);
    for (int i = 0; i < 360; i += 10) {
        for (int j = 0; j < 360; j += 10) {
            glVertex3f((16 * pow(sin(i * M_PI / 180), 3))/10,( 13 * cos(i * M_PI / 180) - 5 * cos(2 * i * M_PI / 180) - 2 * cos(3 * i * M_PI / 180) - cos(4 * i * M_PI / 180))/10, 0.5);
            glVertex3f((16 * pow(sin((i + 10) * M_PI / 180), 3))/10, (13 * cos((i + 10) * M_PI / 180) - 5 * cos(2 * (i + 10) * M_PI / 180) - 2 * cos(3 * (i + 10) * M_PI / 180) - cos(4 * (i + 10) * M_PI / 180))/10, 0.5);
            glVertex3f((16 * pow(sin(i * M_PI / 180), 3))/10,( 13 * cos(i * M_PI / 180) - 5 * cos(2 * i * M_PI / 180) - 2 * cos(3 * i * M_PI / 180) - cos(4 * i * M_PI / 180))/10, 0.5);
            glVertex3f((16 * pow(sin((i + 10) * M_PI / 180), 3))/10, (13 * cos((i + 10) * M_PI / 180) - 5 * cos(2 * (i + 10) * M_PI / 180) - 2 * cos(3 * (i + 10) * M_PI / 180) - cos(4 * (i + 10) * M_PI / 180))/10, 0.5);
            glVertex3f((16 * pow(sin(i * M_PI / 180), 3))/10, (13 * cos(i * M_PI / 180) - 5 * cos(2 * i * M_PI / 180) - 2 * cos(3 * i * M_PI / 180) - cos(4 * i * M_PI / 180))/10, 0.5);
            glVertex3f((16 * pow(sin((i + 10) * M_PI / 180), 3))/10, (13 * cos((i + 10) * M_PI / 180) - 5 * cos(2 * (i + 10) * M_PI / 180) - 2 * cos(3 * (i + 10) * M_PI / 180) - cos(4 * (i + 10) * M_PI / 180))/10, 0.5);
        }
    }


   



    glEnd();
}
