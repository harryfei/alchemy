#ifndef NETWORK_MANAGER_H_H_H_
#define NETWORK_MANAGER_H_H_H_

#include "utils/sigslot.h"
#include "network/network.h"
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

        void on_player_score_added();
        void on_player_card_out(int id);

};

#endif
