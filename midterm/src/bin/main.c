#include "myls.h"
#include <stdio.h>
#include <string.h>

//Printing the ls program takes multiple integers. These are correspondent to the flags in the ls program[5] 
void printLs(char* directory, int flag_a, int flag_all, int flag_l, int flag_v, int flag_version, int flag_h, int flag_help) {
    //No Arguments 
    if(!flag_a && !flag_all && !flag_l && !flag_v && !flag_version && !flag_h && !flag_help) {
        show_directory(directory);
    }
    
    if((flag_a || flag_all) && !flag_l) {
        show_directory_all(directory); 
    }

    if(flag_l) {
        show_directory_long(directory);
    }

    if((flag_a || flag_all) && flag_l) {
        show_directory_long_all(directory);
    }

    if(flag_v || flag_version) {
        printf("Kevin Dotel v.0.0.1");
    }

    if(flag_h || flag_help) {
        printf("\nWelcome to my ls program help center!");
        printf("\nThis program is an emulation of ls which is found in the terminal.");
        printf("\nThese are all of the flags: -a,-l,-h,-v");
        printf("\n-a: Prints all directories, including hidden files");
        printf("\n-l: Prints directories with detailed information.");
        printf("\n-h: Goes to this section, the help center!");
        printf("\n-v: Prints out the version of this program.");
    }
}

//Make a separate method for no arguments
//Otherwise, program is going to check for a variety of flags in order to compute the problem 
int main(int argc, const char* argv[]) {
    //Flag checks for printls method 
    int a_Scan = 0;
    int all_Scan = 0;
    int l_Scan = 0;
    int v_Scan = 0;
    int version_Scan = 0;
    int h_Scan = 0;
    int help_Scan = 0; 

    //Only ls was inputted. No other flags. 
    if(argc == 1) {
        printLs(".", 0,0,0,0,0,0,0);
    }
    //These are all of the other flags 
    else if(argc > 1) {

        //Checks to find "-" before the flag 
        if(argv[0][1] == "-") {

            //For loop to find all of the flags. This loop might need to be altered though. 
            for(int i = 0; i < argc-1; i++) {
                //This iterates through the arguments inputted
                char* check = (char*)(argv[1] + i);
                char** stringCheck = (char**)(argv[1] + i);
                while(*check) {
                    if(*check == 'a') a_Scan = 1;
                    else if(**stringCheck == "-all") all_Scan = 1;
				    else if(*check == 'l') l_Scan = 1;
                    else if(*check == 'v') v_Scan = 1;
                    else if (**stringCheck == "-version") version_Scan = 1;
                    else if(*check == 'h') h_Scan = 1;
                    else if(**stringCheck == "-help") help_Scan = 1;
                }
            }
            printLs(".", a_Scan, all_Scan, l_Scan, v_Scan, version_Scan, h_Scan, help_Scan);
        }
        else {
            printf("ERROR.");
        }
    }

    return 0;
}




