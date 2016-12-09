//
// Copyright (c) 2010-2016, Fabric Software Inc. All rights reserved.
//

#include <FabricUI/GraphView/Graph.h>
#include <FabricUI/GraphView/Port.h>
#include <FabricUI/GraphView/PortLabel.h>

#include <QDrag>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

namespace FabricUI {
namespace GraphView {

PortLabel::PortLabel(
  Port * parent,
  QString const &text,
  QColor color,
  QColor hlColor,
  QFont font
  )
  : TextContainer(
    parent,
    text,
    color,
    hlColor,
    font
    )
  , m_port( parent )
{
  setEditable( m_port->allowEdits() && m_port->graph()->isEditable() );
}

void PortLabel::displayedTextChanged()
{
  TextContainer::displayedTextChanged();
  emit m_port->contentChanged();
}

void PortLabel::submitEditedText(const QString& text)
{
  Port *port = m_port;
  if ( port->allowEdits()
    && port->graph()->isEditable() )
  {
    port->graph()->controller()->gvcDoRenameExecPort( port->nameQString(), text );
  }
}

} // namespace GraphView
} // namespace FabricUI
