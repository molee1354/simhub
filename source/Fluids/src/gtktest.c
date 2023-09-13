#include <gtk/gtk.h>
#include <cairo.h>

#define WIDTH 400
#define HEIGHT 400
#define RADIUS 20
#define SPEED 2

static double circle_x = (double)WIDTH * .78;
static double circle_y = (double)HEIGHT * .544;
static int x_direction = 1;
static int y_direction = 1;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    // Clear the drawing area
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    // Draw the circle
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    cairo_arc(cr, circle_x, circle_y, RADIUS, 0, 2 * G_PI);
    cairo_fill(cr);

    // Update circle position
    circle_x += x_direction * SPEED;
    circle_y += y_direction * SPEED;

    // Bounce off the edges
    if (circle_x < RADIUS || circle_x > WIDTH - RADIUS) {
        x_direction *= -1;
    }
    if (circle_y < RADIUS || circle_y > HEIGHT - RADIUS) {
        y_direction *= -1;
    }

    // Redraw the widget
    gtk_widget_queue_draw(widget);

    return FALSE;
}

static gboolean on_timer(gpointer user_data) {
    GtkWidget *widget = GTK_WIDGET(user_data);
    gtk_widget_queue_draw(widget);
    return G_SOURCE_CONTINUE;
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Bouncing Circle");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a drawing area widget
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, WIDTH, HEIGHT);
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    // Connect the drawing event
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);

    // Create a timer to update the animation
    g_timeout_add(16, on_timer, drawing_area);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
