#include "carro.h"            // Include the header file for the Carro class
#include <QGraphicsScene>      // Include for access to the scene() function, used to manipulate items in the scene

// Constructor for the Carro class. It initializes a car object with the given pixmap (image) and start/end positions (xi, xf, yi, yf).
// The constructor also sets up the animations for both the x and y properties (horizontal and vertical movement).
Carro::Carro(QPixmap pixmap, qreal xi, qreal xf , qreal yi, qreal yf)
    : QGraphicsPixmapItem{pixmap}  // Initialize the base class QGraphicsPixmapItem with the provided pixmap (image of the car)
{
    // Create animations for the 'x' and 'y' properties of the car.
    xanimation = new QPropertyAnimation(this, "x", this);  // Animation for horizontal (x-axis) movement
    yanimation = new QPropertyAnimation(this, "y", this);  // Animation for vertical (y-axis) movement

    // Set the initial position of the car to (xi, yi)
    setPos(xi, yi);

    // Store the final positions (xf and yf) for later use
    xPos = xf;
    yPos = yf;

    // If the y-coordinates are the same, animate the car along the x-axis (horizontal movement)
    // Otherwise, animate along the y-axis (vertical movement)
    if (yi == yf)
        animarX(xi, xf);  // Call the method to animate in the horizontal direction
    else
        animarY(yi, yf);  // Call the method to animate in the vertical direction
}

// Method to set up and start horizontal (x-axis) animation from xi to xf
void Carro::animarX(int xi, int xf) {
    // Set the start and end values for the x animation (initial and final x positions)
    xanimation->setStartValue(xi);
    xanimation->setEndValue(xf);

    // Set the duration of the animation (2000ms or 2 seconds)
    xanimation->setDuration(2000);

    // Use a linear easing curve for smooth, uniform movement
    xanimation->setEasingCurve(QEasingCurve::Linear);

    // Connect the animation's finished signal to a lambda function to remove the car from the scene
    connect(xanimation, &QPropertyAnimation::finished, [=]() {
        qDebug() << "Animation Finished";  // Log when the animation finishes
        scene()->removeItem(this);         // Remove the car from the scene after animation completes
        delete this;                       // Delete the car object to free memory
    });

    // Start the x-axis animation
    xanimation->start();
}

// Method to set up and start vertical (y-axis) animation from yi to yf
void Carro::animarY(int yi, int yf) {
    // Set the start and end values for the y animation (initial and final y positions)
    yanimation->setStartValue(yi);
    yanimation->setEndValue(yf);

    // Set the duration of the animation (2000ms or 2 seconds)
    yanimation->setDuration(2000);

    // Use a linear easing curve for smooth, uniform movement
    yanimation->setEasingCurve(QEasingCurve::Linear);

    // Connect the animation's finished signal to a lambda function to remove the car from the scene
    connect(yanimation, &QPropertyAnimation::finished, [=]() {
        qDebug() << "Animation Finished";  // Log when the animation finishes
        scene()->removeItem(this);         // Remove the car from the scene after animation completes
        delete this;                       // Delete the car object to free memory
    });

    // Start the y-axis animation
    yanimation->start();
}

// Getter method for the y-coordinate (vertical position) of the car
qreal Carro::y() const {
    return m_y;  // Return the current y-position
}

// Getter method for the x-coordinate (horizontal position) of the car
qreal Carro::x() const {
    return m_x;  // Return the current x-position
}

// Setter method for the y-coordinate. It updates the car's position along the y-axis.
void Carro::setY(qreal newY) {
    m_y = newY;  // Update the internal y-coordinate
    // Update the position of the car with the new y-coordinate, maintaining the current x-position (xPos)
    setPos(QPoint(0, 0) + QPoint(xPos, newY));
}

// Setter method for the x-coordinate. It updates the car's position along the x-axis.
void Carro::setX(qreal newX) {
    m_x = newX;  // Update the internal x-coordinate
    // Update the position of the car with the new x-coordinate, maintaining the current y-position (yPos)
    setPos(QPoint(0, 0) + QPoint(newX, yPos));
}

// Destructor for the Carro class. Currently, it does not need to perform any specific cleanup
// as the car object is deleted after the animation is finished and the car is removed from the scene.
Carro::~Carro() {

}
