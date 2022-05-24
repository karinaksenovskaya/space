#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef LINUX
#include <errno.h>
#include <pthread.h>
#endif //LINUX

#ifdef WINDOWS
#include <windows.h>
#include <process.h> 
#endif //WINDOWS