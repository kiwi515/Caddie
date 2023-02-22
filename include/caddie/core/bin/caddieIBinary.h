#ifndef CADDIE_CORE_IBINARY_H
#define CADDIE_CORE_IBINARY_H
#include "types_caddie.h"

#define CADDIE_BIN_VERSION(major, minor) ((major << 8) | minor)

namespace caddie {

/**
 * @brief Interface for (de)serializing binary files
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
    struct Bin {
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
        const Bin& binary = *static_cast<const Bin*>(bin);

        // Check binary kind
        CADDIE_ASSERT_EX(GetBinaryKind() == binary.block.kind,
                         "Not for this class. Got %s", binary.block.kind_str);

        // Check binary version
        CADDIE_ASSERT_EX(GetVersion() == binary.version,
                         "Not for this version. Expected %04X, got %04X",
                         GetVersion(), binary.version);

        DeserializeImpl(binary);
    }

    /**
     * @brief Common behavior before internal deserialization (write kind,
     * version, etc.)
     *
     * @param bin Binary
     */
    void Serialize(void* bin) const {
        CADDIE_ASSERT(bin != NULL);
        Bin& binary = *static_cast<Bin*>(bin);

        binary.version = GetVersion();
        binary.block.kind = GetBinaryKind();

        SerializeImpl(binary);
    }

private:
    virtual void DeserializeImpl(const Bin& bin) = 0;
    virtual void SerializeImpl(Bin& bin) const = 0;
};

} // namespace caddie

#endif
