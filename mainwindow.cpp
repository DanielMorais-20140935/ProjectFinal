#include "mainwindow.h"     // Include the MainWindow class header
#include "ui_mainwindow.h"   // Include the UI generated header for the MainWindow UI elements
#include <QString>           // Include QString to manipulate text strings
#include <QGraphicsPixmapItem> // Include QGraphicsPixmapItem to handle image objects in the scene

// Constructor for MainWindow. It initializes the main window UI and sets up the graphical scene and its elements.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)   // Call the base class constructor with the parent widget
    , ui(new Ui::MainWindow) // Initialize the UI pointer for the main window
{
    // Set up the UI elements from the .ui file. This auto-generates the UI elements in code.
    ui->setupUi(this);

    // Create a new Scene object that will serve as the graphics scene where items are displayed.
    // This scene will contain all the graphical elements such as cars, background, etc.
    s = new Scene(this);

    // Add the background image (scenario) to the scene.
    // QGraphicsPixmapItem is used to display a pixmap (an image). The image is scaled to fit 800x800 size
    // with smooth transformation and aspect ratio preserved.
    QGraphicsPixmapItem *cenarioImg = new QGraphicsPixmapItem(QPixmap(":/imagens/cross.jpg")
                                                                  .scaled(800, 800, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Set the range of the horizontal slider, which is used to control the number of cars or another parameter.
    ui->horizontalSlider->setRange(1, 5);  // Slider allows selecting a value between 1 and 5

    // Add the background image (cenarioImg) to the scene `s`.
    s->addItem(cenarioImg);

    // Configure the QGraphicsView to display the scene. Set the scene's viewable area to 800x800 pixels,
    // which matches the size of the background image.
    ui->graphicsView->setSceneRect(0, 0, 800, 800);

    // Set the scene `s` to the QGraphicsView, which is the widget responsible for displaying the scene on the UI.
    ui->graphicsView->setScene(s);

    // Disable scroll bars for the graphics view since the scene fits exactly within the view.
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Fix the size of the QGraphicsView to 800x800, so it perfectly matches the scene size.
    ui->graphicsView->setFixedSize(800, 800);
}

// Destructor for MainWindow. Cleans up the dynamically allocated UI resources when the window is closed.
MainWindow::~MainWindow()
{
    delete ui;  // Delete the UI pointer to avoid memory leaks
}

// Slot connected to the "Começar" (Start) button click event.
// When the button is clicked, this function is triggered and starts the scene's operations (e.g., moving cars).
void MainWindow::on_comecar_clicked()
{
    s->start();  // Call the start method of the Scene to begin any animations or processes
    qDebug() << "ol";  // Output a debug message to the console for verification
}

// Slot connected to the "Parar" (Stop) button click event.
// When the button is clicked, this function is triggered and stops the scene's operations.
void MainWindow::on_parar_clicked()
{
    s->stop();  // Call the stop method of the Scene to halt any animations or processes
}

// Slot connected to the horizontal slider value change event.
// This function is triggered when the user changes the slider value.
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    // Convert the integer slider value to a QString and update the label (ncars) to display the value.
    QString numberString = QString::number(value);
    ui->ncars->setText(numberString);  // Update the text of the ncars label to show the current slider value
}
