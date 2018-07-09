#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>


GtkApplication *app;
GtkWidget *window;
GtkWidget *grid;
GtkWidget *button;
GtkWidget *scrolled, *view;
GtkWidget *scrolled2, *view2;

void print_btn_msg(GtkWidget *widget, gpointer data);
void print_btn_msg2(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);
void init_gtk();

#endif //UI_H