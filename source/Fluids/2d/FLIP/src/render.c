#include <GL/glew.h>
#include <GL/gl.h> 
#include <GL/glut.h>

#include <time.h>
#include "fluids_commonincl.h"

#define UNUSED(x) (void)(x)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int cellSize;
static bool buttonDown = false;

Fluid* fluid = NULL;
Obstacle* obstacle = NULL;

#define OBSTACLE_COLOR    0.8f, 0.8f, 0.8f
#define WHITE             1.0f, 1.0f, 1.0f
#define BLACK             0.0f, 0.0f, 0.0f

static void simPrompt(int numX, int numY) {
    printf("\t   Fluid Density (kg/m^3) : %g\n", DENSITY);
    printf("\t          Gravity (m/s^2) : %g\n\n", GRAVITY);

    printf("\t  Obstacle radius (ratio) : %g\n", OBSTACLE_RADIUS);
    printf("\t Particles Radius (ratio) : %g\n", PARTICLES_RAD);
    printf("\t Compensate drift (bools) : %d\n", DRIFT);
    printf("\tSeparate Particles (bool) : %d\n", PARTICLES_SEP);
    printf("\t  Particles Count (count) : %d\n\n", numX*numY);

    printf("\t         Window Size (px) : %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("\t      Num Cells X,Y (X*Y) : %dx%d (%d)\n", numX, numY, numX*numY);
}

/**
 * @brief Function that reads in the simulation parameters from 'sim.input'
 */
static void initSimParam() {
    double h = DOMAIN_HEIGHT / RESOLUTION;
    
    double particleRad = PARTICLES_RAD*h;
    double dx = 2. * particleRad;
    double dy = dx * sqrt(3.) / 2.; 

    int numX = floor( (FLUID_WIDTH*DOMAIN_WIDTH - 2. * h - 2. * particleRad)/dx );
    int numY = floor( (FLUID_HEIGHT*DOMAIN_HEIGHT - 2. * h - 2. * particleRad)/dy );

    cellSize = WINDOW_WIDTH / numX;

    // initialize fluid and obstacle
    fluid = initFluid(DENSITY, h, particleRad, DOMAIN_WIDTH, DOMAIN_HEIGHT, numX*numY);
    obstacle = initObstacle( WINDOW_WIDTH/2,
                             WINDOW_HEIGHT/2,
                             OBSTACLE_RADIUS );
    int p = 0; // particle index
    for (int i = 0; i < numX; i++) {
        for (int j = 0; j < numY; j ++) {
            fluid->particlePos[p++] = h + particleRad + dx*(double)i + (j % 2 == 0 ? 0. : particleRad);
            fluid->particlePos[p++] = h + particleRad + dy*(double)j;
        }
    }
    simPrompt(numX, numY);
    initialState(fluid);
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

                fluid->u[i*n + j] = vx;
                fluid->u[(i+1)*n + j] = vx;
                fluid->v[i*n + j] = vy;
                fluid->v[i*n + j+1] = vy;
            }
        }
    }
}

static void drawPoint(double x, double y, double size) {
    glPointSize((float)size);
    glBegin(GL_POINTS);
    glVertex2f((float)x, (float)y);
    glEnd();
    glPointSize(1.0f);
}

static void drawParticles() {
    double r = fluid->particleRad;
    for (int p = 0; p < fluid->numParticles; p++) {
        double x = fluid->particlePos[2*p];
        double y = fluid->particlePos[2*p + 1];
        drawPoint(x, y, 10.0f);
    }
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    simulate(fluid, obstacle, DT, GRAVITY, NUM_ITER);
    setObstacle(obstacle->x, obstacle->y, false);

    /*  Drawing stuff */
    drawParticles();
    glFlush();

    FREE(fluid->p); // free fluid pressure every display

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

/**
 * @brief Function to handle mouse clicks
 *
 * @param button 
 * @param state 
 * @param x 
 * @param y 
 */
static void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            buttonDown = true;
            moveObstacle(obstacle, x, WINDOW_HEIGHT-y); // manual move obstacle set
            setObstacle(x, WINDOW_HEIGHT-y, true);
            glutPostRedisplay(); // Trigger a redraw
        } else {
            buttonDown = false;
        }
    }
}

/**
 * @brief Function to handle mouse drags
 *
 * @param x 
 * @param y 
 */
static void motion(int x, int y) {
    if (buttonDown) {
        moveObstacle(obstacle, x, WINDOW_HEIGHT-y); // manual move obstacle set
        setObstacle(x, WINDOW_HEIGHT-y, false);
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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("FLIP Fluid Simulation");
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutTimerFunc(0, timer, 0);

    atexit(cleanup);
    glutMainLoop();
}

