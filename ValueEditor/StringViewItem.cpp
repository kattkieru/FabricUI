//
// Copyright (c) 2010-2016, Fabric Software Inc. All rights reserved.
//

#include "StringViewItem.h"
#include "QVariantRTVal.h"
#include "VELineEdit.h"
#include "VEDialog.h"

#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>

using namespace FabricUI::ValueEditor;

StringViewItem::StringViewItem(
  QString const &name,
  QVariant const &value,
  ItemMetadata* metadata
  )
  : BaseViewItem( name, metadata )
{
  m_edit = new VELineEdit;
  m_edit->setObjectName( "VELeft" );
  m_edit->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::MinimumExpanding );
  
  QPushButton* inspectButton = new QPushButton;
  inspectButton->setObjectName( "VERight" );
  inspectButton->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::MinimumExpanding );

  onModelValueChanged( value );

  QHBoxLayout *layout = new QHBoxLayout;
  layout->setContentsMargins( 0, 0, 0, 0 );
  layout->setSpacing( 0 );
  layout->addWidget( m_edit );
  layout->addWidget( inspectButton );

  m_widget = new QFrame;
  m_widget->setObjectName( "VEStringViewItem" );
  m_widget->setLayout( layout );

  connect(
    m_edit, SIGNAL( textModified( QString ) ),
    this, SLOT( onTextModified( QString ) )
    );
  connect(
    inspectButton, SIGNAL( clicked() ),
    this, SLOT( onInspect() )
    );
}

StringViewItem::~StringViewItem()
{
}

QWidget *StringViewItem::getWidget()
{
  return m_widget;
}

void StringViewItem::onModelValueChanged( QVariant const &v )
{
  m_edit->setText( v.value<QString>() );
}

void StringViewItem::onTextModified( QString text )
{
  emit viewValueChanged(
    QVariant::fromValue<QString>( text )
    );
}

void StringViewItem::onInspect()
{
  // Show a multi-line dialog to display 
  // the full string contents
  VEDialog dlg( m_widget, Qt::Window | Qt::Dialog /*| Qt::FramelessWindowHint*/ );
  dlg.setModal( true );
  // Add text editor
  QVBoxLayout *layout = new QVBoxLayout( &dlg );
  QPlainTextEdit* txtEdit = new QPlainTextEdit;
  txtEdit->setPlainText( m_edit->text() );
  layout->addWidget( txtEdit );

  // Ok/cancel
  QDialogButtonBox* buttonBox = new QDialogButtonBox( 
                                      QDialogButtonBox::Ok
                                    | QDialogButtonBox::Cancel );

  connect( buttonBox, SIGNAL( accepted() ), &dlg, SLOT( accept() ) );
  connect( buttonBox, SIGNAL( rejected() ), &dlg, SLOT( reject() ) );
  layout->addWidget( buttonBox );
 
  // Post dialog under mouse
  QPoint pos = QCursor::pos();
  dlg.move( pos.x(), pos.y() );

  if ( dlg.exec() == QDialog::Accepted )
  {
    emit viewValueChanged(
      QVariant::fromValue<QString>( txtEdit->toPlainText() )
      );
  }
}

//////////////////////////////////////////////////////////////////////////
// 

BaseViewItem* StringViewItem::CreateItem(
  QString const &name,
  QVariant const &value,
  ItemMetadata* metaData
  )
{
  if (RTVariant::isType<QString>(value))
  {
    return new StringViewItem( name, value, metaData );
  }
  return 0;
}

const int StringViewItem::Priority = 3;
