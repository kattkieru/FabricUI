// Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.

#include "DFGVariablePathComboBox.h"
#include "../DFGBindingUtils.h"
#include <FTL/CStrRef.h>
#include <FTL/JSONValue.h>

using namespace FabricUI;
using namespace FabricUI::DFG;

DFGVariablePathComboBox::DFGVariablePathComboBox(
  QWidget * parent,
  FabricCore::DFGBinding const &binding,
  FTL::CStrRef currentExecPath,
  QString text
  )
  : QComboBox(parent)
{
  setEditable(true);

  FabricCore::DFGBinding localBinding = binding;
  QStringList words = DFGBindingUtils::getVariableWordsFromBinding(localBinding, currentExecPath);
  words.sort();
  addItems(words);
}
