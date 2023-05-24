// define environment
#define GROUND            0.
#define GRAVITY           9.81
#define PI                3.14159

// define projectile properties
#define RADIUS            .1
#define COEF_RESTITUTION  .77

// setting initial values
#define START_X_POS       0.
#define START_Y_POS       0.
#define START_Z_POS       0.

#define START_X_VEL       10.
#define START_Y_VEL       70.
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
