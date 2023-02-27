#include "caddieRvlRichPresence.h"

#include <RevoSDK/IPC.h>
#include <RevoSDK/OS.h>
#include <cstdlib>
#include <cstring>

namespace caddie {

RvlRichPresence::RvlRichPresence(const char* client) : IRichPresence(client) {
    CADDIE_LOG("RvlRichPresence::RvlRichPresence");
    UpdateClient();
}

RvlRichPresence::~RvlRichPresence() {
    CADDIE_LOG("RvlRichPresence::~RvlRichPresence");
}

/**
 * @brief Whether there is an ongoing connection with the caddie_rpc script
 */
bool RvlRichPresence::IsConnected() const {
    CADDIE_LOG("RvlRichPresence::IsConnected");
    return true;
}

/**
 * @brief Retreive the current Unix epoch time (in seconds)
 */
u64 RvlRichPresence::GetTimeNow() const {
    CADDIE_LOG("RvlRichPresence::IsConnected");
    return 0;
}

/**
 * @brief Update Discord client/app ID
 */
void RvlRichPresence::UpdateClient() const {
    CADDIE_LOG("RvlRichPresence::UpdateClient");

    if (!IsConnected()) {
        CADDIE_LOG("Not connected to caddie_rpc!");
        return;
    }
}

/**
 * @brief Update Discord presence status
 */
void RvlRichPresence::UpdatePresence() const {
    CADDIE_LOG("RvlRichPresence::UpdatePresence");

    if (!IsConnected()) {
        CADDIE_LOG("Not connected to caddie_rpc!");
        return;
    }
}

} // namespace caddie
