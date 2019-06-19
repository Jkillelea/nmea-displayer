#include <stdio.h>
#include <nmea/nmea.h>

#include "constants.h"
#include "print_msgs.h"
#include "util.h"

#define BUFF_SIZE 512

void trace(const char *str, int str_size) {
    printf("Trace: ");
    printf("%s\n", str);
    printf("\n");
}

void error(const char *str, int str_size) {
    printf("Error: ");
    printf("%s\n", str);
    printf("\n");
}

int main(int argc, const char *argv[]) {
    char buff[BUFF_SIZE] = {0};
    nmeaPARSER parser;
    nmeaINFO   info;
    nmeaPOS    pos;
    nmeaGPGGA  gpgga;
    nmeaGPGSA  gpgsa;
    nmeaGPGSV  gpgsv;
    nmeaGPRMC  gprmc;
    nmeaGPVTG  gpvtg;

    // nmea_property()->trace_func = &trace;
    // nmea_property()->error_func = &error;

    nmea_parser_init(&parser);

    int fd = try_open(portname);
    if (fd < 0)
        return 1;

    while (true) {
        nmea_zero_INFO(&info);
        nmea_zero_GPGGA(&gpgga);
        nmea_zero_GPGSA(&gpgsa);
        nmea_zero_GPGSV(&gpgsv);
        nmea_zero_GPRMC(&gprmc);
        nmea_zero_GPVTG(&gpvtg);

        // read until buffer is full
        size_t recieved_bytes = 0;
        while(recieved_bytes < BUFF_SIZE) {
            size_t nbytes_read = read(fd, buff + recieved_bytes, BUFF_SIZE - recieved_bytes);
            recieved_bytes += nbytes_read;

            if (nbytes_read == 0) { // failed to read anything?
                fprintf(stderr, "Failed to read from fd (0 bytes)\n");
                try_close(fd);
                fd = try_open(portname);
                if (fd < 0) {
                    perror("Failed to reopen fd:");
                    return 2;
                }
            }
        }

        // printf("%s\n", buff);

        int nparsed = nmea_parse(&parser, buff, BUFF_SIZE, &info);
        printf("parsed %d messages\n", nparsed);

        nmea_info2GPGGA(&info, &gpgga);
        nmea_info2GPGSA(&info, &gpgsa);
        nmea_info2GPGSV(&info, &gpgsv, 1);
        nmea_info2GPRMC(&info, &gprmc);
        nmea_info2GPVTG(&info, &gpvtg);
        nmea_info2pos(&info, &pos);

        print_info(&info);

        // check which messages were recieved
        if (info.smask & GPGGA) {
            puts("got a GPGGA msg");
            print_gpgga(&gpgga);
        }
        if (info.smask & GPGSA) {
            puts("got a GPGSA msg");
            print_gpgsa(&gpgsa);
        }
        if (info.smask & GPGSV) {
            puts("got a GPGSV msg");
            print_gpgsv(&gpgsv);
        }
        if (info.smask & GPRMC) {
            puts("got a GPRMC msg");
            print_gprmc(&gprmc);
        }
        if (info.smask & GPVTG) {
            puts("got a GPVTG msg");
            print_gpvtg(&gpvtg);
        }
    }

    nmea_parser_destroy(&parser);

    return 0;
}
