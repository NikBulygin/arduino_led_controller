#ifndef GTK_WIDGET_LED_WIDGET_H
#define GTK_WIDGET_LED_WIDGET_H

#include <gtk/gtk.h>

#include "../structures/led.h"
#include "../interfaces/interface.h"

G_BEGIN_DECLS

#define LED_WIDGET_T

#define LED_TYPE_WIDGET (led_widget_get_type())
#define BUTTON_PRESS_DELAY 0.000000000001

G_DECLARE_DERIVABLE_TYPE(LedWidget, led_widget, LED, WIDGET, GtkBox)

struct _LedWidgetClass {
  GtkBoxClass parent_class;
};

#define LED_DEFAULT_COLOR "black"
#define LED_HIGHLIGHT_COLOR "red"

GtkWidget* led_widget_new(LED* led_info);
void led_widget_set_color(LedWidget* widget);

G_END_DECLS

#endif // GTK_WIDGET_LED_WIDGET_H
