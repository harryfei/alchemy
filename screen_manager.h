#ifndef SCREEN_MANAGER_H_H_H_
#define SCREEN_MANAGER_H_H_H_

#include "player/player.h"
#include "card/card_array.h"
#include "utils/sigslot.h"
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/frame.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <string>

class PlayerController : public Gtk::Frame
{
    public:
        PlayerController();
        ~PlayerController();
        void show_score(int score);
        void show_card_count(int count);
        Gtk::Button *get_discard();
    protected:
        Gtk::Button discard;
        Gtk::Label label_score;
        Gtk::Label label_card_count;
        Gtk::Box box;

};
class Gui: public Gtk::Window
{
    public:
        Gui();
        virtual ~Gui();
        PlayerController *get_player();
        PlayerController *get_other();

    protected:
        //Member widgets:
        Gtk::Box main_box;
        PlayerController player_controller;
        PlayerController other_controller;
};
class ScreenManager :public sigslot::has_slots<>
{
    public:
        ScreenManager();
        ~ScreenManager();
        void click_card();
        int loop(int argc, char *argv[]);
    private:
        Player *player;
        Gui *desk;
        void player_use_card(int id);
        void player_add_score();
};

#endif
