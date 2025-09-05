#include "context.hpp"

extern "C" {
#include <stdlib.h>
}

void* operator new (size_t count, engine::Context& context) noexcept {
    if (count == 0) {
        count = 1;
    }

    return context.allocate(count);
}

namespace engine {

Context::Context() {
    arena = static_cast<char*>(malloc(DEFAULT_ARENA_SIZE)); // NOLINT
}

Context::~Context() {
    free(arena); //NOLINT
}

void* Context::allocate(size_t count) {
    index += count;
    // handle out of memory
    return arena + index - count; // NOLINT
}

void Context::deallocate(void* /*ptr*/, size_t /*count*/) {
    // TODO
}

}
