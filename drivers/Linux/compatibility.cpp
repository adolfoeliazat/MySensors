#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "Arduino.h"

// For millis()
static unsigned long millis_at_start = 0;

/**
* C++ version 0.4 char* style "itoa":
* Written by Lukás Chmela
* Released under GPLv3.
*/
char *itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }
	
	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;
	
	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );
	
	// Apply negative sign
	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char *ltoa(long value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	long tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

char *ultoa(long num, char *str, int radix)
{
	unsigned long value;
	char *sp = str;
	char *sp2;

	value = num;

	/* Store sign at start of buffer for negative base-10 values */
	if (10 == radix && 0 > num) {
		*sp++ = '-';
		value = -num;
	}

	sp2 = sp;

	do {
		char rem = value % radix;
		value /= radix;
		if (10 > rem) {
			*sp++ = '0' + rem;
		} else {
			*sp++ = 'A' + rem - 10;
		}
	} while (0 < value);

	/* Mark end of string */
	*sp-- = 0;

	/* Reverse string contents (excluding sign) in place */
	while (sp2 < sp) {
		char tmp = *sp2;
		*sp2++ = *sp;
		*sp-- = tmp;
	}

	return str;
}

/**
 * Copyright (c) 2012, Peter A. Bigot <bigotp@acm.org>
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the software nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

char *utoa(int num, char *str, int radix)
{
	unsigned int value;
	char *sp = str;
	char *sp2;

	value = num;

	/* Store sign at start of buffer for negative base-10 values */
	if (10 == radix && 0 > num) {
		*sp++ = '-';
		value = -num;
	}

	sp2 = sp;

	do {
		char rem = value % radix;
		value /= radix;
		if (10 > rem) {
			*sp++ = '0' + rem;
		} else {
			*sp++ = 'A' + rem - 10;
		}
	} while (0 < value);

	/* Mark end of string */
	*sp-- = 0;

	/* Reverse string contents (excluding sign) in place */
	while (sp2 < sp) {
		char tmp = *sp2;
		*sp2++ = *sp;
		*sp-- = tmp;
	}

	return str;
}

char *dtostrf(float f, int width, int decimals, char *result)
{
	sprintf(result,"%*.*f", width, decimals, f);
	return result;
}

unsigned long millis(void)
{
	timeval curTime;

	if (millis_at_start == 0) {
		gettimeofday(&curTime, NULL);
		millis_at_start = curTime.tv_sec;
	}

	gettimeofday(&curTime, NULL);
	return ((curTime.tv_sec - millis_at_start) * 1000) + (curTime.tv_usec / 1000);
}

void delay(unsigned int millis)
{
    struct timespec sleeper;
    
    sleeper.tv_sec  = (time_t)(millis / 1000);
    sleeper.tv_nsec = (long)(millis % 1000) * 1000000;
    nanosleep(&sleeper, NULL);
}
