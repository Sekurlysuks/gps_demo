/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// GPST                 gps           13
// fl                   motor         1
// fr                   motor         7
// bl                   motor         10
// br                   motor         3
// Inertial             inertial      14
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void SpinForAll(directionType dir, int amount, rotationUnits rot, bool yn){
  fl.spinFor(dir,amount,rot,yn);
  bl.spinFor(dir,amount,rot,yn);
  fr.spinFor(dir,amount,rot,yn);
  br.spinFor(dir,amount,rot,yn);
}

void setVelocityAll(double v) {
  fl.setVelocity(v, percent);
  bl.setVelocity(v, percent);
  fr.setVelocity(v, percent);
  br.setVelocity(v, percent);
}

void setStoppingAll(brakeType mode) {
  fl.setStopping(mode);
  bl.setStopping(mode);
  fr.setStopping(mode);
  br.setStopping(mode);
}

void TurnRightio(double Spin){
  setVelocityAll(40);
  fl.spinFor(reverse,Spin,degrees,false);
  br.spinFor(forward,Spin,degrees,false);
  bl.spinFor(reverse,Spin,degrees,false);
  fr.spinFor(forward,Spin,degrees,false);
}

void stop_all_motors() {
  fl.stop();
  bl.stop();
  fr.stop();
  br.stop();
}





void SpinAll(directionType dir){
  fl.spin(dir);
  bl.spin(dir);
  fr.spin(dir);
  br.spin(dir);
}

void TurnRight(double Spin) {
  setVelocityAll(18);
  setStoppingAll(hold);
  Inertial.setRotation(0, degrees);
  while (Inertial.rotation(degrees) < Spin) {
    Controller1.Screen.clearLine();
    fr.spin(reverse);
    br.spin(reverse);
    fl.spin(forward);
    bl.spin(forward);
    Controller1.Screen.print(Inertial.rotation(degrees));
    wait(0.3, seconds);
  }
  stop_all_motors();
}

void TurnLeft(double Spin) {
  setVelocityAll(18);
  setStoppingAll(hold);
  Inertial.setRotation(0, degrees);
  while (fabs(Inertial.rotation(degrees)) < Spin) {
    Controller1.Screen.clearLine();
    fr.spin(forward);
    br.spin(forward);
    fl.spin(reverse);
    bl.spin(reverse);
    Controller1.Screen.print(Inertial.rotation(degrees));
    wait(0.3, seconds);
  }
  stop_all_motors();
}

void drivecode() {
  fl.spin(forward,
          Controller1.Axis3.value() + Controller1.Axis1.value() +
              Controller1.Axis4.value(),
          percent);
  fr.spin(forward,
          Controller1.Axis3.value() - Controller1.Axis1.value() -
              Controller1.Axis4.value(),
          percent);
  bl.spin(forward,
          Controller1.Axis3.value() - Controller1.Axis1.value() +
              Controller1.Axis4.value(),
          percent);
  br.spin(forward,
          Controller1.Axis3.value() + Controller1.Axis1.value() -
              Controller1.Axis4.value(),
          percent);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  bool a = 1;
  bool b = 0;
  bool c = 0;
  bool d = 0; 

  GPST.calibrate();
  setVelocityAll(50);
  while (GPST.isCalibrating()) {
    wait(50, msec);
  }
  while (a) {
    if (GPST.xPosition(inches) > 4) {
      SpinAll(reverse);
      wait(2000, msec);
      // GPST.xPosition(inches);
      Controller1.Screen.print("point a");
    } else if (GPST.xPosition(inches) < -4) {
      SpinAll(forward);
      // GPST.xPosition(inches);
      Controller1.Screen.print("point b");
    } else if (GPST.xPosition(inches) > 4 && GPST.xPosition(inches) < -4) {
      SpinForAll(forward, 30, degrees, false);
      wait(2, sec);
      Controller1.Screen.print("point c");
    } else if (GPST.xPosition(inches) < 4 && GPST.xPosition(inches) > 1) {
      SpinForAll(reverse, 30, degrees, false);
      wait(2, sec);
      Controller1.Screen.print("point d");
    } else if (GPST.xPosition(inches) > -1 && GPST.xPosition(inches) < 1) {
      stop_all_motors();
      //int rightangle = 80;
      //TurnRight(rightangle);
      //Controller1.Screen.print("try to turn %d",rightangle);
      Controller1.rumble(rumbleLong);
      b = 1;
      a = 0;
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(GPST.xPosition(inches));
  }
  while (a) {
    if (GPST.yPosition(inches) > 4) {
      SpinAll(reverse);
      wait(2000, msec);
      // GPST.xPosition(inches);
      Controller1.Screen.print("point a");
    } else if (GPST.yPosition(inches) < -4) {
      SpinAll(forward);
      // GPST.xPosition(inches);
      Controller1.Screen.print("point b");
    } else if (GPST.yPosition(inches) > 4 && GPST.yPosition(inches) < -4) {
      SpinForAll(forward, 30, degrees, false);
      wait(2, sec);
      Controller1.Screen.print("point c");
    } else if (GPST.yPosition(inches) < 4 && GPST.yPosition(inches) > 1) {
      SpinForAll(reverse, 30, degrees, false);
      wait(2, sec);
      Controller1.Screen.print("point d");
    } else if (GPST.yPosition(inches) > -1 && GPST.yPosition(inches) < 1) {
      stop_all_motors();
      int rightangle = 80;
      TurnRight(rightangle);
      Controller1.Screen.print("try to turn %d",rightangle);
      Controller1.rumble(rumbleLong);
      b = 1;
      a = 0;
    }
  }  
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(GPST.xPosition(inches));
  
  while (b) {
    if (GPST.heading() < -5 && GPST.heading() > 5) {
      fl.spinFor(forward, 10, degrees, false);
      fr.spinFor(reverse, 10, degrees, false);
      bl.spinFor(forward, 10, degrees, false);
      br.spinFor(reverse, 10, degrees);
      wait(2, sec);
    } else if (GPST.heading() > -5 && GPST.heading() < 5) {
      c = 1;
      b = 0;
    }
  }

  while (c) {
    if (GPST.yPosition(inches) > 4) {
      SpinAll(reverse);
      wait(2000, msec);
      GPST.xPosition(inches);
    } else if (GPST.yPosition(inches) < -4) {
      SpinAll(forward);
      GPST.xPosition(inches);
    } else if (GPST.yPosition(inches) > -4 && GPST.xPosition(inches) < -1) {
      SpinForAll(forward, 15, degrees, false);
      wait(2, sec);
    } else if (GPST.yPosition(inches) < 4 && GPST.xPosition(inches) > 1) {
      SpinForAll(reverse, 15, degrees, false);
      wait(2, sec);
    } else if (GPST.yPosition(inches) > -1 && GPST.xPosition(inches) < 1) {
      stop_all_motors();
      Controller1.rumble(rumbleLong);
      b = 1;
      a = 0;
    }
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(GPST.yPosition(inches));
    
  
  }
  while (d) {
    int rightangle = 90;
    TurnRight(rightangle);
    Controller1.Screen.print("try to turn %d",rightangle);
    break;
  }
}
// ..........................................................................
// Insert autonomous user code here.
// ..........................................................................

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    drivecode();
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and calblacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
