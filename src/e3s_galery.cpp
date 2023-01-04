#include "../include/e3s_galery.hpp"
#include "../include/e3s_toolset.hpp"


const std::map<std::string,e3s_image_t>& e3s_galery_t::get_images() const {
    return this->images;
}


void e3s_galery_t::load(std::string path){

    DIR* dir_images;

    struct dirent* dir_entry;

    dir_images = opendir(path.c_str());

    if(dir_images == NULL){
        e3s_toolset_fatal_exit("Cannot open images directory");
    }
    while((dir_entry = readdir(dir_images)) != NULL)
    {
        char resolved_path[PATH_MAX] = {0};
        sprintf(resolved_path,"%s/%s",path.c_str(),dir_entry->d_name);

        std::string png_file(dir_entry->d_name);       

        if(png_file != ".." and png_file != "."){
            e3s_image_t new_image = e3s_image_t(std::string(resolved_path));
            this->images.insert({png_file,new_image});
        }

    }


}