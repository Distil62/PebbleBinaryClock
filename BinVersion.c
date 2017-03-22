#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>

static Window* MWindows;
TextLayer* TLayer;

char* Unite(char Unit)
{
    int base;
    if (Unit <= '9' && Unit >= '0')
    {
        switch (Unit)
        {
            case '9':
                return "1001";
            case '8':
                return "1000";
            case '7':
                return "0111";
            case '6':
                return "0110";
            case '5':
                return "0101";
            case '4':
                return "0100";
            case '3':
                return "0011";
            case '2':
                return "0010";
            case '1':
                return "0001";
            case '0':
                return "0000";
        }
    }
    return "Erreur lors de la conversion.";
}

char* conversion(char* buffer)
{
    char* res;
    short i;
    short y;
    short h;
    short p;

    i = 4;
    y = 16;
    res = (char*)malloc(17);
    while(i >= 0)
    {
        if (i != 2)
        {
            char *tmp;

            h = y - 3;
            p = 3;
            tmp = (char*)malloc(5);
            tmp = Unite(buffer[i]); // Prend les lettres une par une et renvoi leur valeur en binaire dans une string.
            while (y >= h)
            {
                res[y] = tmp[p];
                p--;
                y--;
            }
        }
        else
        {
            res[y] = ':';
            y--;
        }
        i--;
        
    }
    return res;
}

static void UpdateTime()
{
  time_t temp = time(NULL);
  struct tm* TickTime = localtime(&temp);
  
  static char* BTime;
  static char buffer[8];
  strftime(buffer, sizeof(buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", TickTime);
  
  BTime = conversion(buffer);
  text_layer_set_text(TLayer, BTime);
  
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
  text_layer_set_font(TLayer, fonts_get_system_font(FONT_KEY_GOTHIC_09));  // Dit quel police d'écriture ont veux params : Le Layer & Le code de la police.
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
