#pragma once

#include <QObject>
class PropertyItem;

class RegistrationParameters : public QObject
{
 public:
   explicit RegistrationParameters(QObject *parent = nullptr);
   ~RegistrationParameters();
};
