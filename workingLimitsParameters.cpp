#include "workingLimitsParameters.h"
#include "choiceModel.h"
#include <QDebug>
#include <QString>
#include <QVariant>

WorkingLimitsParameters::WorkingLimitsParameters(QObject *parent) : QObject(parent)
{
   setObjectName("WorkingLimitsParameters");
   setProperty("X", 1.123f);
   setProperty("Y", 2.123f);
   setProperty("Z", 3.123f);
   setProperty("rX", 4.123f);
   setProperty("rY", 5.123f);
   setProperty("rZ", 6.123f);
   setProperty("W", 7.123f);
   setProperty("OnOff", true);

   QVariant var;
   var.setValue(ChoiceModel({"choice 1", "choice 2", "choice 3"}, 2));
   setProperty("Choices", var);
}

WorkingLimitsParameters::~WorkingLimitsParameters()
{
   qDebug() << "~WorkingLimitsParameters";
}
