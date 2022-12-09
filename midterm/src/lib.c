#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

//I utilized the dirent.h struct in order to show the directory [6]
void show_directory(char* directory){
    DIR *d; 
    struct dirent *list;
    d = opendir(directory);
    char* dotCheck = ".";

    //This prints out the directory file. If "d" contains info, the loop initiates. 
    if(d != NULL) {
        while((list = readdir(d)) != NULL) {
            if(strcmp(dotCheck, list->d_name)) {
                continue;
            }
            printf("%s\n", list->d_name);
        }   
        closedir(d);
    }
    else {
        printf("ERROR");
    }

}

void show_directory_all(char* directory){
    DIR *d; 
    struct dirent *list;
    d = opendir(directory);
    char* dotCheck = ".";

    //This prints out the directory file. If "d" contains info, the loop initiates. 
    if(d != NULL) {
        while((list = readdir(d)) != NULL) {

            //By removing "continue" this prints the hidden files 
            if(strcmp(dotCheck, list->d_name))
            printf("%s\n", list->d_name);
        }   
        closedir(d);
    }
    else {
        printf("ERROR");
    }
}

void show_directory_long(char* directory){
    DIR *d; 
    struct dirent *list;
    struct stat info;
    d = opendir(directory);
    char* dotCheck = ".";
    char execCheck[] = "";

    //This prints out the directory file. If "d" contains info, the loop initiates. 
    if(d != NULL) {
        while((list = readdir(d)) != NULL) {
            if(strcmp(dotCheck, list->d_name) != 0) {
                continue;                
            }  
            //printf("%s\n", list->d_name);

            //Checks to see if the directory is executable [4]
            if(stat(list->d_name, &info) == 0 && info.st_mode & S_IXUSR) {
                //printf("%s\n is executable", list->d_name);
                execCheck[0] = "Executable";
            }
            else {
                //printf("%s\n is not executable", list->d_name);
                execCheck[0] = "Not executable"; 
            }

            //Prints out date created[8]
            stat(list->d_name, &info);
            char* dateGain = ctime(&info.st_birthtimespec);
            //printf("Date Created: %s\n", dateGain);

            //Prints out owner
            stat(list->d_name, &info);
            struct passwd *nameGain = getpwuid(info.st_uid);
            //printf("Owner: %s\n", nameGain);

            //Prints out size of the file 
            stat(list->d_name, &info);
            int sizeGain = info.st_size; 
            //printf("Size: %s\n", sizeGain);

            printf("%-50s %-50s %-50s %-50s %-50s", list->d_name, execCheck[0], dateGain, nameGain, sizeGain);

        }
        closedir(d);
    }
    else {
        printf("ERROR");
    }

}

void show_directory_long_all(char* directory){
    DIR *d; 
    struct dirent *list;
    struct stat info;
    d = opendir(directory);
    char* dotCheck = ".";
    char execCheck[] = "";


    //This prints out the directory file. If "d" contains info, the loop initiates. 
    if(d != NULL) {
        while((list = readdir(d)) != NULL) {

            //By removing "!= 0" this prints the hidden files 
            if(strcmp(dotCheck, list->d_name))
            //printf("%s\n", list->d_name);

            //Checks to see if the directory is executable 
            if(stat(list->d_name, &info) == 0 && info.st_mode & S_IXUSR) {
                //printf("%s\n is executable", list->d_name);
                execCheck[0] = "Executable";

            }
            else {
                //printf("%s\n is not executable", list->d_name);
                execCheck[0] = "Not executable"; 

            }

            //Prints out date created
            stat(list->d_name, &info);
            struct timespec dateGain = info.st_birthtimespec; 
            //printf("Date Created: %s\n", dateGain);

            //Prints out owner 
            stat(list->d_name, &info);
            struct passwd *nameGain = getpwuid(info.st_uid);
            //printf("Owner: %s\n", nameGain);

            //Prints out size of the file 
            stat(list->d_name, &info);
            int sizeGain = info.st_size; 
            //printf("Size: %d\n", sizeGain);

            printf("%-50s %-50s %-50s %-50s %-50s", list->d_name, execCheck[0], dateGain, nameGain, sizeGain);


        }   
        closedir(d);
    }
    else {
        printf("ERROR");
    }
}
