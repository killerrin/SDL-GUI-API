#pragma once
#include "SDLIncludes.h"

namespace GuiAPI {
	struct fps_data
	{
		Uint32 frame_min;
		Uint32 frame_max;
		double frame_average;
		int fps;
	};

	class FrameLimiter
	{
	private:
		fps_data fpsData;

		int FPS;
		int frame_count;

		float max_frame_ticks;
		double average_ticks;

		Uint32 last_frame_ticks;
		Uint32 last_second_ticks;
		Uint32 min_ticks;
		Uint32 max_ticks;
		Uint32 current_ticks;
		Uint32 target_ticks;

	public:
		FrameLimiter(int _fps);
		~FrameLimiter();

		bool Limit();

		double GetFPS()
		{
			return (double)FPS;
		};
	};
}
