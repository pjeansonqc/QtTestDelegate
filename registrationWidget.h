#pragma once

#include <QWidget>

class RegistrationAlgorithm;
class PropertyModel;
class RegistrationParameters;
class PropertyItem;

namespace Ui
{
class RegistrationWidget;
}

class RegistrationWidget : public QWidget
{
   Q_OBJECT

 public:
   explicit RegistrationWidget(QWidget *parent = nullptr);

   ~RegistrationWidget();

 signals:
   void signalAlgorithmChanged(QString inAlgorithm);
   void signalAlgorithmChanged(int inIndex);

 public slots:
   void onSetAlgorithmList(const QStringList &inAlgorithmList);
   void onSetAlgorithmSelection(int inIndex);
   void onSetObject(QObject *inObject);

 private slots:
   void on_algorithmListComboBox_currentIndexChanged(const QString &inAlgorithm);
   void on_algorithmListComboBox_currentIndexChanged(int index);

 private: // methods
   void initGui();
   void resizeContent();
   void setObjectInNode(QObject *inObject, PropertyItem *inItem);

 private:
   Ui::RegistrationWidget *mUiPtr;
   QStringList mHeaders;
   PropertyModel *mPropertyModelPtr = nullptr;
   QStringList mAlgorithmList;
};
