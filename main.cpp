#include "QVTKApplication.h"

#include "GUI4.h"

int main(int argc, char** argv)
{
  QVTKApplication app(argc, argv);
  GUI4 widget;

  widget.show();


  return app.exec();
}
