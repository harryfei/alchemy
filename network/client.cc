#include "network/network.h"
#include <iostream>

class TestHandler:public NetworkHandler{
    public:
        void connect(
                ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet){
            std::cout<<"connect"<<std::endl;
        }
        void data_receive(
                ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet){
            std::cout<<"receive"<<std::endl;
        }
        void disconnect(
                ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet){
            std::cout<<"disconnect"<<std::endl;
        }
};

int main()
{
    TestHandler handler;

    NetClient client(&handler);

    client.start_client();
    client.connect("localhost",9000);
    client.start_loop();
    client.send_data("test");
    client.send_data("test1");
    return 1;
}
