#ifndef BS_SCREEN_MENU_H_INCLUDED
#define BS_SCREEN_MENU_H_INCLUDED

class BS_Font
{
public:
    static float get_width_of_text(std::string text, float font_size)
    {
        return 0;
    }
};

class BS_Body
{
private:
    float width, height, depth = 0;
    float x_coordinate, y_coordinate, z_coordinate;

public:
    void set_location_x(float _x_coordinate)
    {
        x_coordinate = _x_coordinate;
    }
    void set_location_y(float _y_coordinate)
    {
        y_coordinate = _y_coordinate;
    }

    float get_location_x()
    {
        return x_coordinate;
    }
    float get_location_y()
    {
        return y_coordinate;
    }

    void set_width(float _width)
    {
        width = _width;
    }
    void set_height(float _height)
    {
        height = _height;
    }

    float get_width()
    {
        return width;
    }
    float get_height()
    {
        return height;
    }
};

class BS_Textured_Body : private BS_Body
{
private:
    std::string texture_name;

public:
    BS_Textured_Body(float _x_coordinate = 0, float _y_coordinate = 0, std::string _texture_name = "")
    {

    }
};

class BS_Button : private BS_Body
{
private:
    BS_Textured_Body *background_texture;
    std::string text_to_display;
    float x_coordinate_text, y_coordinate_text;
    bool align_left, align_center, align_right;

public:
    BS_Button(float _x_coordinate = 0, float _y_coordinate = 0, float _width = 0, float _height = 0, std::string _text_to_display = "")
    {
        background_texture = new BS_Textured_Body();

        background_texture->set_location_x(_x_coordinate);
        background_texture->set_location_y(_y_coordinate);

        set_location_x(_x_coordinate);
        set_location_y(_y_coordinate);

        text_to_display = _text_to_display;

        align_left = false;
        align_center = false;
        align_right = false;
    }

    void set_text_to_display(std::string _text_to_display)
    {
        text_to_display = _text_to_display;
    }

    std::string get_displayed_text()
    {
        return text_to_display;
    }

    void align_text_left()
    {
        align_left = true;
        align_center = false;
        align_right = false;
    }
    void align_text_center()
    {
        align_left = false;
        align_center = true;
        align_right = false;
    }
    void align_text_right()
    {
        align_left = false;
        align_center = false;
        align_right = true;
    }

    void set_Button_location(float _x_coordinate, float _y_coordinate)
    {
        set_location_x(_x_coordinate);
        set_location_y(_y_coordinate);
    }

    void set_Button_background_location(float _x_coordinate, float _y_coordinate)
    {
        background_texture->set_location_x(_x_coordinate);
        background_texture->set_location_y(_y_coordinate);
    }

    void set_Button_width(float _width)
    {
        set_width(_width);
    }
    void set_Button_height(float _height)
    {
        set_height(_height);
    }

    void set_Button_size(float _width, float _height)
    {
        set_Button_width(_width);
        set_Button_height(_height);
    }

    float get_Button_width()
    {
        return get_width();
    }
    float set_Button_height(float _height)
    {
        return get_height();
    }

    void set_Button_background_location(float _width, float _height)
    {
        background_texture->set_width(_width);
        background_texture->set_height(_height);
    }
};

class BS_Screen_Menu
{
private:
    BS_Textured_Body *background_texture;
    std::vector<BS_Button*> menu_buttons;
    std::string buttons_texture;

public:
    BS_Screen_Menu()
    {

    }

    BS_Screen_Menu(std::string menu_path_loading)
    {
        load_buttons_from_file_dynamic_location(menu_path_loading);
    }

    void set_buttons_texture(std::string _button_texture)
    {
        buttons_texture = _button_texture;
    }

    std::string get_buttons_texture()
    {
        return buttons_texture;
    }

    void load_buttons_from_file_dynamic_location(std::string menu_path_loading)
    {
        std::ifstream fin(menu_path_loading.c_str());

        std::string button_text = "", button_texture_name = "";
        float button_x_coordinate, button_y_coordinate, button_width, button_height, button_gap, button_text_font_size;

        fin>>button_x_coordinate>>button_y_coordinate>>button_width>>button_height>>button_gap>>button_text_font_size>>button_texture_name;

        ///set the texture for every button
        set_buttons_texture(button_texture_name);

        float last_button_position_y = button_y_coordinate;

        while(fin>>button_text)
        {
            BS_Button *new_button = new BS_Button(button_x_coordinate, last_button_position_y, button_width, button_height, button_text);

            last_button_position_y += button_height  + button_gap;

            menu_buttons.push_back(new_button);
        }
    }

    void render_buttons()
    {
        for(int i = 0; i < menu_buttons.size(); i++)
        {
            menu_buttons[i]->draw(get_buttons_texture());
        }
    }

    ~BS_Screen_Menu()
    {
        delete background_texture;

        while(menu_buttons.size())
        {
            delete menu_buttons.back();
            menu_buttons.pop_back();
        }
    }
};


#endif // BS_SCREEN_MENU_H_INCLUDED
