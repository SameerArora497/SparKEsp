#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
    float x;
    float y;

    Vector2() {
        Init();
    }

    Vector2(float X, float Y) {
        Init(X, Y);
    }

    void Init(float ix = 0.0f, float iy = 0.0f) {
        x = ix;
        y = iy;
    }

    static Vector2 Zero() {
        return Vector2(0.0f, 0.0f);
    }

    static Vector2 Up() {
        return Vector2(0.0f, 1.0f);
    }

    static Vector2 Down() {
        return Vector2(0.0f, -1.0f);
    }

    static Vector2 Back() {
        return Vector2(0.0f, 0.0f);
    }

    static Vector2 Forward() {
        return Vector2(0.0f, 0.0f);
    }

    static Vector2 Left() {
        return Vector2(-1.0f, 0.0f);
    }

    static Vector2 Right() {
        return Vector2(1.0f, 0.0f);
    }

    float &operator[](int i) {
        return ((float *) this)[i];
    }

    float operator[](int i) const {
        return ((float *) this)[i];
    }

    bool operator==(const Vector2 &src) const {
        return (src.x == x) && (src.y == y);
    }

    bool operator!=(const Vector2 &src) const {
        return (src.x != x) || (src.y != y);
    }

    Vector2 &operator+=(const Vector2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2 &operator-=(const Vector2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2 &operator*=(float fl) {
        x *= fl;
        y *= fl;
        return *this;
    }

    Vector2 &operator*=(const Vector2 &v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    Vector2 &operator/=(const Vector2 &v) {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    Vector2 &operator+=(float fl) {
        x += fl;
        y += fl;
        return *this;
    }

    Vector2 &operator/=(float fl) {
        x /= fl;
        y /= fl;
        return *this;
    }

    Vector2 &operator-=(float fl) {
        x -= fl;
        y -= fl;
        return *this;
    }

    Vector2 &operator=(const Vector2 &vOther) {
        x = vOther.x;
        y = vOther.y;
        return *this;
    }

    Vector2 operator-(void) const {
        return Vector2(-x, -y);
    }

    Vector2 operator+(const Vector2 &v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2 &v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator*(float fl) const {
        return Vector2(x * fl, y * fl);
    }

    Vector2 operator*(const Vector2 &v) const {
        return Vector2(x * v.x, y * v.y);
    }

    Vector2 operator/(float fl) const {
        return Vector2(x / fl, y / fl);
    }

    Vector2 operator/(const Vector2 &v) const {
        return Vector2(x / v.x, y / v.y);
    }
};

#endif
