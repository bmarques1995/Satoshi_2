#ifdef ST_PLATFORM_WINDOWS

#include "Platform/Windows/Win32InputMapper.hpp"

#include <windows.h>

std::unordered_map<uint16_t, uint16_t> Satoshi::Win32InputMapper::s_Codes =
{
	{ ST_MOUSEBUTTON_LEFT, VK_LBUTTON },
	{ ST_MOUSEBUTTON_MIDDLE, VK_MBUTTON },
	{ ST_MOUSEBUTTON_RIGHT, VK_RBUTTON },
	{ ST_MOUSEBUTTON_VUP, VK_XBUTTON2 },
	{ ST_MOUSEBUTTON_VDOWN, VK_XBUTTON1 },

	{ ST_KEY_ESCAPE, VK_ESCAPE },
	{ ST_KEY_SPACE, VK_SPACE },
	{ ST_KEY_ENTER, VK_RETURN },
	{ ST_KEY_CAPSLOCK, VK_CAPITAL },
	{ ST_KEY_BACKSPACE, VK_BACK },
	{ ST_KEY_TAB, VK_TAB },

	{ ST_KEY_A, 0x41 },
	{ ST_KEY_B, 0x42 },
	{ ST_KEY_C, 0x43 },
	{ ST_KEY_D, 0x44 },
	{ ST_KEY_E, 0x45 },
	{ ST_KEY_F, 0x46 },
	{ ST_KEY_G, 0x47 },
	{ ST_KEY_H, 0x48 },
	{ ST_KEY_I, 0x49 },
	{ ST_KEY_J, 0x4A },
	{ ST_KEY_K, 0x4B },
	{ ST_KEY_L, 0x4C },
	{ ST_KEY_M, 0x4D },
	{ ST_KEY_N, 0x4E },
	{ ST_KEY_O, 0x4F },
	{ ST_KEY_P, 0x50 },
	{ ST_KEY_Q, 0x51 },
	{ ST_KEY_R, 0x52 },
	{ ST_KEY_S, 0x53 },
	{ ST_KEY_T, 0x54 },
	{ ST_KEY_U, 0x55 },
	{ ST_KEY_V, 0x56 },
	{ ST_KEY_W, 0x57 },
	{ ST_KEY_X, 0x58 },
	{ ST_KEY_Y, 0x59 },
	{ ST_KEY_Z, 0x5A },

	{ ST_KEY_PLUS, VK_OEM_PLUS },
	{ ST_KEY_COMMA, VK_OEM_COMMA },
	{ ST_KEY_MINUS, VK_OEM_MINUS },
	{ ST_KEY_PERIOD, VK_OEM_PERIOD },

	{ ST_KEY_US_SEMICOLON, VK_OEM_1 },
	{ ST_KEY_US_QUESTION, VK_OEM_2 },
	{ ST_KEY_US_TILDE, VK_OEM_3 },
	{ ST_KEY_US_LBRACKET, VK_OEM_4 },
	{ ST_KEY_US_BACKSLASH, VK_OEM_5 },
	{ ST_KEY_US_RBRACKET, VK_OEM_6 },
	{ ST_KEY_US_QUOTE, VK_OEM_7 },
	{ ST_KEY_US_SLASH, VK_OEM_8 },
	{ ST_KEY_US_ALTBACKSLASH, VK_OEM_102 },

	{ ST_KEY_0, 0x30 },
	{ ST_KEY_1, 0x31 },
	{ ST_KEY_2, 0x32 },
	{ ST_KEY_3, 0x33 },
	{ ST_KEY_4, 0x34 },
	{ ST_KEY_5, 0x35 },
	{ ST_KEY_6, 0x36 },
	{ ST_KEY_7, 0x37 },
	{ ST_KEY_8, 0x38 },
	{ ST_KEY_9, 0x39 },

	{ ST_KEY_NUMPAD_0, VK_NUMPAD0 },
	{ ST_KEY_NUMPAD_1, VK_NUMPAD1 },
	{ ST_KEY_NUMPAD_2, VK_NUMPAD2 },
	{ ST_KEY_NUMPAD_3, VK_NUMPAD3 },
	{ ST_KEY_NUMPAD_4, VK_NUMPAD4 },
	{ ST_KEY_NUMPAD_5, VK_NUMPAD5 },
	{ ST_KEY_NUMPAD_6, VK_NUMPAD6 },
	{ ST_KEY_NUMPAD_7, VK_NUMPAD7 },
	{ ST_KEY_NUMPAD_8, VK_NUMPAD8 },
	{ ST_KEY_NUMPAD_9, VK_NUMPAD9 },

	{ ST_KEY_DIVIDE, VK_DIVIDE },
	{ ST_KEY_MULTIPLY, VK_MULTIPLY },
	{ ST_KEY_SUBTRACT, VK_SUBTRACT },
	{ ST_KEY_ADD, VK_ADD },
	{ ST_KEY_DECIMAL, VK_DECIMAL },
	{ ST_KEY_CLEAR, VK_OEM_CLEAR },

	{ ST_KEY_ARROW_RIGHT, VK_RIGHT },
	{ ST_KEY_ARROW_UP, VK_UP },
	{ ST_KEY_ARROW_LEFT, VK_LEFT },
	{ ST_KEY_ARROW_DOWN, VK_DOWN },

	{ ST_KEY_INSERT, VK_INSERT },
	{ ST_KEY_DELETE, VK_DELETE },
	{ ST_KEY_HOME, VK_HOME },
	{ ST_KEY_END, VK_END },
	{ ST_KEY_PAGE_UP, VK_PRIOR },
	{ ST_KEY_PAGE_DOWN, VK_NEXT },

	{ ST_KEY_F1, VK_F1 },
	{ ST_KEY_F2, VK_F2 },
	{ ST_KEY_F3, VK_F3 },
	{ ST_KEY_F4, VK_F4 },
	{ ST_KEY_F5, VK_F5 },
	{ ST_KEY_F6, VK_F6 },
	{ ST_KEY_F7, VK_F7 },
	{ ST_KEY_F8, VK_F8 },
	{ ST_KEY_F9, VK_F9 },
	{ ST_KEY_F10, VK_F10 },
	{ ST_KEY_F11, VK_F11 },
	{ ST_KEY_F12, VK_F12 },
	{ ST_KEY_F13, VK_F13 },
	{ ST_KEY_F14, VK_F14 },
	{ ST_KEY_F15, VK_F15 },
	{ ST_KEY_F16, VK_F16 },
	{ ST_KEY_F17, VK_F17 },
	{ ST_KEY_F18, VK_F18 },
	{ ST_KEY_F19, VK_F19 },
	{ ST_KEY_F20, VK_F20 },
	{ ST_KEY_F21, VK_F21 },
	{ ST_KEY_F22, VK_F22 },
	{ ST_KEY_F23, VK_F23 },
	{ ST_KEY_F24, VK_F24 },

	{ ST_KEY_LSHIFT, VK_LSHIFT },
	{ ST_KEY_LCTRL, VK_LCONTROL },
	{ ST_KEY_LALT, VK_LMENU },
	{ ST_KEY_RSHIFT, VK_RSHIFT },
	{ ST_KEY_RCTRL, VK_RCONTROL },
	{ ST_KEY_RALT, VK_RMENU }

};

#endif // ST_PLATFORM_WINDOWS
