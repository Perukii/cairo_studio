
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

    double object_first = 0;
    double object_second = 0;

    cst_host_add_object(host, &object_first, "first");
    cst_host_add_object(host, &object_second, "second");

    cst_host_run(host);

}

void main_loop_func(CstHost* host, void* cr){

    double * query_first = cst_host_query_object(host, "first");
    (*query_first) = 10+((*query_first)-10)*0.95;

    cairo_rectangle(cr, cst_host_get_cursor_x(host)-(*query_first),
                        cst_host_get_cursor_y(host)-(*query_first),
                        (*query_first)*2, 
                        (*query_first)*2);
    cairo_set_source_rgb(cr, 0.0, 0.5, 1.0);
    cairo_fill(cr);

    double * query_second = cst_host_query_object(host, "second");
    (*query_second)++;

    cairo_rectangle(cr, 100+(*query_second), 100, 50, 50);
    cairo_set_source_rgb(cr, 1.0, 0.5, 0.0);
    cairo_fill(cr);

    //printf("%d %d\n", cst_host_get_cursor_x(host), cst_host_get_cursor_y(host));

}

void button_func(CstHost* host, CstEvent* event){
    double * query_first = cst_host_query_object(host, "first");
    (*query_first) += 10*(event->button.type == 0);
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

