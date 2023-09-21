#include "pointToPointParameters.h"
#include <QDebug>
#include <QString>
#include <QVariant>

PointToPointParameters::PointToPointParameters(QObject *parent) : QObject{parent}
{
   setObjectName("PointToPointParameters");
   setProperty("param1", 1.1234e20f);
   setProperty("param2", 200.0);
}

PointToPointParameters::~PointToPointParameters()
{
   qDebug() << "~PointToPointParameters";
}
