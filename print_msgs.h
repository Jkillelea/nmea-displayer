#ifndef PRINT_MSGS_H_
#define PRINT_MSGS_H_

void print_info(nmeaINFO *info);
void print_gpgga(nmeaGPGGA *gpgga);
void print_gpgsa(nmeaGPGSA *gpgsa);
void print_gpgsv(nmeaGPGSV *gpgsv);
void print_gpvtg(nmeaGPVTG *gpvtg);
void print_gprmc(nmeaGPRMC *gpvtg);

#endif // PRINT_MSGS_H_
