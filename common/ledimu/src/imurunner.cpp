#include "ledimu_data.h"
#include "imurunner.h"

using namespace ledvm;

void ImuRunner::set_all(const Color& color)
{
	for(int i=0;i<m_pixel_count;i++) 
	{
		set_pixel(i, color);
	}
}