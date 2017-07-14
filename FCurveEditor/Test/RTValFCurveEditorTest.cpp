
#include <FabricUI/FCurveEditor/Test/Test.h>
#include <FabricUI/FCurveEditor/FCurveEditor.h>
#include <FabricUI/FCurveEditor/Models/AnimXKL/RTValAnimXFCurveModel.h>

#include <FabricCore.h>

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <assert.h>

using namespace FabricUI::FCurveEditor;

void ReportCallBack(
  void *userdata,
  FEC_ReportSource source,
  FEC_ReportLevel level,
  char const *data,
  uint32_t size
)
{
  std::cout << std::string( data, size ).c_str() << std::endl;
}

inline float RandFloat() { return float( rand() ) / RAND_MAX; }

int main()
{
  int argc = 0;
  QApplication app( argc, NULL );

  FabricCore::Client::CreateOptions createOptions = {};
  createOptions.guarded = true;
  FabricCore::Client client( &ReportCallBack, 0, &createOptions );
  client.loadExtension( "AnimX", "", false );

  FabricCore::RTVal curveRTVal = FabricCore::RTVal::Create( client, "AnimX::AnimCurve", 0, NULL );
  QFile curveFile( "curve.json" );
  if( curveFile.open( QIODevice::ReadOnly ) )
  {
    QString curveJSON = QTextStream( &curveFile ).readAll();
    FabricCore::RTVal rtJson = FabricCore::RTVal::ConstructString( client, curveJSON.toUtf8().data() );
    curveRTVal.callMethod( "Boolean", "convertFromString", 1, &rtJson );
  }
  
  RTValAnimXFCurveVersionedModel curve;
  curve.setValue( curveRTVal );

  FCurveEditor* editor = new FCurveEditor();
  editor->setModel( &curve );
  editor->resize( 800, 600 );
  editor->show();
  editor->setStyleSheet( LoadQSS() );

  app.exec();

  curveFile.close();
  curveFile.open( QIODevice::WriteOnly );
  assert( curveFile.isOpen() );
  QTextStream( &curveFile ) << curveRTVal.callMethod( "String", "convertToString", 0, NULL ).getStringCString();
  return 0;
}
