#include "arena.hpp"

extern "C" {
#include <stdlib.h>
}

namespace engine {

Arena::Arena(size_t size) {
    arena = static_cast<char*>(malloc(size)); // NOLINT
}

Arena::~Arena() {
    free(arena); // NOLINT
}

void* Arena::allocate(size_t count) {
    index += count;
    // handle out of memory
    return arena + index - count; // NOLINT
}

void Arena::deallocate(void* /*ptr*/, size_t /*count*/) {
    // TODO
}

}
