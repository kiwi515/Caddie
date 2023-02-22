#include "caddieMessage.h"

namespace caddie {

Message::Message(const void* bin) {
    CADDIE_ASSERT(bin != NULL);
    Deserialize(bin);
}

Message::~Message() {}

/**
 * @brief Deserialize binary message file
 *
 * @param bin Binary message (CMSG)
 */
void Message::DeserializeImpl(const Bin& bin) {
    // Find first block
    const Block* block = reinterpret_cast<const Block*>(&block) + sizeof(Bin);

    // Parse blocks
    for (int i = 0; i < bin.numBlocks; i++) {
        // Check block kind
        switch (block->kind) {
        case DESCBlock::scKind:
            mDescBlock = static_cast<const DESCBlock*>(block);
            break;
        case DATABlock::scKind:
            mDataBlock = static_cast<const DATABlock*>(block);
            break;
        default:
            CADDIE_ASSERT_EX(false, "Unknown block kind: %s", block->kind_str);
            break;
        }

        // Advance block pointer
        block = reinterpret_cast<const Block*>(
            reinterpret_cast<const u8*>(block) + block->size);
    }
}

/**
 * @brief Serialize binary message file
 *
 * @param bin Binary message (CMSG)
 */
void Message::SerializeImpl(Bin& bin) const {
    CADDIE_ASSERT_EX(false, "Not supported.");
}

/**
 * @brief Get message text by ID
 *
 * @param id Message ID
 * @return Message text
 */
const wchar_t* Message::GetMessage(u32 id) const {
    CADDIE_ASSERT(id < mDescBlock->numMsg);
    return reinterpret_cast<const wchar_t*>(mDataBlock->data +
                                            mDescBlock->msgOffsets[id]);
}

} // namespace caddie