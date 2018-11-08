#include <SDL.h>
#include "cairo.h"
#include <string>

#define APP_SDL_WINDOW_WIDTH 800
#define APP_SDL_WINDOW_HEIGHT 600
#define APP_SDL_WINDOW_NAME "SDL2Test"
#define APP_SDL_WINDOW_FLAGS 0
static void print_text(cairo_t *cr);
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

	cairo_surface_t *cairosurf = cairo_image_surface_create_for_data(
		(uint8_t*) surface->pixels,
		CAIRO_FORMAT_RGB24,
		surface->w,
		surface->h,
		surface->pitch);

	cairo_t *cr = cairo_create(cairosurf);
	print_text(cr);



	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);

	SDL_Delay(3000);
	cairo_destroy(cr);
	cairo_surface_destroy(cairosurf);

	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

static void paint_background(cairo_t *cr)
{
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);
}

static void paint_rosace(cairo_t *cr)
{
	cairo_set_source_rgb(cr, 0, 0, 0);
	for (int i = 0; i <= 10000; i++) {
		double x = 200 + cos(2 * M_PI * i / 500) * 70 + cos(2 * M_PI * i / 10000) * 110;
		double y = 200 + sin(2 * M_PI * i / 500) * 70 + sin(2 * M_PI * i / 10000) * 110;
		if (i == 0)
			cairo_move_to(cr, x, y);
		else
			cairo_line_to(cr, x, y);
	}
	cairo_close_path(cr);
	cairo_stroke(cr);
}


static void print_text(cairo_t *cr)
{
	cairo_set_source_rgb(cr, 1, 1, 1);

	cairo_select_font_face(cr, "Old English Text MT",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_font_size(cr, 30);

	cairo_move_to(cr, 20, 30);
	cairo_show_text(cr, "Most relationships seem so transitory");
	cairo_move_to(cr, 20, 60);
	cairo_show_text(cr, "They're all good but not the permanent one");

	cairo_move_to(cr, 20, 120);
	cairo_show_text(cr, "Who doesn't long for someone to hold");

	cairo_move_to(cr, 20, 150);
	cairo_show_text(cr, "Who knows how to love you without being told");
	cairo_move_to(cr, 20, 180);
	cairo_show_text(cr, "Somebody tell me why I'm on my own");
	cairo_move_to(cr, 20, 210);
	cairo_show_text(cr, "If there's a soulmate for everyone");
}