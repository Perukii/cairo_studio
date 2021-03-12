
void cst_host_set_position(CstHost* phost, unsigned int x, unsigned int y){
    phost->ini_x = x;
    phost->ini_y = y;
}

void cst_host_set_scale(CstHost* phost, unsigned int w, unsigned int h){
    phost->ini_w = w;
    phost->ini_h = h;
}


void cst_host_set_title(CstHost* phost, char* tar){
    phost->ini_title = tar;
}

void cst_host_set_mainloop(CstHost* phost, void (*func)(), double dtick){
    phost->tick = 1000 * dtick;
    phost->mainloop = func;
}

void cst_host_set_event(CstHost* phost, const char* tag, void (*func)()){
    if(strcmp(tag, "button") == 0){
        phost->button_press_func = func;
    }
    if(strcmp(tag, "key") == 0){
        phost->key_press_func = func;
    }
    if(strcmp(tag, "motion") == 0){
        phost->motion_func = func;
    }
    if(strcmp(tag, "scroll") == 0){
        phost->scroll_func = func;
    }
}

int cst_host_add_object(CstHost* phost, void* object, const char* key){

    phost->container_size++;

    void**          ptr_c = NULL;
    const char**    ptr_k = NULL;

    ptr_c = (void**)realloc(phost->container, phost->container_size*sizeof(void*));

    if(ptr_c == NULL){
        free(phost->container);
        return 0;
    }

    phost->container = ptr_c;
    phost->container[phost->container_size-1] = object;

    ptr_k = (const char**)realloc(phost->container_key, phost->container_size*sizeof(const char*));
    if(ptr_k == NULL){
        free(phost->container_key);
        return 0;
    }

    phost->container_key = ptr_k;
    phost->container_key[phost->container_size-1] = key;

    return 1;

}
