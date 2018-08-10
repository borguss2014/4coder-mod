/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 15.05.2015
 *
 * Math functions for 4coder
 *
 */

// TOP

#define C_MATH 1

/*
 * Scalar operators
 */

#define DEG_TO_RAD (0.0174533f)

inline f32
ABS(f32 x){
    if (x < 0) x = -x;
    return(x);
}

#if C_MATH
#include <math.h>

inline f32
MOD(f32 x, i32 m){
    f32 whole;
    f32 frac = modff(x, &whole);
    f32 r = ((i32)(whole) % m) + frac;
    return(r);
}

inline f32
SQRT(f32 x){
    f32 r = sqrtf(x);
    return(r);
}

inline f32
SIN(f32 x_degrees){
    f32 r = sinf(x_degrees * DEG_TO_RAD);
    return(r);
}

inline f32
COS(f32 x_degrees){
    f32 r = cosf(x_degrees * DEG_TO_RAD);
    return(r);
}
#endif

/*
 * Vectors
 */

struct Vec2{
    union{
        struct{
            f32 x, y;
        };
        struct{
            f32 v[2];
        };
    };
};

struct Vec3{
    union{
        struct{
            f32 x, y, z;
        };
        struct{
            f32 r, g, b;
        };
        struct{
            Vec2 xy;
            f32 _z;
        };
        struct{
            f32 _x;
            Vec2 yz;
        };
        struct{
            f32 v[3];
        };
    };
};

struct Vec4{
    union{
        struct{
            f32 r, g, b, a;
        };
        
        struct{
            f32 h, s, l, __a;
        };
        struct{
            f32 x, y, z, w;
        };
        struct{
            Vec3 rgb;
            f32 _a;
        };
        struct{
            Vec3 xyz;
            f32 _w;
        };
        struct{
            f32 _x;
            Vec3 yzw;
        };
        struct{
            f32 v[4];
        };
    };
};

inline internal Vec2
V2(f32 x, f32 y){
    Vec2 result;
    result.x = x;
    result.y = y;
    return result;
}

inline internal Vec3
V3(f32 x, f32 y, f32 z){
    Vec3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

inline internal Vec4
V4(f32 x, f32 y, f32 z, f32 w){
    Vec4 result;
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;
    return result;
}

inline internal Vec2
operator+(Vec2 a, Vec2 b){
    Vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

inline internal Vec3
operator+(Vec3 a, Vec3 b){
    Vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

inline internal Vec4
operator+(Vec4 a, Vec4 b){
    Vec4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

inline internal Vec2
operator-(Vec2 a, Vec2 b){
    Vec2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

inline internal Vec3
operator-(Vec3 a, Vec3 b){
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

inline internal Vec4
operator-(Vec4 a, Vec4 b){
    Vec4 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

inline internal Vec2
operator*(Vec2 a, f32 k){
    Vec2 result;
    result.x = a.x * k;
    result.y = a.y * k;
    return result;
}

inline internal Vec3
operator*(Vec3 a, f32 k){
    Vec3 result;
    result.x = a.x * k;
    result.y = a.y * k;
    result.z = a.z * k;
    return result;
}

inline internal Vec4
operator*(Vec4 a, f32 k){
    Vec4 result;
    result.x = a.x * k;
    result.y = a.y * k;
    result.z = a.z * k;
    result.w = a.w * k;
    return result;
}

inline internal Vec2
operator*(f32 k, Vec2 a){
    Vec2 result;
    result.x = a.x * k;
    result.y = a.y * k;
    return result;
}

inline internal Vec3
operator*(f32 k, Vec3 a){
    Vec3 result;
    result.x = a.x * k;
    result.y = a.y * k;
    result.z = a.z * k;
    return result;
}

inline internal Vec4
operator*(f32 k, Vec4 a){
    Vec4 result;
    result.x = a.x * k;
    result.y = a.y * k;
    result.z = a.z * k;
    result.w = a.w * k;
    return result;
}

inline internal Vec2&
operator+=(Vec2 &a, Vec2 b){
    a = (a + b);
    return a;
}

inline internal Vec3&
operator+=(Vec3 &a, Vec3 b){
    a = (a + b);
    return a;
}

inline internal Vec4&
operator+=(Vec4 &a, Vec4 b){
    a = (a + b);
    return a;
}

inline internal Vec2&
operator-=(Vec2 &a, Vec2 b){
    a = (a - b);
    return a;
}

inline internal Vec3&
operator-=(Vec3 &a, Vec3 b){
    a = (a - b);
    return a;
}

inline internal Vec4&
operator-=(Vec4 &a, Vec4 b){
    a = (a - b);
    return a;
}

inline internal Vec2&
operator*=(Vec2 &a, f32 k){
    a = (a * k);
    return a;
}

inline internal Vec3&
operator*=(Vec3 &a, f32 k){
    a = (a * k);
    return a;
}

inline internal Vec4&
operator*=(Vec4 &a, f32 k){
    a = (a * k);
    return a;
}

inline internal f32
dot(Vec2 a, Vec2 b){
    f32 result;
    result = a.x*b.x + a.y*b.y;
    return result;
}

inline internal f32
dot(Vec3 a, Vec3 b){
    f32 result;
    result = a.x*b.x + a.y*b.y + a.z*b.z;
    return result;
}

inline internal f32
dot(Vec4 a, Vec4 b){
    f32 result;
    result = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
    return result;
}

inline internal Vec3
cross(Vec3 a, Vec3 b){
    Vec3 result;
    result.x = a.y*b.z - b.y*a.z;
    result.y = a.z*b.x - b.z*a.x;
    result.z = a.x*b.y - b.x*a.y;
    return result;
}

inline internal Vec2
hadamard(Vec2 a, Vec2 b){
    Vec2 result;
    result.x = a.x*b.x;
    result.y = a.y*b.y;
    return result;
}

inline internal Vec3
hadamard(Vec3 a, Vec3 b){
    Vec3 result;
    result.x = a.x*b.x;
    result.y = a.y*b.y;
    result.z = a.z*b.z;
    return result;
}

inline internal Vec4
hadamard(Vec4 a, Vec4 b){
    Vec4 result;
    result.x = a.x*b.x;
    result.y = a.y*b.y;
    result.z = a.z*b.z;
    result.w = a.w*b.w;
    return result;
}

inline internal Vec2
perp(Vec2 v){
    Vec2 result;
    result.x = -v.y;
    result.y = v.x;
    return result;
}

inline Vec2
polar_to_cartesian(f32 theta_degrees, f32 length){
    Vec2 result;
    result.x = COS(theta_degrees)*length;
    result.y = SIN(theta_degrees)*length;
    return result;
}

inline Vec2
rotate(Vec2 v, f32 theta_degrees){
    Vec2 result;
    f32 c, s;
    c = COS(theta_degrees);
    s = SIN(theta_degrees);
    result.x = v.x*c - v.y*s;
    result.y = v.x*s + v.y*c;
    return result;
}

/*
 * Lerps, Clamps, Thresholds, Etc
 */

inline f32
lerp(f32 a, f32 t, f32 b){
    return(a + (b-a)*t);
}

inline i32
lerp(i32 a, f32 t, i32 b){
    return ((i32)(lerp((f32)a, t, (f32)b)));
}

inline Vec2
lerp(Vec2 a, f32 t, Vec2 b){
    return(a + (b-a)*t);
}

inline Vec3
lerp(Vec3 a, f32 t, Vec3 b){
    return(a + (b-a)*t);
}

inline Vec4
lerp(Vec4 a, f32 t, Vec4 b){
    return(a + (b-a)*t);
}

inline f32
unlerp(f32 a, f32 x, f32 b){
    f32 r = x;
    if (b > a){
        r = (x - a) / (b - a);
    }
    return(r);
}

inline f32
clamp(f32 a, f32 n, f32 z){
    if (n < a) n = a;
    else if (n  > z) n = z;
    return (n);
}

inline i32
clamp(i32 a, i32 n, i32 z){
    if (n < a) n = a;
    else if (n  > z) n = z;
    return (n);
}

inline u32
clamp(u32 a, u32 n, u32 z){
    if (n < a) n = a;
    else if (n  > z) n = z;
    return (n);
}

#define clamp_top(a,b) Min(a,b)
#define clamp_bottom(a,b) Max(a,b)

/*
 * Color
 */

// TODO(allen): Convert colors to Vec4
inline u32
color_blend(u32 a, f32 t, u32 b){
    union{
        u8 byte[4];
        u32 comp;
    } A, B, R;
    
    A.comp = a;
    B.comp = b;
    
    R.byte[0] = (u8)lerp(A.byte[0], t, B.byte[0]);
    R.byte[1] = (u8)lerp(A.byte[1], t, B.byte[1]);
    R.byte[2] = (u8)lerp(A.byte[2], t, B.byte[2]);
    R.byte[3] = (u8)lerp(A.byte[3], t, B.byte[3]);
    
    return R.comp;
}

inline Vec3
unpack_color3(u32 color){
    Vec3 result;
    result.r = ((color >> 16) & 0xFF) / 255.f;
    result.g = ((color >> 8) & 0xFF) / 255.f;
    result.b = ((color >> 0) & 0xFF) / 255.f;
    return result;
}

inline Vec4
unpack_color4(u32 color){
    Vec4 result;
    result.a = ((color >> 24) & 0xFF) / 255.f;
    result.r = ((color >> 16) & 0xFF) / 255.f;
    result.g = ((color >> 8) & 0xFF) / 255.f;
    result.b = ((color >> 0) & 0xFF) / 255.f;
    return result;
}

inline u32
pack_color4(Vec4 color){
    u32 result =
        ((u8)(color.a * 255) << 24) |
        ((u8)(color.r * 255) << 16) |
        ((u8)(color.g * 255) << 8) |
        ((u8)(color.b * 255) << 0);
    return result;
}

internal Vec4
rgba_to_hsla(Vec4 rgba){
    Vec4 hsla = {};
    f32 max, min, delta;
    i32 maxc;
    hsla.a = rgba.a;
    max = rgba.r; min = rgba.r;
    maxc = 0;
    if (rgba.r < rgba.g){
        max = rgba.g;
        maxc = 1;
    }
    if (rgba.b > max){
        max = rgba.b;
        maxc = 2;
    }
    if (rgba.r > rgba.g){
        min = rgba.g;
    }
    if (rgba.b < min){
        min = rgba.b;
    }
    delta = max - min;
    
    hsla.z = (max + min) * .5f;
    if (delta == 0){
        hsla.x = 0.f;
        hsla.y = 0.f;
    }
    else{
        switch (maxc){
            case 0:
            {
                hsla.x = (rgba.g - rgba.b) / delta;
                hsla.x += (rgba.g < rgba.b) * 6.f;
            }break;
            
            case 1:
            {
                hsla.x = (rgba.b - rgba.r) / delta;
                hsla.x += 2.f;
            }break;
            
            case 2:
            {
                hsla.x = (rgba.r - rgba.g) / delta;
                hsla.x += 4.f;
            }break;
        }
        hsla.x *= (1/6.f); // * 60 / 360
        hsla.y = delta / (1.f - ABS(2.f*hsla.z - 1.f));
    }
    
    return hsla;
}

internal Vec4
hsla_to_rgba(Vec4 hsla){
    if (hsla.h >= 1.f) hsla.h = 0.f;
    Vec4 rgba = {0};
    f32 C = (1.f - ABS(2*hsla.z - 1.f)) * hsla.y;
    f32 X = C * (1.f-ABS(MOD(hsla.x*6.f, 2)-1.f));
    f32 m = hsla.z - C*.5f;
    i32 H = floor32(hsla.x * 6.f);
    rgba.a = hsla.a;
    switch (H){
        case 0: rgba.r = C; rgba.g = X; rgba.b = 0; break;
        case 1: rgba.r = X; rgba.g = C; rgba.b = 0; break;
        case 2: rgba.r = 0; rgba.g = C; rgba.b = X; break;
        case 3: rgba.r = 0; rgba.g = X; rgba.b = C; break;
        case 4: rgba.r = X; rgba.g = 0; rgba.b = C; break;
        case 5: rgba.r = C; rgba.g = 0; rgba.b = X; break;
    }
    rgba.r += m;
    rgba.g += m;
    rgba.b += m;
    return(rgba);
}

//
// Rectangle Operations
//

inline i32_Rect
i32R(int32_t l, int32_t t, int32_t r, int32_t b){
    i32_Rect rect;
    rect.x0 = l; rect.y0 = t;
    rect.x1 = r; rect.y1 = b;
    return(rect);
}

inline i32_Rect
i32R(f32_Rect r){
    i32_Rect rect;
    rect.x0 = (i32)r.x0;
    rect.y0 = (i32)r.y0;
    rect.x1 = (i32)r.x1;
    rect.y1 = (i32)r.y1;
    return(rect);
}

inline f32_Rect
f32R(float l, float t, float r, float b){
    f32_Rect rect;
    rect.x0 = l; rect.y0 = t;
    rect.x1 = r; rect.y1 = b;
    return(rect);
}

inline f32_Rect
f32R(i32_Rect r){
    f32_Rect rect;
    rect.x0 = (float)r.x0;
    rect.y0 = (float)r.y0;
    rect.x1 = (float)r.x1;
    rect.y1 = (float)r.y1;
    return(rect);
}

inline int32_t
rect_equal(i32_Rect r1, i32_Rect r2){
    int32_t result = (r1.x0 == r2.x0 && r1.y0 == r2.y0 && r1.x1 == r2.x1 && r1.y1 == r2.y1);
    return(result);
}

inline int32_t
hit_check(int32_t x, int32_t y, int32_t x0, int32_t y0, int32_t x1, int32_t y1){
    return (x >= x0 && x < x1 && y >= y0 && y < y1);
}

inline int32_t
hit_check(int32_t x, int32_t y, i32_Rect rect){
    return (hit_check(x, y, rect.x0, rect.y0, rect.x1, rect.y1));
}

inline i32_Rect
get_inner_rect(i32_Rect outer, i32 margin){
    i32_Rect r;
    r.x0 = outer.x0 + margin;
    r.y0 = outer.y0 + margin;
    r.x1 = outer.x1 - margin;
    r.y1 = outer.y1 - margin;
    return(r);
}

inline f32_Rect
get_inner_rect(f32_Rect outer, f32 margin){
    f32_Rect r;
    r.x0 = outer.x0 + margin;
    r.y0 = outer.y0 + margin;
    r.x1 = outer.x1 - margin;
    r.y1 = outer.y1 - margin;
    return(r);
}

inline int32_t
fits_inside(i32_Rect rect, i32_Rect outer){
    return(rect.x0 >= outer.x0 && rect.x1 <= outer.x1 && rect.y0 >= outer.y0 && rect.y1 <= outer.y1);
}

static int32_t
interval_overlap(float a0, float a1, float b0, float b1){
    if (a0 <= b0 && b0 < a1 ||
        b0 <= a0 && a0 < b1){
        return(true);
    }
    return(false);
}

static int32_t
rect_opverlap(f32_Rect a, f32_Rect b){
    if (interval_overlap(a.x0, a.x1, b.x0, b.x1) &&
        interval_overlap(a.y0, a.y1, b.y0, b.y1)){
        return(true);
    }
    return(false);
}

// BOTTOM

