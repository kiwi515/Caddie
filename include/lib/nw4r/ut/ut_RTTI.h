#ifndef NW4R_UT_RTTI_H
#define NW4R_UT_RTTI_H
#include <types_nw4r.h>

// Declare type RTTI and accessor function
#define NW4R_UT_RTTI_DECL(T)                                                   \
    static nw4r::ut::detail::RuntimeTypeInfo typeInfo;                         \
    virtual const nw4r::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo()      \
        const {                                                                \
        return &typeInfo;                                                      \
    }

// Define type RTTI (base type)
#define NW4R_UT_RTTI_DEF_BASE(T)                                               \
    nw4r::ut::detail::RuntimeTypeInfo T::typeInfo(NULL)

// Define type RTTI (derived type)
#define NW4R_UT_RTTI_DEF_DERIVED(T, BASE)                                      \
    nw4r::ut::detail::RuntimeTypeInfo T::typeInfo(&BASE::typeInfo)

namespace nw4r {
namespace ut {
namespace detail {

struct RuntimeTypeInfo {
    RuntimeTypeInfo(const RuntimeTypeInfo* base) : mBase(base) {}

    bool IsDerivedFrom(const RuntimeTypeInfo* base) const {
        for (const RuntimeTypeInfo* it = this; it != NULL; it = it->mBase) {
            if (it == base) {
                return true;
            }
        }

        return false;
    }

    const RuntimeTypeInfo* mBase; // at 0x0
};

template <typename T>
static const RuntimeTypeInfo* GetTypeInfoFromPtr_(T* ptr) {
    return ptr->typeInfo;
}

} // namespace detail

/**
 * Interface for polymorphic objects
 */
class IPolymorphic {
public:
    virtual const detail::RuntimeTypeInfo*
    GetRuntimeTypeInfo() const = 0; // at 0x8
};

/**
 * Attempt to downcast base type object to derived type object
 */
template <typename TDerived, typename TBase>
static TDerived DynamicCast(TBase* ptr) {
    // Derived type info
    const detail::RuntimeTypeInfo* derivedTypeInfo =
        detail::GetTypeInfoFromPtr_(static_cast<TDerived>(NULL));

    // Downcast if possible
    if (ptr->GetRuntimeTypeInfo()->IsDerivedFrom(derivedTypeInfo)) {
        return static_cast<TDerived>(ptr);
    }

    return NULL;
}

} // namespace ut
} // namespace nw4r

#endif
