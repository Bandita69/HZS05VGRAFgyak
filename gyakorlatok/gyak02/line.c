// hello world
// TODO: a többi függvényhez is beirni a pusht

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define ORIGO_X 320
#define ORIGO_Y 240
#define N 100

// a verem teteje -1, azért nem 0 mert a tömb indexelése 0-tól indul
int top = -1;
float stack[N][3][3];

typedef struct
{
    int x;
    int y;
    int z;
} Point;

typedef struct
{
    int r;
    int g;
    int b;
    int a;
} Color;
void PrintKeyInfo(SDL_KeyboardEvent *key);
float to_rad(double deg);
void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius, int szin);

float *cofactor(float[3][3], float);
float determinant(float[3][3], float);
float *transpose(float[3][3], float[3][3], float);
void push(float[3][3]); //  betesz egy elemet a verem tetejére
void pop();             // kivesz  a verem tetejéről
float *peek();          // visszaadja a verem tetejéről
bool isEmpty();         // üres-e a verem
bool isFull();          // tele van-e a verem

int main(int argc, char *argv[])
{
    // ez a rész a grafikus felület inicializálásához kell
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    // ez az ablak létrehozása
    SDL_Window *window = SDL_CreateWindow("teszt", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Could not create window: %s \n", SDL_GetError());
        return 1;
    }
    // ez a renderer létrehozása
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        fprintf(stderr, "Could not create renderer: %s \n", SDL_GetError());
        return 1;
    }

    SDL_Event event;
    int quit = 0;
    // ez a ciklus a grafikus felület megjelenítéséhez kell

    int x, y = 0;
    Point point;
    // csak egy kezdeti érték
    point.x = ORIGO_X;
    point.y = ORIGO_Y;
    point.z = 1;

    float pont[3] = {0, 0, 1};
    // itt amugy elég lenne egy result vector is, de így látszik hogy melyik pontot kell átadni
    float trans[3][3] = {{1, 0, 0},
                         {0, 1, 0},
                         {10, 10, 1}};
    float trans_inv[3][3] = {{1, 0, 0},
                             {0, 1, 0},
                             {-10, -10, 1}};

    float result[3] = {0, 0, 0};
    float scale[3][3] = {{2, 0, 0},
                         {0, 2, 0},
                         {0, 0, 1}};
    float result2[3] = {0, 0, 0};
    float scale_inv[3][3] = {{0.5, 0, 0},
                             {0, 0.5, 0},
                             {0, 0, 1}};
    float result22[3] = {0, 0, 0};
    float theta = to_rad(30);
    float rote[3][3] = {{cos(theta), -sin(theta), 0},
                        {sin(theta), cos(theta), 0},
                        {0, 0, 1}};
    float result3[3] = {0, 0, 0};
    float rote_acw[3][3] = {{cos(theta), sin(theta), 0},
                            {-sin(theta), cos(theta), 0},
                            {0, 0, 1}};
    float result4[3] = {0, 0, 0};
    float result5[3] = {0, 0, 0};
    int radius = 10;
    int szin = 0;

    // irjuk ki az xy tartalmat és a verem méretét állandóan
    if (TTF_Init() < 0)
    {
        printf("TTF_Init: %s    ", TTF_GetError());
    }

    TTF_Font *font = TTF_OpenFont("arial.ttf", 12);
    SDL_Color color = {255, 0, 0}; // r g b
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    rect.x = 69; // nice
    rect.y = 420;
    rect.h = 25;
    rect.w = 230;

    char text[20] = "x: y: ";
    while (!quit)
    {

        // ez a rész kitölti a képernyőt feketével
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        sprintf(text, "x: %d y: %d undo: %d", point.x, point.y, top + 1);
        if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
        {
            point.x = x;
            point.y = y;
        }

        while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                fprintf(stderr, "\n quit");
                quit = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    fprintf(stderr, "\n escape");
                    quit = 1;
                    break;
                case SDLK_UP:
                    pont[0] = point.x,
                    pont[1] = point.y;
                    pont[2] = 1;
                    result[0] = 0;
                    result[1] = 0;
                    result[2] = 0;
                    for (size_t i = 0; i < 3; i++)
                    {

                        for (size_t l = 0; l < 3; l++)
                        {
                            result[l] += trans_inv[i][l] * pont[i];
                        }
                    }
                    printf("\n +10,10 x: %f, y: %f", result[0], result[1]);

                    point.x = result[0];
                    point.y = result[1];

                    push(trans);
                  
                    break;
                case SDLK_DOWN:

                    pont[0] = point.x,
                    pont[1] = point.y;
                    pont[2] = 1;
                    result[0] = 0;
                    result[1] = 0;
                    result[2] = 0;
                    for (size_t i = 0; i < 3; i++)
                    {

                        for (size_t l = 0; l < 3; l++)
                        {
                            result[l] += trans[i][l] * pont[i];
                        }
                    }
                    printf("\n +10,10 x: %f, y: %f", result[0], result[1]);

                    point.x = result[0];
                    point.y = result[1];

                    float *inverse_tr = cofactor(trans, 3);
                    push(inverse_tr);
                    break;

                case SDLK_SPACE:

                    pont[0] = point.x,
                    pont[1] = point.y;
                    pont[2] = 1;
                    result2[0] = 0;
                    result2[1] = 0;
                    result2[2] = 0;
                    for (size_t i = 0; i < 3; i++)
                    {

                        for (size_t l = 0; l < 3; l++)
                        {
                            result2[l] += scale[i][l] * pont[i];
                        }
                    }

                    printf("\n x2 x: %f, y: %f", result2[0], result2[1]);

                    point.x = result2[0];
                    point.y = result2[1];

                    float *inverse_sc = cofactor(scale, 3);
                    push(inverse_sc);
                    break;
                case SDLK_BACKSPACE:

                    pont[0] = point.x,
                    pont[1] = point.y;
                    pont[2] = 1;
                    result22[0] = 0;
                    result22[1] = 0;
                    result22[2] = 0;
                    for (size_t i = 0; i < 3; i++)
                    {

                        for (size_t l = 0; l < 3; l++)
                        {
                            result22[l] += scale_inv[i][l] * pont[i];
                        }
                    }

                    printf("\n x2 x: %f, y: %f", result22[0], result22[1]);

                    point.x = result22[0];
                    point.y = result22[1];
                    float *inverse_sci = cofactor(scale_inv, 3);
                    push(inverse_sci);
                    break;

                case SDLK_LEFT:
                    pont[0] = point.x,
                    pont[1] = point.y;
                    pont[2] = 1;
                    result3[0] = 0;
                    result3[1] = 0;
                    result3[2] = 0;
                    for (size_t sor = 0; sor < 3; sor++)
                    {
                        for (size_t oszlop = 0; oszlop < 3; oszlop++)
                        {
                            result3[oszlop] += rote[oszlop][sor] * pont[sor];
                            printf("%f ", result3[oszlop]);
                        }
                        printf("\n");
                    }

                    printf("\n %f %f %f", result3[0], result3[1], result3[2]);

                    point.x = result3[0];
                    point.y = result3[1];
                    // float *inverse_rot = cofactor(rote, 3);
                    push(rote);

                    break;

                case SDLK_RIGHT:
                    pont[0] = point.x,
                    pont[1] = point.y;
                    pont[2] = 1;
                    result4[0] = 0;
                    result4[1] = 0;
                    result4[2] = 0;
                    for (size_t sor = 0; sor < 3; sor++)
                    {
                        for (size_t oszlop = 0; oszlop < 3; oszlop++)
                        {
                            result4[oszlop] += rote_acw[oszlop][sor] * pont[sor];
                            printf("%f ", result4[oszlop]);
                        }
                        printf("\n");
                    }

                    printf("\n %f %f %f", result4[0], result4[1], result4[2]);

                    point.x = result4[0];
                    point.y = result4[1];
                    // float *inverse_rotccw = cofactor(rote_acw, 3);
                    push(rote_acw);
                    break;

                case SDLK_1:
                    radius += 10;
                    printf("\n radius: %d", radius);
                    break;
                case SDLK_2:
                    radius -= 10;
                    printf("\n radius: %d", radius);
                    break;
                case SDLK_3:
                    switch (szin)
                    {
                    case 1:
                        szin = 0;
                        break;
                    case 0:
                        szin = 1;
                        break;

                    default:
                        break;
                    }

                    break;
                case SDLK_b:
                    if (top == -1)
                    {
                        printf("\n Nincs mit visszavonni\n");
                    }
                    else
                    {

                        printf("\n peek:\n");
                        float *z = peek();

                        pont[0] = point.x,
                        pont[1] = point.y;
                        pont[2] = 1;
                        result5[0] = 0;
                        result5[1] = 0;
                        result5[2] = 0;
                        int k = 0;
                        for (size_t i = 0; i < 3; i++)
                        {

                            for (size_t l = 0; l < 3; l++)
                            {
                                result5[l] += z[k] * pont[i];
                                k++;
                            }
                        }
                        printf("\n visszavonva x: %f, y: %f", result5[0], result5[1]);

                        point.x = result5[0];
                        point.y = result5[1];
                        pop();
                    }

                    break;

                default:
                    break;
                }

            default:
                break;
            }
        }

        surface = TTF_RenderText_Solid(font, text, color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_RenderCopy(renderer, texture, NULL, &rect);
        DrawCircle(renderer, point.x, point.y, radius, szin);
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        // SDL_RenderDrawLine(renderer, 0, 0, point.x, point.y);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius, int szin)
{
    // ez a függvény rajzol egy köröt a megadott koordinátákra és sugárral
    //  A kör egy nyolcadát rajzolja ki, majd a többi nyolcadat a megfelelő tükrözéssel.
    // a diameter változóban tároljuk a sugár kétszeresét, hogy ne kelljen minden ciklusban szorozni
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;

    int32_t tx = 1;
    int32_t ty = 1;
    // az error változóban tároljuk a kör alakját, hogy a következő pontot melyik irányba kell keresni
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Ezek a pontok a kör egy-egy nyolcadát rajzolják ki.
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        // ez az error kezelés a Bresenham algoritmusból származik
        //  https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
        //  https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    if (szin)
    {
        for (int w = 0; w < radius * 2; w++)
        {
            for (int h = 0; h < radius * 2; h++)
            {
                int dx = radius - w; // horizontal offset
                int dy = radius - h; // vertical offset
                if ((dx * dx + dy * dy) <= (radius * radius))
                {

                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderDrawPoint(renderer, centreX + dx, centreY + dy);
                }
            }
        }
    }
}
float to_rad(double deg)
{
    return deg * (M_PI / 180.0);
}
/* Print all information about a key event */
void PrintKeyInfo(SDL_KeyboardEvent *key)
{
    /* Is it a release or a press? */
    if (key->type == SDL_KEYUP)
        printf("Release:- ");
    else
        printf("Press:- ");

    /* Print the hardware scancode first */
    printf("Scancode: 0x%02X", key->keysym.scancode);
    /* Print the name of the key */
    printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
    /* We want to print the unicode info, but we need to make */
    /* sure its a press event first (remember, release events */
    /* don't have unicode info                                */
    if (key->type == SDL_KEYDOWN)
    {
        /* If the Unicode value is less than 0x80 then the    */
        /* unicode value can be used to get a printable       */
        /* representation of the key, using (char)unicode.    */
        printf(", Unicode: ");
        if (key->keysym.scancode < 0x80 && key->keysym.scancode > 0)
        {
            printf("%c (0x%04X)", (char)key->keysym.scancode,
                   key->keysym.scancode);
        }
        else
        {
            printf("? (0x%04X)", key->keysym.scancode);
        }
    }
    printf("\n");
}

// function for the calculation of determinant
float determinant(float a[3][3], float k)
{
    float s = 1, det = 0, b[3][3];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}

// function for cofactor calculation
float *cofactor(float num[3][3], float f)
{
    float b[3][3], fac[3][3];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    return transpose(num, fac, f);
}

/// function to find the transpose of a matrix
float *transpose(float num[3][3], float fac[3][3], float r)
{
    int i, j;
    static float inverse[3][3];
    float b[3][3], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }

    d = determinant(num, r);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }

    printf("\nThe inverse of matrix: \n");
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
        printf("\n");
    }
    return inverse;
}

// stack implementation

void push(float x[3][3])
{
    // Checking overflow state
    if (top == N - 1)
        printf("Overflow State: can't add more elements into the stack\n");
    else
    {

        top += 1;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                stack[top][i][j] = x[i][j];
            }
        }
    }
}

void pop()
{

    top -= 1;
}

float *peek()
{
    float *x;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f ", stack[top][i][j]);
        }
        printf("\n");
    }

    return stack[top];
}

bool isEmpty()
{
    if (top == -1)
    {
        printf("Stack is empty: Underflow State\n");
        return true;
    }
    printf("Stack is not empty\n");
    return false;
}

bool isFull()
{
    if (top == N - 1)
    {
        printf("Stack is full: Overflow State\n");
        return true;
    }
    printf("Stack is not full\n");
    return false;
}
