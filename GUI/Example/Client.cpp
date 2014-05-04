#include "Client.h"
using namespace Example;
using namespace GuiAPI;

Client* Client::instance;

Client::Client()
{
	////-- Initialize the API
	GUI::Init();

	// Set the API Mode
	GUI::SetAPIHandleMode(APIMode::FocusMode);

	// Set Custom Events
	GUI::SubscribeCustomUpdate(Update);
	GUI::SubscribeCustomDraw(Draw);
	GUI::SubscribeEnterKeyFunc(OnEnterPressed);
	GUI::SubscribeEscapeKeyFunc(OnEscapePressed);

	// Create the Settings
	settings = ClientSettings::GetInstance();

	// Load the Content
	LoadContent();

	// Set the Focus
	//GUI::SetFocus(mainMenu);

	//--Temporary asset loading
	SDL_Texture *_minionTexture = GUIHelper::LoadPNGTexture("Resources/Sprites/MinionSS.png");
	SDL_Texture *_towerTexture = GUIHelper::LoadPNGTexture("Resources/Tiles/sandAndRoads.png");
	SDL_Texture *_projectileTexture = GUIHelper::LoadPNGTexture("Resources/Tiles/sandAndRoads.png");
	GUI::AddTexture("MinionTex", _minionTexture);
	GUI::AddTexture("TowerTex", _towerTexture);
	GUI::AddTexture("ProjectileTex", _projectileTexture);
}
Client::~Client()
{
	//-- Quit the API and clean up our memory once the APIs Main loop is over
	GUI::Quit();
}

void Client::Run() {
	settings->GameState = GS_MainMenu;

	//-- Set the Focus
	GUI::SetFocus(mainMenu);

	//-- Start the APIs main loop
	GUI::BeginMainLoop();
}

void Client::LoadContent()
{
	//--Call individual load methods
	ScreenFader::GetInstance()->Load();

	//load shared assets
	//fonts
	GUI::AddFont("OGWEAR_30", GUIHelper::LoadFont("Resources/Fonts/OGWEAR.ttf", 30));
	GUI::AddFont("OGWEAR", GUIHelper::LoadFont("Resources/Fonts/OGWEAR.ttf", 36));
	GUI::AddFont("Systema_11", GUIHelper::LoadFont("Resources/Fonts/9SYSTEMA.ttf", 11));
	GUI::AddFont("Systema_22", GUIHelper::LoadFont("Resources/Fonts/9SYSTEMA.ttf", 22));
	GUI::AddFont("Systema", GUIHelper::LoadFont("Resources/Fonts/9SYSTEMA.ttf", 22));	

	//audios
	GUI::AddAudio("OptionsAudio", GUIHelper::LoadAudioFile("Resources/Audios/Menu/Bg.ogg"));
	GUI::AddAudio("BtnAudio", GUIHelper::LoadAudioFile("Resources/Audios/Menu/btnClick.ogg"));
	GUI::AddAudio("OptionsAudio", GUIHelper::LoadAudioFile("Resources/Audios/Menu/Bg.ogg"));

	//colors
	GUI::AddColour("White", GUIHelper::ColourHelper(255, 255, 255, 255));
	GUI::AddColour("LightBlue", GUIHelper::ColourHelper(0, 162, 232, 255));
	GUI::AddColour("Red", GUIHelper::ColourHelper(255, 0, 0, 255 ));
	GUI::AddColour("Black", GUIHelper::ColourHelper(0, 0, 0, 255 ));

	//textures
	SDL_Texture *backgroundTex = GUIHelper::LoadPNGTexture("Resources/Images/background.png");
	SDL_Texture *backgroundPlainTex = GUIHelper::LoadPNGTexture("Resources/Images/backgroundPlain.png");
	SDL_Texture *logoTex = GUIHelper::LoadPNGTexture("Resources/Images/ManaCraft.png");
	SDL_Texture *smallBtnNormalTex = GUIHelper::LoadBMPImage("Resources/GUITextures/smallBtnNormal.bmp");
	SDL_Texture *medBtnNormalTex = GUIHelper::LoadBMPImage("Resources/GUITextures/medBtnNormal.bmp");
	SDL_Texture *longBtnNormalTex = GUIHelper::LoadBMPImage("Resources/GUITextures/longBtnNormal.bmp");

	GUI::AddTexture("Background", backgroundTex);
	GUI::AddTexture("BackgroundPlain", backgroundPlainTex);
	GUI::AddTexture("GameLogo", logoTex);
	GUI::AddTexture("SmallBtnNormal", smallBtnNormalTex);
	GUI::AddTexture("MedBtnNormal", medBtnNormalTex);
	GUI::AddTexture("LongBtnNormal", longBtnNormalTex);

	mainMenu = MainMenu::GetInstance();		//MainMenu_O::Load();
	//options = Options::GetInstance();		//Options::Load();
	//credits = Credits::GetInstance();		//Credits::Load();
	//gameLobby = GameLobby::GetInstance();	//GameLobby::Load();
	//viewGames = ViewGames::GetInstance();	//ViewGames::Load();
	//gamePage = GamePage::GetInstance();		//IngamePause::Load(); 

}

void Client::Update(double time)
{
	//cout << "Entering Custom Update" << endl;
	ScreenFader::GetInstance()->Update(time);

	switch (GetInstance()->Settings()->GameState)
	{
	case GS_None:
		break;
	case GS_MainMenu:
		break;
	case GS_Options:
		break;
	case GS_Credits:
		break;
	case GS_InGame:
		break;
	case GS_Paused:
		break;
	}
}

void Client::Draw()
{
	//cout << "Entering Custom Draw" << endl;
	ScreenFader::GetInstance()->Draw();

	switch (GetInstance()->Settings()->GameState)
	{
	case GS_None:
		break;
	case GS_MainMenu:
		break;
	case GS_Options:
		break;
	case GS_Credits:
		break;
	case GS_InGame:
		break;
	case GS_Paused:
		break;
	}
}

void Client::OnEscapePressed()
{
	//IngamePause::Pause();
}

void Client::OnEnterPressed()
{
	Client::GetInstance()->Settings()->isHost = true;
}