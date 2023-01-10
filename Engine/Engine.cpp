#include "trpch.h"
#include "Engine.h"
bool Engine::Initialize(HINSTANCE hInst, std::string windowTitle, std::string windowClass, int width, int height)
{
	if (!this->renderWindow.Initialize(this, hInst, windowTitle, windowClass, width, height))
		return false;

	if (!gfx.Initialize(this->renderWindow.getHWND(), width, height))
		return false;

	return true;
}

bool Engine::ProcessMessages()
{
	return this->renderWindow.ProcessMessages();
}

void Engine::Update()
{
	while (!keyboard.charbufferisEmpty())
	{
		unsigned char ch = keyboard.readChar();
	}

	while (!keyboard.keybufferisEmpty())
	{
		keyboardEvent e = keyboard.readKey();
		unsigned char keycode = e.GetkeyCode();
	}

	while (!mouse.eventbufferisEmpty())
	{
		MouseEvent me = mouse.readEvent();
		if (mouse.isrightDown())
		{
			if (me.getType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}

	const float cameraSpeed = 0.02f;
	if (keyboard.keyisPressed(VK_SHIFT))
	{
		float boost = 5.0f;
		if (keyboard.keyisPressed('W'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed * boost);
		}
		if (keyboard.keyisPressed('S'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed * boost);
		}
		if (keyboard.keyisPressed('A'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed * boost);
		}
		if (keyboard.keyisPressed('D'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed * boost);
		}
		if (keyboard.keyisPressed('E'))
		{
			this->gfx.camera.AdjustPosition(0.0f, cameraSpeed * boost, 0.0f);
		}
		if (keyboard.keyisPressed('Q'))
		{
			this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed * boost, 0.0f);
		}
	}
	else
	{
		if (keyboard.keyisPressed('W'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
		}
		if (keyboard.keyisPressed('S'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);
		}
		if (keyboard.keyisPressed('A'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed);
		}
		if (keyboard.keyisPressed('D'))
		{
			this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed);
		}
		if (keyboard.keyisPressed('E'))
		{
			this->gfx.camera.AdjustPosition(0.0f, cameraSpeed, 0.0f);
		}
		if (keyboard.keyisPressed('Q'))
		{
			this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
		}
	}
}

void Engine::Render()
{
	gfx.Render();
}

void Engine::ReleaseData()
{
	
}
