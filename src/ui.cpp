//#include "Ui.h"
#include <gtk/gtk.h>

GtkApplication *app;
GtkWidget *window;
GtkWidget *grid;
GtkWidget *button;
GtkWidget *scrolled, *view;
GtkWidget *scrolled2, *view2;

void print_btn_msg (GtkWidget *widget, gpointer data) {
  g_print ("Fowarding request\n");
}

void print_btn_msg2 (GtkWidget *widget, gpointer data) {
  g_print ("Fowarding response\n");
}

void activate (GtkApplication *app, gpointer user_data) {
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Spider");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 700);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  grid = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Request");
  g_signal_connect (button, "clicked", G_CALLBACK (print_btn_msg), NULL);

  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Reply");
  g_signal_connect (button, "clicked", G_CALLBACK (print_btn_msg2), NULL);

  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  scrolled = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_size_request (scrolled, 500, 650);
  view = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), TRUE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled), view);

  gtk_grid_attach (GTK_GRID (grid), scrolled, 0, 1, 1, 1);

  scrolled2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_size_request (scrolled2, 500, 650);
  view2 = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view2), TRUE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view2), TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled2), view2);

  gtk_grid_attach (GTK_GRID (grid), scrolled2, 1, 1, 1, 1);

  gtk_widget_show_all (window);
}

int maini (int argc, char *argv[]) {
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return 0;
}