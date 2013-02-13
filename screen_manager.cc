#include "screen_manager.h"
#include <stdio.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/label.h>
#include <gtkmm-3.0/gtkmm/frame.h>
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"
#include <glibmm/ustring.h>
#include <string>


PlayerController::PlayerController ()
    : box(Gtk::ORIENTATION_VERTICAL),
      discard("discard"),
      label_score("0"),
      label_card_count("0")
{
    set_border_width(10);
    box.pack_start(label_score);
    label_score.show();
    box.pack_start(label_card_count);
    label_card_count.show();
    box.pack_start(discard);
    discard.show();
    add(box);
    box.show();
}


PlayerController::~PlayerController()
{}

void PlayerController::show_score(int score)
{
    char score_char[10];
    sprintf(score_char,"%d",score);

    Glib::ustring score_string(score_char);
    label_score.set_text(score_string);
}

void PlayerController::show_card_count(int count)
{
    char count_char[10];
    sprintf(count_char,"%d",count);

    Glib::ustring count_string(count_char);
    label_card_count.set_text(count_string);
}

Gtk::Button *PlayerController::get_discard()
{
    return &discard;
}
Gui::Gui()
{
    set_title("Alchemy");
    set_border_width(10);
    player_controller.set_label("player1");

    main_box.pack_start(player_controller);
    player_controller.show();

    add(main_box);

    main_box.show();
}



Gui::~Gui()
{}


PlayerController *Gui::get_player()
{
    return &player_controller;
}

ScreenManager::ScreenManager()
{
    player = Player::get_instance();

    player->signal_card_out.connect(this,&ScreenManager::player_use_card);
    player->signal_score_added.connect(this,&ScreenManager::player_add_score);

}

ScreenManager::~ScreenManager()
{
}

void ScreenManager::click_card()
{
    player->remove_hand_card(0);
}

void ScreenManager::player_use_card(int id)
{
    desk->get_player()->show_card_count(player->get_hand_num());
}

void ScreenManager::player_add_score()
{
    desk->get_player()->show_score(player->get_score());
}

int ScreenManager::loop(int argc,char *argv[])
{

    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                "org.gtkmm.examples.base");
    desk = new Gui();
    desk->get_player()->get_discard()->signal_clicked().connect(sigc::mem_fun(*this, &ScreenManager::click_card));
    desk->get_player()->show_card_count(player->get_hand_num());
    int result = app->run(*desk);
    delete desk;
    return result;
}
