#ifndef NETWORK_MANAGER_H_H_H_
#define NETWORK_MANAGER_H_H_H_

#include "utils/sigslot.h"
#include "network/network.h"
#include "action_def.h"
class NetworkManager :
            public sigslot::has_slots<>,
            public NetworkHandler{
    public:
        NetworkManager();
        ~NetworkManager();
        void init(bool is_server);
        void destory();
    private:
        Network *network;
        void connect(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet);
        void data_receive(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet);

        void disconnect(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet);
        void process_net_data(Action::NetPacket *packet);

        void on_player_score_added(int score);
        void on_player_card_out(int id);
        //void on_player_win();

};

#endif
