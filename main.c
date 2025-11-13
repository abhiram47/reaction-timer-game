#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<stdbool.h>

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
    double best_time;   // in milliseconds
    double worst_time;  // in milliseconds
    double average_time;    // in milliseconds
    double total_time;  // in milliseconds
    int games_played;   
}PlayerStats;

typedef struct {
    int delay_min;
    int delay_max;
    PlayerStats stats;
    GameState current_state;
} GameSettings;

  // Initialize Game - Sets all defaults
GameSettings initialize_game() {
    GameSettings g;
    g.delay_min = 3000;
    g.delay_max = 7000;
    
    // Initialize stats to safe defaults
    g.stats.best_time = 99999.0; // High value so first game beats it
    g.stats.worst_time = 0.0;
    g.stats.average_time = 0.0;
    g.stats.total_time = 0.0;
    g.stats.games_played = 0;
    
    g.current_state = STATE_MENU;
    return g;
}

// Function to save game settings
void save_settings(PlayerStats *stats){
    FILE *file;
    file = fopen("player_data.dat", "wb");

    if(file == NULL){
        printf("Error opening the file for writing \n");
        return; 
    }
    if(fwrite(stats, sizeof(PlayerStats), 1, file) != 1) {
        printf("Error writing to file\n");
    }else {
        printf("Settings saved successfully \n");
    }
    fclose(file);
}

// Function to load game settings
bool load_settings(PlayerStats *stats){
    FILE *file;
    file = fopen("player_data.dat", "rb");

    if(file == NULL){
        printf("No saved file found. Starting with defaults.\n");
        return false; // Signal to caller: read failed
    }
    if(fread(stats, sizeof(PlayerStats), 1, file) != 1) {
        printf("Error reading from file\n");
        fclose(file);
        return false;  // Signal to caller: read failed
    }
    printf("Game loaded successfully \n");
    fclose(file);
    return true;
}

void handle_menu_settings(GameSettings *settings) {
    // Implement menu handling logic here
                printf("You are in the menu.\n");
                printf("Select an option to proceed...\n\n");
                printf("options...\n");
                printf("\n");
                printf("option 1 -> Start Game\n");
                printf("option 2 -> View Stats\n");
                printf("option 3 -> Quit\n");
                
                char choice = getch();
                if (choice == '1') {
                    settings->current_state = STATE_READY;
                } else if (choice == '2') {
                    settings->current_state = STATE_RESULT;
                } else if (choice == '3') {
                    settings->current_state = STATE_EXIT;
                } else {
                    printf("Invalid option! Please press 1, 2, or 3.\n");
                    printf("Press any key to try again...\n");
                    getch();
                    settings->current_state = STATE_MENU;
                }
}

void handle_ready_settings(GameSettings *settings) {
    // Implement ready state handling logic here
    printf("\n");
    printf("Get ready...\n");
    settings->current_state = STATE_WAITING;
}

void handle_waiting_settings(GameSettings *settings) {
    // Implement waiting state handling logic here
    int random_delay = rand() % (settings->delay_max - settings->delay_min + 1) + settings->delay_min;
    printf("Wait for the FIRE signal...\n");
    Sleep(random_delay);
                
                
    if(kbhit()) {    // Check if the player pressed a key too early
    getch();    // Clearing the alredady pressed key
    printf("\nNo cheating! You pressed too early!\n");
    printf("\n");
    printf("Press any key to return to menu...\n");
    getch();
    settings->current_state = STATE_MENU;
        } else {
            settings->current_state = STATE_FIRED;
        }
    printf("\n");
}

void handle_fired_settings(GameSettings *settings) {
    // Implement fired state handling logic here
    printf("[FIRE!]\n");
    printf("\n");
    printf("Press any key to stop the timer...\n");
    double startTime = getTimeInMS();
    getch();
    double endTime = getTimeInMS();
    double reactionTime = endTime - startTime;
    if (reactionTime < 0 || reactionTime > 10000) {
        printf("Error: Timer glitch or inactivity (%.2f ms). Result discarded.\n", reactionTime);
        printf("Press any key to return to menu...\n");
        getch();
        settings->current_state = STATE_MENU;
        return;
    }
    printf("Your reaction time is: %.2f ms\n", reactionTime);
    settings->stats.games_played++;
    settings->stats.total_time += (reactionTime);
    if (settings->stats.games_played > 0) {
        settings->stats.average_time = settings->stats.total_time / settings->stats.games_played;
    } else {
        settings->stats.average_time = 0.0;
    }
    if (reactionTime < settings->stats.best_time) {
        settings->stats.best_time = reactionTime;
    }
    if (reactionTime > settings->stats.worst_time) {
        settings->stats.worst_time = reactionTime;
    }
    settings->current_state = STATE_RESULT;
    printf("\n");

}

void handle_result_settings(GameSettings *settings) {
    // Implement result state handling logic here

    printf("Displaying stats...\n");
    printf("---------------\n");
    printf("\n");
    printf("Best Time: %.2f ms\n", settings->stats.best_time);
    printf("Worst Time: %.2f ms\n", settings->stats.worst_time);
    printf("Average Time: %.2f ms\n", settings->stats.average_time);
    printf("Total Games Played: %d\n", settings->stats.games_played);
    printf("\n");
    printf("Returning to menu...\n");
    printf("...\n");
    printf("press any key to continue...\n");
    getch();
    settings->current_state = STATE_MENU;   
    printf("\n"); 
}

int main() {
    srand(time(NULL));   
    GameSettings Settings = initialize_game();

    if (!load_settings(&Settings.stats)) {
    printf("Starting fresh with no previous stats.\n");
    }

    Settings.current_state = STATE_MENU;
    
    while (Settings.current_state != STATE_EXIT) {
        // Game continues until exit
        switch (Settings.current_state) {

            case STATE_MENU:
            handle_menu_settings(&Settings); break;

            case STATE_READY:
            handle_ready_settings(&Settings); break;

            case STATE_WAITING:
            handle_waiting_settings(&Settings); break;
                
            case STATE_FIRED:
            handle_fired_settings(&Settings); break;    

            case STATE_RESULT:
            handle_result_settings(&Settings); break;
            
            default:
                printf("Unknown state!\n");
                printf("Returning to menu...\n");
                printf("\n");
                Settings.current_state = STATE_MENU;
                break;
        }
    }
    printf("\n");
    save_settings(&Settings.stats);

    printf("\n");
    printf("Exiting the game. Goodbye!\n");
    printf("\n");

    return 0;
}