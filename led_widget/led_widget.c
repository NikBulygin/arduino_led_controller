#include "led_widget.h"

typedef struct _LedWidgetPrivate {
  LED* led_info;
  GtkWidget* button;
} LedWidgetPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(LedWidget, led_widget, GTK_TYPE_BOX);


static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
  static guint32 last_click_time = 0;  // Store the timestamp of the last click


  guint32 current_time = event->time;  // Get the current timestamp

  // Check the time difference since the last click
  //without this  condition button click doesn't work
  if (last_click_time != 0 && (current_time - last_click_time) < BUTTON_PRESS_DELAY ) {
    return FALSE;  // Exit the handler without doing anything
  }

  last_click_time = current_time;  // Update the last click time

  if (user_data && GTK_IS_WIDGET(user_data)) {
    LedWidgetPrivate* priv =
      led_widget_get_instance_private(LED_WIDGET(user_data));

    if (priv && priv->led_info) {
      priv->led_info->state = !(priv->led_info->state); // Toggle the state
      led_widget_set_color(LED_WIDGET(user_data)); // Set the appropriate color
    }
    
    char label[100];  // Buffer to store the final label
    sprintf(label, "%d:%d\n", priv->led_info->GPIO, priv->led_info->state);  // Convert integer to string and concatenate with "LED"
    send_message(label, "/dev/pts/1");
  }
    else {
      g_warning("user_data is not a GtkWidget");
    }
    return FALSE;
  }


  static void led_widget_dispose(GObject *object) {
    LedWidget *self = LED_WIDGET(object);
    LedWidgetPrivate* priv = led_widget_get_instance_private(self);
    
    if (priv && priv->led_info) {
      led_free(priv->led_info);
      priv->led_info = NULL;
    }

    G_OBJECT_CLASS(led_widget_parent_class)->dispose(object);
  }

  static void led_widget_class_init(LedWidgetClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->dispose = led_widget_dispose;
  
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    widget_class->button_press_event = on_button_press;
  }

  static void led_widget_init(LedWidget *self) {
    LedWidgetPrivate* priv = led_widget_get_instance_private(self);

    priv->button = gtk_button_new_with_label("lbl");

    gtk_container_add(GTK_CONTAINER(self), priv->button);
    g_signal_connect(priv->button, "button-press-event", G_CALLBACK(on_button_press), self);

  
    led_widget_set_color(self); // Set initial color
  }

  GtkWidget* led_widget_new(LED* led_info) {
    LedWidget* widget = g_object_new(LED_TYPE_WIDGET, NULL);
    LedWidgetPrivate* priv = led_widget_get_instance_private(widget);
  
    priv->led_info = led_info;
    led_widget_set_color(widget);

    char label[10];  // Buffer to store the final label
    sprintf(label, "LED%d", priv->led_info->GPIO);  // Convert integer to string and concatenate with "LED"

    gtk_button_set_label(GTK_BUTTON(priv->button), label);
  
    gtk_widget_set_hexpand(priv->button, TRUE);
    gtk_widget_set_vexpand(priv->button, TRUE);
  
    return GTK_WIDGET(widget);
  }

  void led_widget_set_color(LedWidget* widget) {
    LedWidgetPrivate* priv = led_widget_get_instance_private(widget);
  
    if (!priv || !priv->led_info) {
      return;  // Exit if the private data or LED info is not initialized
    }

    GtkStyleContext* context = gtk_widget_get_style_context(priv->button);
    GtkCssProvider* provider = gtk_css_provider_new();

    const char* color;
    if (priv->led_info->state) {
      color = LED_HIGHLIGHT_COLOR;
    } else {
      color = LED_DEFAULT_COLOR;
    }

    char css[256];
    snprintf(css, sizeof(css), "button { background-color: %s; }", color);
    
    gtk_css_provider_load_from_data(provider, css, -1, NULL);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
  }
