#include "caddieMemoryMgr.hpp"

namespace caddie {

MemoryMgr::MemoryMgr() : mStaticHeap(NULL), mSceneHeap(NULL) {
    CreateStaticHeap();
}

MemoryMgr::~MemoryMgr() {
    delete mSceneHeap;
    mSceneHeap = NULL;

    delete mStaticHeap;
    mStaticHeap = NULL;
}

/**
 * @brief Create static heap
 */
void MemoryMgr::CreateStaticHeap() {
    CADDIE_ASSERT(mStaticHeap == NULL);

    mStaticHeap = EGG::ExpHeap::create(scStaticHeapSize, NULL, 0);
    CADDIE_ASSERT_EX(mStaticHeap != NULL, "Static heap creation failed!!!");
}

/**
 * @brief Create scene heap
 */
void MemoryMgr::CreateSceneHeap() {
    CADDIE_ASSERT(mStaticHeap != NULL && mSceneHeap == NULL);

    mSceneHeap = EGG::ExpHeap::create(scSceneHeapSize, mStaticHeap, 0);
    CADDIE_ASSERT_EX(mSceneHeap != NULL, "Scene heap creation failed!!!");
}

/**
 * @brief Destroy scene heap
 */
void MemoryMgr::DestroySceneHeap() {
    CADDIE_ASSERT(mSceneHeap != NULL);

    delete mSceneHeap;
    mSceneHeap = NULL;
}

/**
 * @brief Allocate from static heap
 *
 * @param size Size
 * @param align Alignment
 * @return void* Memory block
 */
void* MemoryMgr::Alloc(size_t size, int align) {
    CADDIE_ASSERT(mStaticHeap != NULL);
    return mStaticHeap->alloc(size, align);
}

/**
 * @brief Allocate from specified heap
 *
 * @param size Size
 * @param align Alignment
 * @param heap Parent heap
 * @return void* Memory block
 */
void* MemoryMgr::Alloc(size_t size, int align, EGG::Heap* heap) {
    CADDIE_ASSERT(heap != NULL);
    return heap->alloc(size, align);
}

/**
 * @brief Free memory to static heap
 *
 * @param block Memory block
 */
void MemoryMgr::Free(void* block) {
    CADDIE_ASSERT(mStaticHeap != NULL);
    mStaticHeap->free(block);
}

/**
 * @brief Free memory to specified heap
 *
 * @param block Memory block
 * @param heap Block parent heap
 */
void MemoryMgr::Free(void* block, EGG::Heap* heap) {
    CADDIE_ASSERT(heap != NULL);
    heap->free(block);
}

} // namespace caddie

/**
 * New
 */
void* operator new(size_t size) {
    return caddie::MemoryMgr::GetInstance().Alloc(size, 4);
}
void* operator new(size_t size, EGG::Heap* heap) {
    return caddie::MemoryMgr::GetInstance().Alloc(size, 4, heap);
}

/**
 * New array
 */
void* operator new[](size_t size) {
    return caddie::MemoryMgr::GetInstance().Alloc(size, 4);
}
void* operator new[](size_t size, EGG::Heap* heap) {
    return caddie::MemoryMgr::GetInstance().Alloc(size, 4, heap);
}

/**
 * Delete
 */
void operator delete(void* block) {
    caddie::MemoryMgr::GetInstance().Free(block);
}
void operator delete(void* block, EGG::Heap* heap) {
    caddie::MemoryMgr::GetInstance().Free(block, heap);
}

/**
 * Delete array
 */
void operator delete[](void* block) {
    caddie::MemoryMgr::GetInstance().Free(block);
}
void operator delete[](void* block, EGG::Heap* heap) {
    caddie::MemoryMgr::GetInstance().Free(block, heap);
}
