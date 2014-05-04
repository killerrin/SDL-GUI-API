#include "Window.h"
using namespace GuiAPI;

//Initialize the unique_ptr's deleters here
std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> Window::mWindow
= std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> Window::mRenderer
= std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>(nullptr, SDL_DestroyRenderer);

//Other static members
SDL_Rect Window::mBox;

bool Window::musicMute;
bool Window::soundEffect1Mute;
bool Window::soundEffect2Mute;
int Window::musicVolumeLevel;
int Window::soundEffect1VolumeLevel;
int Window::soundEffect2VolumeLevel;

void Window::Init(std::string title, int width, int height){
	//initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error("SDL Init Failed");
	if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");
	if (IMG_Init(IMG_INIT_PNG) == -1)
		throw std::runtime_error("Failed to Initialize PNG Extension");
	if (SDL_Init(SDL_INIT_AUDIO) == -1)
		throw std::runtime_error("Failed to Initialize SDL_MIXER");

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		throw std::runtime_error("Unable to Open Audio");
	}

	//Setup our window size
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = width;
	mBox.h = height;
	//Create our window
	mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, mBox.w, mBox.h, SDL_WINDOW_SHOWN));
	//Make sure it created ok
	if (mWindow == nullptr)
		throw std::runtime_error("Failed to create window");

	//Create the renderer
	mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	//Make sure it created ok
	if (mRenderer == nullptr)
		throw std::runtime_error("Failed to create renderer");

	//Set the Audio Level
	Window::musicMute = false;
	Window::soundEffect1Mute = false;
	Window::soundEffect2Mute = false;
	Window::musicVolumeLevel = 64;
	Window::soundEffect1VolumeLevel = 64;
	Window::soundEffect2VolumeLevel = 64;
	Mix_Volume(AudioChannel::MusicChannel, Window::musicVolumeLevel);
	Mix_Volume(AudioChannel::SoundEffectChannel1, Window::soundEffect1VolumeLevel);
	Mix_Volume(AudioChannel::SoundEffectChannel2, Window::soundEffect2VolumeLevel);
}

void Window::Quit(){
	// Destroy the Renderer
	SDL_DestroyRenderer(Window::mRenderer.get());

	// Destroy the Window
	SDL_DestroyWindow(Window::mWindow.get());

	// Quit the Image Extension
	IMG_Quit();

	// Quit the TTF Extension
	TTF_Quit();

	// Quit the Audio Extension
		//if (Mix_Playing(AudioChannel::Channel0) == 1)
	Mix_CloseAudio();

	// Quit the program
	SDL_Quit();
}

void Window::Title(std::string title)
{
	SDL_SetWindowTitle(mWindow.get(), title.c_str());
}

void Window::Draw(SDL_Texture *tex, int x, int y, int w, int h)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

	SDL_RenderCopy(Window::mRenderer.get(), tex, NULL, &pos);
}
void Window::Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip)
{
	//Convert pivot pos from relative to object's center to screen space
	xPivot += dstRect.w / 2;
	yPivot += dstRect.h / 2;
	//SDL expects an SDL_Point as the pivot location
	SDL_Point pivot = { xPivot, yPivot };
	//Draw the texture

	SDL_QueryTexture(tex, NULL, NULL, &dstRect.w, &dstRect.h);
	SDL_RenderCopyEx(mRenderer.get(), tex, clip, &dstRect, angle, &pivot, flip);
}

SDL_Texture* Window::LoadImage(const std::string &file)
{
	SDL_Surface *loadedImage = nullptr;
	SDL_Texture *texture = nullptr;

	loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(Window::mRenderer.get(), loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else {
		std::cout << SDL_GetError() << std::endl;
	}
	return texture;
}
SDL_Texture* Window::LoadTexture(const std::string &file)
{
	SDL_Texture *texture = IMG_LoadTexture(Window::mRenderer.get(), file.c_str());
	if (texture == nullptr)
		std::cout << "LoadTexture()" + file << std::endl;
	return texture;
}
TTF_Font* Window::LoadFont(const std::string &file, int fontSize)
{
	TTF_Font *font = TTF_OpenFont(file.c_str(), fontSize);
	if (font == nullptr){
		std::cout << SDL_GetError() << std::endl;
	}
	return font;
}

SDL_Texture* Window::RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize)
{
	//Open the font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == nullptr){
		TTF_CloseFont(font);
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Window::mRenderer.get(), surf);
	if (texture == nullptr){
		std::cout << SDL_GetError() << std::endl;
	}
	//Clean up the surface and font
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

void Window::Clear(){
	SDL_RenderClear(mRenderer.get());
}
void Window::Present(){
	SDL_RenderPresent(mRenderer.get());
}
SDL_Rect Window::Box(){
	//Update mBox to match the current window size
	SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h);
	return mBox;
}

SDL_Renderer* Window::Renderer()
{
	return Window::mRenderer.get();
}