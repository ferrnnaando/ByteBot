#pragma warning(disable : 4996)

#if defined(__GNUC__) || defined(_MSC_VER) //is better using if than ifdef when checking more than 1 predefined macro
    #pragma once
   
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