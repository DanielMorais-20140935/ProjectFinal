#include "mainwindow.h"    // Include the header file for the MainWindow class

#include <QApplication>    // Include the QApplication class, which manages GUI application control flow and main settings

// The main function is the entry point for the application.
int main(int argc, char *argv[])
{
    // QApplication is responsible for setting up the application environment, handling GUI-related tasks, and managing the event loop.
    // The argc and argv parameters allow the application to accept command-line arguments.
    QApplication a(argc, argv);

    // Create an instance of the MainWindow class.
    // This is the main window of the application, typically containing the UI and any central widgets.
    MainWindow w;

    // Display the main window on the screen.
    // The 'show()' function makes the window visible and initializes its event loop.
    w.show();

    // Enter the application's event loop, which waits for user input and system events (e.g., key presses, mouse clicks, etc.).
    // The 'exec()' method starts the event loop and blocks until the application quits.
    return a.exec();
}
