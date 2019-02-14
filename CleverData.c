/*
 * CleverData.c
 *
 *  Created on: Feb 12, 2019
 *      Author: jock
 */

#include <string.h>
#include <ctype.h>

#include "CleverData.h"

#define NUMSTRINGS  20
#define STRINGWIDTH 21
#define ARRAYLEN    100


uint8_t buf[BUFSIZE];
int32_t array[ARRAYLEN];
char    strings[NUMSTRINGS][STRINGWIDTH];


int32_t arrayGet(int32_t idx)
{
	int32_t ret = 0;

	if(idx >= 0 && idx < ARRAYLEN) {
		ret = array[idx];
	}

	return ret;
}

void arraySet(int32_t idx, int32_t val)
{
	if(idx >= 0 && idx < ARRAYLEN) {
		array[idx] = val;
	}
}


int32_t arrayLen()
{
	return ARRAYLEN;
}


int32_t stringCount()
{
	return stringCount();
}


void stringSet(int32_t sNo, const char *str)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return;
	}

	strncpy(strings[sNo], str, STRINGWIDTH);
	strings[sNo][STRINGWIDTH - 1] = '\0';
}


const char *stringGet(int32_t sNo)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return NULL;
	}

	return strings[sNo];
}


void stringCopy(int32_t sDest, int32_t sSource)
{
	if(sDest < 0 || sDest >= NUMSTRINGS) {
		return;
	}

	if(sSource < 0 || sSource >= NUMSTRINGS) {
		return;
	}

	strncpy(strings[sDest], strings[sSource], STRINGWIDTH);
	strings[sDest][STRINGWIDTH - 1] = '\0';
}


void stringCat(int32_t sDest, int32_t sSource)
{
	if(sDest < 0 || sDest >= NUMSTRINGS) {
		return;
	}

	if(sSource < 0 || sSource >= NUMSTRINGS) {
		return;
	}

	strncat(strings[sDest], strings[sSource], STRINGWIDTH);
	strings[sDest][STRINGWIDTH - 1] = '\0';
}


int32_t stringCompare(int32_t s1, int32_t s2)
{
	if(s1 < 0 || s1 >= NUMSTRINGS) {
		return 0;
	}

	if(s2 < 0 || s2 >= NUMSTRINGS) {
		return 0;
	}

	int32_t ret = strcmp(strings[s1], strings[s2]);
	return (Val) ret;
}


void stringCatChar(int32_t sDest, char c)
{
	if(sDest < 0 || sDest >= NUMSTRINGS) {
		return;
	}

	int32_t catPos = strlen(strings[sDest]);

	if(catPos >= STRINGWIDTH - 1) {
		return;
	}

	strings[sDest][catPos] = c;
	strings[sDest][catPos + 1] = c;
}


int32_t stringLen(int32_t sNo)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return 0;
	}

	return strlen(strings[sNo]);
}


void stringCut(int32_t sNo, int32_t sNo2, int32_t start, int32_t end)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return;
	}

	if(sNo2 < 0 || sNo2 >= NUMSTRINGS) {
		return;
	}

	int32_t len = (end - start) + 1;

	if(len > STRINGWIDTH) {
		len = STRINGWIDTH;
	}

	strncpy((char *)buf, strings[sNo2] + start, len);
	buf[STRINGWIDTH] = '\0';

	strcpy(strings[sNo], (char *)buf);
}


int32_t stringPos(int32_t sNo, int32_t sTarget)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return -1;
	}

	char *pos = strstr(strings[sNo], strings[sTarget]);

	int ret;

	if(pos == NULL) {
		ret = -1;
	} else {
		ret = pos - strings[sNo];
	}
	return ret;
}


void stringToUpper(int32_t sNo)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return;
	}

	int32_t idx = 0;

	while(strings[sNo][idx]) {
		strings[sNo][idx] = toupper((unsigned char)strings[sNo][idx]);

		++idx;
	}
}


void stringToLower(int32_t sNo)
{
	if(sNo < 0 || sNo >= NUMSTRINGS) {
		return;
	}

	int32_t idx = 0;

	while(strings[sNo][idx]) {
		strings[sNo][idx] = tolower((unsigned char)strings[sNo][idx]);

		++idx;
	}
}
