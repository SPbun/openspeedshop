#include "SPCanvasForm.hxx"

#include <qlabel.h> // REMOVE!
#include "debug.hxx"

/*! Work constructor.   Set's the name of the frame, the pointer to the
    parent panel container, and the frame shape and shadow characteristics.
*/
SPCanvasForm::SPCanvasForm( int label_height, QWidget *parent, const char *n, WFlags fl )
    : QWidget( parent, n, fl )
{
  nprintf(DEBUG_CONST_DESTRUCT) ( "SPCanvasForm::SPCanvasForm( ) constructor called\n");
  numColumns = 1;  // We by default create one... yet unused, but created.
setMinimumSize( QSize(30,30) );
  canvasTextList.clear();

  /*! Put all this in a layout so the resize does the right thing...  */
  canvasFormLayout = new QVBoxLayout( this, 0, -1, "CanvasFormLayout");

  canvasFormHeaderLayout = new QHBoxLayout( canvasFormLayout, -1, "canvasFormHeaderLayout" );
  canvasFormHeaderLayout->setMargin(1);

  QSpacerItem *spacerItem = new QSpacerItem(1,label_height, QSizePolicy::Fixed, QSizePolicy::Minimum );
  canvasFormHeaderLayout->addItem( spacerItem );

  header = new QHeader( this, "canvas header" );
  header->setCaption("canvas header");
  canvasFormHeaderLayout->addWidget( header );
  header->addLabel("LN", DEFAULT_CANVAS_WIDTH);
//  header->show();
  header->hide();
setBackgroundColor("blue");
header->setPaletteBackgroundColor("red");

  canvas = new QCanvas( this );
canvas->setBackgroundColor("green");
header->setPaletteBackgroundColor("pink");
  canvas->setBackgroundColor(parent->backgroundColor());
  canvasView = new SPCanvasView(canvas, this, "SPCanvasView");
header->setBackgroundColor("orange");
  canvasFormLayout->addWidget(canvasView);
canvasView->setPaletteBackgroundColor("white");
  canvasView->show();
}


/*! The default destructor. */
SPCanvasForm::~SPCanvasForm( )
{
  // default destructor.
  nprintf(DEBUG_CONST_DESTRUCT) ("  SPCanvasForm::~SPCanvasForm( ) destructor called\n");

  clearAllItems();
}

void
SPCanvasForm::setHighlights(QFont canvas_font, int lineHeight, int topLine, int visibleLines, int line_count, int top_offset)
{
  nprintf(DEBUG_CONST_DESTRUCT) ("SPCanvasForm::setHighlights()\n");
  nprintf(DEBUG_CONST_DESTRUCT) ("lineHeight=%d topLine=%d visibleLines=%d line_count=%d\n", lineHeight, topLine, visibleLines, line_count );

  int i = 0;
  char buffer[100];
  for(i=0;i<visibleLines;i++)
  {
    // Don't allow us to print past the number of lines in the file...
//    if( (topLine+i)-1 > line_count )
    if( topLine+i > line_count )
    {
      nprintf(DEBUG_CONST_DESTRUCT) ("line_count=%d topLine=%d i=%d == %d\n", line_count, topLine, i, topLine+i );
      break;
    }
    sprintf(buffer, "%d", topLine+i);
    QCanvasText *text = new QCanvasText( buffer, canvas_font, canvas);
    text->setColor("black");
    text->setX(10);
    text->setY( (i*lineHeight)-top_offset );
    text->setZ(1);
    text->show();
    canvasTextList.push_back(text);
  }

  canvas->update();
}

void
SPCanvasForm::clearAllItems()
{
    nprintf(DEBUG_CONST_DESTRUCT) ("clearAllItems(%d) entered\n", canvasTextList.count() );

  if( canvasTextList.empty() )
  {
    return;
  }
  
  QCanvasText *text_item = NULL;
  for( CanvasTextList::iterator it = canvasTextList.begin(); it != canvasTextList.end(); ++it )
  {
    text_item = (QCanvasText *)*it;
    text_item->hide();  
    if( text_item )
    {
      delete text_item;
    }
  }

  canvasTextList.clear();
}
