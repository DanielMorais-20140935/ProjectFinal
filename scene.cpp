#include "scene.h"              // Header file for the Scene class
#include "carro.h"              // Header file for the Carro (Car) class
#include <QRandomGenerator>     // Random number generator for traffic light and car timers
#include "semaforo.h"           // Header file for the Semaforo (Traffic light) class
#include <QGraphicsScene>       // QGraphicsScene class for managing 2D graphic items

// Constructor for the Scene class, initializes traffic lights, car timers, and scene setup.
Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}    // Call base class constructor (QGraphicsScene)
{
    // Initialize timers to manage the timing of car and traffic light actions
    timerHorizonTal = new QTimer(this);  // Timer for horizontal car lanes
    timerVertical = new QTimer(this);    // Timer for vertical car lanes and semaphore switching

    // Set up timers for each traffic lane's car generation
    setUpCarLhTimer();  // Left horizontal lane
    setUpCarRhTimer();  // Right horizontal lane
    setUpCarTvTimer();  // Top vertical lane
    setUpCarBvTimer();  // Bottom vertical lane

    // Set up the traffic light control timer
    setTimerVertical();

    // Initialize traffic lights (Semaforo objects) with red light images and default "off" states
    s1 = new Semaforo(QPixmap(":/imagens/semaforoRed.png"), 0);
    s2 = new Semaforo(QPixmap(":/imagens/semaforoRed.png"), 0);
    s3 = new Semaforo(QPixmap(":/imagens/semaforoRed.png"), 0);
    s4 = new Semaforo(QPixmap(":/imagens/semaforoRed.png"), 0);

    // Position, scale, and configure the traffic lights in the scene
    s1->setPos(950 / 2 + 200, 800 / 2 - 200);  // Position the first traffic light
    s1->setZValue(3);                          // Set rendering order (3 is above other items)
    s1->setScale(0.15);                        // Scale down the size
    addItem(s1);                               // Add to the scene

    s2->setPos(440 / 2 - 100, 180 / 2 + 100);  // Position the second traffic light
    s2->setZValue(3);
    s2->setRotation(90);                       // Rotate 90 degrees to match lane orientation
    s2->setScale(0.15);
    addItem(s2);

    s3->setPos(580 / 2 - 20, 350 / 2 + 20);    // Position the third traffic light
    s3->setZValue(3);
    s3->setScale(0.15);
    addItem(s3);

    s4->setPos(1250 / 2 - 100, 180 / 2 + 100); // Position the fourth traffic light
    s4->setZValue(3);
    s4->setRotation(90);
    s4->setScale(0.15);
    addItem(s4);
}

// Start the vertical timer that alternates traffic light states and triggers car movement on vertical lanes.
void Scene::start()
{
    timerVertical->start(7000);  // Start the timer with a 7-second interval for traffic light changes
}

// Stop all car and traffic light timers, and reset the traffic lights to red.
void Scene::stop()
{
    carLhTimer->stop();  // Stop car generation on the left horizontal lane
    carRhTimer->stop();  // Stop car generation on the right horizontal lane
    carTvTimer->stop();  // Stop car generation on the top vertical lane
    carBvTimer->stop();  // Stop car generation on the bottom vertical lane
    timerVertical->stop();  // Stop the timer controlling traffic light changes

    // Set all traffic lights to red (state 0)
    s1->setEstado(0);
    s2->setEstado(0);
    s3->setEstado(0);
    s4->setEstado(0);
}

// Set up the vertical traffic light timer that alternates between allowing horizontal and vertical traffic.
void Scene::setTimerVertical()
{
    // Stop horizontal car timer if it's active (ensures horizontal cars stop before vertical lights turn green)
    if(timerHorizonTal->isActive())
        timerHorizonTal->stop();

    // Initialize semaphore state to 1 (vertical lanes go, horizontal lanes stop)
    Scene::semaforo = 1;

    // Connect the vertical timer to a lambda function to alternate the traffic light states
    connect(timerVertical, &QTimer::timeout, [=]() {
        // Generate random timings for vertical car movements
        int randomNumber = QRandomGenerator::global()->bounded(1000, 6000);
        int randomNumber2 = QRandomGenerator::global()->bounded(1000, 6000);

        if(Scene::semaforo) {
            // Set vertical lanes to green, horizontal lanes to red
            s1->setEstado(1);  // Turn traffic light 1 green
            s2->setEstado(0);  // Turn traffic light 2 red
            s3->setEstado(1);  // Turn traffic light 3 green
            s4->setEstado(0);  // Turn traffic light 4 red

            // Stop horizontal car movement, start vertical movement
            carLhTimer->stop();
            carRhTimer->stop();
            carTvTimer->start(randomNumber);   // Start top vertical car movement
            carBvTimer->start(randomNumber2);  // Start bottom vertical car movement
        } else {
            // Set horizontal lanes to green, vertical lanes to red
            s1->setEstado(0);
            s2->setEstado(1);  // Turn traffic light 2 green
            s3->setEstado(0);
            s4->setEstado(1);  // Turn traffic light 4 green

            // Stop vertical car movement, start horizontal movement
            carLhTimer->start(randomNumber);
            carRhTimer->start(randomNumber2);
            carTvTimer->stop();
            carBvTimer->stop();
        }

        // Toggle the traffic light state for the next cycle
        Scene::semaforo = !Scene::semaforo;
    });
}

// Set up the right horizontal lane timer, which spawns cars moving from right to left periodically.
void Scene::setUpCarRhTimer()
{
    carRhTimer = new QTimer(this);  // Create a new timer for the right horizontal lane

    // Connect the timer to a lambda function to add new cars to the right horizontal lane at fixed intervals
    connect(carRhTimer, &QTimer::timeout, [=]() {
        // Create a car moving right to left and set its position, scale, and rotation
        Carro *c4 = new Carro(QPixmap(":/imagens/carro4.png"), 50, 755, 12 / 2 + 245, 12 / 2 + 245);
        c4->setScale(0.29);    // Scale down the car
        c4->setRotation(-90);  // Rotate to face the correct direction
        addItem(c4);           // Add the car to the scene
    });
}

// Set up the left horizontal lane timer, which spawns cars moving from left to right periodically.
void Scene::setUpCarLhTimer()
{
    carLhTimer = new QTimer(this);  // Create a new timer for the left horizontal lane

    // Connect the timer to a lambda function to add new cars to the left horizontal lane
    connect(carLhTimer, &QTimer::timeout, [=]() {
        // Create a car moving left to right and set its position, scale, and rotation
        Carro *c3 = new Carro(QPixmap(":/imagens/carro3.png"), 775, -775, 650 / 2 - 295, 650 / 2 - 295);
        c3->setScale(0.3);    // Scale the car
        c3->setRotation(90);  // Rotate to face the correct direction
        addItem(c3);          // Add the car to the scene
    });
}

// Set up the top vertical lane timer, which spawns cars moving from top to bottom periodically.
void Scene::setUpCarTvTimer()
{
    carTvTimer = new QTimer(this);  // Create a new timer for the top vertical lane

    // Connect the timer to a lambda function to add new cars to the top vertical lane
    connect(carTvTimer, &QTimer::timeout, [=]() {
        // Create two cars moving top to bottom and set their positions, scale, and rotation
        Carro *c2 = new Carro(QPixmap(":/imagens/carro2.png"), 775 / 2 + 200, 775 / 2 + 260, 650 / 2 - 300, 600);
        c2->setScale(0.27);   // Scale the car
        c2->setRotation(180); // Rotate to face the correct direction
        addItem(c2);          // Add the car to the scene


        // Create a second car for the top vertical lane, positioned to the left of the first car
        Carro *c2_left = new Carro(QPixmap(":/imagens/carro2.png"), 775 / 2 - 145, 775 / 2 - 145, 650 / 2 - 300, 600);
        c2_left->setScale(0.27);   // Scale the car
        c2_left->setRotation(180); // Rotate to face the correct direction
        addItem(c2_left);          // Add the car to the scene

    });

    // Uncomment the line below to start the carTvTimer with an initial interval of 300 milliseconds
    // carTvTimer->start(300);
}

// Set up the bottom vertical lane timer, which spawns cars moving from bottom to top periodically.
void Scene::setUpCarBvTimer()
{
    carBvTimer = new QTimer(this);  // Create a new timer for the bottom vertical lane

    // Connect the timer to a lambda function to add new cars to the bottom vertical lane
    connect(carBvTimer, &QTimer::timeout, [=]() {
        // Create a car moving from bottom to top and set its position, scale, and rotation
        Carro *c1 = new Carro(QPixmap(":/imagens/carro.png"), 775 / 2 + 200, 775 / 2 + 200, 650 / 2 + 135, 650 / 2 - 480);
        c1->setScale(0.10);   // Scale the car
        addItem(c1);          // Add the car to the scene

        // Create a second car for the bottom vertical lane, positioned to the left of the first car
        Carro *c1_left = new Carro(QPixmap(":/imagens/carro.png"), 775 / 2 - 200, 775 / 2 - 200, 650 / 2 + 135, 650 / 2 - 480);
        c1_left->setScale(0.10);   // Scale the car
        addItem(c1_left);         // Add the car to the scene
    });

    // Uncomment the line below to start the carBvTimer with an initial interval of 1000 milliseconds
    // carBvTimer->start(1000);
}
