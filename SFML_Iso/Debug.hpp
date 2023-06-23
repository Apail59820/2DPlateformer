#pragma once

#include <cstdio>
#include <cstdarg>
#include <string>
#include <iostream>

//#define DEBUG

namespace Dbg
{
    inline char buffer[256];

    inline void ClearBuffer() noexcept
    {
        std::memset(buffer, 0, sizeof(buffer));
    }

    inline void Log(const char* format, ...) noexcept
    {
        #ifdef DEBUG
            va_list args;
            va_start(args, format);

            std::vsnprintf(buffer, sizeof(buffer), format, args);


            va_end(args);



            std::cout << std::string(buffer) << std::endl;



            std::memset(buffer, 0, sizeof(buffer));

            ClearBuffer();
        #endif
    }

}