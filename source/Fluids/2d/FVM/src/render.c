#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include "fluids_commonincl.h"

#define UNUSED(x) (void)(x)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int cellSize;

Fluid* fluid = NULL;
Obstacle* obstacle = NULL;

#define OBSTACLE_COLOR  0.8f, 0.8f, 0.8f
#define WHITE           1.0f, 1.0f, 1.0f
#define BLACK           0.0f, 0.0f, 0.0f

typedef struct {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
} RGB;

static void simPrompt(int numX, int numY) {
    printf("\t  Fluid Density (kg/m^3) : %g\n", DENSITY);
    printf("\t         Gravity (m/s^2) : %g\n\n", GRAVITY);

    printf("\t    Inlet Velocity (m/s) : %g\n", INLET_VEL);
    printf("\t    Inlet Height (ratio) : %g\n\n", INLET_HEIGHT);

    printf("\tAngular Velocity (Rev/s) : %g\n",  OBSTACLE_OMEGA );
    printf("\t Obstacle radius (ratio) : %g\n\n", OBSTACLE_RADIUS);

    printf("\t        Window Size (px) : %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("\t     Num Cells X,Y (X*Y) : %dx%d (%d)\n", numX, numY, numX*numY);
}

static void initSimParam() {
    double h = DOMAIN_HEIGHT / RESOLUTION;
    
    int numX = floor(DOMAIN_WIDTH/h);
    int numY = floor(DOMAIN_HEIGHT/h);

    cellSize = WINDOW_WIDTH / numX;

    fluid = initFluid(DENSITY, numX, numY, h);
    obstacle = initObstacle( WINDOW_WIDTH/2,
                             WINDOW_HEIGHT/2,
                             OBSTACLE_RADIUS );

    simPrompt(numX, numY);
}

static void setObstacle(int x, int y, bool reset) {
    double vx = 0.;
    double vy = 0.;

    if (!reset) {
        vx = (x - obstacle->x) / DT;
        vy = (y - obstacle->y) / DT;
    }

    int n = fluid->numY;
    double h = fluid->h;

    for (int i = 1; i < fluid->numX-2; i++) {
        for (int j = 1; j < fluid->numY-2; j++) {
            fluid->s[i*n + j] = 1.;

            double dx = xDistConv((double)i, h, x);
            double dy = yDistConv((double)j, h, y);
            double rad2 = (double)(obstacle->radius * obstacle->radius);

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

static void drawFluid() {
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
                // setting color zero for obstacles
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
    // glFlush();
}

static void drawObstacle() {
    // draw obstacle
    double obsRad = (OBSTACLE_RADIUS + fluid->h) * C_SCALE;
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(OBSTACLE_COLOR);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)numSegments;
        float x = obsRad * cosf(theta);
        float y = obsRad * sinf(theta);
        glVertex2f(x + obstacle->x, y + obstacle->y);
    }
    glEnd();

    // Draw the black outline using GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    glColor3f(BLACK);
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)numSegments;
        float x = obsRad * cosf(theta);
        float y = obsRad * sinf(theta);
        glVertex2f(x + obstacle->x, y + obstacle->y);
    }
    glEnd();
}

static void drawStreamlines() {
    int numSegments = 15;
    int skip = 10;

    for (int i = 1; i < fluid->numX-1; i+=skip) {
        for (int j = 1; j < fluid->numY-1; j+=skip) {
            double x = ((double)i + .5) * fluid->h;
            double y = ((double)j + .5) * fluid->h;

            // move streamline origin here
            glBegin(GL_LINES);
            glColor4f(BLACK, 0.3f);
            for (int n = 0; n < numSegments; n++) {
                glVertex2f(x*C_SCALE,y*C_SCALE);

                double u = sampleField(fluid, x, y, U_FIELD);
                double v = sampleField(fluid, x, y, V_FIELD);
                x += u * .01;
                y += v * .01;

                if ( x > fluid->numX * fluid->h) break;

                // move streamline end to new (x, y)
                glVertex2f(x*C_SCALE,y*C_SCALE);
            }
            glEnd();
        }
    }
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    simulate(fluid, obstacle, DT, GRAVITY, NUM_ITER);
    setObstacle(obstacle->x, obstacle->y, false);
    drawFluid();
    if (STREAMLINES) drawStreamlines();
    drawObstacle();
    glFlush();

    free(fluid->p); // free fluid pressure every display

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    UNUSED(w);
    UNUSED(h);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)WINDOW_WIDTH,
               0.0, (GLdouble)WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to OpenGL coordinates
        moveObstacle(obstacle, x, WINDOW_HEIGHT-y); // manual move obstacle set
        glutPostRedisplay(); // Trigger a redraw
    }
}

static void timer(int value) {
    UNUSED(value);
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
}

static void cleanup() {
    freeFluid(fluid);
    freeObstacle(obstacle);
}

void render(int argc, char** argv) {
    initSimParam();

    initialState(fluid, INLET_VEL, INLET_HEIGHT);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Eulerian Fluid Simulation");
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    atexit(cleanup);
    glutMainLoop();
}

