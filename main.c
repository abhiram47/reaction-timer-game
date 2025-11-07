#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#ifdef _WIN32
    #include<Windows.h>  
#else
    #include<sys/time.h>
#endif

// Function to get time in milliseconds - works on both Windows and Unix systems
double getTimeInMS() {
#ifdef _WIN32
    // Windows high-resolution timer
    LARGE_INTEGER frequency, time;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    return (double)time.QuadPart * 1000.0 / (double)frequency.QuadPart;
#else
    // Unix/Linux timer
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
#endif
}

int main() {
    srand(time(NULL));   
    int delay = rand()%7001 + 3000; // Random delay between 3000ms to 13000ms

    printf("Get ready...\n");
    Sleep(delay);
    printf("[FIRE!]\n");

    // Using Windows high-resolution timer
    double startTime = getTimeInMS();
    getch();
    double endTime = getTimeInMS();
    
    double reaction_time = endTime - startTime; // Already in milliseconds
    printf("Your reaction time is: %.2f ms\n", reaction_time);
    

    return 0;
}