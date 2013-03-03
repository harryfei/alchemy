#include "network/network.h"
#include <iostream>

class TestHandler:public NetworkHandler{
    public:
        virtual void connect(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet){
            if (packet != NULL){
                std::cout<<"connect "
                    <<packet->data
                    <<std::endl;
            }
        }
        virtual void data_receive(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet){
            if (packet != NULL){
                std::cout<<"receive "
                    <<packet->data
                    <<std::endl;
            }
        }
        virtual void disconnect(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet){
            if (packet != NULL){
                std::cout<<"disconnect "
                    <<packet->data
                    <<std::endl;
            }
        }
};
int main()
{
    TestHandler handler;

    NetServer server(&handler);
    server.start_server("localhost",9000);
    server.start_loop();
    server.wait();
    return 1;
}
