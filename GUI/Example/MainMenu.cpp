#include "MainMenu.h"

#include "ClientSettings.h"
#include "Client.h"

#include "ScreenFader.h"

using namespace Example;

std::string MainMenu::username = "";
MainMenu* MainMenu::instance;

MainMenu::MainMenu()
	:Page()
{
	content->SubscribeOnEnterKeyPressed(OnEnterPressed);
	content->SubscribeOnEnterKeyPressed(OnEscapePressed);

	Load();
}

MainMenu* MainMenu::GetInstance()
{
	if (MainMenu::instance == nullptr) { MainMenu::instance = new MainMenu(); }

	return MainMenu::instance;
}

MainMenu::~MainMenu()
{
	Page::~Page();
}

void MainMenu::Load()
{
	content->AddGuiContainer("Menu", new Container());
	content->AddGuiContainer("LoginPopup", new Container());

	LoadMainMenu();
	LoadLoginPopup();
}

void MainMenu::LoadMainMenu(){
	const int SCREEN_WIDTH = Window::Box().w;
	const int SCREEN_HEIGHT = Window::Box().h;
	const int MARGIN_Y = 40;
	const int BUTTON_SPC_Y = 20, BUTTON_SPC_X = 10;

	//-- Convienient rects
	SDL_Rect smallBtnRect = GUIHelper::RectHelper(0, 0, 35, 35);
	SDL_Rect medBtnRect = GUIHelper::RectHelper(0, 0, 95, 35);
	SDL_Rect longBtnRect = GUIHelper::RectHelper(0, 0, 180, 35);
	SDL_Rect centerRect = GUIHelper::RectHelper(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0);

	//-- Additional button rects
	SDL_Rect creditsBtnRect = GUIHelper::RectHelper(SCREEN_WIDTH - medBtnRect.w - BUTTON_SPC_X, SCREEN_HEIGHT - medBtnRect.h - BUTTON_SPC_Y, medBtnRect.w, medBtnRect.h);

	//-- Background
	content->GetGuiContainer("Menu")->AddGuiElement("Background", new Element(GUI::GetTexture("Background"), GUIHelper::RectHelper(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));
	content->GetGuiContainer("LoginPopup")->AddGuiElement("Background", new Element(GUI::GetTexture("Background"), GUIHelper::RectHelper(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)));

	//-- Logo
	content->GetGuiContainer("Menu")->AddGuiElement("Logo", new Element(GUI::GetTexture("GameLogo"), GUIHelper::RectHelper(centerRect.x - 350, MARGIN_Y, 700, 300)));
	content->GetGuiContainer("LoginPopup")->AddGuiElement("Logo", new Element(GUI::GetTexture("GameLogo"), GUIHelper::RectHelper(centerRect.x - 350, MARGIN_Y, 700, 300)));

	//-- Buttons
	content->GetGuiContainer("Menu")->AddGuiContainer("BtnHolder", new Container());
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->SetPosition(GUIHelper::RectHelper(centerRect.x - longBtnRect.w / 2, centerRect.y, longBtnRect.w, 600));

	int xBtn, btnIndex = 0;

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->AddGuiElement("LoginBtn", new Button(GUI::GetTexture("LongBtnNormal"), longBtnRect));
	xBtn = content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("LoginBtn")->GetX();
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("LoginBtn")->SetPosition(xBtn, (btnIndex * (longBtnRect.h + BUTTON_SPC_Y)));
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("LoginBtn")->AddLabel("Login/Logout", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("LoginBtn")->GetLabel()->SetPadding(GUIHelper::RectHelper(7, 2, 0, 0));
	btnIndex++;

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->AddGuiElement("ViewGamesBtn", new Button(GUI::GetTexture("LongBtnNormal"), longBtnRect));
	xBtn = content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("ViewGamesBtn")->GetX();
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("ViewGamesBtn")->SetPosition(xBtn, (btnIndex * (longBtnRect.h + BUTTON_SPC_Y)));
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("ViewGamesBtn")->AddLabel("View Games", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("ViewGamesBtn")->GetLabel()->SetPadding(GUIHelper::RectHelper(7, 2, 0, 0));
	btnIndex++;

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->AddGuiElement("OptionsBtn", new Button(GUI::GetTexture("LongBtnNormal"), longBtnRect));
	xBtn = content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("OptionsBtn")->GetX();
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("OptionsBtn")->SetPosition(xBtn, (btnIndex * (longBtnRect.h + BUTTON_SPC_Y)));
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("OptionsBtn")->AddLabel("Options", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("OptionsBtn")->GetLabel()->SetPadding(GUIHelper::RectHelper(7, 2, 0, 0));
	btnIndex++;

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->AddGuiElement("TutorialBtn", new Button(GUI::GetTexture("LongBtnNormal"), longBtnRect));
	xBtn = content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("TutorialBtn")->GetX();
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("TutorialBtn")->SetPosition(xBtn, (btnIndex * (longBtnRect.h + BUTTON_SPC_Y)));
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("TutorialBtn")->AddLabel("Tutorial", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("TutorialBtn")->GetLabel()->SetPadding(GUIHelper::RectHelper(7, 2, 0, 0));
	btnIndex++;

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->AddGuiElement("QuitBtn", new Button(GUI::GetTexture("LongBtnNormal"), longBtnRect));
	xBtn = content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("QuitBtn")->GetX();
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("QuitBtn")->SetPosition(xBtn, (btnIndex * (longBtnRect.h + BUTTON_SPC_Y)));
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("QuitBtn")->AddLabel("Quit", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("QuitBtn")->GetLabel()->SetPadding(GUIHelper::RectHelper(7, 2, 0, 0));
	btnIndex++;

	content->GetGuiContainer("Menu")->AddGuiElement("CreditsBtn", new Button(GUI::GetTexture("MedBtnNormal"), creditsBtnRect));
	content->GetGuiContainer("Menu")->GetButton("CreditsBtn")->AddLabel("Credits", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("Menu")->GetButton("CreditsBtn")->GetLabel()->SetPadding(GUIHelper::RectHelper(2, 2, 0, 0));

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("LoginBtn")->SubscribeOnMouseClick(MainMenu::Click_loginButton);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("ViewGamesBtn")->SubscribeOnMouseClick(MainMenu::Click_viewButton);

	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("OptionsBtn")->SubscribeOnMouseClick(MainMenu::Click_optionsButton);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("TutorialBtn")->SubscribeOnMouseClick(MainMenu::Click_tutorialButton);
	content->GetGuiContainer("Menu")->GetGuiContainer("BtnHolder")->GetButton("QuitBtn")->SubscribeOnMouseClick(MainMenu::Click_quitButton);
	content->GetGuiContainer("Menu")->GetButton("CreditsBtn")->SubscribeOnMouseClick(MainMenu::Click_creditsButton);

	content->GetGuiContainer("Menu")->SetSfx1Audio(GUI::GetAudio("BtnAudio"));

	//Test Grid Square
	/*	GridSquare mySquare = GridSquare();
	mySquare.id = 0;
	mySquare.xPos = 0;
	mySquare.yPos = 0;
	content->GetGuiContainer("Menu")->AddGuiElement("mySquare", new GuiGridSquare(GUI::GetTexture("MedBtnNormal"), mySquare, 32, 32));*/


	//----------------- GRID LAYER ------------------//
	////Array of GridSquares to pass through to the GuiGridLayer
	//GridSquare mySquares[100];
	//for (int i = 0; i < 100; i++){
	//	mySquares[i].id = 15;
	//}

	////Texture of the resource, just for testing purposes.
	//SDL_Texture *tiletexture = GUIHelper::LoadPNGTexture("Resources/Tiles/grassAndRock.png");

	////GridLayer
	//GridLayer myLayer = GridLayer();
	//myLayer.rows = 10;
	//myLayer.columns = 10;
	//myLayer.tileSize = 32;

	////Add element to the Menu container.
	//content->GetGuiContainer("Menu")->AddGuiElement("myLayer", new GuiGridLayer(tiletexture, myLayer, mySquares));
	//-------------- GRID LAYER END ---------------//


	//FOR TESTING ANIMATED SPRITE
	//SDL_Texture *texture = nullptr;
	//texture = IMG_LoadTexture(Window::Renderer(), "Resources/Sprites/MinionSS.png");
	//if (texture == nullptr)//in case creating renderer fails
	//{
	//	std::cout << SDL_GetError() << std::endl;

	//}
	//AnimatedSprite *sp = new AnimatedSprite(texture, 100, 100,4,4);
	//
	//int i = 0;
	//sp->Down();
	//while (i < 5000)
	//{
	//	sp->Update();
	//}
}

void MainMenu::LoadLoginPopup()
{
	const int SCREEN_WIDTH = Window::Box().w;
	const int SCREEN_HEIGHT = Window::Box().h;

	SDL_Rect loginBtn = GUIHelper::RectHelper(33, 0, 95, 35);
	SDL_Rect cancelBtn = GUIHelper::RectHelper(190, 0, 95, 35);

	//-- Add the Login Bar
	content->GetGuiContainer("LoginPopup")->AddGuiElement("Background", new Element(GUIHelper::SolidColourTexture(300, 150, GUIHelper::ColourHelper(0, 0, 0, 225)), GUIHelper::RectHelper(10, -100, 300, 150)));
	content->GetGuiContainer("LoginPopup")->AddGuiElement("Username", new Label("Username", GUIHelper::RectHelper(102, -80, 200, 100), GUI::GetFont("Systema"), GUI::GetColor("White")));

	//-- Add Container for Elements
	content->GetGuiContainer("LoginPopup")->AddGuiContainer("ElementContainer", new Container());

	//-- Setup the text field
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->AddGuiElement("UsernameField", new TextField(GUIHelper::RectHelper(35, -50, 250, 20), GUI::GetFont("Systema"), GUI::GetColor("White")));
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetTextField("UsernameField")->CharacterLimit = 20;

	//-- Add in Login and Cancel Buttons
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->AddGuiElement("Login", new Button(GUI::GetTexture("MedBtnNormal"), loginBtn));
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetButton("Login")->AddLabel("Login", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetButton("Login")->GetLabel()->SetPadding(GUIHelper::RectHelper(12, 2, 0, 0));

	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->AddGuiElement("Cancel", new Button(GUI::GetTexture("MedBtnNormal"), cancelBtn));
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetButton("Cancel")->AddLabel("Cancel", GUI::GetFont("Systema"), GUI::GetColor("Black"), true);
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetButton("Cancel")->GetLabel()->SetPadding(GUIHelper::RectHelper(7, 2, 0, 0));

	//-- Subscribe to Events
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetButton("Login")->SubscribeOnMouseClick(MainMenu::Click_LoginPopup_Login);
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetButton("Cancel")->SubscribeOnMouseClick(MainMenu::Click_LoginPopup_Cancel);
	//content->GetGuiContainer("LoginPopup")->SubscribeOnEscapeKeyPressed(LoginPopup::ButtonPress_Escape);
	//content->GetGuiContainer("LoginPopup")->SubscribeOnEnterKeyPressed(LoginPopup::ButtonPress_Enter);

	//-- Set Menu Position
	content->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->SetPosition(GUIHelper::RectHelper((int)(SCREEN_WIDTH / 2.9), (int)(SCREEN_HEIGHT / 1.5), 0, 0));

	// Turn off
	content->GetGuiContainer("LoginPopup")->Active = false;
}


void MainMenu::Update(double time)
{
	Page::Update(time);
}

void MainMenu::Draw()
{
	Page::Draw();
}


//===================
//----------- Events
//===================

void MainMenu::OnEnterPressed()
{

}

void MainMenu::OnEscapePressed()
{

}

void MainMenu::Click_loginButton()
{
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Active = false;
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("LoginPopup")->Active = true;

	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();
}

void MainMenu::Click_viewButton()
{
	std::cout << "View saved games.\n";
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();

	ScreenFader::GetInstance()->FadeOut();
}

void MainMenu::Click_optionsButton()
{
	std::cout << "Open options menu.\n";
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();

	ScreenFader::GetInstance()->FadeOut();
}

void MainMenu::Click_tutorialButton()
{
	std::cout << "Disabled until things are hooked up" << std::endl;
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();

	ScreenFader::GetInstance()->FadeOut();
}

void MainMenu::Click_quitButton()
{
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();
	GUI::ExitMainLoop();
}

void MainMenu::Click_creditsButton()
{
	std::cout << "Show credits.\n";
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();

	ScreenFader::GetInstance()->FadeOut();
}

void MainMenu::Click_LoginPopup_Cancel()
{
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Active = true; // Enabled
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("LoginPopup")->Active = false;
}

void MainMenu::Click_LoginPopup_Login()
{
	MainMenu::GetInstance()->username = MainMenu::GetInstance()->GetContent()->GetGuiContainer("LoginPopup")->GetGuiContainer("ElementContainer")->GetTextField("UsernameField")->GetText();

	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Sfx1Play();
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("Menu")->Active = true; // Enabled
	MainMenu::GetInstance()->GetContent()->GetGuiContainer("LoginPopup")->Active = false;
}
