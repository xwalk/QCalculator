#include "CalculatorUI.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QPalette>
#include <QPushButton>
#include <QFont>
#include <QDebug>

const char* CalculatorUI::buttonText[] = {"7","8","9","+","(",
                                           "4","5","6","-",")",
                                           "1","2","3","*","<-",
                                           "0",".","=","/","C"};

CalculatorUI::CalculatorUI(QWidget *parent) : QWidget(parent,Qt::WindowCloseButtonHint)
{
    m_calc = NULL;
}

CalculatorUI::~CalculatorUI()
{

}

CalculatorUI* CalculatorUI::NewInstance(QWidget *parent)
{
    CalculatorUI* ret = new CalculatorUI(parent);

    if( ret == NULL || !ret->construct() )
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

bool CalculatorUI::construct()
{
    bool ret = true;

    QVBoxLayout* mainColumn = new QVBoxLayout();
    if( mainColumn != NULL )
    {
        mainColumn->setSpacing(10);
        QGridLayout* buttonGrid = new QGridLayout();
        if( buttonGrid != NULL )
        {
            buttonGrid->setSpacing(5);
            for( int i=0;i<20;i++ )
            {
                QPushButton* button = new QPushButton();
                if( button!= NULL )
                {
                    button->setText(buttonText[i]);
                    button->setFixedSize(40,40);
                    connect(button,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
                    buttonGrid->addWidget(button,i/5,i%5);
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            if( ret )
            {
                textEdit.insert("0");
                textEdit.setFixedSize(20+40*5,40);
                QFont font = textEdit.font();
                font.setPixelSize(18);
                textEdit.setFont(font);
                textEdit.setReadOnly(true);
                textEdit.setAlignment(Qt::AlignRight);
                mainColumn->addWidget(&textEdit);
                mainColumn->addLayout(buttonGrid);

                setLayout(mainColumn);
                setFixedSize(sizeHint());
            }
        }

    }
    return ret;
}

void CalculatorUI::onButtonClicked()
{
    QPushButton* send = dynamic_cast<QPushButton*>(sender());

    QString text = send->text();
    QString eText = textEdit.text();
    if( text == "C")
    {
        textEdit.setText("0");
    }
    else if( text == "<-")
    {
        if( eText != "0")
        {
            eText.chop(1);
            if( eText == "" )
            {
                eText = "0";
            }
            textEdit.setText(eText);
        }
    }
    else if( text == "=" )
    {
        if( m_calc != NULL )
        {
            m_calc->setOrigin(eText);
            textEdit.setText(m_calc->result());
        }
    }
    else
    {
        if( eText == "0")
        {
            if( text != "*" && text != "÷" && text != ".")
            {
                textEdit.clear();
            }
        }

        textEdit.insert(text);
    }
}

void CalculatorUI::setCalaDelegate(CalcOperations* calc)
{
    m_calc = calc;
}

