#include <fit/pack.h>
#include <fit/always.h>
#include <memory>
#include "test.h"

FIT_TEST_CASE()
{
    static_assert(fit::pack(1, 2)(binary_class()) == 3, "static pack test failed");
    FIT_TEST_CHECK(fit::pack(1, 2)(binary_class()) == 3 );

    static_assert(fit::pack_decay(1, 2)(binary_class()) == 3, "static pack_decay test failed");
    FIT_TEST_CHECK(fit::pack_decay(1, 2)(binary_class()) == 3 );

    static_assert(fit::pack_forward(1, 2)(binary_class()) == 3, "static pack_forward test failed");
    FIT_TEST_CHECK(fit::pack_forward(1, 2)(binary_class()) == 3 );
}

FIT_TEST_CASE()
{
    static_assert(fit::pack()(fit::always(3)) == 3,  "static unary pack test failed");
    FIT_TEST_CHECK(fit::pack()(fit::always(3)) == 3 );
}

FIT_TEST_CASE()
{
    static_assert(fit::pack_join(fit::pack(1), fit::pack(2))(binary_class()) == 3, "static pack test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack(1), fit::pack(2))(binary_class()) == 3 );

    static_assert(fit::pack_join(fit::pack_decay(1), fit::pack_decay(2))(binary_class()) == 3, "static pack_decay test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack_decay(1), fit::pack_decay(2))(binary_class()) == 3 );

    static_assert(fit::pack_join(fit::pack_forward(1), fit::pack_forward(2))(binary_class()) == 3, "static pack_forward test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack_forward(1), fit::pack_forward(2))(binary_class()) == 3 );
}

FIT_TEST_CASE()
{
    static_assert(fit::pack_join(fit::pack(), fit::pack(1, 2))(binary_class()) == 3, "static pack test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack(), fit::pack(1, 2))(binary_class()) == 3 );

    static_assert(fit::pack_join(fit::pack_decay(), fit::pack_decay(1, 2))(binary_class()) == 3, "static pack_decay test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack_decay(), fit::pack_decay(1, 2))(binary_class()) == 3 );

    static_assert(fit::pack_join(fit::pack_forward(), fit::pack_forward(1, 2))(binary_class()) == 3, "static pack_forward test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack_forward(), fit::pack_forward(1, 2))(binary_class()) == 3 );
}

FIT_TEST_CASE()
{
    static_assert(fit::pack_join(fit::pack(1, 2), fit::pack())(binary_class()) == 3, "static pack test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack(1, 2), fit::pack())(binary_class()) == 3 );

    static_assert(fit::pack_join(fit::pack_decay(1, 2), fit::pack_decay())(binary_class()) == 3, "static pack_decay test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack_decay(1, 2), fit::pack_decay())(binary_class()) == 3 );

    static_assert(fit::pack_join(fit::pack_forward(1, 2), fit::pack_forward())(binary_class()) == 3, "static pack_forward test failed");
    FIT_TEST_CHECK(fit::pack_join(fit::pack_forward(1, 2), fit::pack_forward())(binary_class()) == 3 );
}

struct deref
{
    int operator()(const std::unique_ptr<int>& i) const
    {
        return *i;
    }
};

FIT_TEST_CASE()
{
    std::unique_ptr<int> i(new int(3));
    FIT_TEST_CHECK(fit::pack(i)(deref()) == 3);
    FIT_TEST_CHECK(fit::pack(std::unique_ptr<int>(new int(3)))(deref()) == 3);
    FIT_TEST_CHECK(fit::pack_forward(std::unique_ptr<int>(new int(3)))(deref()) == 3);
    FIT_TEST_CHECK(fit::pack_decay(std::unique_ptr<int>(new int(3)))(deref()) == 3);
    auto p = fit::pack(std::unique_ptr<int>(new int(3)));
    FIT_TEST_CHECK(p(deref()) == 3);

    FIT_TEST_CHECK(fit::pack_join(fit::pack(), fit::pack(std::unique_ptr<int>(new int(3))))(deref()) == 3);
    FIT_TEST_CHECK(fit::pack_join(fit::pack_forward(), fit::pack_forward(std::unique_ptr<int>(new int(3))))(deref()) == 3);
    FIT_TEST_CHECK(fit::pack_join(fit::pack_decay(), fit::pack_decay(std::unique_ptr<int>(new int(3))))(deref()) == 3);
    // FIT_TEST_CHECK(p(deref()) == 3);
}