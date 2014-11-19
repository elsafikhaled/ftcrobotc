#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorNormal, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorNormal, PIDControl)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
// AutoTeleSample.c
//
// Part of the FTC Team 417 Software Starter Kit: www.ftc417.org/ssk
//
// This is a template for a single program which can execute both autonomous mode
// and teleop mode of an FTC-competition game robot. A user interface on the NXT,
// executed during the waitForStart() call, chooses between these (among other things;
// see FTCField.h) for details).
//
// Why just one program for both autonomous and teleop modes instead of two separate ones?
// In large part due to the fact that the two pieces of code need to share more than you'd
// initially think. They both probably want code to detect motor stalls, for example, and to
// read sensors and trigger events associated therewith, and to put diagnostic information
// on the display, and so on. And with one program you never end up running the wrong one :-).
// Oh, and, depending on what you're doing, exactly, your code can get so large that two
// different programs won't fit in the file system of the NXT at the same time.
//
// The autonmous mode code here is just a placeholder: fill in what you want your bot
// to do. The teleop mode implements simple tank-like drive logic using one joystick controller.
// Depending on your bot, that may be all you need. Or not. Have a good look at the code
// and figure that out!
//
// The code here as written expects two motors to be defined as motorLeft and motorRight
// in the #pragmas above at the start of the program. We've defined them here as being
// Lego motors on 'A' and 'B'; for your bot, you'll probably want to change that. You can
// use the 'Motors and Sensors Setup' wizard if you like, or manually edit the #pragma's
// if you know what's what.
//
#define USE_DISPLAY_DIAGNOSTICS 0   // turn off the diagnostic display found in JoystickDriver.h

#include "..\lib\FTCField.h"
#include "..\lib\JoystickDriver.h"
#include "..\lib\Music.h"

void InitializeMain()
    {
    // Put any necessary initialization code here
    }

void DoManualDrivingControl(int jyc)
// Interpret the joysticks and manually drive the bot. This implements
// a tank-like drive, where the Y value of the left joystick is forward
// and back, and the X value of the right joystick is steering.
    {
    // Extract values from the joysticks that we find useful
    int ctlPower    = -joyY(jyc, JOY_LEFT);      // -128 to  127
    int ctlSteering =  joyX(jyc, JOY_RIGHT);     //  128 to -127

    // Remove sensitivity in the middle of the controls.
    // At the same time, avoid a big control jump at the
    // edge of the dead zone.
    const int sensitivityThreshold = joyThrottleDeadZone;
    const int sgnPower    = (ctlPower    < 0 ? -1 : 1);
    const int sgnSteering = (ctlSteering < 0 ? -1 : 1);

    ctlPower    = Max(0, abs(ctlPower)    - sensitivityThreshold);
    ctlSteering = Max(0, abs(ctlSteering) - sensitivityThreshold);

    ctlPower    = ctlPower    * sgnPower;
    ctlSteering = ctlSteering * sgnSteering;

    // Convert the signals from the joystick range of values
    // to the motor range of values
    const int motorRange    = 100;
    const int joystickRange = 128 - sensitivityThreshold;
    ctlPower    = ctlPower    * motorRange / joystickRange;
    ctlSteering = ctlSteering * motorRange / joystickRange;

    // Combine the power and steering sections.
    const int powerLeft  = ctlPower - ctlSteering;
    const int powerRight = ctlPower + ctlSteering;

    // Actually change the motor power.
    motor[motorLeft]  = powerLeft;
    motor[motorRight] = powerRight;
    }

void DoTeleOp(int jyc)
// jyc is the joystick controller we are to examine
    {
    while (true)
        {
        if (getJoystickSettings(joystick))
            {
            // Examine the button and hat state to determine if there's something
            // useful to do. Here, as a demonstration, we play a tune if the left
            // upper trigger is pressed. You, of course, would instead do your own
            // thing, presumably a more useful one.
            //
            if (joyBtnOnce(jyc, JOYBTN_LEFTTRIGGER_UPPER))
                {
                PlayHappy();
                }

            // Use the joysticks to manually drive the robot
            DoManualDrivingControl(jyc);
            }
        else if (joyMessageCount() > 0 && nSysTime - joyMessageTime() > MS_JOYSTICK_FCS_DISCONNECTED_THRESHOLD)
            {
            /* We've seen some joystick messages in the past, but we haven't   */
            /* a message in a long time. So we have to consider that we've     */
            /* the connection with the Field Control System>. We take steps to */
            /* reign in a possibly runaway robot.                              */
            motor[motorLeft]  = 0;
            motor[motorRight] = 0;

            /* And we play play an audible alarm. */
            Beep(NOTE_E);
            }
        }
    }

void DoAutonomous()
    {
    // Implement your autonomous logic here
    }

task main()
    {
    // Perform any necessary initialization
    InitializeMain();

    // Wait until the FCS tells us to go
    waitForStart();

    // Run teleop or autonomous as indicated by the user interface
    if (PROGRAM_FLAVOR_TELEOP == programFlavor)
        {
        DoTeleOp(1);
        }
    else if (PROGRAM_FLAVOR_AUTONOMOUS == programFlavor)
        {
        DoAutonomous();
        }

    // As the main task is exiting, so should all others; this will
    // allow the program to gracefully and fully terminate (without this
    // call, the readMsgFromPC() task, e.g., in joystickDriver.h will
    // keep the program alive).
    StopAllTasks();
    }
