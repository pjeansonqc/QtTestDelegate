#pragma once

#include <QObject>

class PointToPointParameters : public QObject
{
 public:
   explicit PointToPointParameters(QObject *parent = nullptr);
   ~PointToPointParameters();
};
