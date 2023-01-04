#include "../include/e3s_crew.hpp"
#include "../include/e3s_controller.hpp"

e3s_crew_t::e3s_crew_t( const std::string       name_p,
                        const std::string       surname_p,
                        const std::string       nationality_p,
                        uint16_t                age_p,
                        bool                    gender_p,
                        uint32_t                id_p,
                        bool                    drugs_p,
                        bool                    suit_p,
                        bool                    helmet_p
                        ):
                        name(name_p),
                        surname(surname_p),
                        nationality(nationality_p),
                        age(age_p),
                        gender(gender_p),
                        id(id_p),
                        vital{drugs_p, suit_p, helmet_p}
                        {
                           this->background = (e3s_image_t*)&(e3s_controller.get_galery().get_images().at("crew_bg.png"));
                           if(gender_p){
                                this->body = (e3s_image_t*)&(e3s_controller.get_galery().get_images().at("crew_male.png"));
                           }else{
                                this->body = (e3s_image_t*)&(e3s_controller.get_galery().get_images().at("crew_female.png"));
                           }
                        }


uint16_t e3s_crew_t::total_crew = 0;

const std::string& e3s_crew_t::get_name() const {return this->name;}

const std::string& e3s_crew_t::get_surname() const{return surname;}

const std::string& e3s_crew_t::get_nationality() const{return nationality;}

const uint16_t e3s_crew_t::get_age() const{return age;}

const uint32_t e3s_crew_t::get_id() const{return id;}

bool e3s_crew_t::get_drugs() const{return vital.drugs;}

bool e3s_crew_t::get_suit() const{return vital.suit;}

bool e3s_crew_t::get_helmet() const{return vital.helmet;}

void e3s_crew_t::set_drugs(bool b){vital.drugs = b;}

void e3s_crew_t::set_suit(bool b){vital.suit = b;}

void e3s_crew_t::set_helmet(bool b){vital.helmet = b;}

bool e3s_crew_t::get_gender() const {
    return this->gender;
}


uint16_t e3s_crew_t::increase_total_crew(uint16_t i){return total_crew += i;}

uint16_t e3s_crew_t::decrease_total_crew(uint16_t d){return total_crew -= d;}

e3s_image_t* const e3s_crew_t::get_background() const{
    return this->background;
}

e3s_image_t* const e3s_crew_t::get_body() const {
    return this->body;
}