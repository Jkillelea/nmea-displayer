#include <stdio.h>
#include <nmea/nmea.h>

#include "print_msgs.h"
#include "util.h"

void print_info(nmeaINFO *info) {
    printf("info {\n");
    printf("    mask = %d,\n", info->smask);
    printf("    utc = {\n");
    printf("        year = %d,\n", info->utc.year);
    printf("        mon  = %d,\n", info->utc.mon);
    printf("        day  = %d,\n", info->utc.day);
    printf("        hour = %d,\n", info->utc.hour);
    printf("        min  = %d,\n", info->utc.min);
    printf("        sec  = %d,\n", info->utc.sec);
    printf("        hsec = %d,\n", info->utc.hsec);
    printf("    }\n");
    printf("    sig         = %d,\n",  info->sig);
    printf("    fix         = %d,\n",  info->fix);
    printf("    PDOP        = %lf,\n", info->PDOP);
    printf("    HDOP        = %lf,\n", info->HDOP);
    printf("    VDOP        = %lf,\n", info->VDOP);
    printf("    lat         = %lf,\n", decimal_minutes2decimal_decimal(info->lat));
    printf("    lon         = %lf,\n", decimal_minutes2decimal_decimal(info->lon));
    printf("    elv         = %lf,\n", info->elv);
    printf("    speed       = %lf,\n", info->speed);
    printf("    direction   = %lf,\n", info->direction);
    printf("    declination = %lf,\n", info->declination);
    printf("};\n");
}

void print_gpgga(nmeaGPGGA *gpgga) {
    printf("GPGGA {\n");
    printf("    utc = {\n");
    printf("        year = %d,\n", gpgga->utc.year);
    printf("        mon  = %d,\n", gpgga->utc.mon);
    printf("        day  = %d,\n", gpgga->utc.day);
    printf("        hour = %d,\n", gpgga->utc.hour);
    printf("        min  = %d,\n", gpgga->utc.min);
    printf("        sec  = %d,\n", gpgga->utc.sec);
    printf("        hsec = %d,\n", gpgga->utc.hsec);
    printf("    },\n");
    printf("    lat      = %lf %s,\n", decimal_minutes2decimal_decimal(gpgga->lat), &gpgga->ns);
    printf("    lon      = %lf %s,\n", decimal_minutes2decimal_decimal(gpgga->lon), &gpgga->ew);
    printf("    sig      = %d,\n",     gpgga->sig);
    printf("    satinuse = %d,\n",     gpgga->satinuse);
    printf("    HDOP     = %lf,\n",    gpgga->HDOP);
    printf("    elv      = %lf %s,\n", gpgga->elv,  &gpgga->elv_units);
    printf("    diff     = %lf %s,\n", gpgga->diff, &gpgga->diff_units);
    printf("    dgps_age = %lf,\n",    gpgga->dgps_age);
    printf("    dgps_sid = %d,\n",     gpgga->dgps_sid);
    printf("};\n");
}

void print_gpgsa(nmeaGPGSA *gpgsa) {
    printf("GPGSA {\n");
    printf("    fix_mode = %s,\n", &gpgsa->fix_mode);
    printf("    fix_type = %d,\n", gpgsa->fix_type);
    // int i = 0;
    // while (gpgsa->sat_prn[i]) {
    //     printf("    sat_prn = %d,\n", gpgsa->sat_prn[i]);
    //     i++;
    // }
    printf("    PDOP = %lf,\n", gpgsa->PDOP);
    printf("    HDOP = %lf,\n", gpgsa->HDOP);
    printf("    VDOP = %lf,\n", gpgsa->VDOP);
    printf("};\n");
}

void print_gpgsv(nmeaGPGSV *gpgsv) {
    printf("GPGSV {\n");
    printf("    pack_count = %d\n", gpgsv->pack_count);
    printf("    pack_index = %d\n", gpgsv->pack_index);
    printf("    sat_count  = %d\n", gpgsv->sat_count);
    // for (int i = 0; i < gpgsv->sat_count; i++) {
    //     nmeaSATELLITE sat = gpgsv->sat_data[i];
    //     printf("    satellite = {\n");
    //     printf("        id      = %d\n", sat.id);
    //     printf("        in_use  = %d\n", sat.in_use);
    //     printf("        elv     = %d\n", sat.elv);
    //     printf("        azimuth = %d\n", sat.azimuth);
    //     printf("        sig     = %d\n", sat.sig);
    //     printf("    }\n");
    // }
    printf("};\n");
}

void print_gpvtg(nmeaGPVTG *gpvtg) {
    printf("GPVTG {\n");
    printf("    dir = %lf %s\n", gpvtg->dir, &gpvtg->dir_t);
    printf("    dec = %lf %s\n", gpvtg->dec, &gpvtg->dec_m);
    printf("    spn = %lf %s\n", gpvtg->spn, &gpvtg->spn_n);
    printf("    spk = %lf %s\n", gpvtg->spk, &gpvtg->spk_k);
    printf("};\n");
}

void print_gprmc(nmeaGPRMC *gprmc) {
    printf("GPRMC {\n");
    printf("    utc = {\n");
    printf("        year = %d,\n", gprmc->utc.year);
    printf("        mon  = %d,\n", gprmc->utc.mon);
    printf("        day  = %d,\n", gprmc->utc.day);
    printf("        hour = %d,\n", gprmc->utc.hour);
    printf("        min  = %d,\n", gprmc->utc.min);
    printf("        sec  = %d,\n", gprmc->utc.sec);
    printf("        hsec = %d,\n", gprmc->utc.hsec);
    printf("    }\n");
    printf("    status      = %s\n",    &gprmc->status);
    printf("    lat         = %lf %s\n", decimal_minutes2decimal_decimal(gprmc->lat), &gprmc->ns);
    printf("    lon         = %lf %s\n", decimal_minutes2decimal_decimal(gprmc->lat), &gprmc->ew);
    printf("    speed       = %lf\n",    gprmc->speed);
    printf("    direction   = %lf\n",    gprmc->direction);
    printf("    declination = %lf %s\n", gprmc->declination, &gprmc->declin_ew);
    printf("    mode        = %s\n",    &gprmc->mode);
    printf("};\n");
}

