#pragma warning(disable : 4996)


#ifdef __GNUC__ || _MSC_VER
    #pragma once
   
#elif
    #ifdef MAINHEADER_H
    #define MAINHEADER_H

    #endif MAINHEADER_H
#endif

#ifdef __linux__
	#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>
#endif

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <dotenv.h>
    #include "dpp/dpp.h"
    #include "../variables/variables.cpp"