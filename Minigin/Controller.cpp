#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib") //places a library record file
#include "Controller.h"

using namespace dae;

//DEFINE IMPL HERE
class Controller::ControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;
	unsigned int m_controllerIndex;

public:
	ControllerImpl(unsigned int controllerIndex)
	{
		m_controllerIndex = controllerIndex;
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(m_controllerIndex, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons; //XOR(^) current to previous
		//-> Checks current to last states, to save what buttons were 

		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);//check with ones complement of current
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return buttonsPressedThisFrame & button;
	}
	bool IsUpThisFrame(unsigned int button) const
	{
		return buttonsReleasedThisFrame & button;
	}
	bool IsPressed(unsigned int button) const
	{
		return currentState.Gamepad.wButtons & button;
	};
};

void dae::Controller::Update()
{
	m_pImpl->Update();
}

bool dae::Controller::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button)); //cast to use for & operator 
}

bool dae::Controller::IsUp(ControllerButton button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool dae::Controller::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

dae::Controller::Controller(unsigned int controllerIndex)
	:m_controllerIndex{ controllerIndex }
{
	m_pImpl = std::make_unique<ControllerImpl>(controllerIndex);
}

dae::Controller::~Controller()
{
}
