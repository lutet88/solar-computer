#ifndef INCLUDE_UTILS_H

#define INCLUDE_UTILS_H
#include <stdint.h>

typedef struct UVec2 {
    uint16_t x;
    uint16_t y;
} uvec2_t;

typedef struct UVec3 {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} uvec3_t;

typedef struct Vec2 {
    float x;
    float y;
} vec2_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} vec3_t;

#endif /* INCLUDE_UTILS_H */
