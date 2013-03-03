#include "network/network.h"
#include <iostream>
#include <enet/enet.h>
//#include <boost/thread/thread.hpp>
//#include <boost/bind.hpp>

NetworkHandler::NetworkHandler(){
}
NetworkHandler::~NetworkHandler(){
}
Network::Network() {
    if(enet_initialize()!=0) {
        std::cout<<"Could not initialize enet."<<std::endl;
    }
}
Network::~Network() {
    enet_deinitialize();
}

void Network::start_loop() {
    loop_thread = new boost::thread(
            boost::bind(&Network::event_dispatch,this));
}

void Network::wait() {
    loop_thread->join();
    delete loop_thread;
    loop_thread = NULL;
}

void Network::event_dispatch(){
    stop_flag = false;
    ENetEvent event;
    while(!stop_flag){
        if(enet_host_service(host, &event, 1000)>0) {
            switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    handler->connect(event.peer,
                            event.channelID,
                            event.packet);
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    handler->data_receive(event.peer,
                            event.channelID,
                            event.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    handler->disconnect(event.peer,
                            event.channelID,
                            event.packet);
                    break;
                default:
                    break;
            }
        }
    }
    enet_host_destroy(host);
    host=NULL;
}
void Network::stop() {
    stop_flag = true;
}

void Network::set_handler(NetworkHandler *handler) {
    this->handler = handler;
}
NetServer::NetServer() {
}

NetServer::NetServer(NetworkHandler *handler) {
    set_handler(handler);
}

NetServer::~NetServer() {
}

void NetServer::start_server(const std::string &hostname,int port) {
    enet_address_set_host(&address, hostname.c_str());
    address.port = port;
    host = enet_host_create(&address, 100, 2, 0, 0);
    if(host == NULL){
        std::cout<< "Could not start server."
                <<std::endl;
        return;
    }
}

void NetServer::send_data(const std::string &data) {
    ENetPacket *packet = enet_packet_create(
            data.c_str(),
            data.length()+1,
            ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(host,0,packet);
}

NetClient::NetClient() {
}

NetClient::NetClient(NetworkHandler *handler) {
    set_handler(handler);
}

NetClient::~NetClient() {
}

void NetClient::start_client() {
    host = enet_host_create(NULL, 1, 2, 5760/8, 1440/8);
}

void NetClient::connect(const std::string &hostname,int port) {
    ENetAddress address;
    enet_address_set_host(&address, hostname.c_str());
    address.port = port;
    peer = enet_host_connect(host, &address, 2, 0);
    if(peer == NULL){
        std::cout<<
            "Could not connect to server"
                <<std::endl;
        return;
    }
    ENetEvent event;
    if(enet_host_service(host, &event, 1000) > 0 &&
            event.type == ENET_EVENT_TYPE_CONNECT) {
        handler->connect(event.peer,
                event.channelID,
                event.packet);
    }else{
        enet_peer_reset(peer);
        std::cout<<
            "Connection to failed."
                <<std::endl;
        return;
    }
}

void NetClient::send_data(const std::string &data) {
    ENetPacket *packet = enet_packet_create(
            data.c_str(),
            data.length()+1,
            ENET_PACKET_FLAG_RELIABLE);
    enet_host_broadcast(host,0,packet);
}

