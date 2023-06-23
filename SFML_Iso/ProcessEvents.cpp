#include "ProcessEvents.hpp"

void EventsCore::Init(sf::RenderWindow* pWindow)
{
	m_pParentWindow = pWindow;
}

void EventsCore::ResetMemberStructs()
{
	std::memset(&m_sWindowEvent, 0, sizeof(m_sWindowEvent));
	std::memset(&m_sMouseEvent, 0, sizeof(m_sMouseEvent));
	std::memset(&m_sKeyboardEvent, 0, sizeof(m_sKeyboardEvent));
}

void EventsCore::EnableKeyboardReading()
{
	m_isKeyboardListening = true;
}

void EventsCore::DisableKeyboardReading()
{
	m_isKeyboardListening = false;
	m_keyboardInput.clear();
}

void EventsCore::ProcessEvents()
{
	ResetMemberStructs();

	while (m_pParentWindow->pollEvent(m_eventLog))
	{
		switch (m_eventLog.type)
		{

			// Window Events

			case sf::Event::Closed:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::Closed");
				m_sWindowEvent.Closed = true;
				break;
			case sf::Event::LostFocus:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::LostFocus");
				m_sWindowEvent.LostFocus = true;
				break;
			case sf::Event::GainedFocus:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::GainedFocus");
				m_sWindowEvent.GainedFocus = true;
				break;
			case sf::Event::Resized:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::Resized\nNew Size : x=%d, y=%d", m_eventLog.size.width, m_eventLog.size.height);
				m_sWindowEvent.Resized = true;
				m_sWindowEvent.newSizeHeight = m_eventLog.size.height;
				m_sWindowEvent.newSizeWidth = m_eventLog.size.width;
				break;

			// Keyboard Events

			case sf::Event::TextEntered:
				m_sKeyboardEvent.TextEntered = true;
				m_sKeyboardEvent.LastCharacterEntered = static_cast<char>(m_eventLog.text.unicode);
				
				if (m_isKeyboardListening)
				{
					if (m_eventLog.text.unicode < 128) // If it is in ASCII's range.
					{
						Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::TextEntered : key=\'%c\'", static_cast<char>(m_eventLog.text.unicode));
						m_keyboardInput += static_cast<char>(m_eventLog.text.unicode);
					}
				}

				break;
			case sf::Event::KeyPressed:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::KeyPressed : keycode=\'%d\'", static_cast<int>(m_eventLog.key.code));
				m_sKeyboardEvent.KeyPressed = true;
				m_sKeyboardEvent.KeyCode = m_eventLog.key.code;
				break;
			case sf::Event::KeyReleased:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::KeyReleased : keycode=\'%d\'", static_cast<int>(m_eventLog.key.code));
				m_sKeyboardEvent.KeyReleased = true;
				m_sKeyboardEvent.KeyCode = m_eventLog.key.code;
				break;


			// Mouse Events

			case sf::Event::MouseWheelScrolled:
				Dbg::Log("[EventsCore.ProcessEvents]\t:\tsf::Event::MouseWheelScrolled\n\tWheelType = %d\n\tWheel_x = %d, Wheel_y = %d\n\tWheelDelta =%f",
					static_cast<int>(m_eventLog.mouseWheelScroll.wheel),
					m_eventLog.mouseWheelScroll.wheel,
					m_sMouseEvent.Wheel_x = m_eventLog.mouseWheelScroll.x,
					m_sMouseEvent.Wheel_y = m_eventLog.mouseWheelScroll.y,
					m_sMouseEvent.WheenMovement = m_eventLog.mouseWheelScroll.delta
					);

				m_sMouseEvent.WheelScrolled = true;
				m_sMouseEvent.WheelType = m_eventLog.mouseWheelScroll.wheel;
				m_sMouseEvent.Wheel_x = m_eventLog.mouseWheelScroll.x;
				m_sMouseEvent.Wheel_y = m_eventLog.mouseWheelScroll.y;
				m_sMouseEvent.WheenMovement = m_eventLog.mouseWheelScroll.delta;
				break;
		}
	}

	EventManager::KeyboardEvent = &m_sKeyboardEvent;
	EventManager::MouseEvent = &m_sMouseEvent;
	EventManager::WindowEvent = &m_sWindowEvent;

}

std::string EventsCore::GetUserKeyboardTextEntered() const
{
	return m_keyboardInput;
}

GWindowEvent* EventsCore::PGetWindowEvents() const
{
	return (GWindowEvent*)&m_sWindowEvent;
}