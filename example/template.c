
#include "cairo_studio.c"

void main_loop_func (CstHost*, void*);
void button_func    (CstHost* host, CstEvent* event);
void key_func       (CstHost* host, CstEvent* event);
void motion_func    (CstHost* host, CstEvent* event);
void scroll_func    (CstHost* host, CstEvent* event);

int main(){
    CstHost* host;

    host = cst_setup_host();
    cst_host_set_position(host,80,80);
    cst_host_set_scale(host,500,500);
    cst_host_set_mainloop(host,main_loop_func,0.01);

    cst_host_set_event(host, "button", button_func);
    cst_host_set_event(host, "key", key_func);
    cst_host_set_event(host, "motion", motion_func);
    cst_host_set_event(host, "scroll", scroll_func);

    cst_host_set_title(host, "Application");

    cst_host_run(host);

}

void main_loop_func(CstHost* host, void* cr){
    //printf("%d %d\n", cst_host_get_cursor_x(host), cst_host_get_cursor_y(host));
}

void button_func(CstHost* host, CstEvent* event){
    //printf("%d %d\n", event->button.value, event->button.type);
}

void key_func(CstHost* host, CstEvent* event){
    //printf("%d %d\n", event->key.value, event->key.type);
}

void motion_func(CstHost* host, CstEvent* event){
    //printf("%d %d\n", event->motion.x, event->motion.y);
}

void scroll_func(CstHost* host, CstEvent* event){
    //printf("%d %d\n", event->scroll.value_v, event->scroll.value_h);
}

