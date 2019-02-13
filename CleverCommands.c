#include "CleverCommands.h"
#include "CleverData.h"


Val cmdArrayGet(Val idx)
{
	return (Val) arrayGet((int32_t) idx);
}


Val cmdArraySet(Val idx, Val val)
{
	arraySet((int32_t) idx, (int32_t) val);
	return (Val) 0;
}


Val cmdArrayLen()
{
	return (Val) arrayLen();
}



Val cmdStringCat(Val sDest, Val sSource)
{
	stringCat((int32_t) sDest, (int32_t) sSource);
	return (Val) 0;
}


Val cmdStringCatChar(Val sDest, Val c)
{
	stringCatChar((int32_t) sDest, (int32_t) c);
	return (Val) 0;
}


Val cmdStringLen(Val sNo)
{
	return stringLen((int32_t) sNo);
}


Val cmdStringCut(Val sNo, Val sNo2, Val start, Val end)
{
	stringCut((int32_t) sNo, (int32_t) sNo2, (int32_t) start, (int32_t) end);
	return (Val) 0;
}


Val cmdStringPos(Val sNo, Val sTarget)
{
	return (Val) stringPos((int32_t) sNo, (int32_t) sTarget);
}


Val cmdStringToUpper(Val sNo)
{
	stringToUpper((int32_t) sNo);
	return (Val) 0;
}


Val cmdStringToLower(Val sNo)
{
	stringToLower((int32_t) sNo);
	return (Val) 0;
}


Val cmdNot(Val v)
{
	return (Val) !v;
}
