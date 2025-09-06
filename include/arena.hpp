#pragma once

extern "C" {
#include <stddef.h>
}

namespace engine {

class Arena {
public:
    Arena(size_t size);
    ~Arena();
    Arena(const Arena&) = delete;
    Arena(Arena&&) = delete;
    Arena& operator=(const Arena&) = delete;
    Arena& operator=(Arena&&) = delete;

    void* allocate(size_t count);
    void deallocate(void* ptr, size_t count);

private:
    char* arena = nullptr;
    size_t index = 0;
};

};
