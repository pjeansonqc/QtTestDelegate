#pragma once

#include <QWidget>

namespace Ui
{
class DoubleScientificSpinBox;
}

class DoubleScientificSpinBox : public QWidget
{
   Q_OBJECT

 public:
   explicit DoubleScientificSpinBox(QWidget *parent = nullptr);
   ~DoubleScientificSpinBox();

   double getValue();
   void setValue(double inValue);

   int getPrecision() const;
   void setPrecision(int inPrecision);

 signals:
   void signalValueChanged();
   void signalPrecisionChanged();

 private:
   Ui::DoubleScientificSpinBox *ui;

   double mValue;
   int mPrecision = 4;
   Q_PROPERTY(double Value READ getValue WRITE setValue NOTIFY signalValueChanged)
   Q_PROPERTY(int Precision READ getPrecision WRITE setPrecision NOTIFY signalPrecisionChanged)
};
