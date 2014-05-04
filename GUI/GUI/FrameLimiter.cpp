#include "FrameLimiter.h"
using namespace GuiAPI;

FrameLimiter::FrameLimiter(int _fps)
{
	fpsData = fps_data();

	FPS = _fps;

	max_frame_ticks = (1000.0 / (float)FPS) + 0.00001;
	frame_count = 0;
	last_second_ticks = SDL_GetTicks();
}


FrameLimiter::~FrameLimiter()
{
}

bool FrameLimiter::Limit()
{
	frame_count++;
	target_ticks = last_second_ticks + Uint32(frame_count * max_frame_ticks);
	current_ticks = SDL_GetTicks();
	
	average_ticks += current_ticks - last_frame_ticks;
	if (current_ticks - last_frame_ticks <= min_ticks)
	{
		min_ticks = current_ticks - last_frame_ticks;
	}
	if (current_ticks - last_frame_ticks >= max_frame_ticks)
	{
		max_ticks = current_ticks - last_frame_ticks;
	}
	
	if (current_ticks<target_ticks)
	{
		SDL_Delay(target_ticks - current_ticks);
		current_ticks = SDL_GetTicks();
	}
	
	last_frame_ticks = current_ticks;
	 
	if (current_ticks - last_second_ticks >= 1000)
	{
		fpsData.fps = frame_count;
		fpsData.frame_average = average_ticks / frame_count;
		fpsData.frame_min = min_ticks;
		fpsData.frame_max = max_ticks;
		
		frame_count = 0;
		min_ticks = 1000;
		max_ticks = 0;
		average_ticks = 0;
		last_second_ticks = SDL_GetTicks();
		return true;
	}
	
	return false;
}
