#include <stdio.h>
#include <nmea/nmea.h>

#include "constants.h"
#include "util.h"

#define BUFF_SIZE 512

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

    nmea_parser_init(&parser);
    nmea_zero_INFO(&info);
    nmea_zero_GPGGA(&gpgga);
    nmea_zero_GPGSA(&gpgsa);
    nmea_zero_GPGSV(&gpgsv);
    nmea_zero_GPRMC(&gprmc);
    nmea_zero_GPVTG(&gpvtg);

    int fd = try_open(portname);
    if (fd < 0)
        return 1;

    while (true) {
        // read until buffer is full
        size_t recieved_bytes = 0;
        while(recieved_bytes < BUFF_SIZE) {
            size_t nbytes_read = read(fd, buff + recieved_bytes, BUFF_SIZE - recieved_bytes);
            recieved_bytes += nbytes_read;

            if (nbytes_read == 0) { // failed to read anything?
                perror("Failed to read from fd.");
                try_close(fd);
                fd = try_open(portname);
                if (fd < 0) {
                    perror("Failed to reopen fd.");
                    return 2;
                }
            }
        }

        nmea_parse(&parser, buff, BUFF_SIZE, &info);

        nmea_info2GPGGA(&info, &gpgga);
        nmea_info2GPGSA(&info, &gpgsa);
        nmea_info2GPGSV(&info, &gpgsv, 1);
        nmea_info2GPRMC(&info, &gprmc);
        nmea_info2GPVTG(&info, &gpvtg);
        nmea_info2pos(&info, &pos);

        printf("GPGGA {\n");
        printf("    utc = {\n");
        printf("        year = %d,\n", gpgga.utc.year);
        printf("        mon  = %d,\n", gpgga.utc.mon);
        printf("        day  = %d,\n", gpgga.utc.day);
        printf("        hour = %d,\n", gpgga.utc.hour);
        printf("        min  = %d,\n", gpgga.utc.min);
        printf("        sec  = %d,\n", gpgga.utc.sec);
        printf("        hsec = %d,\n", gpgga.utc.hsec);
        printf("    },\n");
        printf("    lat      = %lf %s,\n", gpgga.lat, &gpgga.ns);
        printf("    lon      = %lf %s,\n", gpgga.lon, &gpgga.ew);
        printf("    sig      = %d,\n",     gpgga.sig);
        printf("    satinuse = %d,\n",     gpgga.satinuse);
        printf("    HDOP     = %lf,\n",    gpgga.HDOP);
        printf("    elv      = %lf %s,\n", gpgga.elv, &gpgga.elv_units);
        printf("    diff     = %lf %s,\n", gpgga.diff, &gpgga.diff_units);
        printf("    dgps_age = %lf,\n",    gpgga.dgps_age);
        printf("    dgps_sid = %d,\n",     gpgga.dgps_sid);
        printf("};\n");

        printf("GPGSA {\n");
        printf("    fix_mode = %s,\n", &gpgsa.fix_mode);
        printf("    fix_type = %d,\n", gpgsa.fix_type);
        int i = 0;
        while (gpgsa.sat_prn[i]) {
            printf("    sat_prn = %d,\n", *gpgsa.sat_prn);
            i++;
        }
        printf("    PDOP = %lf,\n", gpgsa.PDOP);
        printf("    HDOP = %lf,\n", gpgsa.HDOP);
        printf("    VDOP = %lf,\n", gpgsa.VDOP);
        printf("};\n");

        printf("GPVTG {\n");
        printf("    dir = %lf %s\n", gpvtg.dir, &gpvtg.dir_t);
        printf("    dec = %lf %s\n", gpvtg.dec, &gpvtg.dec_m);
        printf("    spn = %lf %s\n", gpvtg.spn, &gpvtg.spn_n);
        printf("    spk = %lf %s\n", gpvtg.spk, &gpvtg.spk_k);
        printf("};\n");

    }
    nmea_parser_destroy(&parser);

    return 0;
}
