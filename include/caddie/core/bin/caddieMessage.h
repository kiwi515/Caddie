#ifndef CADDIE_CORE_MESSAGE_H
#define CADDIE_CORE_MESSAGE_H
#include "caddieIBinary.h"
#include "types_caddie.h"

namespace caddie {

class Message : IBinary {
public:
    virtual u32 GetBinaryMagic() const { return 'CMSG'; }
    virtual u8 GetVersion() const { return CADDIE_BIN_VERSION(1, 0); }

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
    virtual void DeserializeImpl(const Bin& bin);
    virtual void SerializeImpl(Bin& bin) const;

private:
    // CMSG binary header
    Bin* mHeader;

    // Message descriptor block
    const DESCBlock* mDescBlock;
    // Message data pool block
    const DATABlock* mDataBlock;
};

} // namespace caddie

#endif
