#ifndef INCLUDE_RTL_433_H_
#define INCLUDE_RTL_433_H_

#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "rtl_433_devices.h"

#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include "getopt/getopt.h"
#endif

#define DEFAULT_SAMPLE_RATE     250000
#define DEFAULT_FREQUENCY       433920000
#define DEFAULT_HOP_TIME        (60*10)
#define DEFAULT_HOP_EVENTS      2
#define DEFAULT_ASYNC_BUF_NUMBER    32
#define DEFAULT_BUF_LENGTH      (16 * 16384)
#define DEFAULT_LEVEL_LIMIT     10000
#define DEFAULT_DECIMATION_LEVEL 0
#define MINIMAL_BUF_LENGTH      512
#define MAXIMAL_BUF_LENGTH      (256 * 16384)
#define FILTER_ORDER            1
#define MAX_PROTOCOLS           20
#define SIGNAL_GRABBER_BUFFER   (12 * DEFAULT_BUF_LENGTH)

/* Supported modulation types */
#define     OOK_PWM_D		1   /* Pulses are of the same length, the distance varies (PPM) */
#define     OOK_PWM_P		2   /* The length of the pulses varies */
#define     OOK_MANCHESTER	3	/* Manchester code */
#define     OOK_PULSE_PWM_RAW	4	// Pulse Width Modulation. No startbit removal. Short pulses = 1, Long = 0
#define     OOK_PULSE_MANCHESTER_ZEROBIT	5	// Manchester encoding. Hardcoded zerobit. Rising Edge = 0, Falling edge = 1

extern int debug_output;
int debug_callback(uint8_t buffer[BITBUF_ROWS][BITBUF_COLS], int16_t bits_per_row[BITBUF_ROWS]);


struct protocol_state {
    int (*callback)(uint8_t bits_buffer[BITBUF_ROWS][BITBUF_COLS], int16_t bits_per_row[BITBUF_ROWS]);

    /* bits state */
    int bits_col_idx;
    int bits_row_idx;
    int bits_bit_col_idx;
    uint8_t bits_buffer[BITBUF_ROWS][BITBUF_COLS];
    int16_t bits_per_row[BITBUF_ROWS];
    int bit_rows;
    unsigned int modulation;

    /* demod state */
    int pulse_length;
    int pulse_count;
    int pulse_distance;
    int sample_counter;
    int start_c;

    int packet_present;
    int pulse_start;
    int real_bits;
    int start_bit;
    /* pwm limits */
    int short_limit;
    int long_limit;
    int reset_limit;
};

#endif /* INCLUDE_RTL_433_H_ */
