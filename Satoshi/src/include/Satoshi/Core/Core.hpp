#ifndef CORE_HPP
#define CORE_HPP

#ifdef ST_PLATFORM_WINDOWS
	#ifdef ST_BUILD_DLL
		#define SATOSHI_API __declspec(dllexport)
	#else
		#define SATOSHI_API __declspec(dllimport)
	#endif
#else
	#error Satoshi only supports windows!
#endif

#define BIT(x) (1 << x)

#endif // CORE_HPP
