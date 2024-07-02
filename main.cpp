#include <QApplication>
#include <MainWindow.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow MainWindow;
    MainWindow.showFullScreen();

    MainWindow.show();

    return app.exec();
}
