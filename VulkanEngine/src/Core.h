#pragma once

#include<memory>

#define KB(x) ((uint64_t)1024 * x)
#define MB(x) ((uint64_t)1024 * KB(1))
#define GB(x) ((uint64_t)1024 * MB(1))

#define BIT(i) (1 << i)

#ifdef NDEBUG
const bool DEBUG_BUILD_CONFIGURATION = false;
#else
const bool DEBUG_BUILD_CONFIGURATION = true;
#endif

namespace vkEngine
{
	using QueueFamilyIndex = uint32_t;

	template <typename T>
	using Shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename Deleter = std::default_delete<T>>
	using Scoped = std::unique_ptr<T, Deleter>;
	template<typename T, typename ... Args>
	constexpr Scoped<T> CreateScoped(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Weak = std::weak_ptr<T>;

}
