#pragma once

#include <QMainWindow>

class PropertyItemDelegate;
class RegistrationWidget;
class RegistrationParameters;
class WorkingLimitsParameters;

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

 public:
   MainWindow(QWidget *parent = nullptr);
   virtual ~MainWindow();

 public slots:
   //   void updateActions();

 private slots:
   //   void insertChild();
   //   bool insertColumn();
   //   void insertRow();
   //   bool removeColumn();
   //   void removeRow();

 private:
   Ui::MainWindow *ui;


   RegistrationWidget *mRegistrationWidgetPtr = nullptr;
   RegistrationParameters *mRegistrationParametersPtr = nullptr;
   WorkingLimitsParameters *mWorkingLimitsParametersPtr = nullptr;
};
