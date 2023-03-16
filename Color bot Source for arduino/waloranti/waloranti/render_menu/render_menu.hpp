#ifndef RENDER_MENU_HPP
#define RENDER_MENU_HPP

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\D3DX11.h>
#include <WinUser.h>

#include <d3d11.h>
#include "../utilities/skcrypt.hpp"
#pragma comment(lib, "d3d11.lib")

namespace render_menu
{
	constexpr int width{ 300 };
	constexpr int height{ 210 };
	inline bool is_running{ true };

	inline ImFont* icon_font{ nullptr };
	inline HWND window{ nullptr };
	inline WNDCLASSEX window_class = { };

	static ID3D11Device* device{ NULL };
	static ID3D11DeviceContext* device_context{ NULL };
	static IDXGISwapChain* swap_chain{ NULL };
	static ID3D11RenderTargetView* render_target_view{ NULL };
	static ID3D11ShaderResourceView* background{ NULL };

	inline void create_window(LPCWSTR window_name)
	{
		window_class.cbSize = sizeof(WNDCLASSEX);
		window_class.style = CS_CLASSDC;
		window_class.lpfnWndProc = window_process;
		window_class.cbClsExtra = 0L;
		window_class.cbWndExtra = 0L;
		window_class.hInstance = GetModuleHandleA(NULL);
		window_class.hIcon = LoadIcon(window_class.hInstance, MAKEINTRESOURCE(IDI_ICON1));
		window_class.hCursor = NULL;
		window_class.hbrBackground = NULL;
		window_class.lpszMenuName = NULL;
		window_class.lpszClassName = skcrypt(L"class001");
		window_class.hIconSm = NULL;

		RegisterClassEx(&window_class);

		window = CreateWindow(window_class.lpszClassName, window_name,
			WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU /*| WS_MAXIMIZEBOX*/, 100, 100, width, height, NULL, NULL,
			window_class.hInstance, NULL);

		if (!create_device())
		{
			destroy_device();
			::UnregisterClass(window_class.lpszClassName, window_class.hInstance);
			return;
		}

		::ShowWindow(window, SW_SHOWDEFAULT);
		::UpdateWindow(window);
	}
	void destroy_window();

	bool create_device();
	void destroy_device();

	void create_render_target();
	void destory_render_target();

	void create_imgui();
	void destroy_imgui();

	void begin_render();
	void end_render();
	void render();
}

#endif // !RENDER_MENU_HPP