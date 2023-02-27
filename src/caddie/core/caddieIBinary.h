#ifndef CADDIE_CORE_I_BINARY_H
#define CADDIE_CORE_I_BINARY_H
#include "types_caddie.h"

#define CADDIE_BIN_VERSION(major, minor) ((major << 8) | minor)

namespace caddie {

/**
 * @brief Interface for binary file serialization/deserialization
 */
class IBinary {
public:
    // Base structure for all binary blocks
    struct Block {
        union {
            char kind_str[4];
            u32 kind;
        };
        u32 size;
    };

    // Base structure for all Caddie file formats
    struct Header {
        Block block;   // at 0x0
        u16 version;   // at 0x8
        u16 numBlocks; // at 0xA
    };

public:
    virtual u32 GetBinaryKind() const = 0;
    virtual u16 GetVersion() const = 0;

    /**
     * @brief Common behavior before internal deserialization (check kind,
     * version, etc.)
     *
     * @param bin Binary
     */
    void Deserialize(const void* bin) {
        CADDIE_ASSERT(bin != NULL);
        const Header& header = *static_cast<const Header*>(bin);

        // Check header kind
        CADDIE_ASSERT_EX(GetBinaryKind() == header.block.kind,
                         "Not for this class. Got %s", header.block.kind_str);

        // Check header version
        CADDIE_ASSERT_EX(GetVersion() == header.version,
                         "Not for this version. Expected %04X, got %04X",
                         GetVersion(), header.version);

        DeserializeImpl(header);
    }

    /**
     * @brief Common behavior before internal serialization (write kind,
     * version, etc.)
     *
     * @param bin Binary
     */
    void Serialize(void* bin) const {
        CADDIE_ASSERT(bin != NULL);
        Header& header = *static_cast<Header*>(bin);

        header.version = GetVersion();
        header.block.kind = GetBinaryKind();

        SerializeImpl(header);
    }

private:
    virtual void DeserializeImpl(const Header& header) = 0;
    virtual void SerializeImpl(Header& header) const = 0;
};

} // namespace caddie

#endif
