#include <pebble.h>
#include <stdio.h>

static Window* MWindows;
TextLayer* TLayer;

static void UpdateTime()
{
  time_t temp = time(NULL);
  struct tm* TickTime = localtime(&temp);
  
  static char buffer[8];
  strftime(buffer, sizeof(buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", TickTime);
  
  printf("%s", buffer);
}

static void tick_handler(struct tm* UpTime, TimeUnits Units)
{
  UpdateTime();
}

static void main_window_load(Window* MWindows)
{
  Layer *Wlayer = window_get_root_layer(MWindows);
  GRect bounds = layer_get_bounds(Wlayer);
  
  TLayer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));
  
  text_layer_set_background_color(TLayer, GColorRed);                             // Dit quel couleur de fond on veut params : Le Layer en question & la couleur que l'on veut.
  text_layer_set_text_color(TLayer, GColorBlack);                                 // Dit quel couleur de texte on veut params : Le Layer en question & la couleur que l'on veut.
  //text_layer_set_text(TLayer, "00:00");                                         // Dit quel text on veut.
  text_layer_set_font(TLayer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));  // Dit quel police d'écriture ont veux params : Le Layer & Le code de la police.
  text_layer_set_text_alignment(TLayer, GTextAlignmentCenter);
  
  layer_add_child(Wlayer, text_layer_get_layer(TLayer));
}

static void main_window_unload(Window* MWindows)
{
  text_layer_destroy(TLayer);
}

static void init()
{
  MWindows = window_create(); //créer la fenètre.
  
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler); //Met à jours le temps;
  
    window_set_window_handlers(MWindows, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(MWindows, true);
  UpdateTime();
}


static void deinit()
{
  window_destroy(MWindows);
}

int main()
{
  init();
  app_event_loop();
}

/*
#include "Functions.h"

static Window* MWindows;
Layer* TLayer;
char* BinTime;

void DrawCircle(Layer* TLayer, GContext* ctx)
{
  int XBase;
  int YBase;
  int Radius;
  int i;
  
  i = 0;
  XBase = 30;
  YBase = 120;
  Radius = 10;   
  
  //Couleur
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorWhite);
  
  //Traits du milieu
  graphics_draw_line(ctx, GPoint(XBase + 40, YBase + Radius), GPoint(XBase + 40, YBase - 85));
  graphics_draw_line(ctx, GPoint(XBase + 41, YBase + Radius), GPoint(XBase + 41, YBase - 85));
  
  //Affichage de l'heure
  while (i <= 16)
  {
    if (i != 8 && i != 12 && i != 2 && i != 3)
    {
      if(BinTime[i] == '0')
        graphics_draw_circle(ctx, GPoint(XBase, YBase), Radius);
      else
        graphics_fill_circle(ctx, GPoint(XBase, YBase), Radius);
      if (i == 1 || i == 7 || i == 11)
      {
        XBase += Radius + 15;
        if (i == 7)
          XBase += 5;
        YBase = 120;
      }
      else
      {
        YBase -= Radius + 15;
      }
    }
    i++;
  }
}

static void UpdateTime()
{
  time_t temp = time(NULL);
  struct tm* TickTime = localtime(&temp);
  
  static char buffer[8];
  strftime(buffer, sizeof(buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", TickTime);
  
  BinTime = conversion(buffer);
  layer_mark_dirty(TLayer);
}

static void tick_handler(struct tm* UpTime, TimeUnits Units)
{
  UpdateTime();
}

static void main_window_load(Window* MWindows)
{
  Layer *Wlayer = window_get_root_layer(MWindows);
  TLayer = layer_create(GRect(0, 0, 500, 500));
  window_set_background_color(MWindows, GColorBlack);
  layer_set_update_proc(TLayer, DrawCircle);
  
  layer_add_child(Wlayer, TLayer);
}

static void main_window_unload(Window* MWindows)
{
  layer_destroy(TLayer);
}

static void init()
{
  MWindows = window_create(); //créer la fenètre.
  
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
    window_set_window_handlers(MWindows, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(MWindows, true);
  UpdateTime(); //Met à jours le temps;
}


static void deinit()
{
  window_destroy(MWindows);
}

int main()
{
  init();
  app_event_loop();
}
*/
