#pragma once

#include <QObject>
class PropertyItem;

class RegistrationParameters : public QObject
{
   Q_OBJECT
 public:
   explicit RegistrationParameters(QObject *parent = nullptr);
   ~RegistrationParameters();

   float getValue() const;
   void setValue(float inValue);

   float getFloatValue() const;
   void setFloatValue(float inFloatValue);
   enum Type
   {
      PointTopoint,
      PointToplane,
      PlaneToPlane
   };
   Q_ENUM(Type)
   Type getType() const;
   void setType(Type inType);

 signals:
   void signalValueChanged();
   void signalFloatChanged();
   void signalFloatValueChanged();

   void signalTypeChanged();

 private:
   float mValue = 1.123f;
   float mFloatValue = 2.32f;
   Type mType;


   Q_PROPERTY(float Value READ getValue WRITE setValue NOTIFY signalValueChanged)
   Q_PROPERTY(float FloatValue READ getFloatValue WRITE setFloatValue NOTIFY signalFloatValueChanged)
   Q_PROPERTY(Type Type READ getType WRITE setType NOTIFY signalTypeChanged)
};
