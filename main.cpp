#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <json-glib/json-glib.h>  

class AppStore {
public:
  AppStore() {
    // Create GTK window, widgets
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "SpoinkStore");
    
    app_list = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(window), app_list);
    
    fetch_button = gtk_button_new_with_label("Fetch Apps");
    gtk_container_add(GTK_CONTAINER(window), fetch_button);

    g_signal_connect(fetch_button, "clicked", G_CALLBACK(fetch_apps), this);
    
    // More UI setup..

    gtk_widget_show_all(window);
  }

  static void fetch_apps(AppStore *app) {
    // Clear existing apps
    gtk_container_foreach(GTK_CONTAINER(app->app_list), 
                          (GtkCallback)gtk_widget_destroy, NULL);

    // Get list of available apps
    gchar *output = NULL;
    g_spawn_command_line_sync("snap find", &output, NULL, NULL, NULL);
    
    gchar **lines = g_strsplit(output, "\n", -1);
    for(int i = 0; lines[i]; i++) {
      GtkWidget *row = gtk_list_box_row_new();
      gtk_container_add(GTK_CONTAINER(row), gtk_label_new(lines[i]));
      gtk_container_add(GTK_CONTAINER(app->app_list), row);
    }

    g_strfreev(lines);
    g_free(output);
  }
  
private:
  GtkWidget *window;
  GtkWidget *app_list;
  GtkWidget *fetch_button;
};

int main(int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  AppStore app;
  
  gtk_main();
  
  return 0;
}
