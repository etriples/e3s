#ifndef E3S_IMAGE_HPP
#define E3S_IMAGE_HPP

#include "e3s.hpp"


class e3s_image_t{

private:
    uint32_t width;
    uint32_t height;
    uint32_t** matrix;

public:
    e3s_image_t();
    e3s_image_t(std::string path);
    ~e3s_image_t();

    uint32_t get_width() const;
    uint32_t get_height() const;
    uint32_t** const get_matrix() const;
};


#endif

