#include "CleverCommands.h"
#include "CleverData.h"

#include <nrf_delay.h>

#include "ILI9163C.h"


static uint16_t fgColor;
static uint16_t bgColor;


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


Val cmdStringSet(Val sDest, Val sSource)
{
	stringCopy((int32_t) sDest, (int32_t) sSource);
	return (Val) 0;
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


Val cmdStringCount()
{
	return stringCount();
}

Val cmdStringCompare(Val s1, Val s2)
{
	return stringCompare((int32_t) s1, (int32_t) s2);
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


Val cmdWait(Val v)
{
	nrf_delay_ms((uint32_t) v);
	return (Val) 0;
}


Val cmdRGB(Val r, Val g, Val b)
{
	uint16_t ret = rgbTo16((uint8_t) r, (uint8_t) g, (uint8_t) b);

	return (Val) ret;
}


Val cmdSetFg(Val c)
{
	fgColor = (uint16_t) c;
	return (Val) 0;
}


Val cmdSetBg(Val c)
{
	fgColor = (uint16_t) c;
	return (Val) 0;
}


Val cmdFillScreen(Val c)
{
	ILI9163C_clearScreen((uint16_t) c);
	return (Val) 0;
}


Val cmdScreenWidth()
{
	return (Val) ILI9163C_getWidth();
}


Val cmdScreenHeight()
{
	return (Val) ILI9163C_getHeight();
}


Val cmdDrawChar(Val x, Val y, Val c)
{
	ILI9163C_drawChar((uint16_t) x, (uint16_t) y, (uint8_t) c, fgColor, bgColor);
	return (Val) 0;
}


Val cmdDrawString(Val x, Val y, Val sNo)
{

	ILI9163C_drawString((uint16_t) x, (uint16_t) y, stringGet((int32_t) sNo), fgColor, bgColor);
	return (Val) 0;
}

Val cmdDrawRect(Val x, Val y, Val w, Val h)
{
	ILI9163C_drawRect((uint16_t) x, (uint16_t) y, (uint16_t) w, (uint16_t) h, fgColor);
	return (Val) 0;
}


Val cmdFillRect(Val x, Val y, Val w, Val h)
{
	ILI9163C_fillRect((uint16_t) x, (uint16_t) y, (uint16_t) w, (uint16_t) h, fgColor);
	return (Val) 0;
}


Val cmdPoint(Val x, Val y)
{
	ILI9163C_drawPoint((uint16_t) x, (uint16_t) y, fgColor);
	return (Val) 0;
}


Val cmdHLine(Val x, Val y, Val w, Val z)
{
	ILI9163C_drawHLine((uint16_t) x, (uint16_t) y, (uint16_t) z, fgColor);
	return (Val) 0;
}

Val cmdVLine(Val x, Val y, Val w, Val z)
{
	ILI9163C_drawVLine((uint16_t) x, (uint16_t) y, (uint16_t) z, fgColor);
	return (Val) 0;
}

void addTinyScriptExtensions()
{
	TinyScript_Define("get", BUILTIN, (Val) cmdArrayGet);
	TinyScript_Define("set", BUILTIN, (Val) cmdArraySet);
	TinyScript_Define("alen", BUILTIN, (Val) cmdArrayLen);
	TinyScript_Define("strcnt", BUILTIN, (Val) cmdStringCount);
	TinyScript_Define("strcmp", BUILTIN, (Val) cmdStringCompare);
	TinyScript_Define("strcopy", BUILTIN, (Val) cmdStringSet);
	TinyScript_Define("strcat", BUILTIN, (Val) cmdStringCat);
	TinyScript_Define("strccat", BUILTIN, (Val) cmdStringCatChar);
	TinyScript_Define("strlen", BUILTIN, (Val) cmdStringLen);
	TinyScript_Define("strcut", BUILTIN, (Val) cmdStringCut);
	TinyScript_Define("strpos", BUILTIN, (Val) cmdStringPos);
	TinyScript_Define("strUp", BUILTIN, (Val) cmdStringToUpper);
	TinyScript_Define("strLow", BUILTIN, (Val) cmdStringToLower);
	TinyScript_Define("not", BUILTIN, (Val) cmdNot);
	TinyScript_Define("wait", BUILTIN, (Val) cmdWait);
	TinyScript_Define("rgb", BUILTIN, (Val) cmdRGB);
	TinyScript_Define("fg", BUILTIN, (Val) cmdSetFg);
	TinyScript_Define("bg", BUILTIN, (Val) cmdSetBg);
	TinyScript_Define("cls", BUILTIN, (Val) cmdFillScreen);
	TinyScript_Define("dot", BUILTIN, (Val) cmdPoint);
	TinyScript_Define("w", BUILTIN, (Val) cmdScreenWidth);
	TinyScript_Define("h", BUILTIN, (Val) cmdScreenHeight);
	TinyScript_Define("drawc", BUILTIN, (Val) cmdDrawChar);
	TinyScript_Define("draw", BUILTIN, (Val) cmdDrawString);
	TinyScript_Define("rect", BUILTIN, (Val) cmdDrawRect);
	TinyScript_Define("frect", BUILTIN, (Val) cmdFillRect);
	//TODO	TinyScript_Define("circle", BUILTIN, cmdDrawCircle);
	//TODO	TinyScript_Define("fcircle", BUILTIN, cmdFilledCircle);
	//TODO	TinyScript_Define("line", BUILTIN, cmdLine);
	TinyScript_Define("hline", BUILTIN, (Val) cmdHLine);
	TinyScript_Define("vline", BUILTIN, (Val) cmdVLine);
}
