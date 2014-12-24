#include "cinder/app/AppBasic.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SimulatorApp : public AppBasic {
	public:
	 void setup();
	 void draw();
	 void mouseDrag( MouseEvent event );
     void keyDown( KeyEvent event );
};

void SimulatorApp::setup()
{

}

void SimulatorApp::mouseDrag( MouseEvent event )
{

}

void SimulatorApp::keyDown( KeyEvent event )
{
	switch(event.getChar())
	{
		case 'f':
			setFullScreen(!isFullScreen());
			break;
		case 27: // Escape
			quit();
	}
}

void SimulatorApp::draw()
{
	gl::clear( Color( 0.3f, 0.3f, 0.3f) );
	gl::drawSolidCircle({10, 10}, 10.0f);
}

CINDER_APP_BASIC( SimulatorApp, RendererGl );