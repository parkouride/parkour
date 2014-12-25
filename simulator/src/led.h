#pragma once

#include <memory>
#include "cinder/gl/gl.h"
#include "cinder/Color.h"


class Led {
public:
	Led() : m_color{new ci::Color8u(0, 0, 0)} { }
	~Led() {}

	void draw(float position) {
		// Expects matrix to be applied
		ci::gl::SaveColorState colorState;

		ci::gl::color(*m_color);
		ci::gl::drawSolidCircle({position,0}, 10.0f);
	}

	inline void set_color(std::unique_ptr<ci::Color8u> color) {
		m_color = std::move(color);
	}

private:
	std::unique_ptr<ci::Color8u> m_color;
};