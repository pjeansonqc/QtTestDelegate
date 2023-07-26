#pragma once

#include <QObject>
class PropertyItem;

class RegistrationParameters : public QObject
{
   Q_OBJECT
 public:
   explicit RegistrationParameters(QObject *parent = nullptr);
   ~RegistrationParameters();
};
