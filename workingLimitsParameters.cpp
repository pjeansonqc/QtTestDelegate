#include "workingLimitsParameters.h"
#include "choiceModel.h"
#include <QDebug>
#include <QEvent>
#include <QString>
#include <QVariant>

WorkingLimitsParameters::WorkingLimitsParameters(QObject *parent) : QObject(parent)
{
   setObjectName("WorkingLimitsParameters");

   mChoices = ChoiceModel({"choice 1", "choice 2", "choice 3"}, 2);
}

WorkingLimitsParameters::~WorkingLimitsParameters()
{
   qDebug() << "~WorkingLimitsParameters";
}

float WorkingLimitsParameters::getX() const
{
   return mX;
}

void WorkingLimitsParameters::setX(float inX)
{
   if (qFuzzyCompare(mX, inX))
      return;
   mX = inX;
   emit signalXChanged();
   logMembers();
}

float WorkingLimitsParameters::getY() const
{
   return mY;
}

void WorkingLimitsParameters::setY(float inY)
{
   if (qFuzzyCompare(mY, inY))
      return;
   mY = inY;
   emit signalYChanged();
   logMembers();
}


void WorkingLimitsParameters::logMembers()
{
   qDebug() << "WorkingLimitsParameters";
   qDebug() << "\tX" << mX;
   qDebug() << "\tY" << mY;
   qDebug() << "\tZ" << mZ;
}

const ChoiceModel &WorkingLimitsParameters::getChoices() const
{
   return mChoices;
}

void WorkingLimitsParameters::setChoices(const ChoiceModel &inChoices)
{
   if (mChoices == inChoices)
      return;
   mChoices = inChoices;
   emit signalChoicesChanged();
}

bool WorkingLimitsParameters::getOnOff() const
{
   return mOnOff;
}

void WorkingLimitsParameters::setOnOff(bool inOnOff)
{
   if (mOnOff == inOnOff)
      return;
   mOnOff = inOnOff;
   emit signalOnOffChanged();
}

float WorkingLimitsParameters::getW() const
{
   return mW;
}

void WorkingLimitsParameters::setW(float inW)
{
   if (qFuzzyCompare(mW, inW))
      return;
   mW = inW;
   emit signalWChanged();
}

float WorkingLimitsParameters::getRZ() const
{
   return mRZ;
}

void WorkingLimitsParameters::setRZ(float inRZ)
{
   if (qFuzzyCompare(mRZ, inRZ))
      return;
   mRZ = inRZ;
   emit signalRZChanged();
}

float WorkingLimitsParameters::getRY() const
{
   return mRY;
}

void WorkingLimitsParameters::setRY(float inRY)
{
   if (qFuzzyCompare(mRY, inRY))
      return;
   mRY = inRY;
   emit signalRYChanged();
}

float WorkingLimitsParameters::getRX() const
{
   return mRX;
}

void WorkingLimitsParameters::setRX(float inRX)
{
   if (qFuzzyCompare(mRX, inRX))
      return;
   mRX = inRX;
   emit signalRXChanged();
}

float WorkingLimitsParameters::getZ() const
{
   return mZ;
}

void WorkingLimitsParameters::setZ(float inZ)
{
   if (qFuzzyCompare(mZ, inZ))
      return;
   mZ = inZ;
   emit signalZChanged();
   logMembers();
}
