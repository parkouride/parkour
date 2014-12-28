#include <memory>
#include <vector>

#include "cinder/app/AppBasic.h"
#include "cinder/Color.h"

#include "ledimuff.h"
#include "posix/bytestream.h"
#include "led.h"
#include "simrun.h"

using namespace ci;
using namespace ci::app;
using namespace std;

template class ledvm::LedImuFile<ByteStream, SimulationRunner>;
using LedFile = ledvm::LedImuFile<ByteStream, SimulationRunner>;

const vector<string> extensions {
	"ledprog"
};

class SimulatorApp : public AppBasic {
public:
	 void setup();
	 void draw();
	 void update();
	 void mouseDrag( MouseEvent event );
     void keyDown( KeyEvent event );
 private:
 	unique_ptr<LedFile> m_file;
 	int m_led_count, m_state = 0;
};

void SimulatorApp::setup()
{
	auto vm_program = getOpenFilePath("", extensions);
	if (vm_program.empty()) {
		quit();
	}
	int count = LedFile::RequiredPixelCountFor(vm_program.c_str());
	m_file.reset(new LedFile(count, vm_program.c_str()));

	m_file->Load();

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
		case 'q':
			quit();
	}
}

void SimulatorApp::update()
{
	int next_state = m_file->RunState(m_state);
	if (next_state >= 0) {
		m_state = next_state;
	}
}

void SimulatorApp::draw()
{
	// update();
	gl::clear( Color( 0.3f, 0.3f, 0.3f) );
	gl::pushMatrices();
	gl::translate(50.0f, 50.0f);

    m_file->GetRunner()->draw(0);
	gl::popMatrices();
}

CINDER_APP_BASIC( SimulatorApp, RendererGl );