#include "scene.h"
#include "app.h"

#include <GL/gl.h>
#include <math.h> // mert szeretem a pi(tét)

void init_scene(Scene *scene)
{
}

void update_scene(Scene *scene)
{
}

int getAppToggle(App *app)
{
    return app->toggle;
}

void render_scene(const Scene *scene, int toggle)
{
    draw_origin(toggle);
}

// ez a függvény rajzolja ki a koordináta rendszer tengelyeit
void draw_origin(int toggle)
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

    // ez a függvény egy kört rajzol
    // glColor3f(1, 1, 0);
    // for (int i = 0; i < 360; i += 10) {
    //     glVertex3f(0, 0, 0);
    //     glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
    // }

    // ez a függvény egy piramist rajzol
    // glColor3f(0, 1, 1);
    // for (int i = 0; i < 360; i += 10) {
    //     glVertex3f(0, 0, 0);
    //     glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
    //     glVertex3f(cos((i + 10) * M_PI / 180), sin((i + 10) * M_PI / 180), 0);
    //     glVertex3f(0, 0, 1);
    // }

    switch (toggle)
    {
    case (1):
        // ez a függvény egy szivet rajzol

        glColor3f(1, 0, 1);
        glLineWidth(50);
        for (int i = 0; i < 360; i += 10)
        {
            for (int j = 0; j < 360; j += 10)
            {
                glVertex3f((16 * pow(sin(i * M_PI / 180), 3)) / 10, (13 * cos(i * M_PI / 180) - 5 * cos(2 * i * M_PI / 180) - 2 * cos(3 * i * M_PI / 180) - cos(4 * i * M_PI / 180)) / 10, 0.5);
                glVertex3f((16 * pow(sin((i + 10) * M_PI / 180), 3)) / 10, (13 * cos((i + 10) * M_PI / 180) - 5 * cos(2 * (i + 10) * M_PI / 180) - 2 * cos(3 * (i + 10) * M_PI / 180) - cos(4 * (i + 10) * M_PI / 180)) / 10, 0.5);
                glVertex3f((16 * pow(sin(i * M_PI / 180), 3)) / 10, (13 * cos(i * M_PI / 180) - 5 * cos(2 * i * M_PI / 180) - 2 * cos(3 * i * M_PI / 180) - cos(4 * i * M_PI / 180)) / 10, 0.5);
                glVertex3f((16 * pow(sin((i + 10) * M_PI / 180), 3)) / 10, (13 * cos((i + 10) * M_PI / 180) - 5 * cos(2 * (i + 10) * M_PI / 180) - 2 * cos(3 * (i + 10) * M_PI / 180) - cos(4 * (i + 10) * M_PI / 180)) / 10, 0.5);
                glVertex3f((16 * pow(sin(i * M_PI / 180), 3)) / 10, (13 * cos(i * M_PI / 180) - 5 * cos(2 * i * M_PI / 180) - 2 * cos(3 * i * M_PI / 180) - cos(4 * i * M_PI / 180)) / 10, 0.5);
                glVertex3f((16 * pow(sin((i + 10) * M_PI / 180), 3)) / 10, (13 * cos((i + 10) * M_PI / 180) - 5 * cos(2 * (i + 10) * M_PI / 180) - 2 * cos(3 * (i + 10) * M_PI / 180) - cos(4 * (i + 10) * M_PI / 180)) / 10, 0.5);
            }
        }

        break;
    case (2):
        // ez a függvény egy mandarint rajzol
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1, 0.6, 0);
        for (int i = 0; i < 360; i += 10)
        {
            for (int j = 0; j < 360; j += 10)
            {
                glVertex3f(cos(i * M_PI / 180) * sin(j * M_PI / 180), sin(i * M_PI / 180) * sin(j * M_PI / 180), cos(j * M_PI / 180));
                glVertex3f(cos(i * M_PI / 180) * sin((j + 10) * M_PI / 180), sin(i * M_PI / 180) * sin((j + 10) * M_PI / 180), cos((j + 10) * M_PI / 180));
                glVertex3f(cos((i + 10) * M_PI / 180) * sin(j * M_PI / 180), sin((i + 10) * M_PI / 180) * sin(j * M_PI / 180), cos(j * M_PI / 180));
                glVertex3f(cos((i + 10) * M_PI / 180) * sin((j + 10) * M_PI / 180), sin((i + 10) * M_PI / 180) * sin((j + 10) * M_PI / 180), cos((j + 10) * M_PI / 180));
            }
        }

        break;
    case (3):
        // ez a függvény rajzol egy háromszöget  hát ez gyönyörű
        glEnd();
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); // piros
        glVertex2f(0, 0);
        glColor3f(0, 1, 0); // zöld
        glVertex2f(0, 1);
        glColor3f(0, 0, 1); // kék
        glVertex2f(1, 0);

        break;
    case (4):
        // ez a függvény egy piramist rajzol
        glColor3f(0, 1, 1);
        for (int i = 0; i < 360; i += 10)
        {
            glVertex3f(0, 0, 0);
            glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
            glVertex3f(cos((i + 10) * M_PI / 180), sin((i + 10) * M_PI / 180), 0);
            glVertex3f(0, 0, 1);
        }
        break;
    case (5):
        // ez a függvény egy sakk táblát készít
        glEnd(); // ez fontos
        glBegin(GL_QUADS);
        glColor3f(0, 0, 0);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {

                if ((i + j) % 2 == 0)
                {
                    glColor3f(1, 1, 1);
                }
                else
                {
                    glColor3f(0, 0, 0);
                }
                glVertex3f(i / 10.0, j / 10.0, 0);
                glVertex3f((i + 1) / 10.0, j / 10.0, 0);
                glVertex3f((i + 1) / 10.0, j / 10.0, 0);
                glVertex3f((i + 1) / 10.0, (j + 1) / 10.0, 0);
                glVertex3f((i + 1) / 10.0, (j + 1) / 10.0, 0);

                glVertex3f(i / 10.0, (j + 1) / 10.0, 0);
                glVertex3f(i / 10.0, (j + 1) / 10.0, 0);
                glVertex3f(i / 10.0, j / 10.0, 0);
            }
        }

        break;
    case (6):
        // TODO: betenni az egységkockán belülre
        // ez a függvény egy henger közelítését rajzolja ki
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1, 0, 0);
        for (int i = 0; i < 360; i += 10)
        {
            glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
            glVertex3f(cos((i + 10) * M_PI / 180), sin((i + 10) * M_PI / 180), 0);
            glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 1);
            glVertex3f(cos((i + 10) * M_PI / 180), sin((i + 10) * M_PI / 180), 1);
        }

        break;

    case (7):
        // ez a függvény egy kúp közelítését rajzolja ki
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0, 1, 0);
        for (int i = 0; i < 360; i += 10)
        {
            glVertex3f(0, 0, 1);
            glVertex3f(cos(i * M_PI / 180), sin(i * M_PI / 180), 0);
            glVertex3f(cos((i + 10) * M_PI / 180), sin((i + 10) * M_PI / 180), 0);
        }
        break;
    }

    glEnd();
}
