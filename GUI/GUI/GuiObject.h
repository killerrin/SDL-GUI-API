#pragma once
namespace GuiAPI {
	class GuiObject
	{
	public:
		GuiObject();
		virtual ~GuiObject();

		bool Active = true;
		bool Enabled = true;

		virtual void Update(double time);
		virtual void Draw();
	};
}
