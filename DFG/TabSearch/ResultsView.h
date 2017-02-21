// Copyright (c) 2010-2017 Fabric Software Inc. All rights reserved.

#ifndef __UI_DFG_TabSearch_ResultsView__
#define __UI_DFG_TabSearch_ResultsView__

#include <QListView>
#include <QStringListModel>

#include <FTL/Config.h>

namespace FabricUI
{
  namespace DFG
  {
    namespace TabSearch
    {
      class ResultsView : public QListView
      {
        Q_OBJECT

      public:
        ResultsView();

        QString getSelectedPreset();
        inline int numberResults() const { return m_model.rowCount(); }

      public slots:
        void setResults( std::vector<std::string> results );
        void moveSelection( int increment = +1 );

      signals:
        void presetSelected( QString preset );

      protected:
        void setSelection( unsigned int index );

      private:
        QStringListModel m_model;

        struct SelectionModel : public QItemSelectionModel
        {
          ResultsView* view;
          SelectionModel( ResultsView* view ) : view( view ) {}
          void setCurrentIndex( const QModelIndex &index, QItemSelectionModel::SelectionFlags command ) FTL_OVERRIDE;
        } m_selectionModel;
      };
    }
  };
};

#endif // __UI_DFG_TabSearch_ResultsView__
