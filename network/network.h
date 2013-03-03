#ifndef NETWORK_H_H_H_
#define NETWORK_H_H_H_
#include <enet/enet.h>
#include <string>
#include <boost/thread/thread.hpp>

static int game_channel = 0;
static int chat_channel = 1;

class NetworkHandler{
    public:
        NetworkHandler();
        virtual ~NetworkHandler();

        virtual void connect(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet)=0;
        virtual void data_receive(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet)=0;
        virtual void disconnect(ENetPeer *peer,
                const unsigned char channel,
                ENetPacket *packet)=0;
};

class Network {
    public:
        Network();
        virtual ~Network();
        void stop();
        void set_handler(NetworkHandler *handler);
        //void send_data();
        void start_loop();
        void wait();
        virtual void send_data(const std::string &data)=0;
    protected:
        NetworkHandler *handler;
        ENetHost *host;
    private:
        void event_dispatch();
        bool stop_flag;
        boost::thread *loop_thread;
};

class NetServer:public Network{
    public:
        NetServer();
        NetServer(NetworkHandler *handler);
        ~NetServer();
        void start_server(const std::string &hostname,int port);
        void send_data(const std::string &data);
    private:
        ENetAddress address;
};

class NetClient:public Network{
    public:
        NetClient();
        NetClient(NetworkHandler *handler);
        ~NetClient();
        void start_client();
        void connect(const std::string &hostname,int port);
        void send_data(const std::string &data);
    private:
        ENetPeer *peer;
};
#endif
