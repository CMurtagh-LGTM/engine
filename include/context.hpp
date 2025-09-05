#pragma once

extern "C" {
#include <stddef.h>
}

namespace engine {
class Context;
}

void* operator new (size_t count, engine::Context& context) noexcept;

namespace engine {

constexpr size_t MEGABYTE = static_cast<const size_t>(1024 * 1024);
constexpr size_t DEFAULT_ARENA_SIZE = 0;

template <typename T>
class ContextObject;

class Context {
public:
    Context();
    ~Context();
    Context(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&) = delete;

    void* allocate(size_t count);
    void deallocate(void* ptr, size_t count);

private:
    char* arena = nullptr;
    size_t index = 0;
};

template <typename T>
class ContextObject {
public:
    template <typename ...Args>
    ContextObject(Context* context, Args... args) : m_ptr(new(*context) T(args...)), m_context(context) {}

    ~ContextObject() {
        m_ptr->~T();
        m_context->deallocate(m_ptr, sizeof(T));
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
    Context* m_context;

    friend Context;
};

}
