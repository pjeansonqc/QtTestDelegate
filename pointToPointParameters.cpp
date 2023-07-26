#include "pointToPointParameters.h"
#include <QDebug>
#include <QString>
#include <QVariant>

PointToPointParameters::PointToPointParameters(QObject *parent) : QObject{parent}
{
   setObjectName("PointToPointParameters");
   setProperty("param1", 1.123f);
   setProperty("param2", 2);
}

PointToPointParameters::~PointToPointParameters()
{
   qDebug() << "~PointToPointParameters";
}
