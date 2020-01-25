#include "OptimizationTab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QtMath>
#include <limits>

OptimizationTab::OptimizationTab(QList<QString> variables, QString target_var, double epsilon, double percentage, bool maximize, QWidget *parent) : QWidget(parent)
{
    // init
    mMinimizeButtonId = 0;
    mMaximizeButtonId = 1;
    // Variables
    mpVariablesLabel = new QLabel(tr("Variable:"), this);
    mpVariablesComboBox = new QComboBox(this);
    foreach(QString var_name, variables) {
        mpVariablesComboBox->addItem(var_name);
    }
    int target_var_index = mpVariablesComboBox->findText(target_var);
    mpVariablesComboBox->setCurrentIndex(target_var_index);
    // Goal
    mpGoalButtonGroup = new QButtonGroup(this); // Has to have "this" as parent because it's never assigned to anything
    mpMinRadio = new QRadioButton(tr("Minimize"));
    mpMaxRadio = new QRadioButton(tr("Maximize"));
    toggleOptimType(maximize);
    mpGoalButtonGroup->addButton(mpMinRadio, mMinimizeButtonId);
    mpGoalButtonGroup->addButton(mpMaxRadio, mMaximizeButtonId);
    // Epsilon
    mpEpsilonLabel = new QLabel(tr("Epsilon"));
    mpEpsilonBox = new SciNotationDoubleSpinbox;
    mpEpsilonBox->setRange(std::numeric_limits<double>::min(), 1-std::numeric_limits<double>::min());
    mpEpsilonBox->setValue(epsilon);
    mpEpsilonBox->setSingleStep(0.01);
    mpEpsilonHintLabel = new QLabel(tr("(0 < ε < 1)"));
    // Boundaries
    mpBoundariesLabel = new QLabel(tr("Perturbation boundaries:"));
    mpBoundariesBox = new QDoubleSpinBox;
    mpBoundariesBox->setRange(0.01, std::numeric_limits<double>::max());
    mpBoundariesBox->setValue(percentage);
    mpBoundariesBox->setPrefix("±");
    mpBoundariesBox->setSuffix("%");

    // Layout
    QGridLayout *pMainLayout = new QGridLayout;
    pMainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // Variables
    pMainLayout->addWidget(mpVariablesLabel   ,0,0);
    pMainLayout->addWidget(mpVariablesComboBox,0,1);
    pMainLayout->addWidget(mpMinRadio         ,0,2);
    pMainLayout->addWidget(mpMaxRadio         ,0,3);
    // Epsilon
    pMainLayout->addWidget(mpEpsilonLabel    ,2,0);
    pMainLayout->addWidget(mpEpsilonBox      ,2,1);
    pMainLayout->addWidget(mpEpsilonHintLabel,2,2);
    // Boundaries
    pMainLayout->addWidget(mpBoundariesLabel,3,0);
    pMainLayout->addWidget(mpBoundariesBox  ,3,1);

    // Layout settings
    setLayout(pMainLayout);
}


// Getters
double OptimizationTab::getEpsilon() const
{
    return mpEpsilonBox->value();

}

QString OptimizationTab::getTargetVariable() const
{
    return mpVariablesComboBox->currentText();
}

int OptimizationTab::getGoalId() const
{
    return mpGoalButtonGroup->checkedId();
}


double OptimizationTab::getBoundariesValue() const
{
    return mpBoundariesBox->value();
}

void OptimizationTab::toggleOptimType(bool maximize)
{
    if(maximize)
    {
        mpMaxRadio->toggle();
    }
    else
    {
        mpMinRadio->toggle();
    }
}
