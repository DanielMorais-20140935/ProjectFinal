#ifndef SEMAFORO_H
#define SEMAFORO_H

// Include necessary Qt classes
#include <QObject>                // Base class for all Qt objects, providing signal/slot support
#include <QGraphicsPixmapItem>    // Allows the class to represent a pixmap (image) in a QGraphicsScene

// Semaforo class represents a traffic light in the graphical scene. It inherits from QObject
// to use Qt's signal/slot system and QGraphicsPixmapItem to display a graphical image.
class Semaforo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT  // Required for any class that uses Qt's signal/slot system or meta-object features

public:
    // Constructor: Initializes the traffic light (Semaforo) with an image (QPixmap)
    // and an initial state (true or false). The state (`estado`) likely represents whether the light is on or off.
    explicit Semaforo(QPixmap pixmap, bool estado);

    // Getter for the `estado` variable, which returns the current state of the traffic light.
    // The state could represent whether the traffic light is green (true) or red (false), for example.
    bool getEstado() const;

    // Setter for the `estado` variable, which changes the state of the traffic light.
    // This would typically be used to toggle the traffic light between on and off states or switch between colors.
    void setEstado(bool newEstado);

private:
    // A boolean representing the current state of the traffic light.
    // It could be used to indicate if the light is red/green, on/off, etc.
    bool estado;

signals:
         // This is where signals would be declared. Signals could be used to notify other objects when the state changes,
         // but no signals are defined in this version of the class.
};

#endif // SEMAFORO_H

