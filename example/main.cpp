extern "C" {
#include <stdio.h>
}

#include <context.hpp>

struct A {
    int a;
};

int main() {
    printf("hi\n"); // NOLINT

    auto test = engine::ContextObject<A>(3);

    printf("%d\n", test->a); // NOLINT
}
