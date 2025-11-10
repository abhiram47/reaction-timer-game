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

typedef enum {
    STATE_MENU,
    STATE_READY,
    STATE_WAITING,
    STATE_FIRED,
    STATE_RESULT,
    STATE_EXIT
} GameState;

typedef struct {
    double best_time;
    double worst_time;
    double average_time;
    double total_time;
    int games_played;
}PlayerStats;

typedef struct {
    int delay_min;
    int delay_max;
    PlayerStats stats;
    GameState current_state;
} GameSettings;

int main() {
    srand(time(NULL));   
    GameSettings Settings;
    Settings.delay_min = 3000;
    Settings.delay_max = 7000;
    Settings.stats.best_time = 9999.0;
    Settings.stats.worst_time = 0.0;
    Settings.stats.average_time = 0.0;
    Settings.stats.total_time = 0.0;
    Settings.stats.games_played = 0;
    Settings.current_state = STATE_MENU;
    
    while (Settings.current_state != STATE_EXIT) {
        // Game continues until exit
        switch (Settings.current_state) {

            case STATE_MENU:
                printf("You are in the menu.\n");
                printf("Select an option to proceed...\n\n");
                printf("options...\n");
                printf("\n");
                printf("option 1 -> Start Game\n");
                printf("option 2 -> View Stats\n");
                printf("option 3 -> Quit\n");
                
                char choice = getch();
                if (choice == '1') {
                    Settings.current_state = STATE_READY;
                } else if (choice == '2') {
                    Settings.current_state = STATE_RESULT;
                } else if (choice == '3') {
                    Settings.current_state = STATE_EXIT;
                } else {
                    printf("Invalid option! Returning to menu...\n");
                    Settings.current_state = STATE_MENU;
                }
                break;

            case STATE_READY:
                printf("Get ready...\n");
                Settings.current_state = STATE_WAITING;
                break;

            case STATE_WAITING:
                int random_delay = rand() % (Settings.delay_max - Settings.delay_min + 1) + Settings.delay_min;
                printf("Waiting for random delay of %d ms...\n", random_delay);
                Sleep(random_delay);
                Settings.current_state = STATE_FIRED;
                printf("\n");
                break;

            case STATE_FIRED:
                printf("[FIRE!]\n");
                printf("Press any key to stop the timer...\n");
                double startTime = getTimeInMS();
                getch();
                double endTime = getTimeInMS();
                double reactionTime = endTime - startTime;
                printf("Your reaction time is: %.2f ms\n", reactionTime);
                Settings.stats.games_played++;
                Settings.stats.total_time += (reactionTime);
                Settings.stats.average_time = Settings.stats.total_time / Settings.stats.games_played;
                if (reactionTime < Settings.stats.best_time) {
                    Settings.stats.best_time = reactionTime;
                }
                if (reactionTime > Settings.stats.worst_time) {
                    Settings.stats.worst_time = reactionTime;
                }
                Settings.current_state = STATE_RESULT;
                printf("\n");

                break;
            case STATE_RESULT:
                printf("Displaying stats...\n");
                printf("Best Time: %.2f ms\n", Settings.stats.best_time);
                printf("Worst Time: %.2f ms\n", Settings.stats.worst_time);
                printf("Average Time: %.2f ms\n", Settings.stats.average_time);
                printf("Total Games Played: %d\n", Settings.stats.games_played);
                printf("Returning to menu...\n");
                printf("...\n");
                printf("press any key to continue...\n");
                getch();
                Settings.current_state = STATE_MENU;   
                printf("\n");
                break;  
            
            default:
                printf("Unknown state!\n");
                printf("Returning to menu...\n");
                Settings.current_state = STATE_MENU;
                break;
        }
    }

    printf("Exiting the game. Goodbye!\n");
    printf("\n");

    return 0;
}