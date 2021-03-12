

void cst_event(GdkEvent *event, gpointer data){

    CstHost* phost = (CstHost*)data;

    switch(event->type){
        case GDK_DELETE:
            {
                g_main_loop_quit(phost->gdk_mainloop);
                break;
            }

        case GDK_BUTTON_PRESS:
        case GDK_BUTTON_RELEASE:
            {
                if(phost->button_press_func == NULL)break;
                CstEvent info;
                info.button.x = event->button.x;
                info.button.y = event->button.y;
                info.button.value = event->button.button;
                info.button.type = event->button.type == GDK_BUTTON_PRESS ? 0:1;
                phost->button_press_func(phost, &info);
                break;
            }

        case GDK_KEY_PRESS:
        case GDK_KEY_RELEASE:
            {
                if(phost->key_press_func == NULL)break;
                CstEvent info;
                info.key.value = event->key.keyval;
                info.key.type = event->key.type == GDK_KEY_PRESS ? 0:1;
                phost->key_press_func(phost, &info);
                break;
            }

        case GDK_MOTION_NOTIFY:
            {

                phost->cursor_x = event->motion.x;
                phost->cursor_y = event->motion.y;
                gdk_event_request_motions (&event->motion);

                if(phost->motion_func == NULL)break;
                CstEvent info;
                info.motion.x = event->motion.x;
                info.motion.y = event->motion.y;
                phost->motion_func(phost, &info);
                
                break;
            }

        case GDK_LEAVE_NOTIFY:
            {
                phost->cursor_x = -1;
                phost->cursor_y = -1;
                break;
            }

        case GDK_SCROLL:
            {
                if(phost->scroll_func == NULL)break;
                CstEvent info;
                info.scroll.value_v = (event->scroll.direction == GDK_SCROLL_RIGHT) - (event->scroll.direction == GDK_SCROLL_LEFT);
                info.scroll.value_h = (event->scroll.direction == GDK_SCROLL_DOWN) - (event->scroll.direction == GDK_SCROLL_UP);
                phost->scroll_func(phost, &info);
                break;
            }

        case GDK_EXPOSE:
            {
                cairo_rectangle_int_t region_rect =
                    {0, 0,
                    cst_host_get_w(phost),
                    cst_host_get_h(phost)};

                phost->cairo_region = cairo_region_create_rectangle(&region_rect);

                phost->cairo_context_base = 
                    gdk_window_begin_draw_frame(phost->gdk_window, phost->cairo_region);
                phost->cairo_context = 
                    gdk_drawing_context_get_cairo_context (phost->cairo_context_base);

                cairo_set_source_rgb(phost->cairo_context, 1.0, 1.0, 1.0);
                cairo_paint(phost->cairo_context);

                phost->mainloop(phost, phost->cairo_context);

                gdk_window_end_draw_frame(phost->gdk_window, phost->cairo_context_base);
                cairo_region_destroy(phost->cairo_region);
                break;
            }
            
        default:break;
    }
}


gboolean cst_mainloop(gpointer data){
    
    CstHost* phost = (CstHost*)data;

    if(phost->mainloop == NULL) return 0;
    if(phost->tick == 0) return 0;

    GdkEvent* event_exp = gdk_event_new(GDK_EXPOSE);
    gdk_event_put(event_exp);

    return 1;
}
