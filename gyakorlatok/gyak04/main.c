#include "app.h"

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    App app;
    app.toggle = 1;
    printf("1- heart 2-mandarin 3-haromszog 4-piramis 5-sakktabla 6-henger 7-kup\n");
    init_app(&app, 800, 600);
    while (app.is_running)
    {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }
    destroy_app(&app);

    return 0;
}
