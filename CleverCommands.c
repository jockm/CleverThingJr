#include "CleverCommands.h"
#include "CleverData.h"


Val cmdArrayGet(Val idx)
{
	return (Val) arrayGet((int32_t) idx);
}


void cmdArraySet(Val idx, Val val)
{
	arraySet((int32_t) idx, (int32_t) val);
}


Val cmdArrayLen()
{
	return (Val) arrayLen();
}



void cmdStringCat(Val sDest, Val sSource)
{
	stringCat((int32_t) sDest, (int32_t) sSource);
}


Val cmdStringLen(Val sNo)
{
	return stringLen((int32_t) sNo);
}


void cmdStringCut(Val sNo, Val sNo2, Val start, Val end)
{
	stringCut((int32_t) sNo, (int32_t) sNo2, (int32_t) start, (int32_t) end);
}


Val cmdStringPos(Val sNo, Val sTarget)
{
	return (Val) stringPos((int32_t) sNo, (int32_t) sTarget);
}


void cmdStringToUpper(Val sNo)
{
	stringToUpper((int32_t) sNo);
}


void cmdStringToLower(Val sNo)
{
	stringToLower((int32_t) sNo);
}

