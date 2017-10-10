#include "CalculatorUI.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QPalette>
#include <QPushButton>
#include <QFont>
#include <QEvent>
#include <QKeyEvent>

const char* CalculatorUI::buttonText[] = {"7","8","9","+","(",
                                           "4","5","6","-",")",
                                           "1","2","3","*","<-",
                                           "0",".","=","/","C"};

CalculatorUI::CalculatorUI(QWidget *parent) : QWidget(parent,Qt::WindowCloseButtonHint)
{
    m_calc = NULL;
    nextCalc = true;
    textEdit.installEventFilter(this);
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

void CalculatorUI::handleText(QString text)
{
    QString eText = textEdit.text();
    if( nextCalc )
    {
        eText = "0";
        nextCalc = false;
    }
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
        else
        {
           textEdit.setText("0");
        }
    }
    else if( text == "=" )
    {
        if( m_calc != NULL )
        {
            m_calc->setOrigin(eText);
            textEdit.setText(m_calc->result());
            nextCalc = true;
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
            else
            {
                textEdit.setText("0");
            }
        }

        textEdit.insert(text);
    }
}

void CalculatorUI::onButtonClicked()
{
    QPushButton* send = dynamic_cast<QPushButton*>(sender());

    handleText(send->text());

}

void CalculatorUI::setCalaDelegate(CalcOperations* calc)
{
    m_calc = calc;
}

bool CalculatorUI::eventFilter(QObject *ob, QEvent *e)
{
    bool ret = true;

    if( ob == &textEdit && e->type() == QEvent::KeyRelease )
    {
        QKeyEvent* ke = dynamic_cast<QKeyEvent*>(e);
        QString text;
        switch ( ke->key() )
        {
        case Qt::Key_0:text = "0";break;
        case Qt::Key_1:text = "1";break;
        case Qt::Key_2:text = "2";break;
        case Qt::Key_3:text = "3";break;
        case Qt::Key_4:text = "4";break;
        case Qt::Key_5:text = "5";break;
        case Qt::Key_6:text = "6";break;
        case Qt::Key_7:text = "7";break;
        case Qt::Key_8:text = "8";break;
        case Qt::Key_9:text = "9";break;
        case Qt::Key_Period:text = ".";break;
        case Qt::Key_Enter:text = "=";break;
        case Qt::Key_ParenLeft:text = "(";break;
        case Qt::Key_ParenRight:text = ")";break;
        case Qt::Key_Plus:text = "+";break;
        case Qt::Key_Minus:text = "-";break;
        case Qt::Key_Asterisk:text = "*";break;
        case Qt::Key_Slash:text = "/";break;
        case Qt::Key_Backspace:text = "<-";break;
        case Qt::Key_Escape:text = "C";break;
        default:break;
        }
        handleText( text );
    }
    else
    {
        ret = QWidget::eventFilter(ob,e);
    }

    return ret;
}

