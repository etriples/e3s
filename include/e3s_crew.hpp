#ifndef E3S_CREW_HPP
#define E3S_CREW_HPP

#include "e3s.hpp"
#include "e3s_image.hpp"

class e3s_crew_t{
private:
    e3s_image_t* background;
    e3s_image_t* body;
    static uint16_t total_crew;
    const std::string name;
    const std::string surname;
    const std::string nationality;
    const uint16_t age;
    const uint32_t id;
    const bool gender;

    struct{
        bool drugs;
        bool suit;
        bool helmet;
    }vital;

public:

    const std::string& get_name() const;
    const std::string& get_surname() const;
    const std::string& get_nationality() const;
    const uint16_t get_age() const;
    const uint32_t get_id() const;

    bool get_drugs() const;
    bool get_suit() const;
    bool get_helmet() const;
    bool get_gender() const;

    void set_drugs(bool b);
    void set_suit(bool b);
    void set_helmet(bool b);

    uint16_t increase_total_crew(uint16_t i);
    uint16_t decrease_total_crew(uint16_t d);

    e3s_crew_t( const std::string      name_p,
                const std::string      surname_p,
                const std::string      nationality_p,
                uint16_t                age_p,
                bool                    gender_p,
                uint32_t                id_p,
                bool                    drugs_p,
                bool                    suit_p,
                bool                    helmet_p
                );


    e3s_image_t* const get_background() const;
    e3s_image_t* const get_body() const;

};

#endif