#ifndef GTK_WINDOW_MAIN_GRID_WIDGET_H
#define GTK_WINDOW_MAIN_GRID_WIDGET_H

#include <gtk/gtk.h>

GtkWidget* grid_create(GtkWidget* parent)
{
  GtkWidget *grid;
  grid = gtk_grid_new ();
  gtk_container_add(GTK_CONTAINER(parent), grid);
  gtk_widget_set_hexpand(grid, TRUE); // Растягиваем grid по горизонтали
  gtk_widget_set_vexpand(grid, TRUE); // Растягиваем grid по вертикали

  return grid;
}
#endif //GTK_WINDOW_MAIN_GRID_WIDGET_H
