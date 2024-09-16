#ifndef SCENE_H
#define SCENE_H

// Include necessary Qt classes and custom classes
#include <QObject>           // Base class for all Qt objects, enables signal/slot mechanism
#include <QGraphicsScene>    // Provides the base class for 2D graphic scenes (used for visual content like a game or simulation)
#include <QTimer>            // Allows timed events, frequently used for animations or periodic actions
#include "semaforo.h"        // Custom class, likely representing a traffic light (Semáforo is Portuguese for traffic light)

class Scene : public QGraphicsScene
{
    Q_OBJECT  // Enables Qt's signal/slot mechanism, meta-object system for this class

public:
    // Constructor: Initializes the scene, optionally with a parent QObject.
    // The scene is responsible for managing graphical items (cars, traffic lights, etc.) and their interactions.
    explicit Scene(QObject *parent = nullptr);

    // Starts the scene's operation, typically starting the timers and enabling animations/events.
    void start();

    // Stops the scene's operation, usually stopping the timers and halting animations/events.
    void stop();

private:
    // QTimers to manage different car-related events in the scene (e.g., car movements or traffic light changes).
    QTimer *carLhTimer;  // Timer for left-to-right horizontal car movement
    QTimer *carRhTimer;  // Timer for right-to-left horizontal car movement
    QTimer *carTvTimer;  // Timer for top-to-bottom vertical car movement
    QTimer *carBvTimer;  // Timer for bottom-to-top vertical car movement
    QTimer *timerVertical;  // General timer for vertical events (could be for controlling traffic lights or cars)
    QTimer *timerHorizonTal;  // General timer for horizontal events

    // Boolean flag to indicate the state of the semáforo (traffic lights),
    // likely toggling between red, yellow, and green or on/off.
    bool semaforo;

    // Four instances of the Semaforo (traffic light) class, representing multiple traffic lights at intersections or crossings.
    Semaforo *s1, *s2, *s3, *s4;

    // Private helper methods to set up timers for various car movements in different directions
    void setUpCarLhTimer();    // Sets up the timer for cars moving left to right (horizontal)
    void setUpCarRhTimer();    // Sets up the timer for cars moving right to left (horizontal)
    void setUpCarTvTimer();    // Sets up the timer for cars moving top to bottom (vertical)
    void setUpCarBvTimer();    // Sets up the timer for cars moving bottom to top (vertical)

    // Methods to configure the general timers for vertical and horizontal operations
    void setTimerVertical();   // Configures the timer for vertical actions (likely traffic light or car events)
    void setTimerHorizontal(); // Configures the timer for horizontal actions

signals:
         // The class defines no signals in this version, but could be used to notify other objects
         // about events (e.g., traffic light changes, collisions, etc.).
};

#endif // SCENE_H
