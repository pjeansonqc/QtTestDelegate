#pragma once

#include <QMetaType>
#include <QStringList>

class ChoiceModel
{
 public:
   ChoiceModel(const QStringList &inChoices = {""}, int inSelection = 0) : mChoiceList(inChoices), mSelection(inSelection) {}
   int getSelection();
   void setSelection(int inSelection);

   const QStringList &getChoiceList() const;
   void setChoiceList(const QStringList &inChoiceList);

   QString getSelectedChoice();
   bool operator==(const ChoiceModel &inOther) const
   {
      return (mSelection == inOther.mSelection && mChoiceList == inOther.mChoiceList);
   }

 private: // methods
 private:
   QStringList mChoiceList;
   int mSelection = 0;
};
Q_DECLARE_METATYPE(ChoiceModel)
