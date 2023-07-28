#pragma once

#include "choiceModel.h"
#include "registrationParameters.h"


class WorkingLimitsParameters : public QObject
{
   Q_OBJECT
 public:
   explicit WorkingLimitsParameters(QObject *parent = nullptr);
   ~WorkingLimitsParameters();


 public:
   float getY() const;
   void setY(float inY);

   float getX() const;
   void setX(float inX);

   float getZ() const;
   void setZ(float inZ);

   float getRX() const;
   void setRX(float inRX);

   float getRY() const;
   void setRY(float inRY);

   float getRZ() const;
   void setRZ(float inRZ);

   float getW() const;
   void setW(float inW);

   bool getOnOff() const;
   void setOnOff(bool inOnOff);

   const ChoiceModel &getChoices() const;
   void setChoices(const ChoiceModel &inChoices);

 signals:
   void signalYChanged();
   void signalXChanged();
   void signalZChanged();
   void signalRXChanged();
   void signalRYChanged();
   void signalRZChanged();
   void signalWChanged();
   void signalOnOffChanged();

   void signalChoicesChanged();

 private:
   void logMembers();

 private:
   float mX = 1.234f;
   float mY = 2.234f;
   float mZ = 2.234f;
   float mRX = 4.123f;
   float mRY = 5.123f;
   float mRZ = 6.123f;
   float mW = 7.123f;
   bool mOnOff = true;
   ChoiceModel mChoices;

   // QObject interface
   Q_PROPERTY(float X READ getX WRITE setX NOTIFY signalXChanged)
   Q_PROPERTY(float Y READ getY WRITE setY NOTIFY signalYChanged)
   Q_PROPERTY(float Z READ getZ WRITE setZ NOTIFY signalZChanged)
   Q_PROPERTY(float RX READ getRX WRITE setRX NOTIFY signalRXChanged)
   Q_PROPERTY(float RY READ getRY WRITE setRY NOTIFY signalRYChanged)
   Q_PROPERTY(float RZ READ getRZ WRITE setRZ NOTIFY signalRZChanged)
   Q_PROPERTY(float W READ getW WRITE setW NOTIFY signalWChanged)
   Q_PROPERTY(bool OnOff READ getOnOff WRITE setOnOff NOTIFY signalOnOffChanged)
   Q_PROPERTY(ChoiceModel Choices READ getChoices WRITE setChoices NOTIFY signalChoicesChanged)
};
