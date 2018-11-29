
#include "main.h"

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


	cairo_text_render(surface, window);
	freetype_text_render(surface, window);
	SDL_Delay(3000);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
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
