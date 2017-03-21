// Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.

#ifndef __UI_DFG_TabSearch_DFGPresetSearchWidget__
#define __UI_DFG_TabSearch_DFGPresetSearchWidget__

#include <FabricUI/DFG/DFGTabSearchWidget.h>

#include "QueryEdit.h"
#include "ResultsView.h"
#include "ResultPreview.h"

class QFrame;
class QLabel;
class QScrollArea;

namespace FabricUI
{
  namespace DFG
  {
    class DFGPresetSearchWidget : public DFGAbstractTabSearchWidget
    {
      Q_OBJECT

    typedef DFGAbstractTabSearchWidget Parent;

    public:
      DFGPresetSearchWidget( FabricCore::DFGHost* host );

      void showForSearch( QPoint globalPos ) FTL_OVERRIDE;
      void keyPressEvent( QKeyEvent *event ) FTL_OVERRIDE;
      void hideEvent( QHideEvent * e ) FTL_OVERRIDE;
      bool focusNextPrevChild( bool next ) FTL_OVERRIDE;

    signals:
      // Emitted when a Result (there are different types) has been chosen
      void selectedPreset( QString preset );
      void selectedBackdrop();
      void selectedGetVariable( const std::string name );
      void selectedSetVariable( const std::string name );
      // Emitted when the widget has completed its actions
      void giveFocusToParent();

    public slots:
      // Will ignore already registered variables
      void registerVariable( const std::string& name, const std::string& type );
      void unregisterVariables();

    private slots:
      void onQueryChanged( const TabSearch::Query& query );
      void onResultValidated( const std::string& result );
      void validateSelection();
      void hidePreview();
      void setPreview( const std::string& preset );
      void close();
      void updateSize();
      void registerStaticEntries();
      void updateDetailsPanelVisibility();
      void toggleDetailsPanel( bool toggled );
      void toggleDetailsPanel() { toggleDetailsPanel( !m_detailsPanelToggled ); }

    private:

      // Will the Query persist between 2 invocations ?
      bool m_clearQueryOnClose;
      bool m_staticEntriesAddedToDB;

      // Used to query the database
      FabricCore::DFGHost* m_host;
      std::set<std::string> m_registeredVariables;
      QFrame* m_searchFrame;
      QLabel* m_status;
      TabSearch::QueryEdit* m_queryEdit;
      TabSearch::ResultsView* m_resultsView;
      TabSearch::ResultPreview* m_resultPreview;
      QScrollArea* m_detailsPanel;
      TabSearch::Toggle* m_toggleDetailsButton;
      bool m_detailsPanelToggled;
    };
  };
};

#endif // __UI_DFG_TabSearch_DFGTabSearchWidget__
