#ifndef LIB_EXPORT_H
#define LIB_EXPORT_H

#ifdef _WIN32
	#ifdef LIB_EXPORT_DLL
		#define LIB_DECLSPEC __declspec(dllexport)
	#elif defined(LIB_STATIC)
		#define LIB_DECLSPEC
	#else
		#define LIB_DECLSPEC __declspec(dllimport)
	#endif
#else
	#define LIB_DECLSPEC
#endif

#endif