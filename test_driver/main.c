#include "m88.h"
#include <stdint.h>

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SCLK_PIN PINB5
#define MOSI_PIN PINB3
#define CSEL_PIN PINB2

void spi_init(void);
void spi_send(uint8_t byte);
void spi_send_buf(uint8_t *buf, uint16_t len);

void vga_set_xy(uint8_t x, uint8_t y);
void vga_write(uint8_t pixel);

uint8_t pttn[4] = { 0x0, 0x2, 0x1, 0x3 };

uint8_t tiles[12][8];

#define COL(C0, C1, C2, C3) ((C3<<6) | (C2<<4) | (C1<<2) | (C0<<0))

uint8_t font[60] = 
{
	COL(0, 1, 0, 0), COL(1, 0, 1, 0), COL(1, 0, 1, 0), COL(1, 0, 1, 0), COL(0, 1, 0, 0), COL(0, 0, 0, 0),
	COL(0, 1, 0, 0), COL(0, 1, 0, 0), COL(0, 1, 0, 0), COL(0, 1, 0, 0), COL(0, 1, 0, 0), COL(0, 0, 0, 0),
	COL(2, 1, 0, 0), COL(0, 0, 1, 0), COL(0, 1, 0, 0), COL(1, 0, 0, 0), COL(1, 1, 1, 0), COL(0, 0, 0, 0),
	COL(2, 1, 0, 0), COL(0, 0, 1, 0), COL(0, 1, 0, 0), COL(0, 0, 1, 0), COL(2, 1, 0, 0), COL(0, 0, 0, 0),
	COL(0, 1, 0, 0), COL(2, 1, 0, 0), COL(1, 0, 0, 0), COL(1, 1, 1, 0), COL(0, 1, 0, 0), COL(0, 0, 0, 0),
	COL(1, 1, 1, 0), COL(1, 0, 0, 0), COL(1, 1, 0, 0), COL(0, 0, 1, 0), COL(1, 1, 0, 0), COL(0, 0, 0, 0),
	COL(0, 1, 2, 0), COL(1, 0, 0, 0), COL(2, 1, 0, 0), COL(1, 0, 1, 0), COL(0, 1, 0, 0), COL(0, 0, 0, 0),
	COL(1, 1, 1, 0), COL(0, 0, 1, 0), COL(0, 2, 1, 0), COL(0, 1, 0, 0), COL(0, 1, 0, 0), COL(0, 0, 0, 0),
	COL(0, 1, 0, 0), COL(1, 0, 1, 0), COL(2, 1, 2, 0), COL(1, 0, 1, 0), COL(0, 1, 0, 0), COL(0, 0, 0, 0),
	COL(0, 1, 0, 0), COL(1, 0, 1, 0), COL(0, 1, 2, 0), COL(0, 0, 1, 0), COL(2, 1, 0, 0), COL(0, 0, 0, 0)
};

uint8_t lut[4] = { 0x00, 0x04, 0x08, 0x03 }; 

#define DIG(N, I) (((N)>>((I)<<2)) & 0xf)
#define DIG_LUT(N) ((N) > 5 ? (N) - 3 : (N))

void digit_write(uint8_t dig, uint8_t x, uint8_t y);

uint16_t to_bcd(uint16_t dec);

int
main(void)
{
	uint8_t col = 0;

	spi_init();

	for (uint8_t y = 0; y < 120; y++)
	{
		vga_set_xy(0, y);
		vga_write(0x00);

		for (uint8_t x = 0; x < 160; x++) vga_write(0x00);

		vga_write(0x00);
	}

	for (uint8_t row = 0; row < 4; row++)
	{
		for (uint8_t y = 0; y < 8; y++) 
		{
			vga_set_xy(4, 4 + y + row * 8);
			vga_write(0x00);

			for (uint8_t bar = 0; bar < 16; bar++)
			{
				uint8_t rc = (bar & 0x3)>>0;
				uint8_t gc = (bar & 0xc)>>2;
				col = (pttn[row]<<4) | (pttn[gc]<<2) | (pttn[rc]<<0);
				for (uint8_t x = 0; x < 8; x++) vga_write(col);
			}
			
			vga_write(0x00);
		}
	}

	

	for (uint8_t y = 0; y < 5; y++)
	{
		vga_set_xy(24, y + 58);
		vga_write(lut[0]);
		vga_write(lut[1]);

		for (uint8_t x = 0; x < 14 + y; x++)
		{
			vga_write(lut[y == 0]);
		}

		vga_write(lut[1]);
		vga_write(lut[2]);
	}

	for (uint8_t y = 0; y < 4; y++)
	{
		vga_set_xy(24, 66 - y);
		vga_write(lut[0]);
		vga_write(lut[1]);

		for (uint8_t x = 0; x < 14 + y; x++)
		{
			vga_write(lut[y == 0]);
		}

		vga_write(lut[1]);
		vga_write(lut[2]);
	}

	uint16_t hud_val = 60;
	uint16_t hud_val_bcd = to_bcd(hud_val);

	uint8_t cnt = 0;
	uint8_t accel = 1;

	// hud
	for (;;)
	{
		uint16_t hud_dig = hud_val_bcd;
		uint8_t x = 24;
		
		uint8_t last_dig = DIG_LUT((hud_dig & 0xf));
		uint8_t bar = 4 - (last_dig >= 5 ? last_dig - 5 : last_dig);
		for (uint8_t y = 41; y < 84; y++)
		{
			vga_set_xy(45, y);
			vga_write(0x00);

			for (uint8_t x = 0; x < 4; x++)
			{
				vga_write(lut[bar == 0]);
			}

			if (bar < 4) bar++;
			else bar = 0;

			vga_write(0x00);
		}

		uint8_t dig;
		uint8_t pad = 1;
		for (uint8_t i = 0; i < 3; i++) 
		{
			x += 4;
			hud_dig <<= 4;
			dig = DIG_LUT((hud_dig & 0xf000) >> 12);
			if (pad && dig > 0) pad = 0;
			if (!pad) digit_write(dig, x, 60);
		}

		if (cnt == 0)
		{
			hud_val += accel;
			hud_val_bcd = to_bcd(hud_val);
		}

		// hud test code
		if (hud_val >= 85 && hud_val < 120) accel = 2;
		if (hud_val >= 120 && hud_val < 432) accel = 3;
		if (hud_val >= 432 && hud_val < 476) accel = 2;
		if (hud_val >= 476 && hud_val < 511) accel = 1;
		if (hud_val >= 511) accel = 0;

		cnt = (cnt + 1) & 0x3;
	}

	return 0;
}

void
spi_init(void)
{
	SPI_DDR = MOSI_PIN | SCLK_PIN | CSEL_PIN;
	SPI_PORT |= CSEL_PIN;
	SPCR = SPE | MSTR | SPR0;
}

void
spi_send(uint8_t byte)
{
	SPI_PORT &= ~CSEL_PIN;
	SPDR = byte;
	while (!(SPSR & SPIF));
	SPI_PORT |= CSEL_PIN;
}

void
spi_send_buf(uint8_t *buf, uint16_t len)
{
	uint8_t *buf_end = buf + len;
	uint8_t *byte;
	for (byte = buf; byte < buf_end; byte++)
		spi_send(*byte);
}

void 
vga_set_xy(uint8_t x, uint8_t y)
{
	spi_send(0x11);
	spi_send(x);
	spi_send(y);
}

void 
vga_write(uint8_t pixel)
{
	spi_send(0x20);
	spi_send(pixel);
}

void 
digit_write(uint8_t dig, uint8_t x, uint8_t y)
{
	uint8_t offset = (dig<<2) + (dig<<1);
	uint8_t *dig_pix = font + offset;
	for (uint8_t row = 0; row < 6; row++)
	{
		vga_set_xy(x, y + row);
		vga_write(0x00);
		
		uint8_t row_pix = *(dig_pix + row);
		uint8_t pix;

		for (uint8_t col = 0; col < 3; col++)
		{
			pix = (row_pix & 0x3);
			row_pix >>= 2;
			vga_write(lut[pix]);
		}
	}
}

uint16_t
to_bcd(uint16_t dec)
{
	uint16_t bcd = 0;
		
	uint16_t dec_mask = 0x8000;
	
	for (uint8_t i = 0; i < 16; i++)
	{
		bcd <<= 1;
		if (dec & dec_mask) bcd |= 0x1;
		dec <<= 1;

		uint8_t bcd_mask = 0xf;
		uint8_t bcd_thrs = 0x4;
		uint8_t bcd_add = 0x3;
		for (uint8_t j = 0; j < 4; j++)
		{
			if ((bcd & bcd_mask) > bcd_thrs) bcd += bcd_add;
			bcd_mask <<= 4;
			bcd_thrs <<= 4;
			bcd_add <<= 4;
		}
	}

	return bcd;
}
