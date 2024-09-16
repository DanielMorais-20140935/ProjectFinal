#ifndef CARRO_H
#define CARRO_H

// Including necessary Qt classes
#include <QObject>                // Base class for all Qt objects, enables signal/slot mechanism
#include <QGraphicsPixmapItem>    // Allows the class to represent an image (pixmap) in a QGraphicsScene
#include <QPropertyAnimation>     // Enables property animations (e.g., x and y positions)

class Carro : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT  // Macro required for any class that defines signals/slots or uses Q_PROPERTY

    // Defines properties for animation; these can be animated using QPropertyAnimation
    // They define 'x' and 'y' properties with getter and setter functions
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    // Constructor: Takes a pixmap (image) to represent the car graphically,
    // and initial/final values for x and y positions (xi, xf, yi, yf) for animation setup.
    explicit Carro(QPixmap pixmap, qreal xi, qreal xf, qreal yi, qreal yf);

    // Getter for 'y' position; returns the current y coordinate of the object.
    qreal y() const;

    // Getter for 'x' position; returns the current x coordinate of the object.
    qreal x() const;

    // Setter for 'y' position; updates the object's y coordinate.
    void setY(qreal newY);

    // Setter for 'x' position; updates the object's x coordinate.
    void setX(qreal newX);

    // Destructor: Cleans up any dynamically allocated memory or resources when the object is destroyed.
    ~Carro();

signals:
         // Signals section can be used to define custom signals, but it is empty here.
         // Signals could be used to notify other objects about changes in position or state.

private:
    // Stores the current x and y coordinates of the object.
    qreal m_x;  // The 'x' coordinate of the car.
    qreal m_y;  // The 'y' coordinate of the car.

    // These variables might represent integer versions of the position, though their purpose is not fully clear.
    // Could be used for a grid-based system or rounding the positions.
    int yPos, xPos;

    // Animations for the 'x' and 'y' properties.
    QPropertyAnimation *xanimation;  // Handles the animation of the 'x' property.
    QPropertyAnimation *yanimation;  // Handles the animation of the 'y' property.

    // Helper function to animate the 'x' property from initial (xi) to final (xf) positions.
    void animarX(int xi, int xf);

    // Helper function to animate the 'y' property from initial (yi) to final (yf) positions.
    void animarY(int yi, int yf);
};

#endif // CARRO_H
