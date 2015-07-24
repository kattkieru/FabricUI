//
// Copyright 2010-2015 Fabric Software Inc. All rights reserved.
//

#ifndef __UI_DFG_DFGUICmd_AddSet__
#define __UI_DFG_DFGUICmd_AddSet__

#include <FabricUI/DFG/DFGUICmd/DFGUICmd_AddNode.h>

FABRIC_UI_DFG_NAMESPACE_BEGIN

class DFGUICmd_AddSet
  : public DFGUICmd_AddNode
{
public:

  DFGUICmd_AddSet(
    FabricCore::DFGBinding const &binding,
    FTL::StrRef execPath,
    FabricCore::DFGExec const &exec,
    FTL::StrRef desiredNodeName,
    FTL::StrRef varPath,
    QPointF pos
    )
    : DFGUICmd_AddNode(
      binding,
      execPath,
      exec,
      desiredNodeName,
      pos
      )
    , m_varPath( varPath )
    {}

  static FTL::CStrRef CmdName()
    { return FTL_STR("dfgAddSet"); }

protected:

  FTL::CStrRef getDesiredNodeName()
    { return getPrimaryArg(); }
  
  virtual void appendDesc( std::string &desc );

  virtual FTL::CStrRef invokeAdd( unsigned &coreUndoCount );

private:

  std::string m_varPath;
};

FABRIC_UI_DFG_NAMESPACE_END

#endif // __UI_DFG_DFGUICmd_AddSet__
