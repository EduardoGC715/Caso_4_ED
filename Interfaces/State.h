# pragma once

enum State {
    UNAVAILABLE = 0,
    SEARCH      = 1,
    UNDERGROUND = 2,
    MINING      = 3,
    RETRIEVE    = 4,
    SCORE       = 5,
    DONE        = 6
};