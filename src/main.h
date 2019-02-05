/**
 * Copyright (c) 2018 Stanislas Dolcini. 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#include <SDL.h>
#include <ft2build.h>
#include <cairo.h>
#include <iostream>
#include <string>

#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_OUTLINE_H

#define APP_SDL_WINDOW_WIDTH 1024			
#define APP_SDL_WINDOW_HEIGHT 1024
#define APP_SDL_WINDOW_NAME "SDL2Test"
#define APP_SDL_WINDOW_FLAGS 0

#ifndef main_h
static void cairo_text_render(SDL_Surface *surface, SDL_Window *window);
static void cairo_print_text(cairo_t *cr, double x, double y, const char *utf8);
static void freetype_draw_glyph(SDL_Surface *surface, FT_Bitmap bm, int x, int y);
static void freetype_text_render(SDL_Surface *surface, SDL_Window *window);
static void freetype_print_text(const FT_Face &ftFace, SDL_Surface *surface, int x, int y, const char *utf8);
#endif // !main_h


