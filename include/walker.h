#include <Hubo_Control.h>

/*
enum stance_t {
  DOUBLE_LEFT  = 0,
  DOUBLE_RIGHT = 1,
  SINGLE_LEFT  = 2,
  SINGLE_RIGHT = 3,
};

typedef struct zmp_traj_element {
  double angles[HUBO_JOINT_COUNT];
  double com[3][3]; // XYZ pos/vel/accel in frame of stance foot
  stance_t stance;
} zmp_traj_element_t;

enum {
  TRAJ_FREQ_HZ = 200,
  MAX_TRAJ_SIZE = 2000,
};

typedef struct zmp_traj {
  zmp_traj_element_t traj[MAX_TRAJ_SIZE];
  size_t count;
} zmp_traj_t;

#define HUBO_CHAN_ZMP_TRAJ_NAME "hubo-zmp-traj"
*/


typedef struct foot_state {
    Eigen::Vector3d vprev;
    Eigen::Vector3d verr;
    double larerr;
    double laperr;
    double rarerr;
    double raperr;
} foot_state_t;








const double hipDistance = 0.08843*2.0; // Distance between hip joints

typedef enum {

    STATE_INVALID,
    S_HORSE,
    S_CRANE,
    Q_SHIFTDIST,
    Q_LIFTLEG,
    Q_CROUCH


} balance_state_t;


typedef enum {
    
    T_INVALID,
    T_INCOMPLETE,
    T_COMPLETE

} transition_result_t;




/**
 * The role of this class is to provide a
 * state machine and Kalman filter for
 * balancing and walking operations
*/
class Balance_Monitor
{

public:
    Balance_Monitor();
    

    Eigen::Vector2d shiftFilter( double FLsensor, double FRsensor, double dt );

    bool checkTransition( balance_state_t to ); // TODO: Fill this in all the way


    double hipVelocity; // TODO: Consider making this protected

protected:
    
    // Weight Shifting
    double FRprev;
    double FLprev;
    double Pprev;

    

    balance_state_t state;
 
    

    



};




// Stance Controllers
void calibrateBoth( Hubo_Control &hubo );
void horseStance( Hubo_Control &hubo );
void craneStance( int side, Hubo_Control &hubo, double dt );
void craneStance( int side, Vector6d swingVels, Hubo_Control &hubo, double dt );


// Horse Stance Quasi-Statics
bool shiftToDistribution( int side, double distro, Hubo_Control &hubo, Balance_Monitor &trans, double dt );
bool shiftToSide( int side, Hubo_Control &hubo, Balance_Monitor &trans, double dt );
bool crouch( double height, Hubo_Control &hubo, double dt );


// Crane Stance Quasi-Statics
bool placeSwingFoot( int side, Eigen::Vector3d footPose, Hubo_Control &hubo, double dt );

