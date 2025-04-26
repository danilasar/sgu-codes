#pragma once

#include "figure.hpp"

namespace ssu::figure {

static const Figure HARE = Figure(
    {
        ssu::Path(
            {{0.5f, 3.f}, {1.f, 4.5f},  {0.5f, 6.f}, {0.5f, 7.5f}, {1.f, 8.f},
             {1.5f, 8.f}, {2.f, 7.5f},  {1.5f, 6.f}, {1.5f, 4.5f}, {3.f, 4.5f},
             {3.f, 6.f},  {2.5f, 7.5f}, {3.f, 8.f},  {3.5f, 8.f},  {4.f, 7.5f},
             {4.f, 6.f},  {3.5f, 4.5f}, {4.f, 3.f},  {3.5f, 1.5f}, {2.5f, 1.f},
             {2.f, 1.f},  {1.f, 1.5f},  {0.5f, 3.f}},
            RED,
            2
        ),
        ssu::Path(
            {{1.5f, 3.5f}, {1.5f, 3.f}, {2.f, 3.f}, {2.f, 3.5f}, {1.5f, 3.5f}},
            GREEN,
            4
        ),
        ssu::Path(
            {{2.5f, 3.5f}, {2.5f, 3.f}, {3.f, 3.f}, {3.f, 3.5f}, {2.5f, 3.5f}},
            GREEN,
            4
        ),
    },
    8.5f,
    8.5f
);
} // namespace ssu::figure
