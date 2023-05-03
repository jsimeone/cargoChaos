#ifndef main_menu_h
#define main_menu_h
#include "game.h"
#include "Button.h"

using namespace sf;

class Main_Menu {
private:
    RenderWindow* window;
    Event event;
    int selected_button;
    
    Texture background_texture;
    Sprite background_sprite;
    
    Texture logo_texture;
    Sprite logo_sprite;
    
    vector<Button*> main_menu_buttons;
public:
    Main_Menu();
    void init_window();
    void init_textures();
    void init_buttons();
    void key_press_checker();
    void update();
    void render();
};


#endif /* main_menu_h */
