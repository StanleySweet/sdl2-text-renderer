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

#include "main.h"
#include <locale>
#include <codecvt>
void cairo_print_image_atlas(SDL_Surface *surface, SDL_Window *window);
int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
		APP_SDL_WINDOW_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		APP_SDL_WINDOW_WIDTH,
		APP_SDL_WINDOW_HEIGHT,
		APP_SDL_WINDOW_FLAGS
	);

	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	cairo_print_image_atlas(surface, window);
	SDL_Delay(3000);
	SDL_FillRect(surface, nullptr, 0x000000);
	cairo_text_render(surface, window);
	freetype_text_render(surface, window);
	SDL_Delay(3000);

	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


static void cairo_print_image_atlas(SDL_Surface *surface, SDL_Window *window)
{
	cairo_surface_t *cairosurf = cairo_image_surface_create_for_data(
		static_cast<uint8_t*>(surface->pixels),
		CAIRO_FORMAT_RGB24,
		surface->w,
		surface->h,
		surface->pitch);

	int fontSize = 10;
	cairo_t *cr = cairo_create(cairosurf);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_select_font_face(cr, "DejaVu Sans Mono", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, fontSize);

	int start = 0x20;
	int numberOfCharsPerLine = static_cast<int>(APP_SDL_WINDOW_WIDTH / fontSize * 1.55);
	std::wstring line = L"";
	for (int i = start; i < 0xFFFE; ++i)
	{
		if (0 != (i - start) % numberOfCharsPerLine)
		{
			line += static_cast<wchar_t>(i);
		}
		else if(line.length() != 0)
		{
			float valeur = ((i - start) / numberOfCharsPerLine * 15);
			using convert_type = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_type, wchar_t> converter;

			//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
			std::string converted_str = converter.to_bytes(line);
			cairo_print_text(cr, 0, valeur, converted_str.c_str());
			SDL_UpdateWindowSurface(window);
			line.clear();
		}
	}
	cairo_surface_write_to_png(cairosurf, "file.png");
	cairo_destroy(cr);
	cairo_surface_destroy(cairosurf);
}

static void cairo_text_render(SDL_Surface *surface, SDL_Window *window)
{
	cairo_surface_t *cairosurf = cairo_image_surface_create_for_data(
		static_cast<uint8_t*>(surface->pixels),
		CAIRO_FORMAT_RGB24,
		surface->w,
		surface->h,
		surface->pitch);

	cairo_t *cr = cairo_create(cairosurf);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_select_font_face(cr, "Old English Text MT", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 30);

	cairo_print_text(cr, 20, 330, "Most relationships seem so transitory");
	cairo_print_text(cr, 20, 360, "They're all good but not the permanent one");
	cairo_print_text(cr, 20, 420, "Who doesn't long for someone to hold");
	cairo_print_text(cr, 20, 450, "Who knows how to love you without being told");
	cairo_print_text(cr, 20, 480, "Somebody tell me why I'm on my own");
	cairo_print_text(cr, 20, 510, "If there's a soulmate for everyone");

	SDL_UpdateWindowSurface(window);
	cairo_destroy(cr);
	cairo_surface_destroy(cairosurf);
}

static void cairo_print_text(cairo_t *cr, double x, double y, const char *utf8)
{
	cairo_move_to(cr, x, y);
	cairo_show_text(cr, utf8);
}

static void freetype_print_image_atlas(SDL_Surface *surface, SDL_Window *window)
{
	FT_Library ftLib;
	FT_Bitmap ftTarget;
	FT_Face ftFace;
	FT_Init_FreeType(&ftLib);
	FT_New_Face(ftLib, "C:\\Windows\\Fonts\\OLDENGL.ttf", 0, &ftFace);
	FT_Set_Char_Size(ftFace, 30 << 6, 30 << 6, 72, 72);
}

static void freetype_text_render(SDL_Surface *surface, SDL_Window *window)
{
	FT_Library ftLib;
	FT_Bitmap ftTarget;
	FT_Face ftFace;
	FT_Init_FreeType(&ftLib);
	FT_New_Face(ftLib, "C:\\Windows\\Fonts\\OLDENGL.ttf", 0, &ftFace);
	FT_Set_Char_Size(ftFace, 30 << 6, 30 << 6, 72, 72);

	// Draw text
	freetype_print_text(ftFace, surface, 20, 30, "Most relationships seem so transitory");
	freetype_print_text(ftFace, surface, 20, 60, "They're all good but not the permanent one");
	freetype_print_text(ftFace, surface, 20, 120, "Who doesn't long for someone to hold");
	freetype_print_text(ftFace, surface, 20, 150, "Who knows how to love you without being told");
	freetype_print_text(ftFace, surface, 20, 180, "Somebody tell me why I'm on my own");
	freetype_print_text(ftFace, surface, 20, 210, "If there's a soulmate for everyone");

	SDL_UpdateWindowSurface(window);
	FT_Done_Face(ftFace);
	FT_Done_FreeType(ftLib);
}

static void freetype_print_text(const FT_Face &ftFace, SDL_Surface *surface, int x, int y, const char *text)
{
	for (int n = 0; n < strlen(text); ++n)
	{
		FT_Load_Char(ftFace, text[n], FT_LOAD_RENDER);

		freetype_draw_glyph(surface, ftFace->glyph->bitmap, x + ftFace->glyph->bitmap_left, y - ftFace->glyph->bitmap_top);

		x += ftFace->glyph->advance.x >> 6;
		y += ftFace->glyph->advance.y >> 6;
	}
}

static void freetype_draw_glyph(SDL_Surface *surface, FT_Bitmap bm, int x, int y)
{
	SDL_Surface* glyph = SDL_CreateRGBSurfaceFrom(bm.buffer, static_cast<int>(bm.width), static_cast<int>(bm.rows), 8, bm.pitch, 0, 0, 0, 0xFF);

	SDL_Color colors[256];
	for (int i = 0; i < 256; ++i)
	{
		colors[i].r = colors[i].g = colors[i].b = i;
	}
	SDL_SetPaletteColors(glyph->format->palette, colors, 0, 256);

	SDL_SetSurfaceBlendMode(glyph, SDL_BlendMode::SDL_BLENDMODE_NONE);
	SDL_Rect dest = { x, y, 0, 0 };
	SDL_BlitSurface(glyph, nullptr, surface, &dest);
	SDL_FreeSurface(glyph);
}
