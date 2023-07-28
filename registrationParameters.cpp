#include "registrationParameters.h"
#include "choiceModel.h"
#include "propertyItem.h"
#include <QDebug>
#include <QString>
#include <QVariant>

RegistrationParameters::RegistrationParameters(QObject *parent) : QObject(parent)
{
   setObjectName("RegistrationParameters");
}

RegistrationParameters::~RegistrationParameters()
{
   qDebug() << "~RegistrationParameters";
}

float RegistrationParameters::getValue() const
{
   return mValue;
}

void RegistrationParameters::setValue(float inValue)
{
   if (qFuzzyCompare(mValue, inValue))
      return;
   mValue = inValue;
}

float RegistrationParameters::getFloatValue() const
{
   return mFloatValue;
}

void RegistrationParameters::setFloatValue(float inFloatValue)
{
   if (qFuzzyCompare(mFloatValue, inFloatValue))
      return;
   mFloatValue = inFloatValue;
}

RegistrationParameters::Type RegistrationParameters::getType() const
{
   return mType;
}

void RegistrationParameters::setType(Type inType)
{
   if (mType == inType)
      return;
   mType = inType;
   emit signalTypeChanged();
}
