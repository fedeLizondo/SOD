#ifndef __UTILS_H__
#define __UTILS_H__

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char * mensColor( const char * mensaje,const char * color){
    int size = strlen(mensaje) + (strlen(ANSI_COLOR_RED) * 2) + 1;
    char redString[size];
    char *end = redString;
    sprintf(redString,"%s%s%s",color,mensaje,ANSI_COLOR_RESET);
    return strcat(redString,"\0");
}

char * cRed(char * mensaje ){
    int size = sizeof(char) * (strlen(mensaje) + (strlen(ANSI_COLOR_RED) * 2) + 1);
    printf("%d",size);
    char redString[100];
    char *end = redString;
    sprintf(redString,"%s%s%s",ANSI_COLOR_RED,mensaje,ANSI_COLOR_RESET);
    return strcat(redString,"\0");
}

char * cYellow( const char * mensaje ){
    int size = strlen(mensaje) + (strlen(ANSI_COLOR_RED) * 2) + 1;
    char redString[size];
    char *end = redString;
    sprintf(redString,"%s%s%s",ANSI_COLOR_YELLOW,mensaje,ANSI_COLOR_RESET);
    return strcat(redString,"\0");
}

char * cGreen( const char * mensaje ){
    int size = strlen(mensaje) + (strlen(ANSI_COLOR_RED) * 2) + 1;
    char redString[size];
    char *end = redString;
    sprintf(redString,"%s%s%s",ANSI_COLOR_GREEN,mensaje,ANSI_COLOR_RESET);
    return strcat(redString,"\0");
}

#endif
