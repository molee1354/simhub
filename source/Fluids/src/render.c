#include <GL/glut.h>
#include <math.h>

#include "fluids_commonincl.h"

static int windowWidth = WINDOW_WIDTH;
static int windowHeight = WINDOW_HEIGHT;

static int obstacle_x = WINDOW_WIDTH/2;
static int obstacle_y = WINDOW_HEIGHT/2;

#define FPS 60

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double domainHeight;
static double domainWidth;
static double simHeight;
static double cScale;
static double simWidth;
static int cellSize;

Fluid* fluid = NULL;

#define OBSTACLE_COLOR .82, .82, .82
#define WHITE 1.0f, 1.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f

typedef struct {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
} RGB;

static void initSimParam() {
    simHeight = 1.1;
    cScale = WINDOW_HEIGHT / simHeight;
    simWidth = WINDOW_WIDTH / cScale;

    domainHeight = 1.;
    domainWidth = domainHeight / simHeight * simWidth;
}

static double cX(int x) {
    return (double)x * cScale;
}

static double cY(int y) {
    return WINDOW_HEIGHT - (double)y * cScale;
}

static void setObstacle(Fluid* fluid, int x, int y, bool reset) {
    double vx = 0.;
    double vy = 0.;

    if (!reset) {
        vx = (x - obstacle_x) / DT;
        vy = (y - obstacle_y) / DT;
    }

    obstacle_x = x;
    obstacle_y = y;

    int n = fluid->numY;
    double obsRad = OBSTACLE_RADIUS;

    for (int i = 1; i < fluid->numX-2; i++) {
        for (int j = 1; j < fluid->numY-2; j++) {
            fluid->s[i*n + j] = 1.;

            double dx = ((double)i + .5) * fluid->h - ((double)x/WINDOW_WIDTH)*domainWidth;
            double dy = ((double)j + .5) * fluid->h - ((double)y/WINDOW_HEIGHT)*domainHeight;
            double rad2 = (double)(obsRad*obsRad);

            if (dx*dx + dy*dy < rad2) {
                fluid->s[i*n + j] = 0.;
                fluid->m[i*n + j] = 1.;

                fluid->u[i*n + j] = vx;
                fluid->u[(i+1)*n + j] = vx;
                fluid->v[i*n + j] = vy;
                fluid->v[i*n + j+1] = vy;
            }
        }
    }
}

static RGB getColor(double value, double minVal, double maxVal) {
    RGB out;
    double red, green, blue;
    
    value = findMin( findMax(value, minVal), maxVal - 0.0001);
    double diff = maxVal - minVal;

    value = diff == 0. ? .5 : (value - minVal) / diff;

    double m = .25;
    int num = (int)floor(value/m);

    double s = (value - (double)num*m) / m;
    
    switch (num) {
        case 0: {
            red = 0.;
            green = s;
            blue = 1.;
            break;
        }
        case 1: {
            red = 0.;
            green = 1.;
            blue = 1. - s;
            break;
        }
        case 2: {
            red = s;
            green = 1.;
            blue = 0.;
            break;
        }
        case 3: {
            red = 1.;
            green = 1. - s;
            blue = 0.;
            break;
        }
    }
    out.red = (GLfloat)red;
    out.green = (GLfloat)green;
    out.blue = (GLfloat)blue;
    return out;
}

static void drawFluid(Fluid* fluid) {
    glBegin(GL_QUADS);

    int n = fluid->numY;

    double minP = fluid->p[0];
    double maxP = fluid->p[0];

    for (int i = 0; i < fluid->numCells; i++) {
        minP = findMin(minP, fluid->p[i]);
        maxP = findMax(maxP, fluid->p[i]);
    }
    
    RGB rgb = {255, 255, 255};
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            if (PRESSURE == 1) {
                double pressure = fluid->p[i*n + j];
                double smoke = fluid->m[i*n + j];
                rgb = getColor(pressure, minP, maxP);

                if (SMOKE == 1) {
                    rgb.red = (GLfloat)findMax(0., (double)rgb.red - smoke);
                    rgb.green = (GLfloat)findMax(0., (double)rgb.green - smoke);
                    rgb.blue = (GLfloat)findMax(0., (double)rgb.blue - smoke);
                }
            } else if (SMOKE == 1) {
                double smoke = fluid->m[i*n + j];

                rgb.red = (GLfloat)smoke;
                rgb.green = (GLfloat)smoke;
                rgb.blue = (GLfloat)smoke;
            } else if (fluid->s[i*n + j] == 0.) {
                rgb.red = 0.;
                rgb.green = 0.;
                rgb.blue = 0.;
            }

            // top left corner
            GLfloat x1 = i * cellSize;
            GLfloat y1 = j * cellSize;

            GLfloat x2 = x1 + cellSize;
            GLfloat y2 = y1;

            GLfloat x3 = x2;
            GLfloat y3 = y1 + cellSize;

            GLfloat x4 = x1;
            GLfloat y4 = y3;

            glColor3f(rgb.red, rgb.green, rgb.blue);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x3, y3);
            glVertex2f(x4, y4);
        }
    }
    glEnd();
    glFlush();
}

static void drawObstacle(Fluid* fluid) {
    // draw obstacle
    double obsRad = (OBSTACLE_RADIUS + fluid->h) * cScale;
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(OBSTACLE_COLOR);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)numSegments;
        float x = obsRad * cosf(theta);
        float y = obsRad * sinf(theta);
        glVertex2f(x + obstacle_x, y + obstacle_y);
    }
    glEnd();

    // Draw the black outline using GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    glColor3f(BLACK);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)numSegments;
        float x = obsRad * cosf(theta);
        float y = obsRad * sinf(theta);
        glVertex2f(x + obstacle_x, y + obstacle_y);
    }
    glEnd();
}

static void initialState(Fluid* fluid, double inVel) {
    int n = fluid->numY;
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            double s = 1.; // fluid
            if (i == 0 || j == 0 || j == fluid->numY-1) s = 0.; // solid

            fluid->s[i*n + j] = s;
            if (i == 1) {
                fluid->u[i*n + j] = inVel;
            }
        }
    }

    double pipeHeight = INLET_HEIGHT * (double)(fluid->numY);
    double minJ = (int)floor(.5 * fluid->numY - .5*pipeHeight);
    double maxJ = (int)floor(.5 * fluid->numY + .5*pipeHeight);

    for (int j = minJ; j < maxJ; j++) {
        fluid->m[j] = 0.;
    }
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    simulate(fluid, DT, GRAVITY, NUM_ITER);
    setObstacle(fluid, obstacle_x, obstacle_y, false);
    drawFluid(fluid);
    drawObstacle(fluid);
    free(fluid->p);
    glutSwapBuffers();
}

static void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    windowWidth = w;
    windowHeight = h;
}

static void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to OpenGL coordinates
        obstacle_x = (float)x;
        obstacle_y = (float)(WINDOW_HEIGHT - y);

        setObstacle(fluid, obstacle_x, obstacle_y, true);
        
        glutPostRedisplay(); // Trigger a redraw
    }
}

static void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
}

static void cleanup() {
    freeFluid(fluid);
}

void render(int argc, char** argv) {
    initSimParam();

    double h = domainHeight / RESOLUTION;
    
    int numX = floor(domainWidth/h);
    int numY = floor(domainHeight/h);

    cellSize = WINDOW_WIDTH / numX;

    printf("\tFluid Density (kg/m^3) : %g\n", DENSITY);
    printf("\t  Inlet Velocity (m/s) : %g\n", INLET_VEL);
    printf("\t       Gravity (m/s^2) : %g\n\n", GRAVITY);
    printf("\t      Window Size (px) : %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("\t        Num Cells X, Y : %dx%d\n", numX, numY);

    fluid = initFluid(DENSITY, numX, numY, h);
    initialState(fluid, INLET_VEL);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Eulerian Fluid Example");
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    atexit(cleanup);
    glutMainLoop();
}
