#include "doubleScientificSpinBox.h"
#include "ui_doubleScientificSpinBox.h"
#include <cmath>


DoubleScientificSpinBox::DoubleScientificSpinBox(QWidget *parent) : QWidget(parent), ui(new Ui::DoubleScientificSpinBox)
{
   ui->setupUi(this);
   ui->doubleSpinBox->setDecimals(mPrecision);
}

DoubleScientificSpinBox::~DoubleScientificSpinBox()
{
   delete ui;
}

double DoubleScientificSpinBox::getValue()
{
   ui->doubleSpinBox->value();
   ui->spinBox->value();
   mValue = ui->doubleSpinBox->value() * std::pow(10, ui->spinBox->value());
   return mValue;
}

void DoubleScientificSpinBox::setValue(double inValue)
{
   if (qFuzzyCompare(mValue, inValue))
      return;
   int power = std::floor(log10(inValue));
   if (abs(power) > mPrecision)
   {
      double mantissa = inValue / std::pow(10, power);
      ui->doubleSpinBox->setMinimum(-10.0);
      ui->doubleSpinBox->setMaximum(10.0);
      ui->doubleSpinBox->setValue(mantissa);
      ui->spinBox->setEnabled(true);
      ui->spinBox->setVisible(true);
      ui->label->setVisible(true);
      ui->spinBox->setValue(power);
   }
   else
   {
      ui->doubleSpinBox->setMinimum(-std::numeric_limits<double>::min());
      ui->doubleSpinBox->setMaximum(std::numeric_limits<double>::max());
      ui->doubleSpinBox->setValue(inValue);
      ui->spinBox->setEnabled(false);
      ui->spinBox->setVisible(false);
      ui->label->setVisible(false);
   }

   ui->doubleSpinBox->setSingleStep(pow(10, -mPrecision));
   mValue = inValue;
   emit signalValueChanged();
}

int DoubleScientificSpinBox::getPrecision() const
{
   return mPrecision;
}

void DoubleScientificSpinBox::setPrecision(int inPrecision)
{
   if (mPrecision == inPrecision)
      return;
   mPrecision = inPrecision;
   emit signalPrecisionChanged();
}
