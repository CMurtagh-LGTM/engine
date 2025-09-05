extern "C" {
#include <stdio.h>
}

#include <context.hpp>

struct A {
    int a;
};

int main() {
    printf("hi\n"); // NOLINT
    engine::Context ctx;

    auto test = engine::ContextObject<A>(&ctx, 3);

    printf("%d\n", test->a); // NOLINT
}
