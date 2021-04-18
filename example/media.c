
#include "cairo_studio.c"

void main_loop_func (CstHost*, void*);

int main(){
    CstHost* host;

    host = cst_setup_host();
    cst_host_set_position(host,80,80);
    cst_host_set_scale(host,500,500);
    cst_host_set_mainloop(host,main_loop_func,0.01);

    cairo_surface_t *img = cairo_image_surface_create_from_png("./example.png"); 
    cst_host_add_object(host, img, "image");

    cst_host_set_title(host, "Application");

    cst_host_run(host);

}

void main_loop_func(CstHost* host, void* cr){
    cairo_set_source_rgb(cr, 0.3 , 0.3 , 0.3);
    
    cairo_select_font_face(cr, "Purisa",
        CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_BOLD);

    cairo_set_font_size(cr, 30);

    cairo_text_extents_t extents;
    cairo_text_extents(cr, "Test", &extents);

    cairo_move_to(cr, 0, extents.height);

    cairo_show_text(cr, "Test");

    // ---

    cairo_surface_t *img = cst_host_query_object(host, "image");

    double img_scale = 200;
    double img_scale_ref = cairo_image_surface_get_width(img)/img_scale;
    cairo_scale(cr, 1.0/img_scale_ref, 1.0/img_scale_ref);
    cairo_set_source_surface(cr, img, 200,400);
    cairo_scale(cr, img_scale_ref, img_scale_ref);

    cairo_paint(cr);
    
}

