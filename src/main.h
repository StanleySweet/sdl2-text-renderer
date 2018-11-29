#include <SDL.h>
#include <ft2build.h>
#include <cairo.h>
#include <string>

#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_OUTLINE_H

#define APP_SDL_WINDOW_WIDTH 800
#define APP_SDL_WINDOW_HEIGHT 600
#define APP_SDL_WINDOW_NAME "SDL2Test"
#define APP_SDL_WINDOW_FLAGS 0

#ifndef main_h
static void cairo_text_render(SDL_Surface *surface, SDL_Window *window);
static void cairo_print_text(cairo_t *cr, double x, double y, const char *utf8);
static void freetype_draw_glyph(SDL_Surface *surface, FT_Bitmap bm, int x, int y);
static void freetype_text_render(SDL_Surface *surface, SDL_Window *window);
static void freetype_print_text(const FT_Face &ftFace, SDL_Surface *surface, int x, int y, const char *utf8);
#endif // !main_h


