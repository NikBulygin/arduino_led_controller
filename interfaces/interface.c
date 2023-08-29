#include "interface.h"

#define DEFAULT_SERIAL_PORT "/dev/ttyS0"  // Значение по умолчанию

static bool send_via_serial(const char* message, const char* port);

bool send_message(const char* message, const char* port) {
    if (!port) {
        port = DEFAULT_SERIAL_PORT;
    }
    return send_via_serial(message, port);
}

static bool send_via_serial(const char* message, const char* port) {
    int fd = open(port, O_WRONLY | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("Cannot open serial port");
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error from tcgetattr");
        close(fd);
        return false;
    }

    cfsetospeed(&tty, B115200);
    cfsetispeed(&tty, B115200);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 5;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        close(fd);
        return false;
    }

    ssize_t length = write(fd, message, strlen(message));
    if (length < 0) {
        perror("Error while writing to serial port");
        close(fd);
        return false;
    }

    close(fd);
    return true;
}
