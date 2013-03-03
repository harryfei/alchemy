#include "network_manager.h"
#include "player/player.h"
#include "action_def.h"
#include <string>
#include <sstream>

NetworkManager::NetworkManager(){

    auto player_manager = PlayerManager::get_instance();
    auto player= player_manager->fetch(1);

    player->signal_card_out.connect(this,&NetworkManager::on_player_card_out);
    player->signal_score_added.connect(this,&NetworkManager::on_player_score_added);
    //player->signal_win.connect(this,&NetworkManager::on_player_win);

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
        auto data = (Action::NetPacket*)(packet->data);
        process_net_data(data);
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
void NetworkManager::process_net_data(Action::NetPacket *packet){
    switch(packet->type){
        case CardOut::TYPE_ID: {
            auto data= (CardOut::NetPacket *)packet;
            auto player_manager = PlayerManager::get_instance();
            auto other = player_manager->fetch(2);
            other->remove_hand_card(data->arg1);
            }
            break;
        case ScoreAdd::TYPE_ID:{
            auto data= (ScoreAdd::NetPacket*)packet;
            auto player_manager = PlayerManager::get_instance();
            auto other = player_manager->fetch(2);
            other->add_score(data->arg1);
            }
            break;
        case Win::TYPE_ID:{
            auto data= (Win::NetPacket*)packet;
            auto player_manager = PlayerManager::get_instance();
            auto other = player_manager->fetch(2);
            other->win();
            }
            break;
        default: ;
    }

}

void NetworkManager::on_player_card_out(int id){
    CardOut::NetPacket data;
    data.arg1= 0;
    network->send_data((void *)&data,sizeof(data));

}
void NetworkManager::on_player_score_added(int score){
    ScoreAdd::NetPacket data;
    data.arg1 = score;
    network->send_data((void *)&data,sizeof(data));
}
//void NetworkManager::on_player_win(){
    //Win::NetPacket data;
    //network->send_data((void *)&data,sizeof(data));
//}
