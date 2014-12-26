#include <memory>
#include <vector>

#include "cinder/app/AppBasic.h"
#include "cinder/Color.h"

#include "ledimuff.h"
#include "led.h"
#include "simrun.h"

using namespace ci;
using namespace ci::app;
using namespace std;

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
 	shared_ptr<ledvm::ImuRunner> m_runner;
 	unique_ptr<ledvm::LedImuFile> m_file;
 	int m_led_count, m_state = 0;
};

void SimulatorApp::setup()
{
	auto vm_program = getOpenFilePath("", extensions);
	if (vm_program.empty()) {
		quit();
	}
	int count = ledvm::LedImuFile::RequiredPixelCountFor(vm_program.c_str());
	m_runner.reset(static_cast<ledvm::ImuRunner*>(new SimulationRunner(count)));
	m_file.reset(new ledvm::LedImuFile(m_runner, count));

	m_file->Load(vm_program.c_str());

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

	static_cast<SimulationRunner*>(m_runner.get())->draw(0);
	gl::popMatrices();
}

CINDER_APP_BASIC( SimulatorApp, RendererGl );