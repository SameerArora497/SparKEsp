#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3(float x, float y) {
        this->x = x;
        this->y = y;
        this->z = 0;
    }

    static Vector3 Zero() {
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    static Vector3 Up() {
        return Vector3(0.0f, 1.0f, 0.0f);
    }

    static Vector3 Down() {
        return Vector3(0.0f, -1.0f, 0.0f);
    }

    static Vector3 Back() {
        return Vector3(0.0f, 0.0f, -1.0f);
    }

    static Vector3 Forward() {
        return Vector3(0.0f, 0.0f, 1.0f);
    }

    static Vector3 Left() {
        return Vector3(-1.0f, 0.0f, 0.0f);
    }

    static Vector3 Right() {
        return Vector3(1.0f, 0.0f, 0.0f);
    }

    float &operator[](int i) {
        return ((float *) this)[i];
    }

    float operator[](int i) const {
        return ((float *) this)[i];
    }

    bool operator==(const Vector3 &src) const {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }

    bool operator!=(const Vector3 &src) const {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    Vector3 &operator+=(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3 &operator*=(float fl) {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }

    Vector3 &operator*=(const Vector3 &v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    Vector3 &operator/=(const Vector3 &v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }

    Vector3 &operator+=(float fl) {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }

    Vector3 &operator/=(float fl) {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }

    Vector3 &operator-=(float fl) {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }

    Vector3 &operator=(const Vector3 &vOther) {
        x = vOther.x;
        y = vOther.y;
        z = vOther.z;
        return *this;
    }

    Vector3 operator-(void) const {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3 &v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3 &v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(float fl) const {
        return Vector3(x * fl, y * fl, z * fl);
    }

    Vector3 operator*(const Vector3 &v) const {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    Vector3 operator/(float fl) const {
        return Vector3(x / fl, y / fl, z / fl);
    }

    Vector3 operator/(const Vector3 &v) const {
        return Vector3(x / v.x, y / v.y, z / v.z);
    }

    static float Distance(Vector3 a, Vector3 b) {
        Vector3 vector = Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
        return sqrt(((vector.x * vector.x) + (vector.y * vector.y)) + (vector.z * vector.z));
    }

    static float Dot(Vector3 lhs, Vector3 rhs) {
        return (((lhs.x * rhs.x) + (lhs.y * rhs.y)) + (lhs.z * rhs.z));
    }

    float sqrMagnitude() const {
        return (x * x + y * y + z * z);
    }
};

#endif
