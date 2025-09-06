#pragma once

extern "C" {
#include <stddef.h>
}

#include "arena.hpp"

namespace engine {
class Context;
}

void* operator new (size_t count, engine::Context& context) noexcept;

namespace engine {

constexpr size_t MEGABYTE = static_cast<const size_t>(1024 * 1024);
constexpr size_t DEFAULT_ARENA_SIZE = 256 * MEGABYTE;

class ContextBroker;

class Context {
public:
    void* allocate(size_t count);
    void deallocate(void* ptr, size_t count);

private:
    Arena arena{DEFAULT_ARENA_SIZE};

    Context() = default;
    friend ContextBroker;
};

class ContextBroker {
public:
    static Context& context();
};

template <typename T>
class ContextObject {
public:
    template <typename ...Args>
    ContextObject(Args... args) : m_ptr(new(ContextBroker::context()) T(args...)) {}

    ~ContextObject() {
        m_ptr->~T();
        ContextBroker::context().deallocate(m_ptr, sizeof(T));
    };
    ContextObject(const ContextObject&) = delete;
    ContextObject(ContextObject&& other);
    ContextObject& operator=(const ContextObject&) = delete;
    ContextObject& operator=(ContextObject&& other);

    T& operator*() { return m_ptr; }
    T* operator->() { return m_ptr; }
    const T& operator*() const { return m_ptr; }
    const T* operator->() const { return m_ptr; }
private:
    T* m_ptr;

    friend Context;
};

}
