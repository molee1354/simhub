// define environment
#define GROUND            0.
#define GRAVITY           9.81
#define PI                3.14159

// define projectile properties
#define RADIUS            .1
#define COEF_RESTITUTION  .77

// setting initial values
#define START_X_POS       0.
#define START_Y_POS       100.
#define START_Z_POS       0.

#define START_X_VEL       10.
#define START_Y_VEL       -10.
#define START_Z_VEL       10.

// simulation start and end parameters
#define SIM_START         0
#define SIM_END           10000
#define SIM_FREQ          100 // stdout print frequency
#define SIM_START_T       0.

// output file
#define DATA_OUT          "dump.out"

// TODO
// make walls the projectile can bounce off of
// box origin at bottom-center
#define SIM_BOX_ENABLE      1
#define SIM_BOX_ORIGIN_X    0.
#define SIM_BOX_ORIGIN_Y    0.
#define SIM_BOX_ORIGIN_Z    50.
#define SIM_BOX_WIDTH       50.
#define SIM_BOX_DEPTH       50.

#define SIM_BOX_OPEN        1  // 1 for open box, 0 for closed box
#define SIM_BOX_INF         0  // 1 for infinite wall height
#define SIM_BOX_HEIGHT      50.
