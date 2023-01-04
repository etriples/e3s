#ifndef E3S_GALERY_HPP
#define E3S_GALERY_HPP

#include "e3s.hpp"
#include "e3s_image.hpp"

class e3s_galery_t{

private:
    std::map<std::string,e3s_image_t> images;

public:
    void load(std::string path);
    const std::map<std::string,e3s_image_t>& get_images() const;

};

class e3s_controller_t;

#endif