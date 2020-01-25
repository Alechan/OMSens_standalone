#ifndef OPTIMIZATIONTAB_H
#define OPTIMIZATIONTAB_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include "../SciNotationDoubleSpinbox.h"

class OptimizationTab : public QWidget
{
    Q_OBJECT
public:
    explicit OptimizationTab(QList<QString> variables, QString target_var, double epsilon, double percentage, bool maximize, QWidget *parent = 0);

    // Conventions
    //   Columns ordering
    int mMinimizeButtonId;
    int mMaximizeButtonId;
    // Getters
    double getEpsilon() const;
    QString getTargetVariable() const;
    int getGoalId() const;
    double  getBoundariesValue() const;

private:
    // Variable
    QLabel    *mpVariablesLabel;
    QComboBox *mpVariablesComboBox;
    QButtonGroup *mpGoalButtonGroup;
    QRadioButton *mpMinRadio;
    QRadioButton *mpMaxRadio;
    // Epsilon
    QLabel   *mpEpsilonLabel;
    SciNotationDoubleSpinbox *mpEpsilonBox;
    QLabel   *mpEpsilonHintLabel;
    // Boundaries
    QLabel *mpBoundariesLabel;
    QDoubleSpinBox *mpBoundariesBox;

    void toggleOptimType(bool maximize);

signals:

public slots:
};

#endif // OPTIMIZATIONTAB_H
