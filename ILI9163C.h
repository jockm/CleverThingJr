 #ifndef ILI9163_H
 #	define ILI9163_H

# define ILIINLINE inline


 	typedef struct glyphInfo {
 	    const uint16_t img[16][16];
 	    uint16_t fg;
 	    uint16_t bg;
 	} glyph;


 #	define ILI9163C_BLACK 0x0000
 #	define ILI9163C_WHITE 0xFFFF



 	typedef enum Orientation {
 		RibbonTop = 0,
 		RibbonLeft = 96,
 		RibbonRight = 160,
 		RibbonBottom = 192,
 	} ILI9163C_Orientation;


 	void ILI9163C(uint8_t cs, uint8_t dc, uint8_t rst);
 	void ILI9163C_start();
 	void ILI9163C_init(ILI9163C_Orientation orient);
 	void ILI9163C_close();
 	void ILI9163C_setColor(uint16_t c);
 	void ILI9163C_fillScreen(uint16_t c);
 	uint16_t  ILI9163C_getWidth();
 	uint16_t ILI9163C_getHeight();
 	void ILI9163C_drawChar(uint16_t xPos, uint16_t yPos, uint8_t c, uint16_t fg, uint16_t bg);
 	void ILI9163C_drawString(uint8_t x, uint8_t y, const char *str, uint16_t fg, uint16_t bg);
 	void ILI9163C_fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
 	void ILI9163C_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
 	void ILI9163C_drawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t c);
 	void ILI9163C_drawVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t c);
 	void ILI9163C_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
 	void ILI9163C_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
 	void ILI9163C_drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
 	void ILI9163C_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color);
 	void ILI9163C_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
 	void ILI9163C_clearScreen(uint16_t color);
 	void ILI9163C_clearRows(uint8_t startY, uint8_t endY, uint16_t color);
 	void ILI9163C_drawPoint(uint8_t x, uint8_t y, uint16_t color);
 	void ILI9163C_drawGlyph(uint8_t x, uint8_t y, const uint8_t *glyph, uint16_t fgColor, uint16_t bgColor);
 	void ILI9163C_drawGlyph16(uint8_t x, uint8_t y, glyph g);
 	void ILI9163C_drawGlyphString(uint8_t x, uint8_t y, const uint8_t glyphs[][8], const char *str, uint16_t fgColor, uint16_t bgColor);
 	void IILI9163C_drawBufOnLine(uint8_t x, uint8_t y, uint8_t w);
 	void ILI9163C_drawImage(const uint8_t *img);


 	//todo make macro
 	ILIINLINE static int map(int x, int in_min, int in_max, int out_min, int out_max)
 	 {
 		 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 	 }

 	 //todo make macro
 	ILIINLINE static uint16_t rgb16(uint8_t r, uint8_t g, uint8_t b)
 	 {
 		 return (b << 11) | (g << 6) | (r);
 	 }

 	 //todo make macro
 	ILIINLINE static uint16_t rgbTo16(uint8_t r, uint8_t g, uint8_t b)
 	 {
 		 r = map(r, 0, 255, 0, 31);
 		 g = map(g, 0, 255, 0, 63);
 		 b = map(b, 0, 255, 0, 31);

 		 uint16_t ret = rgb16(r, g, b);
 		 return ret;
 	 }


// 	 //todo make macro
// 	ILIINLINE static uint16_t rgb2bgr(uint16_t c)
// 	 {
// 		 uint8_t r = c >> 11;
// 		 uint8_t g = (c >> 5) & 0b11111 ;
// 		 uint8_t b = c & 0b11111;
//
// 		 return (b << 11) | (g << 6) | (r);
// 	 }

 	 //todo make macro
 	ILIINLINE static uint16_t rgb32To16(uint32_t rgb)
 	 {
 		 uint8_t r = (rgb & 0xFF0000) >> 16;
 		 uint8_t g = (rgb & 0xFF00) >> 8;
 		 uint8_t b = rgb & 0xFF;


 		 uint16_t ret = rgbTo16(r, g, b);
 		 return ret;
 	 }



 #endif
