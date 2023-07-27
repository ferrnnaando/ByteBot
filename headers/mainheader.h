#pragma warning(disable : 4996)

#ifdef __linux__
	#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
	#include <Windows.h>

#endif

#ifdef __GNUC__ || _MSC_VER
    #pragma once
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <dotenv.h>
    #include "dpp/dpp.h"
    #include "../variables/variables.cpp"
#elif
    #ifdef MAINHEADER_H
    #define MAINHEADER_H

    #include <iostream>
    #include <fstream>
    #include <string>
    #include <dotenv.h>
    #include "dpp/dpp.h"
    #include "../variables/variables.cpp"

    #endif MAINHEADER_H
#endif