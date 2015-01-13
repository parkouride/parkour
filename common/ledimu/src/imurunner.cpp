#include <iostream>
#include "color.h"
#include "ledimu_data.h"
#include "imurunner.h"

using namespace ledvm;

void ImuRunner::set_all(const Color& color)
{
	for(int i=0;i<m_pixel_count;i++) 
	{
		std::cout << "Setting pixel " << i << " to " << (int)color.red << ", " << (int)color.green << ", " << (int)color.blue << std::endl;
		set_pixel(i, color);
	}
}
