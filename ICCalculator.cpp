#include "ICCalculator.h"

ICCalculator::ICCalculator(QWidget *parent) : QWidget(parent)
{
    calcUI = NULL;
    setWindowTitle(tr("calculator"));
}

ICCalculator* ICCalculator::NewInstance(QWidget *parent)
{
    ICCalculator* ret = new ICCalculator(parent);

    if( ret == NULL || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

bool ICCalculator::construct()
{
    bool ret = true;

    calcUI = CalculatorUI::NewInstance(this);

    if( calcUI != NULL )
    {
        calcUI->setCalaDelegate(&calcOp);
    }

    return ret;
}
