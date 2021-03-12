
unsigned int cst_host_get_w(CstHost* phost){
    return gdk_window_get_width(phost->gdk_window);
}

unsigned int cst_host_get_h(CstHost* phost){
    return gdk_window_get_height(phost->gdk_window);
}

unsigned int cst_host_get_cursor_x(CstHost* phost){
    return phost->cursor_x;
}

unsigned int cst_host_get_cursor_y(CstHost* phost){
    return phost->cursor_y;
}

void* cst_host_query_object(CstHost* phost, const char* key){

    unsigned int res = -1;

    for(unsigned int i=0; i<phost->container_size; i++){
        if(strcmp(phost->container_key[i], key) == 0){
            res = i;
            break;
        }
        else continue;
    }

    if(res == -1)   return NULL;
    else            return phost->container[res];

}