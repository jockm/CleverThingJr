#include <stdlib.h>
#include <string.h>


#include "nrf_gpio.h"
#include "nrf_delay.h"


#include "ezSPI.h"
#include "ILI9163C.h"
#include "font8x8/font8x8.h"

#include "CleverData.h"


////////////////////////////////
//#include <stdio.h>
//#define uartPrint(s)                    simple_uart_putstring((const uint8_t *) s);
//void simple_uart_putstring(const uint8_t *);
////////////////////////////////

#ifndef _swap_int16_t
#	define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

 // ILI9163 LCD Controller Commands
 enum
 {
 	displayWidth = 128,
 	displayHeight = 128,

	lineBufferSize = 256,

 	CMD_NOP = 0x00,
 	CMD_SOFT_RESET = 0x01,
 	CMD_GET_RED_CHANNEL = 0x06,
 	CMD_GET_GREEN_CHANNEL = 0x07,
 	CMD_GET_BLUE_CHANNEL = 0x08,
 	CMD_GET_PIXEL_FORMAT = 0x0C,
 	CMD_GET_POWER_MODE = 0x0A,
 	CMD_GET_ADDRESS_MODE = 0x0B,
 	CMD_GET_DISPLAY_MODE = 0x0D,
 	CMD_GET_SIGNAL_MODE = 0x0E,
 	CMD_GET_DIAGNOSTIC_RESULT = 0x0F,
 	CMD_ENTER_SLEEP_MODE = 0x10,
 	CMD_EXIT_SLEEP_MODE = 0x11,
 	CMD_ENTER_PARTIAL_MODE = 0x12,
 	CMD_ENTER_NORMAL_MODE = 0x13,
 	CMD_EXIT_INVERT_MODE = 0x20,
 	CMD_ENTER_INVERT_MODE = 0x21,
 	CMD_SET_GAMMA_CURVE = 0x26,
 	CMD_SET_DISPLAY_OFF = 0x28,
 	CMD_SET_DISPLAY_ON = 0x29,
 	CMD_SET_COLUMN_ADDRESS = 0x2A,
 	CMD_SET_PAGE_ADDRESS = 0x2B,
 	CMD_WRITE_MEMORY_START = 0x2C,
 	CMD_WRITE_LUT = 0x2D,
 	CMD_READ_MEMORY_START = 0x2E,
 	CMD_SET_PARTIAL_AREA = 0x30,
 	CMD_SET_SCROLL_AREA = 0x33,
 	CMD_SET_TEAR_OFF = 0x34,
 	CMD_SET_TEAR_ON = 0x35,
 	CMD_SET_ADDRESS_MODE = 0x36,
 	CMD_SET_SCROLL_START = 0X37,
 	CMD_EXIT_IDLE_MODE = 0x38,
 	CMD_ENTER_IDLE_MODE = 0x39,
 	CMD_SET_PIXEL_FORMAT = 0x3A,
 	CMD_WRITE_MEMORY_CONTINUE = 0x3C,
 	CMD_READ_MEMORY_CONTINUE = 0x3E,
 	CMD_SET_TEAR_SCANLINE = 0x44,
 	CMD_GET_SCANLINE = 0x45,
 	CMD_READ_ID1 = 0xDA,
 	CMD_READ_ID2 = 0xDB,
 	CMD_READ_ID3 = 0xDC,
 	CMD_FRAME_RATE_CONTROL1 = 0xB1,
 	CMD_FRAME_RATE_CONTROL2 = 0xB2,
 	CMD_FRAME_RATE_CONTROL3 = 0xB3,
 	CMD_DISPLAY_INVERSION = 0xB4,
 	CMD_SOURCE_DRIVER_DIRECTION = 0xB7,
 	CMD_GATE_DRIVER_DIRECTION = 0xB8,
 	CMD_POWER_CONTROL1 = 0xC0,
 	CMD_POWER_CONTROL2 = 0xC1,
 	CMD_POWER_CONTROL3 = 0xC2,
 	CMD_POWER_CONTROL4 = 0xC3,
 	CMD_POWER_CONTROL5 = 0xC4,
 	CMD_VCOM_CONTROL1 = 0xC5,
 	CMD_VCOM_CONTROL2 = 0xC6,
 	CMD_VCOM_OFFSET_CONTROL = 0xC7,
 	CMD_WRITE_ID4_VALUE = 0xD3,
 	CMD_NV_MEMORY_FUNCTION1 = 0xD7,
 	CMD_NV_MEMORY_FUNCTION2 = 0xDE,
 	CMD_POSITIVE_GAMMA_CORRECT = 0xE0,
 	CMD_NEGATIVE_GAMMA_CORRECT = 0xE1,
 	CMD_GAM_R_SEL = 0xF2,
 };


 static uint16_t    currColor;

 static uint8_t     csPin;
 static uint8_t     dcPin;
 static uint8_t     rstPin;

 ///////////////////////////////////////////////////////////////////////
 // Private Functions
 ///////////////////////////////////////////////////////////////////////
 void ILI9163C_reset(void);
 void ILI9163C_writeCommand(uint8_t cmd);
 void ILI9163C_writeParam(uint8_t param);
 void ILI9163C_writeColor(uint16_t color);
 void ILI9163C_setUpdateWindow(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY);
 ///////////////////////////////////////////////////////////////////////


 void ILI9163C(uint8_t cs, uint8_t dc, uint8_t rst)
 {
	 csPin = cs;
	 dcPin = dc;
	 rstPin = rst;

	 nrf_gpio_cfg_output(csPin);
	 nrf_gpio_cfg_output(dcPin);
	 nrf_gpio_cfg_output(rstPin);
 }


 void ILI9163C_start()
 {
 	currColor = ILI9163C_BLACK;

 	// Reset the display
 	nrf_gpio_pin_set(rstPin);
 	nrf_delay_ms(1);
 	nrf_gpio_pin_clear(rstPin);
 	nrf_delay_ms(2);
 	nrf_gpio_pin_set(rstPin);
 	nrf_delay_ms(120);

 	// 8 bit spi mode 0
 	//JEM ILI9163C_spi.format(8, 0);

 	// 40Mhz is the max SPI speed of the STM32L43x
 	//JEM ILI9163C_spi.frequency(40L * 1000000L);
 }

 void ILI9163C_init(ILI9163C_Orientation orient)
 {

 	// Hardware reset the LCD
 	ILI9163C_reset();

 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_writeCommand(CMD_SOFT_RESET);
 	nrf_delay_ms(50);

 	ILI9163C_writeCommand(CMD_EXIT_SLEEP_MODE);
 	nrf_delay_ms(5); // Wait for the screen to wake up

 	ILI9163C_writeCommand(0x3A);
 	ILI9163C_writeParam(0x05);
 	nrf_delay_ms(10);

 	ILI9163C_writeCommand(CMD_SET_PIXEL_FORMAT);
 	ILI9163C_writeParam(0x05); // 16 bits per pixel

 	ILI9163C_writeCommand(CMD_SET_GAMMA_CURVE);
 	ILI9163C_writeParam(0x04); // Select gamma curve 3

 	ILI9163C_writeCommand(CMD_GAM_R_SEL);
 	ILI9163C_writeParam(0x01); // Gamma adjustment enabled

 //    ILI9163C_writeCommand(CMD_POSITIVE_GAMMA_CORRECT);
 //    ILI9163C_writeParam(0x3f); // 1st Parameter
 //    ILI9163C_writeParam(0x25); // 2nd Parameter
 //    ILI9163C_writeParam(0x1c); // 3rd Parameter
 //    ILI9163C_writeParam(0x1e); // 4th Parameter
 //    ILI9163C_writeParam(0x20); // 5th Parameter
 //    ILI9163C_writeParam(0x12); // 6th Parameter
 //    ILI9163C_writeParam(0x2a); // 7th Parameter
 //    ILI9163C_writeParam(0x90); // 8th Parameter
 //    ILI9163C_writeParam(0x24); // 9th Parameter
 //    ILI9163C_writeParam(0x11); // 10th Parameter
 //    ILI9163C_writeParam(0x00); // 11th Parameter
 //    ILI9163C_writeParam(0x00); // 12th Parameter
 //    ILI9163C_writeParam(0x00); // 13th Parameter
 //    ILI9163C_writeParam(0x00); // 14th Parameter
 //    ILI9163C_writeParam(0x00); // 15th Parameter
 //
 //    ILI9163C_writeCommand(CMD_NEGATIVE_GAMMA_CORRECT);
 //    ILI9163C_writeParam(0x20); // 1st Parameter
 //    ILI9163C_writeParam(0x20); // 2nd Parameter
 //    ILI9163C_writeParam(0x20); // 3rd Parameter
 //    ILI9163C_writeParam(0x20); // 4th Parameter
 //    ILI9163C_writeParam(0x05); // 5th Parameter
 //    ILI9163C_writeParam(0x00); // 6th Parameter
 //    ILI9163C_writeParam(0x15); // 7th Parameter
 //    ILI9163C_writeParam(0xa7); // 8th Parameter
 //    ILI9163C_writeParam(0x3d); // 9th Parameter
 //    ILI9163C_writeParam(0x18); // 10th Parameter
 //    ILI9163C_writeParam(0x25); // 11th Parameter
 //    ILI9163C_writeParam(0x2a); // 12th Parameter
 //    ILI9163C_writeParam(0x2b); // 13th Parameter
 //    ILI9163C_writeParam(0x2b); // 14th Parameter
 //    ILI9163C_writeParam(0x3a); // 15th Parameter

 	ILI9163C_writeCommand(CMD_FRAME_RATE_CONTROL1);
 #if 0
 	ILI9163C_writeParam(0x0e);
 	ILI9163C_writeParam(0x10);
 #else
 	ILI9163C_writeParam(0x08); // DIVA = 8
 //    ILI9163C_writeParam(0x08); // VPA = 8
 	ILI9163C_writeParam(0x02); // VPA = 8
 #endif

 	ILI9163C_writeCommand(CMD_DISPLAY_INVERSION);
 	ILI9163C_writeParam(0x07); // NLA = 1, NLB = 1, NLC = 1 (all on Frame Inversion)

 	ILI9163C_writeCommand(CMD_POWER_CONTROL1);
 	ILI9163C_writeParam(0x0a); // VRH = 10:  GVDD = 4.30
 	ILI9163C_writeParam(0x02); // VC = 2: VCI1 = 2.65

 	ILI9163C_writeCommand(CMD_POWER_CONTROL2);
 	ILI9163C_writeParam(0x02); // BT = 2: AVDD = 2xVCI1, VCL = -1xVCI1, VGH = 5xVCI1, VGL = -2xVCI1

 	ILI9163C_writeCommand(CMD_VCOM_CONTROL1);
 	ILI9163C_writeParam(0x50); // VMH = 80: VCOMH voltage = 4.5
 	ILI9163C_writeParam(0x5b); // VML = 91: VCOML voltage = -0.225

 	ILI9163C_writeCommand(CMD_VCOM_OFFSET_CONTROL);
 	ILI9163C_writeParam(0x40); // nVM = 0, VMF = 64: VCOMH output = VMH, VCOML output = VML

 	ILI9163C_writeCommand(CMD_SET_COLUMN_ADDRESS);
 	ILI9163C_writeParam(0x00); // XSH
 	ILI9163C_writeParam(0x00); // XSL
 	ILI9163C_writeParam(0x00); // XEH
 	ILI9163C_writeParam(0x7f); // XEL (128 pixels x)

 	ILI9163C_writeCommand(CMD_SET_PAGE_ADDRESS);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(0x7f); // 128 pixels y

 	int cspace = 1;
 	int ori = orient;
 	if(cspace < 1) {
 		//rgb
 		ori &= ~(1 << 3);  // bitClear(_Mactrl_Data,3);
 	} else {
 		//bgr
 		ori |= 1 << 3;     // bitSet(_Mactrl_Data,3);
 	}
 	// Select display orientation
 	ILI9163C_writeCommand(CMD_SET_ADDRESS_MODE);
 	ILI9163C_writeParam(ori);

 	// Set the display to on
 	ILI9163C_writeCommand(CMD_ENTER_NORMAL_MODE);
 	nrf_delay_ms(10);

 	// Set the display to on
 	ILI9163C_writeCommand(CMD_SET_DISPLAY_ON);
 	nrf_delay_ms(10);

 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	nrf_gpio_pin_set(csPin); // Disable CS

 }

 void ILI9163C_close() {
 	// Nothing
 }

 void ILI9163C_setColor(uint16_t c) {
 	currColor = c;
 }

 void ILI9163C_fillScreen(uint16_t c) {
 	ILI9163C_clearScreen(c);
 }

 uint16_t  ILI9163C_getWidth() {
 	return displayWidth;
 }

 uint16_t ILI9163C_getHeight() {
 	return displayHeight;
 }

 void ILI9163C_drawChar(uint16_t xPos, uint16_t yPos, uint8_t c, uint16_t fg, uint16_t bg)
 {
 	ILI9163C_drawGlyph((uint8_t) xPos, (uint8_t) yPos, font8x8_basic[c], rgb32To16(fg), rgb32To16(bg));
 }


 void ILI9163C_drawString(uint8_t x, uint8_t y, const char *str, uint16_t fg, uint16_t bg)
 {
 	ILI9163C_drawGlyphString((uint8_t) x, (uint8_t) y, font8x8_basic, str, fg, bg);
 }

 void ILI9163C_fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c)
 {
 	if(h > w) {
 	 	for(uint8_t i = 0; i < w; ++i) {
 	 		ILI9163C_drawVLine(x + i, y, h, c);
 	 	}
 	} else {
 	 	for(uint8_t i = 0; i < h; ++i) {
 	 		ILI9163C_drawHLine(x, y + i, w, c);
 	 	}
 	}
 }


 void ILI9163C_drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c)
 {
 	ILI9163C_drawHLine(x, y, w, c);
 	ILI9163C_drawHLine(x, y + h, w, c);

 	ILI9163C_drawVLine(x, y, h, c);
 	ILI9163C_drawVLine(x + w, y, h, c);

 }


 void ILI9163C_drawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t c)
 {
	 	nrf_gpio_pin_clear(csPin); // Enable CS

	 	ILI9163C_setUpdateWindow(x, y, x + w, y);

	 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

	 	uint16_t idx = 0;

	 	for(uint8_t i = 0; i < w; ++i) {
	 			buf[idx++] = c >> 8;
	 			buf[idx++] = c & 0xff;
	 	}

	 	nrf_gpio_pin_set(dcPin);

	 	ezSPIBulkWrite(buf, idx, NULL, 0);

	 	nrf_gpio_pin_set(csPin); // Disable CS
 }


 void ILI9163C_drawVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t c)
 {
 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(x, y, x, y + h);

 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	uint16_t idx = 0;

 	for(uint8_t i = 0; i < h; ++i) {
 			buf[idx++] = c >> 8;
 			buf[idx++] = c & 0xff;
 	}

 	nrf_gpio_pin_set(dcPin);

 	ezSPIBulkWrite(buf, idx, NULL, 0);

 	nrf_gpio_pin_set(csPin); // Disable CS
 }


 void ILI9163C_clearScreen(uint16_t color)
 {
 	for(uint16_t i = 0; i < lineBufferSize; i += 2) {
 		buf[i] = color >> 8;
 		buf[i + 1] = color & 0xff;
 	}

 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(0, 0, 127, 127);

 	// Plot the pixels
 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	nrf_gpio_pin_set(dcPin);

 	for(uint16_t i = 0; i < displayHeight; ++i) {
 		ezSPIBulkWrite(buf, lineBufferSize, NULL, 0);
 	}

 	nrf_gpio_pin_set(csPin); // Disable CS
 }

 void ILI9163C_clearRows(uint8_t startY, uint8_t endY, uint16_t color)
 {
 	for(uint16_t i = 0; i < lineBufferSize; i += 2) {
 		buf[i] = color >> 8;
 		buf[i + 1] = color & 0xff;
 	}

 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(0, startY, 127, endY);

 	// Plot the pixels
 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	nrf_gpio_pin_set(dcPin);

 	for(uint16_t i = startY; i < endY; ++i) {
 		ezSPIBulkWrite(buf, lineBufferSize, NULL, 0);
 	}

 	nrf_gpio_pin_set(csPin); // Disable CS

 }

 void ILI9163C_drawPoint(uint8_t x, uint8_t y, uint16_t color)
 {
 	nrf_gpio_pin_clear(csPin); // Enable CS
 	ILI9163C_setUpdateWindow(x, y, x, y);

 	// Draw the point
 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);
 	ILI9163C_writeColor(color);
 	nrf_gpio_pin_set(csPin); // Disable CS
 }

 void ILI9163C_drawGlyph(uint8_t x, uint8_t y, const uint8_t *glyph,
 		uint16_t fgColor, uint16_t bgColor)
 {
 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(x, y, x + 7, y + 7);

 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	uint8_t idx = 0;

 	// Plot the font data
 	for(uint8_t row = 0; row < 8; ++row) {
 		for(uint8_t col = 0; col < 8; ++col) {
 			uint16_t c = glyph[row] & (1 << col) ? fgColor : bgColor;

 			buf[idx++] = c >> 8;
 			buf[idx++] = c & 0xff;
 		}
 	}

 	nrf_gpio_pin_set(dcPin);

 	for(uint16_t i = 0; i < displayHeight; ++i) {
 		ezSPIBulkWrite(buf, idx, NULL, 0);
 	}

 	nrf_gpio_pin_set(csPin); // Disable CS
 }

 void ILI9163C_drawGlyph16(uint8_t x, uint8_t y, glyph g)
 {
 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(x, y, x + 15, y + 15);

 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	// Plot the font data
 	for(uint8_t row = 0; row < 16; ++row) {
 		for(uint8_t col = 0; col < 16; ++col) {
 			ILI9163C_writeColor(g.img[row][col]);
 		}
 	}
 	nrf_gpio_pin_set(csPin); // Disable CS
 }

 void ILI9163C_drawGlyphString(uint8_t x, uint8_t y, const uint8_t glyphs[][8],
 		const char *str, uint16_t fgColor, uint16_t bgColor)
 {
	 uint16_t len = strlen(str); //todo clip length

	 if(len > displayWidth / 8) {
		len = displayWidth / 8;
	 }

	nrf_gpio_pin_clear(csPin); // Enable CS

	ILI9163C_setUpdateWindow(x, y, x + len * 8, y + 7);
	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	nrf_gpio_pin_set(dcPin);


	for(uint8_t row = 0; row < 8; ++row) {
		uint16_t idx = 0;
		const char     *s = str;

		ILI9163C_setUpdateWindow(x, y + row, x + len * 8, y + row);
		ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

	 	nrf_gpio_pin_set(dcPin);

		for(uint8_t col = 0; col < len; ++col) {
			const uint8_t *g = glyphs[(int) *s];
			uint8_t        gRow = g[row];

			for(uint8_t bit = 0; bit < 8; ++bit) {
				uint16_t c = gRow & (1 << bit) ? fgColor : bgColor;

				buf[idx++] = c >> 8;
				buf[idx++] = c & 0xff;

			}
 			++s;
		}

	 	ezSPIBulkWrite(buf, idx, NULL, 0);
	}

 	nrf_gpio_pin_set(csPin); // Disable CS
 }


void ILI9163C_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_int16_t(x0, y0);
		_swap_int16_t(x1, y1);
	}

	if (x0 > x1) {
		_swap_int16_t(x0, x1);
		_swap_int16_t(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			ILI9163C_drawPoint(y0, x0, color);
		} else {
			ILI9163C_drawPoint(x0, y0, color);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}


void ILI9163C_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	ILI9163C_drawPoint(x0  , y0+r, color);
	ILI9163C_drawPoint(x0  , y0-r, color);
	ILI9163C_drawPoint(x0+r, y0  , color);
	ILI9163C_drawPoint(x0-r, y0  , color);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}

		x++;
		ddF_x += 2;
		f += ddF_x;

		ILI9163C_drawPoint(x0 + x, y0 + y, color);
		ILI9163C_drawPoint(x0 - x, y0 + y, color);
		ILI9163C_drawPoint(x0 + x, y0 - y, color);
		ILI9163C_drawPoint(x0 - x, y0 - y, color);
		ILI9163C_drawPoint(x0 + y, y0 + x, color);
		ILI9163C_drawPoint(x0 - y, y0 + x, color);
		ILI9163C_drawPoint(x0 + y, y0 - x, color);
		ILI9163C_drawPoint(x0 - y, y0 - x, color);
	}
}


void ILI9163C_drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
        	ILI9163C_drawPoint(x0 + x, y0 + y, color);
        	ILI9163C_drawPoint(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
        	ILI9163C_drawPoint(x0 + x, y0 - y, color);
        	ILI9163C_drawPoint(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
        	ILI9163C_drawPoint(x0 - y, y0 + x, color);
        	ILI9163C_drawPoint(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
        	ILI9163C_drawPoint(x0 - y, y0 - x, color);
        	ILI9163C_drawPoint(x0 - x, y0 - y, color);
        }
    }
}


void ILI9163C_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color)
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
    int16_t px    = x;
    int16_t py    = y;

    delta++; // Avoid some +1's in the loop

    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if(x < (y + 1)) {
            if(corners & 1) ILI9163C_drawVLine(x0+x, y0-y, 2*y+delta, color);
            if(corners & 2) ILI9163C_drawVLine(x0-x, y0-y, 2*y+delta, color);
        }
        if(y != py) {
            if(corners & 1) ILI9163C_drawVLine(x0+py, y0-px, 2*px+delta, color);
            if(corners & 2) ILI9163C_drawVLine(x0-py, y0-px, 2*px+delta, color);
            py = y;
        }
        px = x;
    }
}


void ILI9163C_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	ILI9163C_drawVLine(x0, y0-r, 2*r+1, color);
    ILI9163C_fillCircleHelper(x0, y0, r, 3, 0, color);
}



void IILI9163C_drawBufOnLine(uint8_t x, uint8_t y, uint8_t w)
{
 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(x, y, x + w, y);

 	ezSPIBulkWrite(buf, w, NULL, 0);

 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	nrf_gpio_pin_set(csPin); // Disable CS
}


 void ILI9163C_drawImage(const uint8_t *img)
 {
 	nrf_gpio_pin_clear(csPin); // Enable CS

 	ILI9163C_setUpdateWindow(0, 0, 127, 127);

 	// Plot the pixels
 	ILI9163C_writeCommand(CMD_WRITE_MEMORY_START);

 	nrf_gpio_pin_set(dcPin);

 	ezSPIBulkWrite((uint8_t *) img, displayWidth * 2 * displayHeight, NULL, 0);
// 	for(uint16_t i = 0; i < displayHeight * displayWidth * 2; ++i) {
// 		ezSPIWrite(img[i]);
// 	}

 	nrf_gpio_pin_set(csPin); // Disable CS
 }

 void ILI9163C_reset(void)
 {
 	nrf_gpio_pin_clear(rstPin);
 	nrf_delay_ms(50);

 	nrf_gpio_pin_set(rstPin);
 	nrf_delay_ms(120);
 }

 void ILI9163C_writeCommand(uint8_t cmd)
 {
 	nrf_gpio_pin_clear(dcPin);

 	ezSPIWrite(cmd);
 }

 void ILI9163C_writeParam(uint8_t param)
 {
 	nrf_gpio_pin_set(dcPin);

 	ezSPIWrite(param);
 }

 void ILI9163C_writeColor(uint16_t color)
 {
 	nrf_gpio_pin_set(dcPin);

 	ezSPIWrite(color >> 8);
 	ezSPIWrite(color);
 }

 void ILI9163C_setUpdateWindow(uint8_t startX, uint8_t startY, uint8_t endX,
 		uint8_t endY)
 {
#if 1
	nrf_gpio_pin_clear(dcPin);

 	// Set the X Bounds
 	ILI9163C_writeCommand(CMD_SET_COLUMN_ADDRESS);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(startX + 2);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(endX + 2);

 	// Set the Y Bounds
 	ILI9163C_writeCommand(CMD_SET_PAGE_ADDRESS);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(startY + 3);
 	ILI9163C_writeParam(0x00);
 	ILI9163C_writeParam(endY + 3);
#else
	nrf_gpio_pin_clear(dcPin);
	uint8_t bPos = 0;

 	// Set the X Bounds
 	buf[bPos++] = CMD_SET_COLUMN_ADDRESS;
 	buf[bPos++] = 0x00;
 	buf[bPos++] = startX + 2;
 	buf[bPos++] = 0x00;
 	buf[bPos++] = endX + 2;

 	// Set the Y Bounds
 	buf[bPos++] = CMD_SET_PAGE_ADDRESS;
 	buf[bPos++] = 0x00;
 	buf[bPos++] = startY + 3;
 	buf[bPos++] = 0x00;
 	buf[bPos++] = endY + 3;

 	ezSPIBulkWrite(buf, bPos, NULL, 0);
#endif
 }



