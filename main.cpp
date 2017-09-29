#include "QCalculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCalculator w;
    w.show();

    return a.exec();
}
