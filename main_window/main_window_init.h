#ifndef GTK_WINDOW_MAIN_WINDOW_INIT_H
#define GTK_WINDOW_MAIN_WINDOW_INIT_H

#include <gtk/gtk.h>

#include "grid_widget.h"
#include "../led_widget/led_widget.h"
#include "../structures/led.h"
#include "../structures/config.h"

#define GRID_COUNT_IN_COL 2

// Функция для создания новой метки "Hello world"
static GtkWidget* create_hello_button() {
  return gtk_button_new_with_label("Hello world");
}

static void activate(GtkApplication* app, gpointer user_data) {
  Config* cfg = (Config*)user_data;
    
  GtkWidget* window;
  GtkWidget* grid;
  GtkWidget* scrolled_window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  // создаем скролл-окно
  scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(window), scrolled_window);
    
  // Создаем grid
  grid = grid_create(scrolled_window);

  // Check if cfg is valid
  if (cfg) {

    int row = 0,
      col = 0;
    for (int i = 0; i < cfg->count; i++)
      {
	GtkWidget* led = led_widget_new(&cfg->leds[i]);
	gtk_grid_attach(GTK_GRID(grid), led, row, col, 1, 1);
	
	gtk_widget_set_hexpand(led, TRUE);
	gtk_widget_set_vexpand(led, TRUE);
	if(++row == GRID_COUNT_IN_COL)
	  {
	    row = 0;
	    col++;
	  }
      }
    
  } else {
    g_warning("Config not provided or invalid");
  }

  gtk_widget_show_all(window);
}

// Modify this function to pass the cfg pointer when connecting the activate signal
static int main_window_init(Config* cfg, int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), cfg);  // Pass cfg here
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
#endif //GTK_WINDOW_MAIN_WINDOW_INIT_H
