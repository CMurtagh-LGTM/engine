#include "context.hpp"

void* operator new (size_t count, engine::Context& context) noexcept {
    if (count == 0) {
        count = 1;
    }

    return context.allocate(count);
}

namespace engine {

void* Context::allocate(size_t count) {
    return arena.allocate(count);
}

void Context::deallocate(void* ptr, size_t count) {
    arena.deallocate(ptr, count);
}

Context& ContextBroker::context() {
    static Context context{};
    return context;
}

}
