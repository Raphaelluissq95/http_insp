#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>

class Ui{
public:
	void print_btn_msg( GtkWidget *widget, gpointer data );
	void print_btn_msg2( GtkWidget *widget, gpointer data );
	void activate( GtkApplication *app, gpointer user_data );
	static void init_gtk();
};

#endif //UI_H