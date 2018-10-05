#include <StaticHook.h>
#include <string>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

class NetworkIdentifier;

class ClientToServerHandshakePacket;

struct ServerNetworkHandler {
    void handle(NetworkIdentifier const &, ClientToServerHandshakePacket const &);
};

TInstanceHook(void, _ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK11LoginPacket, ServerNetworkHandler,
              NetworkIdentifier const &netId,
              void *packet) {
    original(this, netId, packet);
    ClientToServerHandshakePacket *handshakePacket = nullptr;
    this->handle(netId, *handshakePacket);
}

struct NetworkIdentifier {
};
struct Packet {
    size_t vt;
};

static auto vt_ServerToClientHandshakePacket =
        (size_t) dlsym(MinecraftHandle(), "_ZTV29ServerToClientHandshakePacket") + 0x10;

TClasslessInstanceHook(void, _ZN12PacketSender19sendToPrimaryClientERK17NetworkIdentifierRK6Packet,
                       NetworkIdentifier const &id, Packet const &pkt) {
    if (pkt.vt != vt_ServerToClientHandshakePacket) original(this, id, pkt);
}

TClasslessInstanceHook(void,
                       _ZN20EncryptedNetworkPeer16enableEncryptionERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE) {}

#pragma clang diagnostic pop