/** 
 * 8x8 monochrome bitmap fonts for rendering
 * Author: Daniel Hepper <daniel AT hepper.net>
 * 
 * License: Public Domain
 * 
 * Based on:
 * // Summary: font8x8.h
 * // 8x8 monochrome bitmap fonts for rendering
 * //
 * // Author:
 * //     Marcel Sondaar
 * //     International Business Machines (public domain VGA fonts)
 * //
 * // License:
 * //     Public Domain
 * 
 * Fetched from: http://dimensionalrift.homelinux.net/combuster/mos3/?p=viewsource&file=/modules/gfx/font8_8.asm
 **/

// Constant: font8x8_0390
// Contains an 8x8 font map for unicode points U+0390 - U+03C9 (greek characters)
static const uint8_t font8x8_greek[58][8] = {
    { 0x2D, 0x00, 0x0C, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+0390 (iota with tonos and diaeresis)
    { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0391 (Alpha)
    { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},   // U+0392 (Beta)
    { 0x3F, 0x33, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00},   // U+0393 (Gamma)
    { 0x08, 0x1C, 0x1C, 0x36, 0x36, 0x63, 0x7F, 0x00},   // U+0394 (Delta)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},   // U+0395 (Epsilon)
    { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},   // U+0396 (Zeta)
    { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},   // U+0397 (Eta)
    { 0x1C, 0x36, 0x63, 0x7F, 0x63, 0x36, 0x1C, 0x00},   // U+0398 (Theta)
    { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0399 (Iota)
    { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},   // U+039A (Kappa)
    { 0x08, 0x1C, 0x1C, 0x36, 0x36, 0x63, 0x63, 0x00},   // U+039B (Lambda)
    { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},   // U+039C (Mu)
    { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},   // U+039D (Nu)
    { 0x7F, 0x63, 0x00, 0x3E, 0x00, 0x63, 0x7F, 0x00},   // U+039E (Xi)
    { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},   // U+039F (Omikron)
    { 0x7F, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x00},   // U+03A0 (Pi)
    { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},   // U+03A1 (Rho)
    { 0x00, 0x01, 0x02, 0x04, 0x4F, 0x90, 0xA0, 0x40},   // U+03A2
    { 0x7F, 0x63, 0x06, 0x0C, 0x06, 0x63, 0x7F, 0x00},   // U+03A3 (Sigma 2)
    { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+03A4 (Tau)
    { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},   // U+03A5 (Upsilon)
    { 0x18, 0x7E, 0xDB, 0xDB, 0xDB, 0x7E, 0x18, 0x00},   // U+03A6 (Phi)
    { 0x63, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x63, 0x00},   // U+03A7 (Chi)
    { 0xDB, 0xDB, 0xDB, 0x7E, 0x18, 0x18, 0x3C, 0x00},   // U+03A8 (Psi)
    { 0x3E, 0x63, 0x63, 0x63, 0x36, 0x36, 0x77, 0x00},   // U+03A9 (Omega)
    { 0x33, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},   // U+0399 (Iota with diaeresis)
    { 0x33, 0x00, 0x33, 0x33, 0x1E, 0x0C, 0x1E, 0x00},   // U+03A5 (Upsilon with diaeresis)
    { 0x70, 0x00, 0x6E, 0x3B, 0x13, 0x3B, 0x6E, 0x00},   // U+03AC (alpha aigu)
    { 0x38, 0x00, 0x1E, 0x03, 0x0E, 0x03, 0x1E, 0x00},   // U+03AD (epsilon aigu)
    { 0x38, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x30},   // U+03AE (eta aigu)
    { 0x38, 0x00, 0x0C, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+03AF (iota aigu)
    { 0x2D, 0x00, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+03B0 (upsilon with tonos and diaeresis)
    { 0x00, 0x00, 0x6E, 0x3B, 0x13, 0x3B, 0x6E, 0x00},   // U+03B1 (alpha)
    { 0x00, 0x1E, 0x33, 0x1F, 0x33, 0x1F, 0x03, 0x03},   // U+03B2 (beta)
    { 0x00, 0x00, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x00},   // U+03B3 (gamma)
    { 0x38, 0x0C, 0x18, 0x3E, 0x33, 0x33, 0x1E, 0x00},   // U+03B4 (delta)
    { 0x00, 0x00, 0x1E, 0x03, 0x0E, 0x03, 0x1E, 0x00},   // U+03B5 (epsilon)
    { 0x00, 0x3F, 0x06, 0x03, 0x03, 0x1E, 0x30, 0x1C},   // U+03B6 (zeta)
    { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x30},   // U+03B7 (eta)
    { 0x00, 0x00, 0x1E, 0x33, 0x3F, 0x33, 0x1E, 0x00},   // U+03B8 (theta)
    { 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x2C, 0x18, 0x00},   // U+03B9 (iota)
    { 0x00, 0x00, 0x33, 0x1B, 0x0F, 0x1B, 0x33, 0x00},   // U+03BA (kappa)
    { 0x00, 0x03, 0x06, 0x0C, 0x1C, 0x36, 0x63, 0x00},   // U+03BB (lambda)
    { 0x00, 0x00, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x03},   // U+03BC (mu)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},   // U+03BD (nu)
    { 0x1E, 0x03, 0x0E, 0x03, 0x03, 0x1E, 0x30, 0x1C},   // U+03BE (xi)
    { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+03BF (omikron)
    { 0x00, 0x00, 0x7F, 0x36, 0x36, 0x36, 0x36, 0x00},   // U+03C0 (pi)
    { 0x00, 0x00, 0x3C, 0x66, 0x66, 0x36, 0x06, 0x06},   // U+03C1 (rho)
    { 0x00, 0x00, 0x3E, 0x03, 0x03, 0x1E, 0x30, 0x1C},   // U+03C2 (sigma 1)
    { 0x00, 0x00, 0x7E, 0x1B, 0x1B, 0x1B, 0x0E, 0x00},   // U+03C3 (sigma 2)
    { 0x00, 0x00, 0x7E, 0x18, 0x18, 0x58, 0x30, 0x00},   // U+03C4 (tau)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x00},   // U+03C5 (upsilon)
    { 0x00, 0x00, 0x76, 0xDB, 0xDB, 0x7E, 0x18, 0x00},   // U+03C6 (phi)
    { 0x00, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},   // U+03C7 (chi)
    { 0x00, 0x00, 0xDB, 0xDB, 0xDB, 0x7E, 0x18, 0x00},   // U+03C8 (psi)
    { 0x00, 0x00, 0x36, 0x63, 0x6B, 0x7F, 0x36, 0x00}    // U+03C9 (omega)
};
