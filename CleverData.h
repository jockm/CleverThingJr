#ifndef CLEVERDATA_H
#	define CLEVERDATA_H

#	include <stdint.h>
#	include "tinyscript.h"

#	define BUFSIZE     256

	extern uint8_t buf[BUFSIZE];


	void cleverDataInit();


	int32_t arrayGet(int32_t idx);
	void arraySet(int32_t idx, int32_t val);
	int32_t arrayLen();

	int32_t stringCount();
	void stringSet(int32_t sNo, const char *str);
	const char *stringGet(int32_t sNo);
	void stringCopy(int32_t sDest, int32_t sSource);
	int32_t stringCompare(int32_t s1, int32_t s2);
	void stringCat(int32_t sDest, int32_t sSource);
	void stringCatChar(int32_t sDest, char sSource);
	int32_t stringLen(int32_t sNo);
	void stringCut(int32_t sNo, int32_t sNo2, int32_t start, int32_t end);
	int32_t stringPos(int32_t sNo, int32_t sTarget);
	void stringToUpper(int32_t sNo);
	void stringToLower(int32_t sNo);
#endif
