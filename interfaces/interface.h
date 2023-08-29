
#ifndef GTK_WIDGET_INTERFACE_H
#define GTK_WIDGET_INTERFACE_H


#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>


bool send_message(const char* message, const char* port);



#endif // GTK_WIDGET_INTERFACE_H
