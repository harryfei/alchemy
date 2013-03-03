#include "network_manager.h"
#include "player/player.h"
#include <string>
#include <sstream>

NetworkManager::NetworkManager(){

    auto player = Player::get_instance();

    player->signal_card_out.connect(this,&NetworkManager::on_player_card_out);
    player->signal_score_added.connect(this,&NetworkManager::on_player_score_added);

}

NetworkManager::~NetworkManager(){
}

void NetworkManager::init(bool is_server){
    if(is_server){
        NetServer *server = new NetServer(this);
        server->start_server("localhost",9000);
        server->start_loop();
        network = server;

    }else{
        NetClient *client= new NetClient(this);
        client->start_client();
        client->connect("localhost",9000);
        client->start_loop();
        network = client;
    }
}

void NetworkManager::destory(){
    network->stop();
    network->wait();
    delete network;
}

void NetworkManager::connect(ENetPeer *peer,
        const unsigned char channel,
        ENetPacket *packet){
    //if (packet != NULL){
        std::cout<<"connect "
            //<<packet->data
            <<std::endl;
    //}
}
void NetworkManager::data_receive(ENetPeer *peer,
        const unsigned char channel,
        ENetPacket *packet){
    if (packet != NULL){
        std::cout<<"receive "
            <<packet->data
            <<std::endl;
    }
}
void NetworkManager::disconnect(ENetPeer *peer,
        const unsigned char channel,
        ENetPacket *packet){
    if (packet != NULL){
        std::cout<<"disconnect "
            <<packet->data
            <<std::endl;
    }
}

void NetworkManager::on_player_card_out(int id){
    std::stringstream data_buff;
    data_buff<<"card out "<<id;
    //std::string data = class_buff.str();
    network->send_data(data_buff.str());

}
void NetworkManager::on_player_score_added(){
    network->send_data("score add");

}
