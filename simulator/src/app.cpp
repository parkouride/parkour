#include <memory>

#include "cinder/app/AppBasic.h"
#include "cinder/Color.h"

using namespace ci;
using namespace ci::app;
using namespace std;

constexpr float led_size = 10.0f;
constexpr float led_spacing = 15.0f;
constexpr float step = led_size + led_spacing;

class Led {
public:
	Led() : m_color{new Color8u(0, 0, 0)} { }
	~Led() {}

	void draw(float position) {
		// Expects matrix to be applied
		gl::SaveColorState colorState;

		gl::color(*m_color);
		gl::drawSolidCircle({position,0}, 10.0f);
	}

	void set_color(unique_ptr<Color8u> color) {
		m_color = move(color);
	}

private:
	unique_ptr<Color8u> m_color;
};

class SimulatorApp : public AppBasic {
public:
	 void setup();
	 void draw();
	 void update();
	 void mouseDrag( MouseEvent event );
     void keyDown( KeyEvent event );
 private:
 	unique_ptr<Led[]> m_leds;
 	int m_led_count = 3;
};

void SimulatorApp::setup()
{
	// TODO: Load VM, set initial state, determine number of leds
	// TODO: Determine how to show a file dialog
	m_leds.reset(new Led[m_led_count]);
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

void SimulatorApp::update()
{
	// TODO: Run Current State of the VM
}

void SimulatorApp::draw()
{
	gl::pushMatrices();
	gl::translate(50.0f, 50.0f);
	gl::clear( Color( 0.3f, 0.3f, 0.3f) );
	for (int i=0; i< m_led_count; ++i) {
		m_leds[i].draw(static_cast<float>(i) * step);
		// TODO: Layout Manager that lays out the leds in different patterns
	}
	gl::popMatrices();
}

CINDER_APP_BASIC( SimulatorApp, RendererGl );