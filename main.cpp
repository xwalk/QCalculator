#include <QApplication>
#include "ICCalculator.h"

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);

    ICCalculator* calc = ICCalculator::NewInstance();
    if( calc != NULL )
    {
        calc->show();
        ret = a.exec();
    }

    return ret;
}
