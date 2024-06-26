#pragma once

#include <string>
#include <vector>
#include <utility>
#include "Swapchain.h"
#include "Devices/Instance.h"

namespace vkEngine
{
	class Application;
	class Window
	{
		friend Application;
	public:

		Window() = default;
		Window(uint32_t width, uint32_t height, const std::string& title);
		~Window();

		inline GLFWwindow* getWindowGLFW() { return m_glfwWindow; }

		inline bool shouldClose() const { return glfwWindowShouldClose(m_glfwWindow); };
		inline void setCursorPosition(float xPos, float yPos) { glfwSetCursorPos(m_glfwWindow, xPos, yPos); };
		inline void setWindowTitle(const char* title);
		VkSurfaceKHR getSurface() const { return m_Surface; }

		std::pair<float, float> getCursorPosition() const;
		std::pair<int, int> getWindowSize() const;


		bool isMinimized() const;
		void disableCursor(bool IsDisabled);
		void pollEvents() const { glfwPollEvents(); }
		void waitEvents() const { glfwWaitEvents(); }
	private:
		void createSurface(const Shared<Instance>& inst);
		void destroySurface(const Shared<Instance>& inst);
		void initWindow();
	private:
		GLFWwindow* m_glfwWindow{ nullptr };
		VkSurfaceKHR m_Surface = nullptr; //TODO: WRAPPER CLASS
		bool m_IsMinimized;
		std::pair<uint32_t, uint32_t> m_InitialExtent{};
		std::pair<double, double> m_CurrentExtent{};
		std::string m_Title{};

	};
}
