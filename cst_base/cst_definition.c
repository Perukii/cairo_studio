
typedef struct{
    GdkDisplay* gdk_display;
    GdkScreen*  gdk_screen;
    GdkWindow*  gdk_window;
    GMainLoop*  gdk_mainloop;

    GdkDrawingContext*  cairo_context_base;
    cairo_t*            cairo_context;
    cairo_region_t*     cairo_region;

    unsigned int ini_x, ini_y, ini_w, ini_h;
    char* ini_title;
    
    void** container;
    const char** container_key;
    unsigned int container_size;
    void (*mainloop)(void*, void*);
    void (*button_press_func)(void*, void*);
    void (*key_press_func)(void*, void*);
    void (*motion_func)(void*, void*);
    void (*scroll_func)(void*, void*);

    unsigned int tick;
    int cursor_x, cursor_y;
    
} CstHost;

typedef union{
    struct{
        unsigned int x, y, type, value;
    } button;

    struct{
        unsigned int type, value;
    } key;

    struct{
        unsigned int x, y;
    } motion;

    struct{
        int value_v, value_h;
    } scroll;

} CstEvent;