// Copyright(c) 2020 Purpasmart
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <time.h>
#include <windows.h>
#include <glfw3.h>

#include "common/timer.h"

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define EPOCH  116444736000000000Ui64
#else
  #define EPOCH  11644473600000000ULL
#endif

#ifdef _WIN32
int gettimeofday(struct timeval *tp, struct timezone *tzp)
{
    FILETIME file_time;
    SYSTEMTIME system_time;
    ULARGE_INTEGER ularge;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    ularge.LowPart = file_time.dwLowDateTime;
    ularge.HighPart = file_time.dwHighDateTime;

    tp->tv_sec = (long) ((ularge.QuadPart - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);

    return 0;
}
#endif

double GetDeltaTime(TimeInfo_t *self)
{
    double time = glfwGetTime();
    double delta = (time - self->previous_time);
    self->previous_time = time;
    return delta;
}

TimeInfo_t *TimeInfo_New()
{
    TimeInfo_t *time_info = malloc(sizeof(*time_info));
    time_info->accumulator = 0;
    time_info->alpha = 0;
    time_info->current_time = 0.0;
    time_info->previous_time = glfwGetTime();
    time_info->timer = time_info->previous_time;
    return time_info;
}


