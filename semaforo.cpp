#include "semaforo.h"
#include <QGraphicsScene>

// Constructor for the Semaforo class
// Initializes the traffic light with a pixmap and sets its initial state (on/off)
Semaforo::Semaforo(QPixmap pixmap, bool estado)
    : QGraphicsPixmapItem{pixmap} // Initialize the base class with the given pixmap
{
    setEstado(estado); // Set the initial state of the traffic light
}

// Getter method for the state of the traffic light
// Returns true if the traffic light is green, false if it is red
bool Semaforo::getEstado() const
{
    return estado;
}

// Setter method for the state of the traffic light
// Updates the state and changes the pixmap based on the new state
void Semaforo::setEstado(bool newEstado)
{
    estado = newEstado; // Update the internal state

    // Update the pixmap based on the state
    if (estado == 0) {
        // Set pixmap to red traffic light image when state is 0 (off/red)
        setPixmap(QPixmap(":/imagens/semaforoRed.png"));
    } else {
        // Set pixmap to green traffic light image when state is 1 (on/green)
        setPixmap(QPixmap(":/imagens/semaforoGreen.png"));
    }
}
