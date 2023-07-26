#include "registrationParameters.h"
#include "choiceModel.h"
#include "propertyItem.h"
#include <QDebug>
#include <QString>
#include <QVariant>

RegistrationParameters::RegistrationParameters(QObject *parent) : QObject(parent)
{
   setObjectName("RegistrationParameters");
   setProperty("value", 123);
   setProperty("float", 123.2f);
}

RegistrationParameters::~RegistrationParameters()
{
   qDebug() << "~RegistrationParameters";
}
