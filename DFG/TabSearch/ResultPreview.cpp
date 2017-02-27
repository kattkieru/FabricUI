// Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.

#include "ResultPreview.h"

#include "ItemView.h"

#include <FabricCore.h>
#include <iostream>
#include <QLayout>
#include <QLabel>
#include <FTL/JSONValue.h>

using namespace FabricUI::DFG::TabSearch;
using namespace FabricCore;

ResultPreview::ResultPreview( QString preset, DFGHost* host )
  : m_preset( preset )
{
  QVBoxLayout* layout = new QVBoxLayout();

  String descStr = host->getPresetDesc( preset.toStdString().data() );
  FTL::JSONValue* desc = FTL::JSONValue::Decode( std::string( descStr.getCStr(), descStr.getSize() ) );
  FTL::CStrRef nameStr = desc->cast<FTL::JSONObject>()->getString( "presetName" );

  QFont font;

  // Name
  {
    QLabel* label = new QLabel( "<b>" + QString::fromStdString( nameStr ) + "</b>" );
    font.setPointSize( 16 ); label->setFont( font );
    layout->addWidget( label );
  }

  // Path
  {
    QLabel* label = new QLabel( "<i>" + preset + "</i>" );
    font.setPointSize( 8 ); label->setFont( font );
    layout->addWidget( label );
  }

  // Tags
  {
    FEC_StringRef tagsStrR = FEC_DFGHostGetPresetTags( host->getFECDFGHostRef(), preset.toStdString().data() );
    FTL::StrRef tagsStr( FEC_StringGetCStr( tagsStrR ), FEC_StringGetSize( tagsStrR ) );
    FTL::JSONValue* tags = FTL::JSONValue::Decode( tagsStr );
    FTL::JSONArray* tagsA = tags->cast<FTL::JSONArray>();

    for( FTL::JSONArray::const_iterator it = tagsA->begin(); it != tagsA->end(); it++ )
      layout->addWidget( new TagView( (*it)->getStringValue() ) );
  }

  layout->setAlignment( Qt::AlignTop );
  this->setLayout( layout );
}

QString ResultPreview::getPreset() const { return m_preset; }
