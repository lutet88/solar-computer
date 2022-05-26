#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

uvec2_t uvec2_add(uvec2_t a, uvec2_t b) {
    return (uvec2_t) {a.x + b.x, a.y + b.y};
}
