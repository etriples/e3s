#include "../include/e3s_image.hpp"
#include "../include/e3s_toolset.hpp"

e3s_image_t::e3s_image_t(std::string path): matrix(nullptr){
    png::image<png::index_pixel> png_image;
    png_image.read(path);

    uint32_t png_width = png_image.get_width();
    uint32_t png_height = png_image.get_height();


    matrix = new uint32_t*[png_height];

    this->height = png_height;
    this->width = png_width;

    for (uint32_t row = 0; row < png_height; row++) {
        matrix[row] = new uint32_t[png_width];
        for (uint32_t col = 0; col < png_width; col++) {
            if (png_image[row][col] != 0)
                matrix[row][col] = png_image[row][col];
        }
    }

}

uint32_t** const e3s_image_t::get_matrix() const{
    return this->matrix;
}


e3s_image_t::e3s_image_t():height(0),width(0),matrix(nullptr){
    
}

e3s_image_t::~e3s_image_t(){

}

uint32_t e3s_image_t::get_width() const {
    return this->width;
}

uint32_t e3s_image_t::get_height() const {
    return this->height;
}