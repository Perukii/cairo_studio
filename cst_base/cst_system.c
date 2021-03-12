
int cst_host_init(CstHost* phost){

    gdk_init(NULL, NULL);

    phost->gdk_display = gdk_display_open("");
    if(phost->gdk_display == NULL){
        printf("cadn't open display\n");
        return 0;
    } 

    phost->gdk_screen = gdk_display_get_default_screen(phost->gdk_display);
    if(phost->gdk_screen == NULL){
        printf("can't open screen\n");
        return 0;
    }

    phost->container = NULL;
    phost->container_key = NULL;
    phost->container_size = 0;
    phost->tick = 1;
    phost->mainloop = NULL;
    phost->button_press_func = NULL;
    phost->key_press_func = NULL;
    phost->motion_func = NULL;
    phost->scroll_func = NULL;
    phost->cursor_x = -1;
    phost->cursor_y = -1;
    phost->ini_title = "";
    return 1;
}

CstHost* cst_setup_host(){
    CstHost* target = &global_cst_host_main;
    cst_host_init(target);
    return target;
}


void cst_host_run(CstHost* phost){

    GdkWindowAttr main_attr;
    main_attr.window_type = GDK_WINDOW_TOPLEVEL;
    main_attr.x = phost->ini_x;
    main_attr.y = phost->ini_y;
    main_attr.width = phost->ini_w;
    main_attr.height = phost->ini_h;
    main_attr.wclass = GDK_INPUT_OUTPUT;
    main_attr.event_mask =  GDK_ALL_EVENTS_MASK;
    
    phost->gdk_window = gdk_window_new(NULL, &main_attr, 0);

    phost->gdk_mainloop = g_main_loop_new (NULL, 1);

    g_timeout_add (phost->tick, cst_mainloop, phost); 
    gdk_event_handler_set(cst_event, phost, NULL);

    gdk_window_set_title(phost->gdk_window, phost->ini_title);

    gdk_window_show(phost->gdk_window);   

    g_main_loop_run(phost->gdk_mainloop);

    gdk_window_destroy(phost->gdk_window);
    free(phost->container);
    free(phost->container_key);

}

