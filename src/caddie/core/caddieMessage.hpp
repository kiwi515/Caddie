#ifndef CADDIE_CORE_MESSAGE_H
#define CADDIE_CORE_MESSAGE_H
#include "caddieIBinary.hpp"
#include "types_caddie.hpp"

namespace caddie {

class Message : IBinary {
public:
    virtual u32 GetBinaryKind() const { return 'CMSG'; }
    virtual u16 GetVersion() const { return CADDIE_BIN_VERSION(0x01, 0x00); }

private:
    // Message descriptor block
    struct DESCBlock : Block {
        static const u32 scKind = 'DESC';
        u32 numMsg;
        u32 msgOffsets[];
    };

    // Message pool data block
    struct DATABlock : Block {
        static const u32 scKind = 'DATA';
        char data[];
    };

public:
    Message(const void* bin);
    virtual ~Message();

    const wchar_t* GetMessage(u32 id) const;

private:
    virtual void DeserializeImpl(const Header& header);
    virtual void SerializeImpl(Header& header) const;

private:
    // CMSG binary header
    Header* mHeader;

    // Message descriptor block
    const DESCBlock* mDescBlock;
    // Message data pool block
    const DATABlock* mDataBlock;
};

} // namespace caddie

#endif
