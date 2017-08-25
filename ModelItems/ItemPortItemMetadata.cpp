//
// Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.
//


#include <FabricUI/ModelItems/ItemPortItemMetadata.h>

#include <sstream>

using namespace FabricUI::ModelItems;

ItemPortItemMetadata::ItemPortItemMetadata( ItemPortModelItem *nodePortModelItem )
  : m_nodePortModelItem( nodePortModelItem )
{
  this->computeDFGPath();
}

void ItemPortItemMetadata::computeDFGPath()
{
  QString bdid = QString::number(m_nodePortModelItem->getBinding().getBindingID());
  m_bindingId = bdid.toUtf8().constData();

  m_portPath = m_nodePortModelItem->getExec().getExecPath().getCStr();
  m_portPath += ".";
  m_portPath += m_nodePortModelItem->getPortPath().c_str();

  QString dfgPath = m_portPath.c_str();
	if(dfgPath.mid(0, 1) == ".")
    dfgPath = dfgPath.mid(1);

  m_dfgPath = (bdid + "." + dfgPath).toUtf8().constData();
}
