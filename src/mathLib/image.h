#ifndef IMAGE_H
#define IMAGE_H

// disable pedantic warnings for this lib
#ifdef _MSC_VER
	// Microsoft Visual C++ Compiler
	#pragma warning (push, 0)
#endif 

#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb_image.h"

// restore warning levels
#ifdef _MSC_VER
	// Microsoft Visual C++ Compiler
	#pragma warning (pop)
#endif

#endif // IMAGE_H