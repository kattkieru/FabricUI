//
// Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.
//

#ifndef FABRICUI_FCURVEEDITOR_FCURVEEDITOR_H
#define FABRICUI_FCURVEEDITOR_FCURVEEDITOR_H

#include <QFrame>
#include <FabricUI/FCurveEditor/FCurveItem.h>
#include <FTL/Config.h>

class QGraphicsScene;

namespace FabricUI
{
namespace FCurveEditor
{
class RuledGraphicsView;

class FCurveEditor : public QFrame
{
  Q_OBJECT

  typedef QFrame Parent;

  // relative position of the value editor (negative values will be from the right/bottom)
  Q_PROPERTY( QPoint vePos READ vePos WRITE setVEPos )
  QPoint m_vePos;
  Q_PROPERTY( bool toolBarEnabled READ toolBarEnabled WRITE setToolBarEnabled )
  bool m_toolbarEnabled;

  RuledGraphicsView* m_rview;
  AbstractFCurveModel* m_model;
  QGraphicsScene* m_scene;
  FCurveItem* m_curveItem;
  class KeyValueEditor;
  KeyValueEditor* m_keyValueEditor;
  class ToolBar;
  ToolBar* m_toolBar;
  void veEditFinished( bool isXNotY );
  void updateVEPos();
  QAction* m_keysFrameAllAction;
  QAction* m_keysFrameSelectedAction;
  QAction* m_keysDeleteAction;

public:
  FCurveEditor();
  ~FCurveEditor();
  void setModel( AbstractFCurveModel* );
  void frameAllKeys();
  void frameSelectedKeys();

  inline QPoint vePos() const { return m_vePos; }
  inline void setVEPos( const QPoint& p ) { m_vePos = p; this->updateVEPos(); }
  inline bool toolBarEnabled() const { return m_toolbarEnabled; }
  void setToolBarEnabled( bool );

protected:
  void mousePressEvent( QMouseEvent * ) FTL_OVERRIDE;
  void resizeEvent( QResizeEvent * ) FTL_OVERRIDE;
  void keyPressEvent( QKeyEvent * ) FTL_OVERRIDE;
  void keyReleaseEvent( QKeyEvent * ) FTL_OVERRIDE;

private slots:
  void onRectangleSelectReleased( const QRectF&, Qt::KeyboardModifiers );
  void onFrameAllKeys();
  void onFrameSelectedKeys();
  void onDeleteSelectedKeys();
  void onSelectAllKeys();
  void onDeselectAllKeys();
  void onEditedKeysChanged();
  void onRepaintViews();
  void onModeChanged();
  void setModeSelect() { m_curveItem->setMode( FCurveItem::SELECT ); }
  void setModeAdd() { m_curveItem->setMode( FCurveItem::ADD ); }
  void setModeRemove() { m_curveItem->setMode( FCurveItem::REMOVE ); }
  inline void veXEditFinished() { this->veEditFinished( true ); }
  inline void veYEditFinished() { this->veEditFinished( false ); }
  void showContextMenu(const QPoint& pos);

signals:
  void interactionBegin();
  void interactionEnd();
};

} // namespace FCurveEditor
} // namespace FabricUI

#endif // FABRICUI_FCURVEEDITOR_FCURVEEDITOR_H
