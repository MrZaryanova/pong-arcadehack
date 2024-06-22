#include <cassert>
#include <chrono>
#include <ratio>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <vector>
#include <optional>
#include <cstddef>
#include <filesystem>
#include <locale>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iterator>
#define SFML_VERSION_MAJOR      3
#define SFML_VERSION_MINOR      0
#define SFML_VERSION_PATCH      0
#define SFML_VERSION_IS_RELEASE false


////////////////////////////////////////////////////////////
// Identify the operating system
// see https://sourceforge.net/p/predef/wiki/Home/
////////////////////////////////////////////////////////////
#if defined(_WIN32)

// Windows
#define SFML_SYSTEM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(__APPLE__) && defined(__MACH__)

// Apple platform, see which one it is
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

// iOS
#define SFML_SYSTEM_IOS

#elif TARGET_OS_MAC

// macOS
#define SFML_SYSTEM_MACOS

#else

// Unsupported Apple system
#error This Apple operating system is not supported by SFML library

#endif

#elif defined(__unix__)

// UNIX system, see which one it is
#if defined(__ANDROID__)

// Android
#define SFML_SYSTEM_ANDROID

#elif defined(__linux__)

// Linux
#define SFML_SYSTEM_LINUX

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

// FreeBSD
#define SFML_SYSTEM_FREEBSD

#elif defined(__OpenBSD__)

// OpenBSD
#define SFML_SYSTEM_OPENBSD

#elif defined(__NetBSD__)

// NetBSD
#define SFML_SYSTEM_NETBSD

#else

// Unsupported UNIX system
#error This UNIX operating system is not supported by SFML library

#endif

#else

// Unsupported system
#error This operating system is not supported by SFML library

#endif


////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

#define SFML_DEBUG

#endif


////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if !defined(SFML_STATIC)

#if defined(SFML_SYSTEM_WINDOWS)

// Windows compilers need specific (and different) keywords for export and import
#define SFML_API_EXPORT __declspec(dllexport)
#define SFML_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif

#else // Linux, FreeBSD, macOS

#define SFML_API_EXPORT __attribute__((__visibility__("default")))
#define SFML_API_IMPORT __attribute__((__visibility__("default")))

#endif

#else

// Static build doesn't need import/export macros
#define SFML_API_EXPORT
#define SFML_API_IMPORT

#endif

/// system files
namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Represents an angle value.
///
////////////////////////////////////////////////////////////
class Angle
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Sets the angle value to zero.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Angle();

    ////////////////////////////////////////////////////////////
    /// \brief Return the angle's value in degrees
    ///
    /// \return Angle in degrees
    ///
    /// \see asRadians
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] constexpr float asDegrees() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return the angle's value in radians
    ///
    /// \return Angle in radians
    ///
    /// \see asDegrees
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] constexpr float asRadians() const;

    ////////////////////////////////////////////////////////////
    /// \brief Wrap to a range such that -180° <= angle < 180°
    ///
    /// Similar to a modulo operation, this returns a copy of the angle
    /// constrained to the range [-180°, 180°) == [-Pi, Pi).
    /// The resulting angle represents a rotation which is equivalent to *this.
    ///
    /// The name "signed" originates from the similarity to signed integers:
    /// <table>
    /// <tr>
    ///   <th></th>
    ///   <th>signed</th>
    ///   <th>unsigned</th>
    /// </tr>
    /// <tr>
    ///   <td>char</td>
    ///   <td>[-128, 128)</td>
    ///   <td>[0, 256)</td>
    /// </tr>
    /// <tr>
    ///   <td>Angle</td>
    ///   <td>[-180°, 180°)</td>
    ///   <td>[0°, 360°)</td>
    /// </tr>
    /// </table>
    ///
    /// \return Signed angle, wrapped to [-180°, 180°)
    ///
    /// \see wrapUnsigned
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] constexpr Angle wrapSigned() const;

    ////////////////////////////////////////////////////////////
    /// \brief Wrap to a range such that 0° <= angle < 360°
    ///
    /// Similar to a modulo operation, this returns a copy of the angle
    /// constrained to the range [0°, 360°) == [0, Tau) == [0, 2*Pi).
    /// The resulting angle represents a rotation which is equivalent to *this.
    ///
    /// The name "unsigned" originates from the similarity to unsigned integers:
    /// <table>
    /// <tr>
    ///   <th></th>
    ///   <th>signed</th>
    ///   <th>unsigned</th>
    /// </tr>
    /// <tr>
    ///   <td>char</td>
    ///   <td>[-128, 128)</td>
    ///   <td>[0, 256)</td>
    /// </tr>
    /// <tr>
    ///   <td>Angle</td>
    ///   <td>[-180°, 180°)</td>
    ///   <td>[0°, 360°)</td>
    /// </tr>
    /// </table>
    ///
    /// \return Unsigned angle, wrapped to [0°, 360°)
    ///
    /// \see wrapSigned
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] constexpr Angle wrapUnsigned() const;

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTNEXTLINE(readability-identifier-naming)
    static const Angle Zero; //!< Predefined 0 degree angle value

private:
    friend constexpr Angle degrees(float angle);
    friend constexpr Angle radians(float angle);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from a number of degrees
    ///
    /// This function is internal. To construct angle values,
    /// use sf::radians or sf::degrees instead.
    ///
    /// \param degrees Angle in degrees
    ///
    ////////////////////////////////////////////////////////////
    constexpr explicit Angle(float degrees);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    float m_degrees{}; //!< Angle value stored as degrees
};

////////////////////////////////////////////////////////////
/// \brief Construct an angle value from a number of degrees
///
/// \param angle Number of degrees
///
/// \return Angle value constructed from the number of degrees
///
/// \see radians
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle degrees(float angle);

////////////////////////////////////////////////////////////
/// \brief Construct an angle value from a number of radians
///
/// \param angle Number of radians
///
/// \return Angle value constructed from the number of radians
///
/// \see degrees
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle radians(float angle);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of == operator to compare two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return True if both angle values are equal
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator==(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of != operator to compare two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return True if both angle values are different
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator!=(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of < operator to compare two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return True if \a left is less than \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator<(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of > operator to compare two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return True if \a left is greater than \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator>(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of <= operator to compare two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return True if \a left is less than or equal to \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator<=(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of >= operator to compare two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return True if \a left is greater than or equal to \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator>=(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of unary - operator to negate an angle value.
///
/// Represents a rotation in the opposite direction.
///
/// \param right Right operand (an angle)
///
/// \return Negative of the angle value
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator-(Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary + operator to add two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return Sum of the two angle values
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator+(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary += operator to add/assign two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return Sum of the two angle values
///
////////////////////////////////////////////////////////////
constexpr Angle& operator+=(Angle& left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary - operator to subtract two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return Difference of the two angle values
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator-(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary -= operator to subtract/assign two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return Difference of the two angle values
///
////////////////////////////////////////////////////////////
constexpr Angle& operator-=(Angle& left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary * operator to scale an angle value
///
/// \param left  Left operand (an angle)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator*(Angle left, float right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary * operator to scale an angle value
///
/// \param left  Left operand (a number)
/// \param right Right operand (an angle)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator*(float left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary *= operator to scale/assign an angle value
///
/// \param left  Left operand (an angle)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
constexpr Angle& operator*=(Angle& left, float right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary / operator to scale an angle value
///
/// \param left  Left operand (an angle)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator/(Angle left, float right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary /= operator to scale/assign an angle value
///
/// \param left  Left operand (an angle)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
constexpr Angle& operator/=(Angle& left, float right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary / operator to compute the ratio of two angle values
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr float operator/(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary % operator to compute modulo of an angle value.
///
/// Right hand angle must be greater than zero.
///
/// Examples:
/// \code
/// sf::degrees(90) % sf::degrees(40)  // 10 degrees
/// sf::degrees(-90) % sf::degrees(40) // 30 degrees (not -10)
/// \endcode
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return \a left modulo \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator%(Angle left, Angle right);

////////////////////////////////////////////////////////////
/// \relates Angle
/// \brief Overload of binary %= operator to compute/assign remainder of an angle value
///
/// \param left  Left operand (an angle)
/// \param right Right operand (an angle)
///
/// \return \a left modulo \a right
///
////////////////////////////////////////////////////////////
constexpr Angle& operator%=(Angle& left, Angle right);

namespace Literals
{

////////////////////////////////////////////////////////////
/// \relates sf::Angle
/// \brief User defined literal for angles in degrees, e.g. 10.5_deg
///
/// \param angle Angle in degrees
///
/// \return \a Angle
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator"" _deg(long double angle);

////////////////////////////////////////////////////////////
/// \relates sf::Angle
/// \brief User defined literal for angles in degrees, e.g. 90_deg
///
/// \param angle Angle in degrees
///
/// \return \a Angle
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator"" _deg(unsigned long long int angle);

////////////////////////////////////////////////////////////
/// \relates sf::Angle
/// \brief User defined literal for angles in radians, e.g. 0.1_rad
///
/// \param angle Angle in radians
///
/// \return \a Angle
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator"" _rad(long double angle);

////////////////////////////////////////////////////////////
/// \relates sf::Angle
/// \brief User defined literal for angles in radians, e.g. 2_rad
///
/// \param angle Angle in radians
///
/// \return \a Angle
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Angle operator"" _rad(unsigned long long int angle);

} // namespace Literals

namespace priv
{
constexpr float pi = 3.141592654f;

constexpr float positiveRemainder(float a, float b)
{
    assert(b > 0.0f && "Cannot calculate remainder with non-positive divisor");
    const float val = a - static_cast<float>(static_cast<int>(a / b)) * b;
    if (val >= 0.f)
        return val;
    else
        return val + b;
}
} // namespace priv


////////////////////////////////////////////////////////////
constexpr Angle::Angle() = default;


////////////////////////////////////////////////////////////
constexpr float Angle::asDegrees() const
{
    return m_degrees;
}


////////////////////////////////////////////////////////////
constexpr float Angle::asRadians() const
{
    return m_degrees * (priv::pi / 180);
}


////////////////////////////////////////////////////////////
constexpr Angle Angle::wrapSigned() const
{
    return degrees(priv::positiveRemainder(m_degrees + 180, 360) - 180);
}

} 

#if defined(SFML_SYSTEM_EXPORTS)

#define SFML_SYSTEM_API SFML_API_EXPORT

#else

#define SFML_SYSTEM_API SFML_API_IMPORT

#endif

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Class template for manipulating
///        2-dimensional vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class Vector2
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates a Vector2(0, 0).
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from cartesian coordinates
    ///
    /// \param x X coordinate
    /// \param y Y coordinate
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2(T x, T y);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from another type of vector
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param vector Vector to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    constexpr explicit Vector2(const Vector2<U>& vector);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from polar coordinates <i><b>(floating-point)</b></i>
    ///
    /// \param r   Length of vector (can be negative)
    /// \param phi Angle from X axis
    ///
    /// Note that this constructor is lossy: calling length() and angle()
    /// may return values different to those provided in this constructor.
    ///
    /// In particular, these transforms can be applied:
    /// * Vector2(r, phi) == Vector2(-r, phi + 180_deg)
    /// * Vector2(r, phi) == Vector2(r, phi + n * 360_deg)
    ///
    ////////////////////////////////////////////////////////////
    SFML_SYSTEM_API Vector2(T r, Angle phi);

    ////////////////////////////////////////////////////////////
    /// \brief Length of the vector <i><b>(floating-point)</b></i>.
    ///
    /// If you are not interested in the actual length, but only in comparisons, consider using lengthSq().
    ///
    ////////////////////////////////////////////////////////////
    SFML_SYSTEM_API T length() const;

    ////////////////////////////////////////////////////////////
    /// \brief Square of vector's length.
    ///
    /// Suitable for comparisons, more efficient than length().
    ///
    ////////////////////////////////////////////////////////////
    constexpr T lengthSq() const;

    ////////////////////////////////////////////////////////////
    /// \brief Vector with same direction but length 1 <i><b>(floating-point)</b></i>.
    ///
    /// \pre \c *this is no zero vector.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] SFML_SYSTEM_API Vector2 normalized() const;

    ////////////////////////////////////////////////////////////
    /// \brief Signed angle from \c *this to \c rhs <i><b>(floating-point)</b></i>.
    ///
    /// \return The smallest angle which rotates \c *this in positive
    /// or negative direction, until it has the same direction as \c rhs.
    /// The result has a sign and lies in the range [-180, 180) degrees.
    /// \pre Neither \c *this nor \c rhs is a zero vector.
    ///
    ////////////////////////////////////////////////////////////
    SFML_SYSTEM_API Angle angleTo(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Signed angle from +X or (1,0) vector <i><b>(floating-point)</b></i>.
    ///
    /// For example, the vector (1,0) corresponds to 0 degrees, (0,1) corresponds to 90 degrees.
    ///
    /// \return Angle in the range [-180, 180) degrees.
    /// \pre This vector is no zero vector.
    ///
    ////////////////////////////////////////////////////////////
    SFML_SYSTEM_API Angle angle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Rotate by angle \c phi <i><b>(floating-point)</b></i>.
    ///
    /// Returns a vector with same length but different direction.
    ///
    /// In SFML's default coordinate system with +X right and +Y down,
    /// this amounts to a clockwise rotation by \c phi.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] SFML_SYSTEM_API Vector2 rotatedBy(Angle phi) const;

    ////////////////////////////////////////////////////////////
    /// \brief Projection of this vector onto \c axis <i><b>(floating-point)</b></i>.
    ///
    /// \param axis Vector being projected onto. Need not be normalized.
    /// \pre \c axis must not have length zero.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] SFML_SYSTEM_API Vector2 projectedOnto(const Vector2& axis) const;

    ////////////////////////////////////////////////////////////
    /// \brief Returns a perpendicular vector.
    ///
    /// Returns \c *this rotated by +90 degrees; (x,y) becomes (-y,x).
    /// For example, the vector (1,0) is transformed to (0,1).
    ///
    /// In SFML's default coordinate system with +X right and +Y down,
    /// this amounts to a clockwise rotation.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2 perpendicular() const;

    ////////////////////////////////////////////////////////////
    /// \brief Dot product of two 2D vectors.
    ///
    ////////////////////////////////////////////////////////////
    constexpr T dot(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Z component of the cross product of two 2D vectors.
    ///
    /// Treats the operands as 3D vectors, computes their cross product
    /// and returns the result's Z component (X and Y components are always zero).
    ///
    ////////////////////////////////////////////////////////////
    constexpr T cross(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Component-wise multiplication of \c *this and \c rhs.
    ///
    /// Computes <tt>(lhs.x*rhs.x, lhs.y*rhs.y)</tt>.
    ///
    /// Scaling is the most common use case for component-wise multiplication/division.
    /// This operation is also known as the Hadamard or Schur product.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2 cwiseMul(const Vector2& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Component-wise division of \c *this and \c rhs.
    ///
    /// Computes <tt>(lhs.x/rhs.x, lhs.y/rhs.y)</tt>.
    ///
    /// Scaling is the most common use case for component-wise multiplication/division.
    ///
    /// \pre Neither component of \c rhs is zero.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2 cwiseDiv(const Vector2& rhs) const;


    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T x{}; //!< X coordinate of the vector
    T y{}; //!< Y coordinate of the vector


    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTBEGIN(readability-identifier-naming)
    static const Vector2 UnitX; //!< The X unit vector (1, 0), usually facing right
    static const Vector2 UnitY; //!< The Y unit vector (0, 1), usually facing down
    // NOLINTEND(readability-identifier-naming)
};

// Define the most common types
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of unary operator -
///
/// \param right Vector to negate
///
/// \return Memberwise opposite of the vector
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator +=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator -=
///
/// This operator performs a memberwise subtraction of both vectors,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator +
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator -
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise multiplication by \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(const Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a scalar value)
/// \param right Right operand (a vector)
///
/// \return Memberwise multiplication by \c left
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator*(T left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator *=
///
/// This operator performs a memberwise multiplication by \c right,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator /
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise division by \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector2<T> operator/(const Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator /=
///
/// This operator performs a memberwise division by \c right,
/// and assigns the result to \c left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \c left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \c left is equal to \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \c left is not equal to \c right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
constexpr Vector2<T>::Vector2() = default;


////////////////////////////////////////////////////////////
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#endif
template <typename T>
constexpr Vector2<T>::Vector2(T x, T y) : x(x), y(y)
{
}
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
constexpr Vector2<T>::Vector2(const Vector2<U>& vector) : x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y))
{
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector2<T>::lengthSq() const
{
    return dot(*this);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> Vector2<T>::perpendicular() const
{
    return Vector2<T>(-y, x);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector2<T>::dot(const Vector2<T>& rhs) const
{
    return x * rhs.x + y * rhs.y;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector2<T>::cross(const Vector2<T>& rhs) const
{
    return x * rhs.y - y * rhs.x;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> Vector2<T>::cwiseMul(const Vector2<T>& rhs) const
{
    return Vector2<T>(x * rhs.x, y * rhs.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> Vector2<T>::cwiseDiv(const Vector2<T>& rhs) const
{
    assert(rhs.x != 0 && "Vector2::cwiseDiv() cannot divide by 0");
    assert(rhs.y != 0 && "Vector2::cwiseDiv() cannot divide by 0");
    return Vector2<T>(x / rhs.x, y / rhs.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& right)
{
    return Vector2<T>(-right.x, -right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x + right.x, left.y + right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(left.x - right.x, left.y - right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator*(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x * right, left.y * right);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator*(T left, const Vector2<T>& right)
{
    return Vector2<T>(right.x * left, right.y * left);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator*=(Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> operator/(const Vector2<T>& left, T right)
{
    return Vector2<T>(left.x / right, left.y / right);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T>& operator/=(Vector2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}


////////////////////////////////////////////////////////////
// Static member data
////////////////////////////////////////////////////////////

template <typename T>
const Vector2<T> Vector2<T>::UnitX(static_cast<T>(1), static_cast<T>(0));

template <typename T>
const Vector2<T> Vector2<T>::UnitY(static_cast<T>(0), static_cast<T>(1));
}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Represents a time value
///
////////////////////////////////////////////////////////////
class Time
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Sets the time value to zero.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Time();

    ////////////////////////////////////////////////////////////
    /// \brief Construct from std::chrono::duration
    ///
    ////////////////////////////////////////////////////////////
    template <typename Rep, typename Period>
    constexpr Time(const std::chrono::duration<Rep, Period>& duration);

    ////////////////////////////////////////////////////////////
    /// \brief Return the time value as a number of seconds
    ///
    /// \return Time in seconds
    ///
    /// \see asMilliseconds, asMicroseconds
    ///
    ////////////////////////////////////////////////////////////
    constexpr float asSeconds() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return the time value as a number of milliseconds
    ///
    /// \return Time in milliseconds
    ///
    /// \see asSeconds, asMicroseconds
    ///
    ////////////////////////////////////////////////////////////
    constexpr std::int32_t asMilliseconds() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return the time value as a number of microseconds
    ///
    /// \return Time in microseconds
    ///
    /// \see asSeconds, asMilliseconds
    ///
    ////////////////////////////////////////////////////////////
    constexpr std::int64_t asMicroseconds() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return the time value as a std::chorono::duration
    ///
    /// \return Time in microseconds
    ///
    ////////////////////////////////////////////////////////////
    constexpr std::chrono::microseconds toDuration() const;

    ////////////////////////////////////////////////////////////
    /// \brief Implicit conversion to std::chrono::duration
    ///
    /// \return Duration in microseconds
    ///
    ////////////////////////////////////////////////////////////
    template <typename Rep, typename Period>
    constexpr operator std::chrono::duration<Rep, Period>() const;

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTNEXTLINE(readability-identifier-naming)
    static const Time Zero; //!< Predefined "zero" time value

private:
    friend constexpr Time seconds(float);
    friend constexpr Time milliseconds(std::int32_t);
    friend constexpr Time microseconds(std::int64_t);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::chrono::microseconds m_microseconds{}; //!< Time value stored as microseconds
};

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Construct a time value from a number of seconds
///
/// \param amount Number of seconds
///
/// \return Time value constructed from the amount of seconds
///
/// \see milliseconds, microseconds
///
////////////////////////////////////////////////////////////
constexpr Time seconds(float amount);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Construct a time value from a number of milliseconds
///
/// \param amount Number of milliseconds
///
/// \return Time value constructed from the amount of milliseconds
///
/// \see seconds, microseconds
///
////////////////////////////////////////////////////////////
constexpr Time milliseconds(std::int32_t amount);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Construct a time value from a number of microseconds
///
/// \param amount Number of microseconds
///
/// \return Time value constructed from the amount of microseconds
///
/// \see seconds, milliseconds
///
////////////////////////////////////////////////////////////
constexpr Time microseconds(std::int64_t amount);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of == operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if both time values are equal
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator==(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of != operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if both time values are different
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator!=(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of < operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is lesser than \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator<(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of > operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is greater than \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator>(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of <= operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is lesser or equal than \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator<=(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of >= operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is greater or equal than \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator>=(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of unary - operator to negate a time value
///
/// \param right Right operand (a time)
///
/// \return Opposite of the time value
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator-(Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary + operator to add two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Sum of the two times values
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator+(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary += operator to add/assign two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Sum of the two times values
///
////////////////////////////////////////////////////////////
constexpr Time& operator+=(Time& left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary - operator to subtract two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Difference of the two times values
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator-(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary -= operator to subtract/assign two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Difference of the two times values
///
////////////////////////////////////////////////////////////
constexpr Time& operator-=(Time& left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator*(Time left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator*(Time left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a number)
/// \param right Right operand (a time)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator*(float left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a number)
/// \param right Right operand (a time)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator*(std::int64_t left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary *= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
constexpr Time& operator*=(Time& left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary *= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
constexpr Time& operator*=(Time& left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary / operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator/(Time left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary / operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator/(Time left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary /= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
constexpr Time& operator/=(Time& left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary /= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
constexpr Time& operator/=(Time& left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary / operator to compute the ratio of two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr float operator/(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary % operator to compute remainder of a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return \a left modulo \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Time operator%(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary %= operator to compute/assign remainder of a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return \a left modulo \a right
///
////////////////////////////////////////////////////////////
constexpr Time& operator%=(Time& left, Time right);

constexpr Time::Time() = default;


////////////////////////////////////////////////////////////
template <typename Rep, typename Period>
constexpr Time::Time(const std::chrono::duration<Rep, Period>& duration) : m_microseconds(duration)
{
}


////////////////////////////////////////////////////////////
constexpr float Time::asSeconds() const
{
    return std::chrono::duration<float>(m_microseconds).count();
}


////////////////////////////////////////////////////////////
constexpr std::int32_t Time::asMilliseconds() const
{
    return std::chrono::duration_cast<std::chrono::duration<std::int32_t, std::milli>>(m_microseconds).count();
}


////////////////////////////////////////////////////////////
constexpr std::int64_t Time::asMicroseconds() const
{
    return m_microseconds.count();
}


////////////////////////////////////////////////////////////
constexpr std::chrono::microseconds Time::toDuration() const
{
    return m_microseconds;
}


////////////////////////////////////////////////////////////
template <typename Rep, typename Period>
constexpr Time::operator std::chrono::duration<Rep, Period>() const
{
    return m_microseconds;
}


////////////////////////////////////////////////////////////
constexpr Time seconds(float amount)
{
    return Time(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount)));
}


////////////////////////////////////////////////////////////
constexpr Time milliseconds(std::int32_t amount)
{
    return Time(std::chrono::milliseconds(amount));
}


////////////////////////////////////////////////////////////
constexpr Time microseconds(std::int64_t amount)
{
    return Time(std::chrono::microseconds(amount));
}


////////////////////////////////////////////////////////////
constexpr bool operator==(Time left, Time right)
{
    return left.asMicroseconds() == right.asMicroseconds();
}


////////////////////////////////////////////////////////////
constexpr bool operator!=(Time left, Time right)
{
    return left.asMicroseconds() != right.asMicroseconds();
}


////////////////////////////////////////////////////////////
constexpr bool operator<(Time left, Time right)
{
    return left.asMicroseconds() < right.asMicroseconds();
}


////////////////////////////////////////////////////////////
constexpr bool operator>(Time left, Time right)
{
    return left.asMicroseconds() > right.asMicroseconds();
}


////////////////////////////////////////////////////////////
constexpr bool operator<=(Time left, Time right)
{
    return left.asMicroseconds() <= right.asMicroseconds();
}


////////////////////////////////////////////////////////////
constexpr bool operator>=(Time left, Time right)
{
    return left.asMicroseconds() >= right.asMicroseconds();
}


////////////////////////////////////////////////////////////
constexpr Time operator-(Time right)
{
    return microseconds(-right.asMicroseconds());
}


////////////////////////////////////////////////////////////
constexpr Time operator+(Time left, Time right)
{
    return microseconds(left.asMicroseconds() + right.asMicroseconds());
}


////////////////////////////////////////////////////////////
constexpr Time& operator+=(Time& left, Time right)
{
    return left = left + right;
}


////////////////////////////////////////////////////////////
constexpr Time operator-(Time left, Time right)
{
    return microseconds(left.asMicroseconds() - right.asMicroseconds());
}


////////////////////////////////////////////////////////////
constexpr Time& operator-=(Time& left, Time right)
{
    return left = left - right;
}


////////////////////////////////////////////////////////////
constexpr Time operator*(Time left, float right)
{
    return seconds(left.asSeconds() * right);
}


////////////////////////////////////////////////////////////
constexpr Time operator*(Time left, std::int64_t right)
{
    return microseconds(left.asMicroseconds() * right);
}


////////////////////////////////////////////////////////////
constexpr Time operator*(float left, Time right)
{
    return right * left;
}


////////////////////////////////////////////////////////////
constexpr Time operator*(std::int64_t left, Time right)
{
    return right * left;
}


////////////////////////////////////////////////////////////
constexpr Time& operator*=(Time& left, float right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
constexpr Time& operator*=(Time& left, std::int64_t right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
constexpr Time operator/(Time left, float right)
{
    return seconds(left.asSeconds() / right);
}


////////////////////////////////////////////////////////////
constexpr Time operator/(Time left, std::int64_t right)
{
    return microseconds(left.asMicroseconds() / right);
}


////////////////////////////////////////////////////////////
constexpr Time& operator/=(Time& left, float right)
{
    return left = left / right;
}


////////////////////////////////////////////////////////////
constexpr Time& operator/=(Time& left, std::int64_t right)
{
    return left = left / right;
}


////////////////////////////////////////////////////////////
constexpr float operator/(Time left, Time right)
{
    return left.asSeconds() / right.asSeconds();
}


////////////////////////////////////////////////////////////
constexpr Time operator%(Time left, Time right)
{
    return microseconds(left.asMicroseconds() % right.asMicroseconds());
}


////////////////////////////////////////////////////////////
constexpr Time& operator%=(Time& left, Time right)
{
    return left = left % right;
}

} 


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility template class for manipulating
///        3-dimensional vectors
///
////////////////////////////////////////////////////////////
template <typename T>
class Vector3
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates a Vector3(0, 0, 0).
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector3();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from its coordinates
    ///
    /// \param x X coordinate
    /// \param y Y coordinate
    /// \param z Z coordinate
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector3(T x, T y, T z);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from another type of vector
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param vector Vector to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    constexpr explicit Vector3(const Vector3<U>& vector);

    ////////////////////////////////////////////////////////////
    /// \brief Length of the vector <i><b>(floating-point)</b></i>.
    ///
    /// If you are not interested in the actual length, but only in comparisons, consider using lengthSq().
    ///
    ////////////////////////////////////////////////////////////
    SFML_SYSTEM_API T length() const;

    ////////////////////////////////////////////////////////////
    /// \brief Square of vector's length.
    ///
    /// Suitable for comparisons, more efficient than length().
    ///
    ////////////////////////////////////////////////////////////
    constexpr T lengthSq() const;

    ////////////////////////////////////////////////////////////
    /// \brief Vector with same direction but length 1 <i><b>(floating-point)</b></i>.
    ///
    /// \pre \c *this is no zero vector.
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] SFML_SYSTEM_API Vector3 normalized() const;

    ////////////////////////////////////////////////////////////
    /// \brief Dot product of two 3D vectors.
    ///
    ////////////////////////////////////////////////////////////
    constexpr T dot(const Vector3& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Cross product of two 3D vectors.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector3 cross(const Vector3& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Component-wise multiplication of \c *this and \c rhs.
    ///
    /// Computes <tt>(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z)</tt>.
    ///
    /// Scaling is the most common use case for component-wise multiplication/division.
    /// This operation is also known as the Hadamard or Schur product.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector3 cwiseMul(const Vector3& rhs) const;

    ////////////////////////////////////////////////////////////
    /// \brief Component-wise division of \c *this and \c rhs.
    ///
    /// Computes <tt>(lhs.x/rhs.x, lhs.y/rhs.y, lhs.z/rhs.z)</tt>.
    ///
    /// Scaling is the most common use case for component-wise multiplication/division.
    ///
    /// \pre Neither component of \c rhs is zero.
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector3 cwiseDiv(const Vector3& rhs) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T x{}; //!< X coordinate of the vector
    T y{}; //!< Y coordinate of the vector
    T z{}; //!< Z coordinate of the vector
};

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of unary operator -
///
/// \param left Vector to negate
///
/// \return Memberwise opposite of the vector
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& left);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator +=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator -=
///
/// This operator performs a memberwise subtraction of both vectors,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator +
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator -
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise multiplication by \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(const Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *
///
/// \param left  Left operand (a scalar value)
/// \param right Right operand (a vector)
///
/// \return Memberwise multiplication by \a left
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator*(T left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator *=
///
/// This operator performs a memberwise multiplication by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator*=(Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator /
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Memberwise division by \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr Vector3<T> operator/(const Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator /=
///
/// This operator performs a memberwise division by \a right,
/// and assigns the result to \a left.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a scalar value)
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator/=(Vector3<T>& left, T right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two vectors.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return True if \a left is not equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right);

template <typename T>
constexpr Vector3<T>::Vector3() = default;


////////////////////////////////////////////////////////////
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#endif
template <typename T>
constexpr Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z)
{
}
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
constexpr Vector3<T>::Vector3(const Vector3<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y)),
z(static_cast<T>(vector.z))
{
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector3<T>::lengthSq() const
{
    return dot(*this);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr T Vector3<T>::dot(const Vector3<T>& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> Vector3<T>::cross(const Vector3<T>& rhs) const
{
    return Vector3<T>((y * rhs.z) - (z * rhs.y), (z * rhs.x) - (x * rhs.z), (x * rhs.y) - (y * rhs.x));
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> Vector3<T>::cwiseMul(const Vector3<T>& rhs) const
{
    return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> Vector3<T>::cwiseDiv(const Vector3<T>& rhs) const
{
    assert(rhs.x != 0 && "Vector3::cwiseDiv() cannot divide by 0");
    assert(rhs.y != 0 && "Vector3::cwiseDiv() cannot divide by 0");
    assert(rhs.z != 0 && "Vector3::cwiseDiv() cannot divide by 0");
    return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator-(const Vector3<T>& left)
{
    return Vector3<T>(-left.x, -left.y, -left.z);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator*(const Vector3<T>& left, T right)
{
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator*(T left, const Vector3<T>& right)
{
    return Vector3<T>(right.x * left, right.y * left, right.z * left);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator*=(Vector3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T> operator/(const Vector3<T>& left, T right)
{
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector3<T>& operator/=(Vector3<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

// Define the most common types
using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

}

#ifdef SFML_SYSTEM_ANDROID

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Android, chrono-compatible, suspend-aware clock
///
/// Linux steady clock is represented by CLOCK_MONOTONIC.
/// However, this implementation does not work properly for
/// long-running clocks that work in the background when the
/// system is suspended.
///
/// SuspendAwareClock uses CLOCK_BOOTTIME which is identical
/// to CLOCK_MONOTONIC, except that it also includes any time
/// that the system is suspended.
///
/// Note: In most cases, CLOCK_MONOTONIC is a better choice.
/// Make sure this implementation is required for your use case.
///
////////////////////////////////////////////////////////////
class SFML_SYSTEM_API SuspendAwareClock
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Type traits and static members
    ///
    /// These type traits and static members meet the requirements
    /// of a Clock concept in the C++ Standard. More specifically,
    /// TrivialClock requirements are met. Thus, naming convention
    /// has been kept consistent to allow for extended use e.g.
    /// https://en.cppreference.com/w/cpp/chrono/is_clock
    ///
    ////////////////////////////////////////////////////////////
    using duration   = std::chrono::nanoseconds;
    using rep        = duration::rep;
    using period     = duration::period;
    using time_point = std::chrono::time_point<SuspendAwareClock, duration>;

    static constexpr bool is_steady = true; // NOLINT(readability-identifier-naming)

    static time_point now() noexcept;
};

}
#endif

namespace sf
{
namespace priv
{

////////////////////////////////////////////////////////////
/// \brief Chooses a monotonic clock of highest resolution
///
/// The high_resolution_clock is usually an alias for other
/// clocks: steady_clock or system_clock, whichever has a
/// higher precision.
///
/// sf::Clock, however, is aimed towards monotonic time
/// measurements and so system_clock could never be a choice
/// as its subject to discontinuous jumps in the system time
/// (e.g., if the system administrator manually changes
/// the clock), and by the incremental adjustments performed
/// by `adjtime` and Network Time Protocol. On the other
/// hand, monotonic clocks are unaffected by this behavior.
///
/// Note: Linux implementation of a monotonic clock that
/// takes sleep time into account is represented by
/// CLOCK_BOOTTIME. Android devices can define the macro:
/// SFML_ANDROID_USE_SUSPEND_AWARE_CLOCK to use a separate
/// implementation of that clock, instead.
///
/// For more information on Linux clocks visit:
/// https://linux.die.net/man/2/clock_gettime
///
////////////////////////////////////////////////////////////
#if defined(SFML_SYSTEM_ANDROID) && defined(SFML_ANDROID_USE_SUSPEND_AWARE_CLOCK)
using ClockImpl = SuspendAwareClock;
#else
using ClockImpl = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;
#endif

static_assert(ClockImpl::is_steady, "Provided implementation is not a monotonic clock");
static_assert(std::ratio_less_equal_v<ClockImpl::period, std::micro>,
              "Clock resolution is too low. Expecting at least a microsecond precision");

} // namespace priv

class Time;

////////////////////////////////////////////////////////////
/// \brief Utility class that measures the elapsed time
///
/// The clock starts automatically after being constructed.
///
////////////////////////////////////////////////////////////
class SFML_SYSTEM_API Clock
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Get the elapsed time
    ///
    /// This function returns the time elapsed since the last call
    /// to restart() (or the construction of the instance if restart()
    /// has not been called).
    ///
    /// \return Time elapsed
    ///
    ////////////////////////////////////////////////////////////
    Time getElapsedTime() const;

    ////////////////////////////////////////////////////////////
    /// \brief Check whether the clock is running
    ///
    /// \return True if the clock is running, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool isRunning() const;

    ////////////////////////////////////////////////////////////
    /// \brief Start the clock
    ///
    /// \see stop
    ///
    ////////////////////////////////////////////////////////////
    void start();

    ////////////////////////////////////////////////////////////
    /// \brief Stop the clock
    ///
    /// \see start
    ///
    ////////////////////////////////////////////////////////////
    void stop();

    ////////////////////////////////////////////////////////////
    /// \brief Restart the clock
    ///
    /// This function puts the time counter back to zero, returns
    /// the elapsed time, and leaves the clock in a running state.
    ///
    /// \return Time elapsed
    ///
    /// \see reset
    ///
    ////////////////////////////////////////////////////////////
    Time restart();

    ////////////////////////////////////////////////////////////
    /// \brief Reset the clock
    ///
    /// This function puts the time counter back to zero, returns
    /// the elapsed time, and leaves the clock in a paused state.
    ///
    /// \return Time elapsed
    ///
    /// \see restart
    ///
    ////////////////////////////////////////////////////////////
    Time reset();

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    priv::ClockImpl::time_point m_refPoint{priv::ClockImpl::now()}; //!< Time of last reset
    priv::ClockImpl::time_point m_stopPoint;                        //!< Time of last stop
};

} 



// window files
#if defined(SFML_WINDOW_EXPORTS)

#define SFML_WINDOW_API SFML_API_EXPORT

#else

#define SFML_WINDOW_API SFML_API_IMPORT

#endif

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Structure defining the settings of the OpenGL
///        context attached to a window
///
////////////////////////////////////////////////////////////
struct ContextSettings
{
    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the context attribute flags
    ///
    ////////////////////////////////////////////////////////////
    enum Attribute
    {
        Default = 0,      //!< Non-debug, compatibility context (this and the core attribute are mutually exclusive)
        Core    = 1 << 0, //!< Core attribute
        Debug   = 1 << 2  //!< Debug attribute
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param depth        Depth buffer bits
    /// \param stencil      Stencil buffer bits
    /// \param antialiasing Antialiasing level
    /// \param major        Major number of the context version
    /// \param minor        Minor number of the context version
    /// \param attributes   Attribute flags of the context
    /// \param sRgb         sRGB capable framebuffer
    ///
    ////////////////////////////////////////////////////////////
    constexpr explicit ContextSettings(
        unsigned int depth        = 0,
        unsigned int stencil      = 0,
        unsigned int antialiasing = 0,
        unsigned int major        = 1,
        unsigned int minor        = 1,
        unsigned int attributes   = Default,
        bool         sRgb         = false) :
    depthBits(depth),
    stencilBits(stencil),
    antialiasingLevel(antialiasing),
    majorVersion(major),
    minorVersion(minor),
    attributeFlags(attributes),
    sRgbCapable(sRgb)
    {
    }

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int  depthBits;         //!< Bits of the depth buffer
    unsigned int  stencilBits;       //!< Bits of the stencil buffer
    unsigned int  antialiasingLevel; //!< Level of antialiasing
    unsigned int  majorVersion;      //!< Major number of the context version to create
    unsigned int  minorVersion;      //!< Minor number of the context version to create
    std::uint32_t attributeFlags;    //!< The attribute flags to create the context with
    bool          sRgbCapable;       //!< Whether the context framebuffer is sRGB capable
};

} 

namespace sf
{
using ContextDestroyCallback = void (*)(void*);

////////////////////////////////////////////////////////////
/// \brief Base class for classes that require an OpenGL context
///
////////////////////////////////////////////////////////////
class SFML_WINDOW_API GlResource
{
protected:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    GlResource();

    ////////////////////////////////////////////////////////////
    /// \brief Register an OpenGL object to be destroyed when its containing context is destroyed
    ///
    /// This is used for internal purposes in order to properly
    /// clean up OpenGL resources that cannot be shared between
    /// contexts.
    ///
    /// \param object Object to be destroyed when its containing context is destroyed
    ///
    ////////////////////////////////////////////////////////////
    static void registerUnsharedGlObject(std::shared_ptr<void> object);

    ////////////////////////////////////////////////////////////
    /// \brief Unregister an OpenGL object from its containing context
    ///
    /// \param object Object to be unregistered
    ///
    ////////////////////////////////////////////////////////////
    static void unregisterUnsharedGlObject(std::shared_ptr<void> object);

    ////////////////////////////////////////////////////////////
    /// \brief RAII helper class to temporarily lock an available context for use
    ///
    ////////////////////////////////////////////////////////////
    class SFML_WINDOW_API TransientContextLock
    {
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        ////////////////////////////////////////////////////////////
        TransientContextLock();

        ////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        ////////////////////////////////////////////////////////////
        ~TransientContextLock();

        ////////////////////////////////////////////////////////////
        /// \brief Deleted copy constructor
        ///
        ////////////////////////////////////////////////////////////
        TransientContextLock(const TransientContextLock&) = delete;

        ////////////////////////////////////////////////////////////
        /// \brief Deleted copy assignment
        ///
        ////////////////////////////////////////////////////////////
        TransientContextLock& operator=(const TransientContextLock&) = delete;
    };

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::shared_ptr<void> m_sharedContext; //!< Shared context used to link all contexts together for resource sharing
};

}

using VkInstance = struct VkInstance_T*;

#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__)) || defined(_M_X64) || \
    defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)

using VkSurfaceKHR = struct VkSurfaceKHR_T*;

#else

using VkSurfaceKHR = std::uint64_t;

#endif

struct VkAllocationCallbacks;


namespace sf
{

using VulkanFunctionPointer = void (*)();

////////////////////////////////////////////////////////////
/// \brief Vulkan helper functions
///
////////////////////////////////////////////////////////////
namespace Vulkan
{
////////////////////////////////////////////////////////////
/// \brief Tell whether or not the system supports Vulkan
///
/// This function should always be called before using
/// the Vulkan features. If it returns false, then
/// any attempt to use Vulkan will fail.
///
/// If only compute is required, set \a requireGraphics
/// to false to skip checking for the extensions necessary
/// for graphics rendering.
///
/// \param requireGraphics
///
/// \return True if Vulkan is supported, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isAvailable(bool requireGraphics = true);

////////////////////////////////////////////////////////////
/// \brief Get the address of a Vulkan function
///
/// \param name Name of the function to get the address of
///
/// \return Address of the Vulkan function, 0 on failure
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API VulkanFunctionPointer getFunction(const char* name);

////////////////////////////////////////////////////////////
/// \brief Get Vulkan instance extensions required for graphics
///
/// \return Vulkan instance extensions required for graphics
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API const std::vector<const char*>& getGraphicsRequiredInstanceExtensions();
} // namespace Vulkan

#ifndef SFML_WINDOWSTYLE_HPP
#define SFML_WINDOWSTYLE_HPP
namespace Style
{
////////////////////////////////////////////////////////////
/// \ingroup window
/// \brief Enumeration of the window styles
///
////////////////////////////////////////////////////////////
enum
{
    None       = 0,      //!< No border / title bar (this flag and all others are mutually exclusive)
    Titlebar   = 1 << 0, //!< Title bar + fixed border
    Resize     = 1 << 1, //!< Title bar + resizable border + maximize button
    Close      = 1 << 2, //!< Title bar + close button
    Fullscreen = 1 << 3, //!< Fullscreen mode (this flag and all others are mutually exclusive)

    Default = Titlebar | Resize | Close //!< Default window style
};

} 

}
#endif

#if defined(SFML_SYSTEM_WINDOWS)
struct HWND__; // NOLINT(bugprone-reserved-identifier)
#endif

namespace sf
{
#if defined(SFML_SYSTEM_WINDOWS)

// Window handle is HWND (HWND__*) on Windows
using WindowHandle = HWND__*;

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD) || defined(SFML_SYSTEM_OPENBSD) || \
    defined(SFML_SYSTEM_NETBSD)

// Window handle is Window (unsigned long) on Unix - X11
using WindowHandle = unsigned long;

#elif defined(SFML_SYSTEM_MACOS)

// Window handle is NSWindow or NSView (void*) on macOS - Cocoa
using WindowHandle = void*;

#elif defined(SFML_SYSTEM_IOS)

// Window handle is UIWindow (void*) on iOS - UIKit
using WindowHandle = void*;

#elif defined(SFML_SYSTEM_ANDROID)

// Window handle is ANativeWindow* (void*) on Android
using WindowHandle = void*;

#elif defined(SFML_DOXYGEN)

// Define type alias symbol so that Doxygen can attach some documentation to it
using WindowHandle = "platform-specific";

#endif

} 

namespace sf
{
class String;

////////////////////////////////////////////////////////////
/// \brief Give access to the real-time state of the keyboard
///
////////////////////////////////////////////////////////////
namespace Keyboard
{
////////////////////////////////////////////////////////////
/// \brief Key codes
///
/// The enumerators refer to the "localized" key; i.e. depending
/// on the layout set by the operating system, a key can be mapped
/// to `Y` or `Z`.
///
////////////////////////////////////////////////////////////
enum Key
{
    Unknown = -1, //!< Unhandled key
    A       = 0,  //!< The A key
    B,            //!< The B key
    C,            //!< The C key
    D,            //!< The D key
    E,            //!< The E key
    F,            //!< The F key
    G,            //!< The G key
    H,            //!< The H key
    I,            //!< The I key
    J,            //!< The J key
    K,            //!< The K key
    L,            //!< The L key
    M,            //!< The M key
    N,            //!< The N key
    O,            //!< The O key
    P,            //!< The P key
    Q,            //!< The Q key
    R,            //!< The R key
    S,            //!< The S key
    T,            //!< The T key
    U,            //!< The U key
    V,            //!< The V key
    W,            //!< The W key
    X,            //!< The X key
    Y,            //!< The Y key
    Z,            //!< The Z key
    Num0,         //!< The 0 key
    Num1,         //!< The 1 key
    Num2,         //!< The 2 key
    Num3,         //!< The 3 key
    Num4,         //!< The 4 key
    Num5,         //!< The 5 key
    Num6,         //!< The 6 key
    Num7,         //!< The 7 key
    Num8,         //!< The 8 key
    Num9,         //!< The 9 key
    Escape,       //!< The Escape key
    LControl,     //!< The left Control key
    LShift,       //!< The left Shift key
    LAlt,         //!< The left Alt key
    LSystem,      //!< The left OS specific key: window (Windows and Linux), apple (macOS), ...
    RControl,     //!< The right Control key
    RShift,       //!< The right Shift key
    RAlt,         //!< The right Alt key
    RSystem,      //!< The right OS specific key: window (Windows and Linux), apple (macOS), ...
    Menu,         //!< The Menu key
    LBracket,     //!< The [ key
    RBracket,     //!< The ] key
    Semicolon,    //!< The ; key
    Comma,        //!< The , key
    Period,       //!< The . key
    Apostrophe,   //!< The ' key
    Slash,        //!< The / key
    Backslash,    //!< The \ key
    Grave,        //!< The ` key
    Equal,        //!< The = key
    Hyphen,       //!< The - key (hyphen)
    Space,        //!< The Space key
    Enter,        //!< The Enter/Return keys
    Backspace,    //!< The Backspace key
    Tab,          //!< The Tabulation key
    PageUp,       //!< The Page up key
    PageDown,     //!< The Page down key
    End,          //!< The End key
    Home,         //!< The Home key
    Insert,       //!< The Insert key
    Delete,       //!< The Delete key
    Add,          //!< The + key
    Subtract,     //!< The - key (minus, usually from numpad)
    Multiply,     //!< The * key
    Divide,       //!< The / key
    Left,         //!< Left arrow
    Right,        //!< Right arrow
    Up,           //!< Up arrow
    Down,         //!< Down arrow
    Numpad0,      //!< The numpad 0 key
    Numpad1,      //!< The numpad 1 key
    Numpad2,      //!< The numpad 2 key
    Numpad3,      //!< The numpad 3 key
    Numpad4,      //!< The numpad 4 key
    Numpad5,      //!< The numpad 5 key
    Numpad6,      //!< The numpad 6 key
    Numpad7,      //!< The numpad 7 key
    Numpad8,      //!< The numpad 8 key
    Numpad9,      //!< The numpad 9 key
    F1,           //!< The F1 key
    F2,           //!< The F2 key
    F3,           //!< The F3 key
    F4,           //!< The F4 key
    F5,           //!< The F5 key
    F6,           //!< The F6 key
    F7,           //!< The F7 key
    F8,           //!< The F8 key
    F9,           //!< The F9 key
    F10,          //!< The F10 key
    F11,          //!< The F11 key
    F12,          //!< The F12 key
    F13,          //!< The F13 key
    F14,          //!< The F14 key
    F15,          //!< The F15 key
    Pause,        //!< The Pause key

    KeyCount, //!< Keep last -- the total number of keyboard keys
};

////////////////////////////////////////////////////////////
/// \brief Scancodes
///
/// The enumerators are bound to a physical key and do not depend on
/// the keyboard layout used by the operating system. Usually, the AT-101
/// keyboard can be used as reference for the physical position of the keys.
///
////////////////////////////////////////////////////////////
enum class Scan
{
    Unknown = -1, //!< Represents any scancode not present in this enum
    A       = 0,  //!< Keyboard a and A key
    B,            //!< Keyboard b and B key
    C,            //!< Keyboard c and C key
    D,            //!< Keyboard d and D key
    E,            //!< Keyboard e and E key
    F,            //!< Keyboard f and F key
    G,            //!< Keyboard g and G key
    H,            //!< Keyboard h and H key
    I,            //!< Keyboard i and I key
    J,            //!< Keyboard j and J key
    K,            //!< Keyboard k and K key
    L,            //!< Keyboard l and L key
    M,            //!< Keyboard m and M key
    N,            //!< Keyboard n and N key
    O,            //!< Keyboard o and O key
    P,            //!< Keyboard p and P key
    Q,            //!< Keyboard q and Q key
    R,            //!< Keyboard r and R key
    S,            //!< Keyboard s and S key
    T,            //!< Keyboard t and T key
    U,            //!< Keyboard u and U key
    V,            //!< Keyboard v and V key
    W,            //!< Keyboard w and W key
    X,            //!< Keyboard x and X key
    Y,            //!< Keyboard y and Y key
    Z,            //!< Keyboard z and Z key
    Num1,         //!< Keyboard 1 and ! key
    Num2,         //!< Keyboard 2 and @ key
    Num3,         //!< Keyboard 3 and # key
    Num4,         //!< Keyboard 4 and $ key
    Num5,         //!< Keyboard 5 and % key
    Num6,         //!< Keyboard 6 and ^ key
    Num7,         //!< Keyboard 7 and & key
    Num8,         //!< Keyboard 8 and * key
    Num9,         //!< Keyboard 9 and ) key
    Num0,         //!< Keyboard 0 and ) key
    Enter,        //!< Keyboard Enter/Return key
    Escape,       //!< Keyboard Escape key
    Backspace,    //!< Keyboard Backspace key
    Tab,          //!< Keyboard Tab key
    Space,        //!< Keyboard Space key
    Hyphen,       //!< Keyboard - and _ key
    Equal,        //!< Keyboard = and +
    LBracket,     //!< Keyboard [ and { key
    RBracket,     //!< Keyboard ] and } key
    // For US keyboards mapped to key 29 (Microsoft Keyboard Scan Code Specification)
    // For Non-US keyboards mapped to key 42 (Microsoft Keyboard Scan Code Specification)
    // Typical language mappings: Belg:£µ` FrCa:<>} Dan:*' Dutch:`´ Fren:µ* Ger:'# Ital:§ù LatAm:[}` Nor:*@ Span:ç} Swed:*' Swiss:$£} UK:~# Brazil:}]
    Backslash,      //!< Keyboard \ and | key OR various keys for Non-US keyboards
    Semicolon,      //!< Keyboard ; and : key
    Apostrophe,     //!< Keyboard ' and " key
    Grave,          //!< Keyboard ` and ~ key
    Comma,          //!< Keyboard , and < key
    Period,         //!< Keyboard . and > key
    Slash,          //!< Keyboard / and ? key
    F1,             //!< Keyboard F1 key
    F2,             //!< Keyboard F2 key
    F3,             //!< Keyboard F3 key
    F4,             //!< Keyboard F4 key
    F5,             //!< Keyboard F5 key
    F6,             //!< Keyboard F6 key
    F7,             //!< Keyboard F7 key
    F8,             //!< Keyboard F8 key
    F9,             //!< Keyboard F9 key
    F10,            //!< Keyboard F10 key
    F11,            //!< Keyboard F11 key
    F12,            //!< Keyboard F12 key
    F13,            //!< Keyboard F13 key
    F14,            //!< Keyboard F14 key
    F15,            //!< Keyboard F15 key
    F16,            //!< Keyboard F16 key
    F17,            //!< Keyboard F17 key
    F18,            //!< Keyboard F18 key
    F19,            //!< Keyboard F19 key
    F20,            //!< Keyboard F20 key
    F21,            //!< Keyboard F21 key
    F22,            //!< Keyboard F22 key
    F23,            //!< Keyboard F23 key
    F24,            //!< Keyboard F24 key
    CapsLock,       //!< Keyboard Caps %Lock key
    PrintScreen,    //!< Keyboard Print Screen key
    ScrollLock,     //!< Keyboard Scroll %Lock key
    Pause,          //!< Keyboard Pause key
    Insert,         //!< Keyboard Insert key
    Home,           //!< Keyboard Home key
    PageUp,         //!< Keyboard Page Up key
    Delete,         //!< Keyboard Delete Forward key
    End,            //!< Keyboard End key
    PageDown,       //!< Keyboard Page Down key
    Right,          //!< Keyboard Right Arrow key
    Left,           //!< Keyboard Left Arrow key
    Down,           //!< Keyboard Down Arrow key
    Up,             //!< Keyboard Up Arrow key
    NumLock,        //!< Keypad Num %Lock and Clear key
    NumpadDivide,   //!< Keypad / key
    NumpadMultiply, //!< Keypad * key
    NumpadMinus,    //!< Keypad - key
    NumpadPlus,     //!< Keypad + key
    NumpadEqual,    //!< keypad = key
    NumpadEnter,    //!< Keypad Enter/Return key
    NumpadDecimal,  //!< Keypad . and Delete key
    Numpad1,        //!< Keypad 1 and End key
    Numpad2,        //!< Keypad 2 and Down Arrow key
    Numpad3,        //!< Keypad 3 and Page Down key
    Numpad4,        //!< Keypad 4 and Left Arrow key
    Numpad5,        //!< Keypad 5 key
    Numpad6,        //!< Keypad 6 and Right Arrow key
    Numpad7,        //!< Keypad 7 and Home key
    Numpad8,        //!< Keypad 8 and Up Arrow key
    Numpad9,        //!< Keypad 9 and Page Up key
    Numpad0,        //!< Keypad 0 and Insert key
    // For US keyboards doesn't exist
    // For Non-US keyboards mapped to key 45 (Microsoft Keyboard Scan Code Specification)
    // Typical language mappings: Belg:<\> FrCa:«°» Dan:<\> Dutch:]|[ Fren:<> Ger:<|> Ital:<> LatAm:<> Nor:<> Span:<> Swed:<|> Swiss:<\> UK:\| Brazil: \|.
    NonUsBackslash,     //!< Keyboard Non-US \ and | key
    Application,        //!< Keyboard Application key
    Execute,            //!< Keyboard Execute key
    ModeChange,         //!< Keyboard Mode Change key
    Help,               //!< Keyboard Help key
    Menu,               //!< Keyboard Menu key
    Select,             //!< Keyboard Select key
    Redo,               //!< Keyboard Redo key
    Undo,               //!< Keyboard Undo key
    Cut,                //!< Keyboard Cut key
    Copy,               //!< Keyboard Copy key
    Paste,              //!< Keyboard Paste key
    VolumeMute,         //!< Keyboard Volume Mute key
    VolumeUp,           //!< Keyboard Volume Up key
    VolumeDown,         //!< Keyboard Volume Down key
    MediaPlayPause,     //!< Keyboard Media Play Pause key
    MediaStop,          //!< Keyboard Media Stop key
    MediaNextTrack,     //!< Keyboard Media Next Track key
    MediaPreviousTrack, //!< Keyboard Media Previous Track key
    LControl,           //!< Keyboard Left Control key
    LShift,             //!< Keyboard Left Shift key
    LAlt,               //!< Keyboard Left Alt key
    LSystem,            //!< Keyboard Left System key
    RControl,           //!< Keyboard Right Control key
    RShift,             //!< Keyboard Right Shift key
    RAlt,               //!< Keyboard Right Alt key
    RSystem,            //!< Keyboard Right System key
    Back,               //!< Keyboard Back key
    Forward,            //!< Keyboard Forward key
    Refresh,            //!< Keyboard Refresh key
    Stop,               //!< Keyboard Stop key
    Search,             //!< Keyboard Search key
    Favorites,          //!< Keyboard Favorites key
    HomePage,           //!< Keyboard Home Page key
    LaunchApplication1, //!< Keyboard Launch Application 1 key
    LaunchApplication2, //!< Keyboard Launch Application 2 key
    LaunchMail,         //!< Keyboard Launch Mail key
    LaunchMediaSelect,  //!< Keyboard Launch Media Select key

    ScancodeCount //!< Keep last -- the total number of scancodes
};

using Scancode = Scan;

////////////////////////////////////////////////////////////
/// \brief Check if a key is pressed
///
/// \param key Key to check
///
/// \return True if the key is pressed, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isKeyPressed(Key key);

////////////////////////////////////////////////////////////
/// \brief Check if a key is pressed
///
/// \param code Scancode to check
///
/// \return True if the physical key is pressed, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isKeyPressed(Scancode code);

////////////////////////////////////////////////////////////
/// \brief Localize a physical key to a logical one
///
/// \param code Scancode to localize
///
/// \return The key corresponding to the scancode under the current
///         keyboard layout used by the operating system, or
///         sf::Keyboard::Unknown when the scancode cannot be mapped
///         to a Key.
///
/// \see delocalize
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API Key localize(Scancode code);

////////////////////////////////////////////////////////////
/// \brief Identify the physical key corresponding to a logical one
///
/// \param key Key to "delocalize"
///
/// \return The scancode corresponding to the key under the current
///         keyboard layout used by the operating system, or
///         sf::Keyboard::Scan::Unknown when the key cannot be mapped
///         to a sf::Keyboard::Scancode.
///
/// \see localize
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API Scancode delocalize(Key key);

////////////////////////////////////////////////////////////
/// \brief Provide a string representation for a given scancode
///
/// The returned string is a short, non-technical description of
/// the key represented with the given scancode. Most effectively
/// used in user interfaces, as the description for the key takes
/// the users keyboard layout into consideration.
///
/// \warning The result is OS-dependent: for example, sf::Keyboard::Scan::LSystem
///          is "Left Meta" on Linux, "Left Windows" on Windows and
///          "Left Command" on macOS.
///
/// The current keyboard layout set by the operating system is used to
/// interpret the scancode: for example, sf::Keyboard::Semicolon is
/// mapped to ";" for layout and to "é" for others.
///
/// \return The localized description of the code
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API String getDescription(Scancode code);

////////////////////////////////////////////////////////////
/// \brief Show or hide the virtual keyboard
///
/// \warning The virtual keyboard is not supported on all
///          systems. It will typically be implemented on mobile OSes
///          (Android, iOS) but not on desktop OSes (Windows, Linux, ...).
///
/// If the virtual keyboard is not available, this function does
/// nothing.
///
/// \param visible True to show, false to hide
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API void setVirtualKeyboardVisible(bool visible);
} // namespace Keyboard

}


namespace sf
{
class WindowBase;

////////////////////////////////////////////////////////////
/// \brief Give access to the real-time state of the mouse
///
////////////////////////////////////////////////////////////
namespace Mouse
{
////////////////////////////////////////////////////////////
/// \brief Mouse buttons
///
////////////////////////////////////////////////////////////
enum Button
{
    Left,     //!< The left mouse button
    Right,    //!< The right mouse button
    Middle,   //!< The middle (wheel) mouse button
    XButton1, //!< The first extra mouse button
    XButton2, //!< The second extra mouse button

    ButtonCount //!< Keep last -- the total number of mouse buttons
};

////////////////////////////////////////////////////////////
/// \brief Mouse wheels
///
////////////////////////////////////////////////////////////
enum Wheel
{
    VerticalWheel,  //!< The vertical mouse wheel
    HorizontalWheel //!< The horizontal mouse wheel
};

////////////////////////////////////////////////////////////
/// \brief Check if a mouse button is pressed
///
/// \warning Checking the state of buttons Mouse::XButton1 and
/// Mouse::XButton2 is not supported on Linux with X11.
///
/// \param button Button to check
///
/// \return True if the button is pressed, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isButtonPressed(Button button);

////////////////////////////////////////////////////////////
/// \brief Get the current position of the mouse in desktop coordinates
///
/// This function returns the global position of the mouse
/// cursor on the desktop.
///
/// \return Current position of the mouse
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API Vector2i getPosition();

////////////////////////////////////////////////////////////
/// \brief Get the current position of the mouse in window coordinates
///
/// This function returns the current position of the mouse
/// cursor, relative to the given window.
///
/// \param relativeTo Reference window
///
/// \return Current position of the mouse
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API Vector2i getPosition(const WindowBase& relativeTo);

////////////////////////////////////////////////////////////
/// \brief Set the current position of the mouse in desktop coordinates
///
/// This function sets the global position of the mouse
/// cursor on the desktop.
///
/// \param position New position of the mouse
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API void setPosition(const Vector2i& position);

////////////////////////////////////////////////////////////
/// \brief Set the current position of the mouse in window coordinates
///
/// This function sets the current position of the mouse
/// cursor, relative to the given window.
///
/// \param position New position of the mouse
/// \param relativeTo Reference window
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API void setPosition(const Vector2i& position, const WindowBase& relativeTo);
} // namespace Mouse

}


namespace sf
{
class Cursor;
class String;
class VideoMode;

namespace priv
{
class WindowImpl;
}

class Event;

////////////////////////////////////////////////////////////
/// \brief Window that serves as a base for other windows
///
////////////////////////////////////////////////////////////
class SFML_WINDOW_API WindowBase
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor doesn't actually create the window,
    /// use the other constructors or call create() to do so.
    ///
    ////////////////////////////////////////////////////////////
    WindowBase();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a new window
    ///
    /// This constructor creates the window with the size and pixel
    /// depth defined in \a mode. An optional style can be passed to
    /// customize the look and behavior of the window (borders,
    /// title bar, resizable, closable, ...). If \a style contains
    /// Style::Fullscreen, then \a mode must be a valid video mode.
    ///
    /// \param mode  Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param title Title of the window
    /// \param style %Window style, a bitwise OR combination of sf::Style enumerators
    ///
    ////////////////////////////////////////////////////////////
    WindowBase(VideoMode mode, const String& title, std::uint32_t style = Style::Default);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the window from an existing control
    ///
    /// \param handle Platform-specific handle of the control
    ///
    ////////////////////////////////////////////////////////////
    explicit WindowBase(WindowHandle handle);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Closes the window and frees all the resources attached to it.
    ///
    ////////////////////////////////////////////////////////////
    virtual ~WindowBase();

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy constructor
    ///
    ////////////////////////////////////////////////////////////
    WindowBase(const WindowBase&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy assignment
    ///
    ////////////////////////////////////////////////////////////
    WindowBase& operator=(const WindowBase&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window
    ///
    /// If the window was already created, it closes it first.
    /// If \a style contains Style::Fullscreen, then \a mode
    /// must be a valid video mode.
    ///
    /// \param mode  Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param title Title of the window
    /// \param style %Window style, a bitwise OR combination of sf::Style enumerators
    ///
    ////////////////////////////////////////////////////////////
    virtual void create(VideoMode mode, const String& title, std::uint32_t style = Style::Default);

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window from an existing control
    ///
    /// \param handle Platform-specific handle of the control
    ///
    ////////////////////////////////////////////////////////////
    virtual void create(WindowHandle handle);

    ////////////////////////////////////////////////////////////
    /// \brief Close the window and destroy all the attached resources
    ///
    /// After calling this function, the sf::Window instance remains
    /// valid and you can call create() to recreate the window.
    /// All other functions such as pollEvent() or display() will
    /// still work (i.e. you don't have to test isOpen() every time),
    /// and will have no effect on closed windows.
    ///
    ////////////////////////////////////////////////////////////
    virtual void close();

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether or not the window is open
    ///
    /// This function returns whether or not the window exists.
    /// Note that a hidden window (setVisible(false)) is open
    /// (therefore this function would return true).
    ///
    /// \return True if the window is open, false if it has been closed
    ///
    ////////////////////////////////////////////////////////////
    bool isOpen() const;

    ////////////////////////////////////////////////////////////
    /// \brief Pop the next event from the front of the FIFO event queue, if any, and return it
    ///
    /// This function is not blocking: if there's no pending event then
    /// it will return false and leave \a event unmodified.
    /// Note that more than one event may be present in the event queue,
    /// thus you should always call this function in a loop
    /// to make sure that you process every pending event.
    /// \code
    /// for (sf::Event event; window.pollEvent(event);)
    /// {
    ///    // process event...
    /// }
    /// \endcode
    ///
    /// \param event Event to be returned
    ///
    /// \return True if an event was returned, or false if the event queue was empty
    ///
    /// \see waitEvent
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool pollEvent(Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Wait for an event and return it
    ///
    /// This function is blocking: if there's no pending event then
    /// it will wait until an event is received.
    /// After this function returns (and no error occurred),
    /// the \a event object is always valid and filled properly.
    /// This function is typically used when you have a thread that
    /// is dedicated to events handling: you want to make this thread
    /// sleep as long as no new event is received.
    /// \code
    /// sf::Event event;
    /// if (window.waitEvent(event))
    /// {
    ///    // process event...
    /// }
    /// \endcode
    ///
    /// \param event Event to be returned
    ///
    /// \return False if any error occurred
    ///
    /// \see pollEvent
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool waitEvent(Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the window
    ///
    /// \return Position of the window, in pixels
    ///
    /// \see setPosition
    ///
    ////////////////////////////////////////////////////////////
    Vector2i getPosition() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the position of the window on screen
    ///
    /// This function only works for top-level windows
    /// (i.e. it will be ignored for windows created from
    /// the handle of a child window/control).
    ///
    /// \param position New position, in pixels
    ///
    /// \see getPosition
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const Vector2i& position);

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the rendering region of the window
    ///
    /// The size doesn't include the titlebar and borders
    /// of the window.
    ///
    /// \return Size in pixels
    ///
    /// \see setSize
    ///
    ////////////////////////////////////////////////////////////
    Vector2u getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the size of the rendering region of the window
    ///
    /// \param size New size, in pixels
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    void setSize(const Vector2u& size);

    ////////////////////////////////////////////////////////////
    /// \brief Set the minimum window rendering region size
    ///
    /// Pass std::nullopt to unset the minimum size
    ///
    /// \param minimumSize New minimum size, in pixels
    ///
    ////////////////////////////////////////////////////////////
    void setMinimumSize(const std::optional<Vector2u>& minimumSize);

    ////////////////////////////////////////////////////////////
    /// \brief Set the maximum window rendering region size
    ///
    /// Pass std::nullopt to unset the maximum size
    ///
    /// \param maximumSize New maximum size, in pixels
    ///
    ////////////////////////////////////////////////////////////
    void setMaximumSize(const std::optional<Vector2u>& maximumSize);

    ////////////////////////////////////////////////////////////
    /// \brief Change the title of the window
    ///
    /// \param title New title
    ///
    /// \see setIcon
    ///
    ////////////////////////////////////////////////////////////
    void setTitle(const String& title);

    ////////////////////////////////////////////////////////////
    /// \brief Change the window's icon
    ///
    /// \a pixels must be an array of \a width x \a height pixels
    /// in 32-bits RGBA format.
    ///
    /// The OS default icon is used by default.
    ///
    /// \param size   Icon's width and height, in pixels
    /// \param pixels Pointer to the array of pixels in memory. The
    ///               pixels are copied, so you need not keep the
    ///               source alive after calling this function.
    ///
    /// \see setTitle
    ///
    ////////////////////////////////////////////////////////////
    void setIcon(const Vector2u& size, const std::uint8_t* pixels);

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the window
    ///
    /// The window is shown by default.
    ///
    /// \param visible True to show the window, false to hide it
    ///
    ////////////////////////////////////////////////////////////
    void setVisible(bool visible);

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the mouse cursor
    ///
    /// The mouse cursor is visible by default.
    ///
    /// \param visible True to show the mouse cursor, false to hide it
    ///
    ////////////////////////////////////////////////////////////
    void setMouseCursorVisible(bool visible);

    ////////////////////////////////////////////////////////////
    /// \brief Grab or release the mouse cursor
    ///
    /// If set, grabs the mouse cursor inside this window's client
    /// area so it may no longer be moved outside its bounds.
    /// Note that grabbing is only active while the window has
    /// focus.
    ///
    /// \param grabbed True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    void setMouseCursorGrabbed(bool grabbed);

    ////////////////////////////////////////////////////////////
    /// \brief Set the displayed cursor to a native system cursor
    ///
    /// Upon window creation, the arrow cursor is used by default.
    ///
    /// \warning The cursor must not be destroyed while in use by
    ///          the window.
    ///
    /// \warning Features related to Cursor are not supported on
    ///          iOS and Android.
    ///
    /// \param cursor Native system cursor type to display
    ///
    /// \see sf::Cursor::loadFromSystem
    /// \see sf::Cursor::loadFromPixels
    ///
    ////////////////////////////////////////////////////////////
    void setMouseCursor(const Cursor& cursor);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable automatic key-repeat
    ///
    /// If key repeat is enabled, you will receive repeated
    /// KeyPressed events while keeping a key pressed. If it is disabled,
    /// you will only get a single event when the key is pressed.
    ///
    /// Key repeat is enabled by default.
    ///
    /// \param enabled True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    void setKeyRepeatEnabled(bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Change the joystick threshold
    ///
    /// The joystick threshold is the value below which
    /// no JoystickMoved event will be generated.
    ///
    /// The threshold value is 0.1 by default.
    ///
    /// \param threshold New threshold, in the range [0, 100]
    ///
    ////////////////////////////////////////////////////////////
    void setJoystickThreshold(float threshold);

    ////////////////////////////////////////////////////////////
    /// \brief Request the current window to be made the active
    ///        foreground window
    ///
    /// At any given time, only one window may have the input focus
    /// to receive input events such as keystrokes or mouse events.
    /// If a window requests focus, it only hints to the operating
    /// system, that it would like to be focused. The operating system
    /// is free to deny the request.
    /// This is not to be confused with setActive().
    ///
    /// \see hasFocus
    ///
    ////////////////////////////////////////////////////////////
    void requestFocus();

    ////////////////////////////////////////////////////////////
    /// \brief Check whether the window has the input focus
    ///
    /// At any given time, only one window may have the input focus
    /// to receive input events such as keystrokes or most mouse
    /// events.
    ///
    /// \return True if window has focus, false otherwise
    /// \see requestFocus
    ///
    ////////////////////////////////////////////////////////////
    bool hasFocus() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the OS-specific handle of the window
    ///
    /// The type of the returned handle is sf::WindowHandle,
    /// which is a type alias to the handle type defined by the OS.
    /// You shouldn't need to use this function, unless you have
    /// very specific stuff to implement that SFML doesn't support,
    /// or implement a temporary workaround until a bug is fixed.
    ///
    /// \return System handle of the window
    ///
    ////////////////////////////////////////////////////////////
    WindowHandle getSystemHandle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Create a Vulkan rendering surface
    ///
    /// \param instance  Vulkan instance
    /// \param surface   Created surface
    /// \param allocator Allocator to use
    ///
    /// \return True if surface creation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool createVulkanSurface(const VkInstance&            instance,
                                           VkSurfaceKHR&                surface,
                                           const VkAllocationCallbacks* allocator = nullptr);

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Function called after the window has been created
    ///
    /// This function is called so that derived classes can
    /// perform their own specific initialization as soon as
    /// the window is created.
    ///
    ////////////////////////////////////////////////////////////
    virtual void onCreate();

    ////////////////////////////////////////////////////////////
    /// \brief Function called after the window has been resized
    ///
    /// This function is called so that derived classes can
    /// perform custom actions when the size of the window changes.
    ///
    ////////////////////////////////////////////////////////////
    virtual void onResize();

private:
    friend class Window;

    ////////////////////////////////////////////////////////////
    /// \brief Processes an event before it is sent to the user
    ///
    /// This function is called every time an event is received
    /// from the internal window (through pollEvent or waitEvent).
    /// It filters out unwanted events, and performs whatever internal
    /// stuff the window needs before the event is returned to the
    /// user.
    ///
    /// \param event Event to filter
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool filterEvent(const Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Perform some common internal initializations
    ///
    ////////////////////////////////////////////////////////////
    void initialize();

    ////////////////////////////////////////////////////////////
    /// \brief Get the fullscreen window
    ///
    /// \return The fullscreen window or a null pointer if there is none
    ///
    ////////////////////////////////////////////////////////////
    const WindowBase* getFullscreenWindow();

    ////////////////////////////////////////////////////////////
    /// \brief Set a window as the fullscreen window
    ///
    /// \param window Window to set as fullscreen window
    ///
    ////////////////////////////////////////////////////////////
    void setFullscreenWindow(const WindowBase* window);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::unique_ptr<priv::WindowImpl> m_impl; //!< Platform-specific implementation of the window
    Vector2u                          m_size; //!< Current size of the window
};

} 

namespace sf
{
namespace priv
{
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt dFirst);
}

template <unsigned int N>
class Utf;

////////////////////////////////////////////////////////////
/// \brief Specialization of the Utf template for UTF-8
///
////////////////////////////////////////////////////////////
template <>
class Utf<8>
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Decode a single UTF-8 character
    ///
    /// Decoding a character means finding its unique 32-bits
    /// code (called the codepoint) in the Unicode standard.
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Codepoint of the decoded UTF-8 character
    /// \param replacement Replacement character to use in case the UTF-8 sequence is invalid
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static In decode(In begin, In end, std::uint32_t& output, std::uint32_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Encode a single UTF-8 character
    ///
    /// Encoding a character means converting a unique 32-bits
    /// code (called the codepoint) in the target encoding, UTF-8.
    ///
    /// \param input       Codepoint to encode as UTF-8
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to UTF-8 (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename Out>
    static Out encode(std::uint32_t input, Out output, std::uint8_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Advance to the next UTF-8 character
    ///
    /// This function is necessary for multi-elements encodings, as
    /// a single character may use more than 1 storage element.
    ///
    /// \param begin Iterator pointing to the beginning of the input sequence
    /// \param end   Iterator pointing to the end of the input sequence
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static In next(In begin, In end);

    ////////////////////////////////////////////////////////////
    /// \brief Count the number of characters of a UTF-8 sequence
    ///
    /// This function is necessary for multi-elements encodings, as
    /// a single character may use more than 1 storage element, thus the
    /// total size can be different from (begin - end).
    ///
    /// \param begin Iterator pointing to the beginning of the input sequence
    /// \param end   Iterator pointing to the end of the input sequence
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static std::size_t count(In begin, In end);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an ANSI characters range to UTF-8
    ///
    /// The current global locale will be used by default, unless you
    /// pass a custom one in the \a locale parameter.
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    /// \param locale Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Convert a wide characters range to UTF-8
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromWide(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a latin-1 (ISO-5589-1) characters range to UTF-8
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromLatin1(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-8 characters range to ANSI characters
    ///
    /// The current global locale will be used by default, unless you
    /// pass a custom one in the \a locale parameter.
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to ANSI (use 0 to skip them)
    /// \param locale      Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-8 characters range to wide characters
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to wide (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-8 characters range to latin-1 (ISO-5589-1) characters
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to wide (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toLatin1(In begin, In end, Out output, char replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-8 characters range to UTF-8
    ///
    /// This functions does nothing more than a direct copy;
    /// it is defined only to provide the same interface as other
    /// specializations of the sf::Utf<> template, and allow
    /// generic code to be written on top of it.
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf8(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-8 characters range to UTF-16
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf16(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-8 characters range to UTF-32
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf32(In begin, In end, Out output);
};

////////////////////////////////////////////////////////////
/// \brief Specialization of the Utf template for UTF-16
///
////////////////////////////////////////////////////////////
template <>
class Utf<16>
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Decode a single UTF-16 character
    ///
    /// Decoding a character means finding its unique 32-bits
    /// code (called the codepoint) in the Unicode standard.
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Codepoint of the decoded UTF-16 character
    /// \param replacement Replacement character to use in case the UTF-8 sequence is invalid
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static In decode(In begin, In end, std::uint32_t& output, std::uint32_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Encode a single UTF-16 character
    ///
    /// Encoding a character means converting a unique 32-bits
    /// code (called the codepoint) in the target encoding, UTF-16.
    ///
    /// \param input       Codepoint to encode as UTF-16
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to UTF-16 (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename Out>
    static Out encode(std::uint32_t input, Out output, std::uint16_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Advance to the next UTF-16 character
    ///
    /// This function is necessary for multi-elements encodings, as
    /// a single character may use more than 1 storage element.
    ///
    /// \param begin Iterator pointing to the beginning of the input sequence
    /// \param end   Iterator pointing to the end of the input sequence
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static In next(In begin, In end);

    ////////////////////////////////////////////////////////////
    /// \brief Count the number of characters of a UTF-16 sequence
    ///
    /// This function is necessary for multi-elements encodings, as
    /// a single character may use more than 1 storage element, thus the
    /// total size can be different from (begin - end).
    ///
    /// \param begin Iterator pointing to the beginning of the input sequence
    /// \param end   Iterator pointing to the end of the input sequence
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static std::size_t count(In begin, In end);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an ANSI characters range to UTF-16
    ///
    /// The current global locale will be used by default, unless you
    /// pass a custom one in the \a locale parameter.
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    /// \param locale Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Convert a wide characters range to UTF-16
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromWide(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a latin-1 (ISO-5589-1) characters range to UTF-16
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromLatin1(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-16 characters range to ANSI characters
    ///
    /// The current global locale will be used by default, unless you
    /// pass a custom one in the \a locale parameter.
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to ANSI (use 0 to skip them)
    /// \param locale      Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-16 characters range to wide characters
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to wide (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-16 characters range to latin-1 (ISO-5589-1) characters
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to wide (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toLatin1(In begin, In end, Out output, char replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-16 characters range to UTF-8
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf8(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-16 characters range to UTF-16
    ///
    /// This functions does nothing more than a direct copy;
    /// it is defined only to provide the same interface as other
    /// specializations of the sf::Utf<> template, and allow
    /// generic code to be written on top of it.
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf16(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-16 characters range to UTF-32
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf32(In begin, In end, Out output);
};

////////////////////////////////////////////////////////////
/// \brief Specialization of the Utf template for UTF-32
///
////////////////////////////////////////////////////////////
template <>
class Utf<32>
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Decode a single UTF-32 character
    ///
    /// Decoding a character means finding its unique 32-bits
    /// code (called the codepoint) in the Unicode standard.
    /// For UTF-32, the character value is the same as the codepoint.
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Codepoint of the decoded UTF-32 character
    /// \param replacement Replacement character to use in case the UTF-8 sequence is invalid
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static In decode(In begin, In end, std::uint32_t& output, std::uint32_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Encode a single UTF-32 character
    ///
    /// Encoding a character means converting a unique 32-bits
    /// code (called the codepoint) in the target encoding, UTF-32.
    /// For UTF-32, the codepoint is the same as the character value.
    ///
    /// \param input       Codepoint to encode as UTF-32
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to UTF-32 (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename Out>
    static Out encode(std::uint32_t input, Out output, std::uint32_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Advance to the next UTF-32 character
    ///
    /// This function is trivial for UTF-32, which can store
    /// every character in a single storage element.
    ///
    /// \param begin Iterator pointing to the beginning of the input sequence
    /// \param end   Iterator pointing to the end of the input sequence
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static In next(In begin, In end);

    ////////////////////////////////////////////////////////////
    /// \brief Count the number of characters of a UTF-32 sequence
    ///
    /// This function is trivial for UTF-32, which can store
    /// every character in a single storage element.
    ///
    /// \param begin Iterator pointing to the beginning of the input sequence
    /// \param end   Iterator pointing to the end of the input sequence
    ///
    /// \return Iterator pointing to one past the last read element of the input sequence
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static std::size_t count(In begin, In end);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an ANSI characters range to UTF-32
    ///
    /// The current global locale will be used by default, unless you
    /// pass a custom one in the \a locale parameter.
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    /// \param locale Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromAnsi(In begin, In end, Out output, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Convert a wide characters range to UTF-32
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromWide(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a latin-1 (ISO-5589-1) characters range to UTF-32
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out fromLatin1(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-32 characters range to ANSI characters
    ///
    /// The current global locale will be used by default, unless you
    /// pass a custom one in the \a locale parameter.
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to ANSI (use 0 to skip them)
    /// \param locale      Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toAnsi(In begin, In end, Out output, char replacement = 0, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-32 characters range to wide characters
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to wide (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toWide(In begin, In end, Out output, wchar_t replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Convert an UTF-16 characters range to latin-1 (ISO-5589-1) characters
    ///
    /// \param begin       Iterator pointing to the beginning of the input sequence
    /// \param end         Iterator pointing to the end of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement for characters not convertible to wide (use 0 to skip them)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toLatin1(In begin, In end, Out output, char replacement = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-32 characters range to UTF-8
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf8(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-32 characters range to UTF-16
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf16(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Convert a UTF-32 characters range to UTF-32
    ///
    /// This functions does nothing more than a direct copy;
    /// it is defined only to provide the same interface as other
    /// specializations of the sf::Utf<> template, and allow
    /// generic code to be written on top of it.
    ///
    /// \param begin  Iterator pointing to the beginning of the input sequence
    /// \param end    Iterator pointing to the end of the input sequence
    /// \param output Iterator pointing to the beginning of the output sequence
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename In, typename Out>
    static Out toUtf32(In begin, In end, Out output);

    ////////////////////////////////////////////////////////////
    /// \brief Decode a single ANSI character to UTF-32
    ///
    /// This function does not exist in other specializations
    /// of sf::Utf<>, it is defined for convenience (it is used by
    /// several other conversion functions).
    ///
    /// \param input  Input ANSI character
    /// \param locale Locale to use for conversion
    ///
    /// \return Converted character
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static std::uint32_t decodeAnsi(In input, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Decode a single wide character to UTF-32
    ///
    /// This function does not exist in other specializations
    /// of sf::Utf<>, it is defined for convenience (it is used by
    /// several other conversion functions).
    ///
    /// \param input Input wide character
    ///
    /// \return Converted character
    ///
    ////////////////////////////////////////////////////////////
    template <typename In>
    static std::uint32_t decodeWide(In input);

    ////////////////////////////////////////////////////////////
    /// \brief Encode a single UTF-32 character to ANSI
    ///
    /// This function does not exist in other specializations
    /// of sf::Utf<>, it is defined for convenience (it is used by
    /// several other conversion functions).
    ///
    /// \param codepoint   Iterator pointing to the beginning of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement if the input character is not convertible to ANSI (use 0 to skip it)
    /// \param locale      Locale to use for conversion
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename Out>
    static Out encodeAnsi(std::uint32_t codepoint, Out output, char replacement = 0, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Encode a single UTF-32 character to wide
    ///
    /// This function does not exist in other specializations
    /// of sf::Utf<>, it is defined for convenience (it is used by
    /// several other conversion functions).
    ///
    /// \param codepoint   Iterator pointing to the beginning of the input sequence
    /// \param output      Iterator pointing to the beginning of the output sequence
    /// \param replacement Replacement if the input character is not convertible to wide (use 0 to skip it)
    ///
    /// \return Iterator to the end of the output sequence which has been written
    ///
    ////////////////////////////////////////////////////////////
    template <typename Out>
    static Out encodeWide(std::uint32_t codepoint, Out output, wchar_t replacement = 0);
};

template <typename InputIt, typename OutputIt>
OutputIt priv::copy(InputIt first, InputIt last, OutputIt dFirst)
{
    while (first != last)
        *dFirst++ = static_cast<typename OutputIt::container_type::value_type>(*first++);

    return dFirst;
}

template <typename In>
In Utf<8>::decode(In begin, In end, std::uint32_t& output, std::uint32_t replacement)
{
    // clang-format off
    // Some useful precomputed data
    static constexpr int trailing[256] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
    };

    static constexpr std::uint32_t offsets[6] =
    {
        0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080
    };
    // clang-format on

    // decode the character
    const int trailingBytes = trailing[static_cast<std::uint8_t>(*begin)];
    if (trailingBytes < std::distance(begin, end))
    {
        output = 0;

        // clang-format off
        switch (trailingBytes)
        {
            case 5: output += static_cast<std::uint8_t>(*begin++); output <<= 6; [[fallthrough]];
            case 4: output += static_cast<std::uint8_t>(*begin++); output <<= 6; [[fallthrough]];
            case 3: output += static_cast<std::uint8_t>(*begin++); output <<= 6; [[fallthrough]];
            case 2: output += static_cast<std::uint8_t>(*begin++); output <<= 6; [[fallthrough]];
            case 1: output += static_cast<std::uint8_t>(*begin++); output <<= 6; [[fallthrough]];
            case 0: output += static_cast<std::uint8_t>(*begin++);
        }
        // clang-format on

        output -= offsets[trailingBytes];
    }
    else
    {
        // Incomplete character
        begin  = end;
        output = replacement;
    }

    return begin;
}


////////////////////////////////////////////////////////////
template <typename Out>
Out Utf<8>::encode(std::uint32_t input, Out output, std::uint8_t replacement)
{
    // Some useful precomputed data
    static constexpr std::uint8_t firstBytes[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

    // encode the character
    if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF)))
    {
        // Invalid character
        if (replacement)
            *output++ = static_cast<typename Out::container_type::value_type>(replacement);
    }
    else
    {
        // Valid character

        // Get the number of bytes to write
        std::size_t bytestoWrite = 1;

        // clang-format off
        if      (input <  0x80)       bytestoWrite = 1;
        else if (input <  0x800)      bytestoWrite = 2;
        else if (input <  0x10000)    bytestoWrite = 3;
        else if (input <= 0x0010FFFF) bytestoWrite = 4;
        // clang-format on

        // Extract the bytes to write
        std::byte bytes[4];

        // clang-format off
        switch (bytestoWrite)
        {
            case 4: bytes[3] = static_cast<std::byte>((input | 0x80) & 0xBF); input >>= 6; [[fallthrough]];
            case 3: bytes[2] = static_cast<std::byte>((input | 0x80) & 0xBF); input >>= 6; [[fallthrough]];
            case 2: bytes[1] = static_cast<std::byte>((input | 0x80) & 0xBF); input >>= 6; [[fallthrough]];
            case 1: bytes[0] = static_cast<std::byte> (input | firstBytes[bytestoWrite]);
        }
        // clang-format on

        // Add them to the output
        output = priv::copy(bytes, bytes + bytestoWrite, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In>
In Utf<8>::next(In begin, In end)
{
    std::uint32_t codepoint;
    return decode(begin, end, codepoint);
}


////////////////////////////////////////////////////////////
template <typename In>
std::size_t Utf<8>::count(In begin, In end)
{
    std::size_t length = 0;
    while (begin < end)
    {
        begin = next(begin, end);
        ++length;
    }

    return length;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::fromAnsi(In begin, In end, Out output, const std::locale& locale)
{
    while (begin < end)
    {
        const std::uint32_t codepoint = Utf<32>::decodeAnsi(*begin++, locale);
        output                        = encode(codepoint, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::fromWide(In begin, In end, Out output)
{
    while (begin < end)
    {
        std::uint32_t codepoint = Utf<32>::decodeWide(*begin++);
        output                  = encode(codepoint, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::fromLatin1(In begin, In end, Out output)
{
    // Latin-1 is directly compatible with Unicode encodings,
    // and can thus be treated as (a sub-range of) UTF-32
    while (begin < end)
        output = encode(*begin++, output);

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::toAnsi(In begin, In end, Out output, char replacement, const std::locale& locale)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin  = decode(begin, end, codepoint);
        output = Utf<32>::encodeAnsi(codepoint, output, replacement, locale);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::toWide(In begin, In end, Out output, wchar_t replacement)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin  = decode(begin, end, codepoint);
        output = Utf<32>::encodeWide(codepoint, output, replacement);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::toLatin1(In begin, In end, Out output, char replacement)
{
    // Latin-1 is directly compatible with Unicode encodings,
    // and can thus be treated as (a sub-range of) UTF-32
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin     = decode(begin, end, codepoint);
        *output++ = codepoint < 256 ? static_cast<char>(codepoint) : replacement;
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::toUtf8(In begin, In end, Out output)
{
    return priv::copy(begin, end, output);
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::toUtf16(In begin, In end, Out output)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin  = decode(begin, end, codepoint);
        output = Utf<16>::encode(codepoint, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<8>::toUtf32(In begin, In end, Out output)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin     = decode(begin, end, codepoint);
        *output++ = codepoint;
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In>
In Utf<16>::decode(In begin, In end, std::uint32_t& output, std::uint32_t replacement)
{
    const std::uint16_t first = *begin++;

    // If it's a surrogate pair, first convert to a single UTF-32 character
    if ((first >= 0xD800) && (first <= 0xDBFF))
    {
        if (begin < end)
        {
            const std::uint32_t second = *begin++;
            if ((second >= 0xDC00) && (second <= 0xDFFF))
            {
                // The second element is valid: convert the two elements to a UTF-32 character
                output = ((first - 0xD800u) << 10) + (second - 0xDC00) + 0x0010000;
            }
            else
            {
                // Invalid character
                output = replacement;
            }
        }
        else
        {
            // Invalid character
            begin  = end;
            output = replacement;
        }
    }
    else
    {
        // We can make a direct copy
        output = first;
    }

    return begin;
}


////////////////////////////////////////////////////////////
template <typename Out>
Out Utf<16>::encode(std::uint32_t input, Out output, std::uint16_t replacement)
{
    if (input <= 0xFFFF)
    {
        // The character can be copied directly, we just need to check if it's in the valid range
        if ((input >= 0xD800) && (input <= 0xDFFF))
        {
            // Invalid character (this range is reserved)
            if (replacement)
                *output++ = replacement;
        }
        else
        {
            // Valid character directly convertible to a single UTF-16 character
            *output++ = static_cast<std::uint16_t>(input);
        }
    }
    else if (input > 0x0010FFFF)
    {
        // Invalid character (greater than the maximum Unicode value)
        if (replacement)
            *output++ = replacement;
    }
    else
    {
        // The input character will be converted to two UTF-16 elements
        input -= 0x0010000;
        *output++ = static_cast<std::uint16_t>((input >> 10) + 0xD800);
        *output++ = static_cast<std::uint16_t>((input & 0x3FFUL) + 0xDC00);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In>
In Utf<16>::next(In begin, In end)
{
    std::uint32_t codepoint;
    return decode(begin, end, codepoint);
}


////////////////////////////////////////////////////////////
template <typename In>
std::size_t Utf<16>::count(In begin, In end)
{
    std::size_t length = 0;
    while (begin < end)
    {
        begin = next(begin, end);
        ++length;
    }

    return length;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::fromAnsi(In begin, In end, Out output, const std::locale& locale)
{
    while (begin < end)
    {
        std::uint32_t codepoint = Utf<32>::decodeAnsi(*begin++, locale);
        output                  = encode(codepoint, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::fromWide(In begin, In end, Out output)
{
    while (begin < end)
    {
        std::uint32_t codepoint = Utf<32>::decodeWide(*begin++);
        output                  = encode(codepoint, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::fromLatin1(In begin, In end, Out output)
{
    // Latin-1 is directly compatible with Unicode encodings,
    // and can thus be treated as (a sub-range of) UTF-32
    return priv::copy(begin, end, output);
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::toAnsi(In begin, In end, Out output, char replacement, const std::locale& locale)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin  = decode(begin, end, codepoint);
        output = Utf<32>::encodeAnsi(codepoint, output, replacement, locale);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::toWide(In begin, In end, Out output, wchar_t replacement)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin  = decode(begin, end, codepoint);
        output = Utf<32>::encodeWide(codepoint, output, replacement);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::toLatin1(In begin, In end, Out output, char replacement)
{
    // Latin-1 is directly compatible with Unicode encodings,
    // and can thus be treated as (a sub-range of) UTF-32
    while (begin < end)
    {
        *output++ = *begin < 256 ? static_cast<char>(*begin) : replacement;
        ++begin;
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::toUtf8(In begin, In end, Out output)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin  = decode(begin, end, codepoint);
        output = Utf<8>::encode(codepoint, output);
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::toUtf16(In begin, In end, Out output)
{
    return priv::copy(begin, end, output);
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<16>::toUtf32(In begin, In end, Out output)
{
    while (begin < end)
    {
        std::uint32_t codepoint;
        begin     = decode(begin, end, codepoint);
        *output++ = codepoint;
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In>
In Utf<32>::decode(In begin, In /*end*/, std::uint32_t& output, std::uint32_t /*replacement*/)
{
    output = *begin++;
    return begin;
}


////////////////////////////////////////////////////////////
template <typename Out>
Out Utf<32>::encode(std::uint32_t input, Out output, std::uint32_t /*replacement*/)
{
    *output++ = input;
    return output;
}


////////////////////////////////////////////////////////////
template <typename In>
In Utf<32>::next(In begin, In /*end*/)
{
    return ++begin;
}


////////////////////////////////////////////////////////////
template <typename In>
std::size_t Utf<32>::count(In begin, In end)
{
    return begin - end;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::fromAnsi(In begin, In end, Out output, const std::locale& locale)
{
    while (begin < end)
        *output++ = decodeAnsi(*begin++, locale);

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::fromWide(In begin, In end, Out output)
{
    while (begin < end)
        *output++ = decodeWide(*begin++);

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::fromLatin1(In begin, In end, Out output)
{
    // Latin-1 is directly compatible with Unicode encodings,
    // and can thus be treated as (a sub-range of) UTF-32
    return priv::copy(begin, end, output);
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::toAnsi(In begin, In end, Out output, char replacement, const std::locale& locale)
{
    while (begin < end)
        output = encodeAnsi(*begin++, output, replacement, locale);

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::toWide(In begin, In end, Out output, wchar_t replacement)
{
    while (begin < end)
        output = encodeWide(*begin++, output, replacement);

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::toLatin1(In begin, In end, Out output, char replacement)
{
    // Latin-1 is directly compatible with Unicode encodings,
    // and can thus be treated as (a sub-range of) UTF-32
    while (begin < end)
    {
        *output++ = *begin < 256 ? static_cast<char>(*begin) : replacement;
        ++begin;
    }

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::toUtf8(In begin, In end, Out output)
{
    while (begin < end)
        output = Utf<8>::encode(*begin++, output);

    return output;
}

////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::toUtf16(In begin, In end, Out output)
{
    while (begin < end)
        output = Utf<16>::encode(*begin++, output);

    return output;
}


////////////////////////////////////////////////////////////
template <typename In, typename Out>
Out Utf<32>::toUtf32(In begin, In end, Out output)
{
    return priv::copy(begin, end, output);
}


////////////////////////////////////////////////////////////
template <typename In>
std::uint32_t Utf<32>::decodeAnsi(In input, [[maybe_unused]] const std::locale& locale)
{
    // Get the facet of the locale which deals with character conversion
    const auto& facet = std::use_facet<std::ctype<wchar_t>>(locale);

    // Use the facet to convert each character of the input string
    return static_cast<std::uint32_t>(facet.widen(input));
}


////////////////////////////////////////////////////////////
template <typename In>
std::uint32_t Utf<32>::decodeWide(In input)
{
    // The encoding of wide characters is not well defined and is left to the system;
    // however we can safely assume that it is UCS-2 on Windows and
    // UCS-4 on Unix systems.
    // In both cases, a simple copy is enough (UCS-2 is a subset of UCS-4,
    // and UCS-4 *is* UTF-32).

    return static_cast<std::uint32_t>(input);
}


////////////////////////////////////////////////////////////
template <typename Out>
Out Utf<32>::encodeAnsi(std::uint32_t codepoint, Out output, char replacement, [[maybe_unused]] const std::locale& locale)
{
    // Get the facet of the locale which deals with character conversion
    const auto& facet = std::use_facet<std::ctype<wchar_t>>(locale);

    // Use the facet to convert each character of the input string
    *output++ = facet.narrow(static_cast<wchar_t>(codepoint), replacement);

    return output;
}


////////////////////////////////////////////////////////////
template <typename Out>
Out Utf<32>::encodeWide(std::uint32_t codepoint, Out output, wchar_t replacement)
{
    // The encoding of wide characters is not well defined and is left to the system;
    // however we can safely assume that it is UCS-2 on Windows and
    // UCS-4 on Unix systems.
    // For UCS-2 we need to check if the source characters fits in (UCS-2 is a subset of UCS-4).
    // For UCS-4 we can do a direct copy (UCS-4 *is* UTF-32).

    switch (sizeof(wchar_t))
    {
        case 4:
        {
            *output++ = static_cast<wchar_t>(codepoint);
            break;
        }

        default:
        {
            if ((codepoint <= 0xFFFF) && ((codepoint < 0xD800) || (codepoint > 0xDFFF)))
            {
                *output++ = static_cast<wchar_t>(codepoint);
            }
            else if (replacement)
            {
                *output++ = replacement;
            }
            break;
        }
    }

    return output;
}


// Make type aliases to get rid of the template syntax
using Utf8  = Utf<8>;
using Utf16 = Utf<16>;
using Utf32 = Utf<32>;

} 

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility string class that automatically handles
///        conversions between types and encodings
///
////////////////////////////////////////////////////////////
class SFML_SYSTEM_API String
{
public:
    ////////////////////////////////////////////////////////////
    // Types
    ////////////////////////////////////////////////////////////
    using Iterator      = std::u32string::iterator;       //!< Iterator type
    using ConstIterator = std::u32string::const_iterator; //!< Read-only iterator type

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTBEGIN(readability-identifier-naming)
    /// Represents an invalid position in the string
    static const std::size_t InvalidPos{std::u32string::npos};
    // NOLINTEND(readability-identifier-naming)

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor creates an empty string.
    ///
    ////////////////////////////////////////////////////////////
    String();

    ////////////////////////////////////////////////////////////
    /// \brief Construct from a single ANSI character and a locale
    ///
    /// The source character is converted to UTF-32 according
    /// to the given locale.
    ///
    /// \param ansiChar ANSI character to convert
    /// \param locale   Locale to use for conversion
    ///
    ////////////////////////////////////////////////////////////
    String(char ansiChar, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Construct from single wide character
    ///
    /// \param wideChar Wide character to convert
    ///
    ////////////////////////////////////////////////////////////
    String(wchar_t wideChar);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from single UTF-32 character
    ///
    /// \param utf32Char UTF-32 character to convert
    ///
    ////////////////////////////////////////////////////////////
    String(char32_t utf32Char);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from a null-terminated C-style ANSI string and a locale
    ///
    /// The source string is converted to UTF-32 according
    /// to the given locale.
    ///
    /// \param ansiString ANSI string to convert
    /// \param locale     Locale to use for conversion
    ///
    ////////////////////////////////////////////////////////////
    String(const char* ansiString, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Construct from an ANSI string and a locale
    ///
    /// The source string is converted to UTF-32 according
    /// to the given locale.
    ///
    /// \param ansiString ANSI string to convert
    /// \param locale     Locale to use for conversion
    ///
    ////////////////////////////////////////////////////////////
    String(const std::string& ansiString, const std::locale& locale = std::locale());

    ////////////////////////////////////////////////////////////
    /// \brief Construct from null-terminated C-style wide string
    ///
    /// \param wideString Wide string to convert
    ///
    ////////////////////////////////////////////////////////////
    String(const wchar_t* wideString);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from a wide string
    ///
    /// \param wideString Wide string to convert
    ///
    ////////////////////////////////////////////////////////////
    String(const std::wstring& wideString);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from a null-terminated C-style UTF-32 string
    ///
    /// \param utf32String UTF-32 string to assign
    ///
    ////////////////////////////////////////////////////////////
    String(const char32_t* utf32String);

    ////////////////////////////////////////////////////////////
    /// \brief Construct from an UTF-32 string
    ///
    /// \param utf32String UTF-32 string to assign
    ///
    ////////////////////////////////////////////////////////////
    String(std::u32string utf32String);

    ////////////////////////////////////////////////////////////
    /// \brief Create a new sf::String from a UTF-8 encoded string
    ///
    /// \param begin Forward iterator to the beginning of the UTF-8 sequence
    /// \param end   Forward iterator to the end of the UTF-8 sequence
    ///
    /// \return A sf::String containing the source string
    ///
    /// \see fromUtf16, fromUtf32
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    static String fromUtf8(T begin, T end);

    ////////////////////////////////////////////////////////////
    /// \brief Create a new sf::String from a UTF-16 encoded string
    ///
    /// \param begin Forward iterator to the beginning of the UTF-16 sequence
    /// \param end   Forward iterator to the end of the UTF-16 sequence
    ///
    /// \return A sf::String containing the source string
    ///
    /// \see fromUtf8, fromUtf32
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    static String fromUtf16(T begin, T end);

    ////////////////////////////////////////////////////////////
    /// \brief Create a new sf::String from a UTF-32 encoded string
    ///
    /// This function is provided for consistency, it is equivalent to
    /// using the constructors that takes a const char32_t* or
    /// a std::u32string.
    ///
    /// \param begin Forward iterator to the beginning of the UTF-32 sequence
    /// \param end   Forward iterator to the end of the UTF-32 sequence
    ///
    /// \return A sf::String containing the source string
    ///
    /// \see fromUtf8, fromUtf16
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
    static String fromUtf32(T begin, T end);

    ////////////////////////////////////////////////////////////
    /// \brief Implicit conversion operator to std::string (ANSI string)
    ///
    /// The current global locale is used for conversion. If you
    /// want to explicitly specify a locale, see toAnsiString.
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    /// This operator is defined for convenience, and is equivalent
    /// to calling toAnsiString().
    ///
    /// \return Converted ANSI string
    ///
    /// \see toAnsiString, operator std::wstring
    ///
    ////////////////////////////////////////////////////////////
    operator std::string() const;

    ////////////////////////////////////////////////////////////
    /// \brief Implicit conversion operator to std::wstring (wide string)
    ///
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    /// This operator is defined for convenience, and is equivalent
    /// to calling toWideString().
    ///
    /// \return Converted wide string
    ///
    /// \see toWideString, operator std::string
    ///
    ////////////////////////////////////////////////////////////
    operator std::wstring() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to an ANSI string
    ///
    /// The UTF-32 string is converted to an ANSI string in
    /// the encoding defined by \a locale.
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    ///
    /// \param locale Locale to use for conversion
    ///
    /// \return Converted ANSI string
    ///
    /// \see toWideString, operator std::string
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] std::string toAnsiString(const std::locale& locale = std::locale()) const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to a wide string
    ///
    /// Characters that do not fit in the target encoding are
    /// discarded from the returned string.
    ///
    /// \return Converted wide string
    ///
    /// \see toAnsiString, operator std::wstring
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] std::wstring toWideString() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to a UTF-8 string
    ///
    /// \return Converted UTF-8 string
    ///
    /// \see toUtf16, toUtf32
    ///
    ////////////////////////////////////////////////////////////
    std::basic_string<std::uint8_t> toUtf8() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to a UTF-16 string
    ///
    /// \return Converted UTF-16 string
    ///
    /// \see toUtf8, toUtf32
    ///
    ////////////////////////////////////////////////////////////
    std::u16string toUtf16() const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert the Unicode string to a UTF-32 string
    ///
    /// This function doesn't perform any conversion, since the
    /// string is already stored as UTF-32 internally.
    ///
    /// \return Converted UTF-32 string
    ///
    /// \see toUtf8, toUtf16
    ///
    ////////////////////////////////////////////////////////////
    std::u32string toUtf32() const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of += operator to append an UTF-32 string
    ///
    /// \param right String to append
    ///
    /// \return Reference to self
    ///
    ////////////////////////////////////////////////////////////
    String& operator+=(const String& right);

    ////////////////////////////////////////////////////////////
    /// \brief Overload of [] operator to access a character by its position
    ///
    /// This function provides read-only access to characters.
    /// Note: the behavior is undefined if \a index is out of range.
    ///
    /// \param index Index of the character to get
    ///
    /// \return Character at position \a index
    ///
    ////////////////////////////////////////////////////////////
    char32_t operator[](std::size_t index) const;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of [] operator to access a character by its position
    ///
    /// This function provides read and write access to characters.
    /// Note: the behavior is undefined if \a index is out of range.
    ///
    /// \param index Index of the character to get
    ///
    /// \return Reference to the character at position \a index
    ///
    ////////////////////////////////////////////////////////////
    char32_t& operator[](std::size_t index);

    ////////////////////////////////////////////////////////////
    /// \brief Clear the string
    ///
    /// This function removes all the characters from the string.
    ///
    /// \see isEmpty, erase
    ///
    ////////////////////////////////////////////////////////////
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the string
    ///
    /// \return Number of characters in the string
    ///
    /// \see isEmpty
    ///
    ////////////////////////////////////////////////////////////
    std::size_t getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Check whether the string is empty or not
    ///
    /// \return True if the string is empty (i.e. contains no character)
    ///
    /// \see clear, getSize
    ///
    ////////////////////////////////////////////////////////////
    bool isEmpty() const;

    ////////////////////////////////////////////////////////////
    /// \brief Erase one or more characters from the string
    ///
    /// This function removes a sequence of \a count characters
    /// starting from \a position.
    ///
    /// \param position Position of the first character to erase
    /// \param count    Number of characters to erase
    ///
    ////////////////////////////////////////////////////////////
    void erase(std::size_t position, std::size_t count = 1);

    ////////////////////////////////////////////////////////////
    /// \brief Insert one or more characters into the string
    ///
    /// This function inserts the characters of \a str
    /// into the string, starting from \a position.
    ///
    /// \param position Position of insertion
    /// \param str      Characters to insert
    ///
    ////////////////////////////////////////////////////////////
    void insert(std::size_t position, const String& str);

    ////////////////////////////////////////////////////////////
    /// \brief Find a sequence of one or more characters in the string
    ///
    /// This function searches for the characters of \a str
    /// in the string, starting from \a start.
    ///
    /// \param str   Characters to find
    /// \param start Where to begin searching
    ///
    /// \return Position of \a str in the string, or String::InvalidPos if not found
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] std::size_t find(const String& str, std::size_t start = 0) const;

    ////////////////////////////////////////////////////////////
    /// \brief Replace a substring with another string
    ///
    /// This function replaces the substring that starts at index \a position
    /// and spans \a length characters with the string \a replaceWith.
    ///
    /// \param position    Index of the first character to be replaced
    /// \param length      Number of characters to replace. You can pass InvalidPos to
    ///                    replace all characters until the end of the string.
    /// \param replaceWith String that replaces the given substring.
    ///
    ////////////////////////////////////////////////////////////
    void replace(std::size_t position, std::size_t length, const String& replaceWith);

    ////////////////////////////////////////////////////////////
    /// \brief Replace all occurrences of a substring with a replacement string
    ///
    /// This function replaces all occurrences of \a searchFor in this string
    /// with the string \a replaceWith.
    ///
    /// \param searchFor   The value being searched for
    /// \param replaceWith The value that replaces found \a searchFor values
    ///
    ////////////////////////////////////////////////////////////
    void replace(const String& searchFor, const String& replaceWith);

    ////////////////////////////////////////////////////////////
    /// \brief Return a part of the string
    ///
    /// This function returns the substring that starts at index \a position
    /// and spans \a length characters.
    ///
    /// \param position Index of the first character
    /// \param length   Number of characters to include in the substring (if
    ///                 the string is shorter, as many characters as possible
    ///                 are included). \ref InvalidPos can be used to include all
    ///                 characters until the end of the string.
    ///
    /// \return String object containing a substring of this object
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] String substring(std::size_t position, std::size_t length = InvalidPos) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get a pointer to the C-style array of characters
    ///
    /// This functions provides a read-only access to a
    /// null-terminated C-style representation of the string.
    /// The returned pointer is temporary and is meant only for
    /// immediate use, thus it is not recommended to store it.
    ///
    /// \return Read-only pointer to the array of characters
    ///
    ////////////////////////////////////////////////////////////
    const char32_t* getData() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the beginning of the string
    ///
    /// \return Read-write iterator to the beginning of the string characters
    ///
    /// \see end
    ///
    ////////////////////////////////////////////////////////////
    Iterator begin();

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the beginning of the string
    ///
    /// \return Read-only iterator to the beginning of the string characters
    ///
    /// \see end
    ///
    ////////////////////////////////////////////////////////////
    ConstIterator begin() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the end of the string
    ///
    /// The end iterator refers to 1 position past the last character;
    /// thus it represents an invalid character and should never be
    /// accessed.
    ///
    /// \return Read-write iterator to the end of the string characters
    ///
    /// \see begin
    ///
    ////////////////////////////////////////////////////////////
    Iterator end();

    ////////////////////////////////////////////////////////////
    /// \brief Return an iterator to the end of the string
    ///
    /// The end iterator refers to 1 position past the last character;
    /// thus it represents an invalid character and should never be
    /// accessed.
    ///
    /// \return Read-only iterator to the end of the string characters
    ///
    /// \see begin
    ///
    ////////////////////////////////////////////////////////////
    ConstIterator end() const;

private:
    friend SFML_SYSTEM_API bool operator==(const String& left, const String& right);
    friend SFML_SYSTEM_API bool operator<(const String& left, const String& right);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::u32string m_string; //!< Internal string of UTF-32 characters
};

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of == operator to compare two UTF-32 strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return True if both strings are equal
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator==(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of != operator to compare two UTF-32 strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return True if both strings are different
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator!=(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of < operator to compare two UTF-32 strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return True if \a left is lexicographically before \a right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator<(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of > operator to compare two UTF-32 strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return True if \a left is lexicographically after \a right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator>(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of <= operator to compare two UTF-32 strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return True if \a left is lexicographically before or equivalent to \a right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator<=(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of >= operator to compare two UTF-32 strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return True if \a left is lexicographically after or equivalent to \a right
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API bool operator>=(const String& left, const String& right);

////////////////////////////////////////////////////////////
/// \relates String
/// \brief Overload of binary + operator to concatenate two strings
///
/// \param left  Left operand (a string)
/// \param right Right operand (a string)
///
/// \return Concatenated string
///
////////////////////////////////////////////////////////////
SFML_SYSTEM_API String operator+(const String& left, const String& right);

template <typename T>
String String::fromUtf8(T begin, T end)
{
    String string;
    Utf8::toUtf32(begin, end, std::back_inserter(string.m_string));
    return string;
}


////////////////////////////////////////////////////////////
template <typename T>
String String::fromUtf16(T begin, T end)
{
    String string;
    Utf16::toUtf32(begin, end, std::back_inserter(string.m_string));
    return string;
}


////////////////////////////////////////////////////////////
template <typename T>
String String::fromUtf32(T begin, T end)
{
    String string;
    string.m_string.assign(begin, end);
    return string;
}
}


namespace sf
{
namespace priv
{
class GlContext;
}

class Event;

////////////////////////////////////////////////////////////
/// \brief Window that serves as a target for OpenGL rendering
///
////////////////////////////////////////////////////////////
class SFML_WINDOW_API Window : public WindowBase, GlResource
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor doesn't actually create the window,
    /// use the other constructors or call create() to do so.
    ///
    ////////////////////////////////////////////////////////////
    Window();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a new window
    ///
    /// This constructor creates the window with the size and pixel
    /// depth defined in \a mode. An optional style can be passed to
    /// customize the look and behavior of the window (borders,
    /// title bar, resizable, closable, ...). If \a style contains
    /// Style::Fullscreen, then \a mode must be a valid video mode.
    ///
    /// The fourth parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param title    Title of the window
    /// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    Window(VideoMode              mode,
           const String&          title,
           std::uint32_t          style    = Style::Default,
           const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Construct the window from an existing control
    ///
    /// Use this constructor if you want to create an OpenGL
    /// rendering area into an already existing control.
    ///
    /// The second parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param handle   Platform-specific handle of the control
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    explicit Window(WindowHandle handle, const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Closes the window and frees all the resources attached to it.
    ///
    ////////////////////////////////////////////////////////////
    ~Window() override;

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window
    ///
    /// If the window was already created, it closes it first.
    /// If \a style contains Style::Fullscreen, then \a mode
    /// must be a valid video mode.
    ///
    /// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param title    Title of the window
    /// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
    ///
    ////////////////////////////////////////////////////////////
    void create(VideoMode mode, const String& title, std::uint32_t style = Style::Default) override;

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window
    ///
    /// If the window was already created, it closes it first.
    /// If \a style contains Style::Fullscreen, then \a mode
    /// must be a valid video mode.
    ///
    /// The fourth parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param title    Title of the window
    /// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    virtual void create(VideoMode mode, const String& title, std::uint32_t style, const ContextSettings& settings);

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window from an existing control
    ///
    /// Use this function if you want to create an OpenGL
    /// rendering area into an already existing control.
    /// If the window was already created, it closes it first.
    ///
    /// \param handle   Platform-specific handle of the control
    ///
    ////////////////////////////////////////////////////////////
    void create(WindowHandle handle) override;

    ////////////////////////////////////////////////////////////
    /// \brief Create (or recreate) the window from an existing control
    ///
    /// Use this function if you want to create an OpenGL
    /// rendering area into an already existing control.
    /// If the window was already created, it closes it first.
    ///
    /// The second parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc.
    ///
    /// \param handle   Platform-specific handle of the control
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    virtual void create(WindowHandle handle, const ContextSettings& settings);

    ////////////////////////////////////////////////////////////
    /// \brief Close the window and destroy all the attached resources
    ///
    /// After calling this function, the sf::Window instance remains
    /// valid and you can call create() to recreate the window.
    /// All other functions such as pollEvent() or display() will
    /// still work (i.e. you don't have to test isOpen() every time),
    /// and will have no effect on closed windows.
    ///
    ////////////////////////////////////////////////////////////
    void close() override;

    ////////////////////////////////////////////////////////////
    /// \brief Get the settings of the OpenGL context of the window
    ///
    /// Note that these settings may be different from what was
    /// passed to the constructor or the create() function,
    /// if one or more settings were not supported. In this case,
    /// SFML chose the closest match.
    ///
    /// \return Structure containing the OpenGL context settings
    ///
    ////////////////////////////////////////////////////////////
    const ContextSettings& getSettings() const;

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable vertical synchronization
    ///
    /// Activating vertical synchronization will limit the number
    /// of frames displayed to the refresh rate of the monitor.
    /// This can avoid some visual artifacts, and limit the framerate
    /// to a good value (but not constant across different computers).
    ///
    /// Vertical synchronization is disabled by default.
    ///
    /// \param enabled True to enable v-sync, false to deactivate it
    ///
    ////////////////////////////////////////////////////////////
    void setVerticalSyncEnabled(bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Limit the framerate to a maximum fixed frequency
    ///
    /// If a limit is set, the window will use a small delay after
    /// each call to display() to ensure that the current frame
    /// lasted long enough to match the framerate limit.
    /// SFML will try to match the given limit as much as it can,
    /// but since it internally uses sf::sleep, whose precision
    /// depends on the underlying OS, the results may be a little
    /// imprecise as well (for example, you can get 65 FPS when
    /// requesting 60).
    ///
    /// \param limit Framerate limit, in frames per seconds (use 0 to disable limit)
    ///
    ////////////////////////////////////////////////////////////
    void setFramerateLimit(unsigned int limit);

    ////////////////////////////////////////////////////////////
    /// \brief Activate or deactivate the window as the current target
    ///        for OpenGL rendering
    ///
    /// A window is active only on the current thread, if you want to
    /// make it active on another thread you have to deactivate it
    /// on the previous thread first if it was active.
    /// Only one window can be active on a thread at a time, thus
    /// the window previously active (if any) automatically gets deactivated.
    /// This is not to be confused with requestFocus().
    ///
    /// \param active True to activate, false to deactivate
    ///
    /// \return True if operation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool setActive(bool active = true) const;

    ////////////////////////////////////////////////////////////
    /// \brief Display on screen what has been rendered to the window so far
    ///
    /// This function is typically called after all OpenGL rendering
    /// has been done for the current frame, in order to show
    /// it on screen.
    ///
    ////////////////////////////////////////////////////////////
    void display();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Processes an event before it is sent to the user
    ///
    /// This function is called every time an event is received
    /// from the internal window (through pollEvent or waitEvent).
    /// It filters out unwanted events, and performs whatever internal
    /// stuff the window needs before the event is returned to the
    /// user.
    ///
    /// \param event Event to filter
    ///
    ////////////////////////////////////////////////////////////
    bool filterEvent(const Event& event);

    ////////////////////////////////////////////////////////////
    /// \brief Perform some common internal initializations
    ///
    ////////////////////////////////////////////////////////////
    void initialize();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::unique_ptr<priv::GlContext> m_context;        //!< Platform-specific implementation of the OpenGL context
    Clock                            m_clock;          //!< Clock for measuring the elapsed time between frames
    Time                             m_frameTimeLimit; //!< Current framerate limit
};

}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief VideoMode defines a video mode (width, height, bpp)
///
////////////////////////////////////////////////////////////
class SFML_WINDOW_API VideoMode
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructors initializes all members to 0.
    ///
    ////////////////////////////////////////////////////////////
    VideoMode();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the video mode with its attributes
    ///
    /// \param modeSize         Width and height in pixels
    /// \param modeBitsPerPixel Pixel depths in bits per pixel
    ///
    ////////////////////////////////////////////////////////////
    VideoMode(unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel = 32);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current desktop video mode
    ///
    /// \return Current desktop video mode
    ///
    ////////////////////////////////////////////////////////////
    static VideoMode getDesktopMode();

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve all the video modes supported in fullscreen mode
    ///
    /// When creating a fullscreen window, the video mode is restricted
    /// to be compatible with what the graphics driver and monitor
    /// support. This function returns the complete list of all video
    /// modes that can be used in fullscreen mode.
    /// The returned array is sorted from best to worst, so that
    /// the first element will always give the best mode (higher
    /// width, height and bits-per-pixel).
    ///
    /// \return Array containing all the supported fullscreen modes
    ///
    ////////////////////////////////////////////////////////////
    static const std::vector<VideoMode>& getFullscreenModes();

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether or not the video mode is valid
    ///
    /// The validity of video modes is only relevant when using
    /// fullscreen windows; otherwise any video mode can be used
    /// with no restriction.
    ///
    /// \return True if the video mode is valid for fullscreen mode
    ///
    ////////////////////////////////////////////////////////////
    bool isValid() const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int width;            //!< Video mode width and height, in pixels
    unsigned int height; //!< Video mode pixel depth, in bits per pixels
    unsigned int bitsPerPixel;
};

////////////////////////////////////////////////////////////
/// \relates VideoMode
/// \brief Overload of == operator to compare two video modes
///
/// \param left  Left operand (a video mode)
/// \param right Right operand (a video mode)
///
/// \return True if modes are equal
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool operator==(const VideoMode& left, const VideoMode& right);

////////////////////////////////////////////////////////////
/// \relates VideoMode
/// \brief Overload of != operator to compare two video modes
///
/// \param left  Left operand (a video mode)
/// \param right Right operand (a video mode)
///
/// \return True if modes are different
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool operator!=(const VideoMode& left, const VideoMode& right);

////////////////////////////////////////////////////////////
/// \relates VideoMode
/// \brief Overload of < operator to compare video modes
///
/// \param left  Left operand (a video mode)
/// \param right Right operand (a video mode)
///
/// \return True if \a left is lesser than \a right
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool operator<(const VideoMode& left, const VideoMode& right);

////////////////////////////////////////////////////////////
/// \relates VideoMode
/// \brief Overload of > operator to compare video modes
///
/// \param left  Left operand (a video mode)
/// \param right Right operand (a video mode)
///
/// \return True if \a left is greater than \a right
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool operator>(const VideoMode& left, const VideoMode& right);

////////////////////////////////////////////////////////////
/// \relates VideoMode
/// \brief Overload of <= operator to compare video modes
///
/// \param left  Left operand (a video mode)
/// \param right Right operand (a video mode)
///
/// \return True if \a left is lesser or equal than \a right
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool operator<=(const VideoMode& left, const VideoMode& right);

////////////////////////////////////////////////////////////
/// \relates VideoMode
/// \brief Overload of >= operator to compare video modes
///
/// \param left  Left operand (a video mode)
/// \param right Right operand (a video mode)
///
/// \return True if \a left is greater or equal than \a right
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool operator>=(const VideoMode& left, const VideoMode& right);

}

namespace sf::Sensor
{
////////////////////////////////////////////////////////////
/// \brief Sensor type
///
////////////////////////////////////////////////////////////
enum Type
{
    Accelerometer,    //!< Measures the raw acceleration (m/s^2)
    Gyroscope,        //!< Measures the raw rotation rates (degrees/s)
    Magnetometer,     //!< Measures the ambient magnetic field (micro-teslas)
    Gravity,          //!< Measures the direction and intensity of gravity, independent of device acceleration (m/s^2)
    UserAcceleration, //!< Measures the direction and intensity of device acceleration, independent of the gravity (m/s^2)
    Orientation,      //!< Measures the absolute 3D orientation (degrees)

    Count //!< Keep last -- the total number of sensor types
};

////////////////////////////////////////////////////////////
/// \brief Check if a sensor is available on the underlying platform
///
/// \param sensor Sensor to check
///
/// \return True if the sensor is available, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isAvailable(Type sensor);

////////////////////////////////////////////////////////////
/// \brief Enable or disable a sensor
///
/// All sensors are disabled by default, to avoid consuming too
/// much battery power. Once a sensor is enabled, it starts
/// sending events of the corresponding type.
///
/// This function does nothing if the sensor is unavailable.
///
/// \param sensor  Sensor to enable
/// \param enabled True to enable, false to disable
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API void setEnabled(Type sensor, bool enabled);

////////////////////////////////////////////////////////////
/// \brief Get the current sensor value
///
/// \param sensor Sensor to read
///
/// \return The current sensor value
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API Vector3f getValue(Type sensor);
}
namespace sf::Joystick
{
////////////////////////////////////////////////////////////
/// \brief Constants related to joysticks capabilities
///
////////////////////////////////////////////////////////////
// NOLINTBEGIN(readability-identifier-naming)
static constexpr unsigned int Count{8};        //!< Maximum number of supported joysticks
static constexpr unsigned int ButtonCount{32}; //!< Maximum number of supported buttons
static constexpr unsigned int AxisCount{8};    //!< Maximum number of supported axes
// NOLINTEND(readability-identifier-naming)

////////////////////////////////////////////////////////////
/// \brief Axes supported by SFML joysticks
///
////////////////////////////////////////////////////////////
enum Axis
{
    X,    //!< The X axis
    Y,    //!< The Y axis
    Z,    //!< The Z axis
    R,    //!< The R axis
    U,    //!< The U axis
    V,    //!< The V axis
    PovX, //!< The X axis of the point-of-view hat
    PovY  //!< The Y axis of the point-of-view hat
};

////////////////////////////////////////////////////////////
/// \brief Structure holding a joystick's identification
///
////////////////////////////////////////////////////////////
struct SFML_WINDOW_API Identification
{
    String       name{"No Joystick"}; //!< Name of the joystick
    unsigned int vendorId{};          //!< Manufacturer identifier
    unsigned int productId{};         //!< Product identifier
};

////////////////////////////////////////////////////////////
/// \brief Check if a joystick is connected
///
/// \param joystick Index of the joystick to check
///
/// \return True if the joystick is connected, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isConnected(unsigned int joystick);

////////////////////////////////////////////////////////////
/// \brief Return the number of buttons supported by a joystick
///
/// If the joystick is not connected, this function returns 0.
///
/// \param joystick Index of the joystick
///
/// \return Number of buttons supported by the joystick
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API unsigned int getButtonCount(unsigned int joystick);

////////////////////////////////////////////////////////////
/// \brief Check if a joystick supports a given axis
///
/// If the joystick is not connected, this function returns false.
///
/// \param joystick Index of the joystick
/// \param axis     Axis to check
///
/// \return True if the joystick supports the axis, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool hasAxis(unsigned int joystick, Axis axis);

////////////////////////////////////////////////////////////
/// \brief Check if a joystick button is pressed
///
/// If the joystick is not connected, this function returns false.
///
/// \param joystick Index of the joystick
/// \param button   Button to check
///
/// \return True if the button is pressed, false otherwise
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API bool isButtonPressed(unsigned int joystick, unsigned int button);

////////////////////////////////////////////////////////////
/// \brief Get the current position of a joystick axis
///
/// If the joystick is not connected, this function returns 0.
///
/// \param joystick Index of the joystick
/// \param axis     Axis to check
///
/// \return Current position of the axis, in range [-100 .. 100]
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API float getAxisPosition(unsigned int joystick, Axis axis);

////////////////////////////////////////////////////////////
/// \brief Get the joystick information
///
/// \param joystick Index of the joystick
///
/// \return Structure containing joystick information.
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API Identification getIdentification(unsigned int joystick);

////////////////////////////////////////////////////////////
/// \brief Update the states of all joysticks
///
/// This function is used internally by SFML, so you normally
/// don't have to call it explicitly. However, you may need to
/// call it if you have no window yet (or no window at all):
/// in this case the joystick states are not updated automatically.
///
////////////////////////////////////////////////////////////
SFML_WINDOW_API void update();
}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Defines a system event and its parameters
///
////////////////////////////////////////////////////////////
class Event
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Size events parameters (Resized)
    ///
    ////////////////////////////////////////////////////////////
    struct SizeEvent
    {
        unsigned int width;  //!< New width, in pixels
        unsigned int height; //!< New height, in pixels
    };

    ////////////////////////////////////////////////////////////
    /// \brief Keyboard event parameters (KeyPressed, KeyReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct KeyEvent
    {
        Keyboard::Key      code;     //!< Code of the key that has been pressed
        Keyboard::Scancode scancode; //!< Physical code of the key that has been pressed
        bool               alt;      //!< Is the Alt key pressed?
        bool               control;  //!< Is the Control key pressed?
        bool               shift;    //!< Is the Shift key pressed?
        bool               system;   //!< Is the System key pressed?
    };

    ////////////////////////////////////////////////////////////
    /// \brief Text event parameters (TextEntered)
    ///
    ////////////////////////////////////////////////////////////
    struct TextEvent
    {
        std::uint32_t unicode; //!< UTF-32 Unicode value of the character
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse move event parameters (MouseMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseMoveEvent
    {
        int x; //!< X position of the mouse pointer, relative to the left of the owner window
        int y; //!< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons events parameters
    ///        (MouseButtonPressed, MouseButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseButtonEvent
    {
        Mouse::Button button; //!< Code of the button that has been pressed
        int           x;      //!< X position of the mouse pointer, relative to the left of the owner window
        int           y;      //!< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse wheel events parameters (MouseWheelScrolled)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseWheelScrollEvent
    {
        Mouse::Wheel wheel; //!< Which wheel (for mice with multiple ones)
        float        delta; //!< Wheel offset (positive is up/left, negative is down/right). High-precision mice may use non-integral offsets.
        int          x; //!< X position of the mouse pointer, relative to the left of the owner window
        int          y; //!< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick connection events parameters
    ///        (JoystickConnected, JoystickDisconnected)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickConnectEvent
    {
        unsigned int joystickId; //!< Index of the joystick (in range [0 .. Joystick::Count - 1])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick axis move event parameters (JoystickMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickMoveEvent
    {
        unsigned int   joystickId; //!< Index of the joystick (in range [0 .. Joystick::Count - 1])
        Joystick::Axis axis;       //!< Axis on which the joystick moved
        float          position;   //!< New position on the axis (in range [-100 .. 100])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick buttons events parameters
    ///        (JoystickButtonPressed, JoystickButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickButtonEvent
    {
        unsigned int joystickId; //!< Index of the joystick (in range [0 .. Joystick::Count - 1])
        unsigned int button; //!< Index of the button that has been pressed (in range [0 .. Joystick::ButtonCount - 1])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Touch events parameters (TouchBegan, TouchMoved, TouchEnded)
    ///
    ////////////////////////////////////////////////////////////
    struct TouchEvent
    {
        unsigned int finger; //!< Index of the finger in case of multi-touch events
        int          x;      //!< X position of the touch, relative to the left of the owner window
        int          y;      //!< Y position of the touch, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Sensor event parameters (SensorChanged)
    ///
    ////////////////////////////////////////////////////////////
    struct SensorEvent
    {
        Sensor::Type type; //!< Type of the sensor
        float        x;    //!< Current value of the sensor on X axis
        float        y;    //!< Current value of the sensor on Y axis
        float        z;    //!< Current value of the sensor on Z axis
    };

    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the different types of events
    ///
    ////////////////////////////////////////////////////////////
    enum EventType
    {
        Closed,                 //!< The window requested to be closed (no data)
        Resized,                //!< The window was resized (data in event.size)
        LostFocus,              //!< The window lost the focus (no data)
        GainedFocus,            //!< The window gained the focus (no data)
        TextEntered,            //!< A character was entered (data in event.text)
        KeyPressed,             //!< A key was pressed (data in event.key)
        KeyReleased,            //!< A key was released (data in event.key)
        MouseWheelScrolled,     //!< The mouse wheel was scrolled (data in event.mouseWheelScroll)
        MouseButtonPressed,     //!< A mouse button was pressed (data in event.mouseButton)
        MouseButtonReleased,    //!< A mouse button was released (data in event.mouseButton)
        MouseMoved,             //!< The mouse cursor moved (data in event.mouseMove)
        MouseEntered,           //!< The mouse cursor entered the area of the window (no data)
        MouseLeft,              //!< The mouse cursor left the area of the window (no data)
        JoystickButtonPressed,  //!< A joystick button was pressed (data in event.joystickButton)
        JoystickButtonReleased, //!< A joystick button was released (data in event.joystickButton)
        JoystickMoved,          //!< The joystick moved along an axis (data in event.joystickMove)
        JoystickConnected,      //!< A joystick was connected (data in event.joystickConnect)
        JoystickDisconnected,   //!< A joystick was disconnected (data in event.joystickConnect)
        TouchBegan,             //!< A touch event began (data in event.touch)
        TouchMoved,             //!< A touch moved (data in event.touch)
        TouchEnded,             //!< A touch event ended (data in event.touch)
        SensorChanged,          //!< A sensor value changed (data in event.sensor)

        Count //!< Keep last -- the total number of event types
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    EventType type; //!< Type of the event

    union
    {
        SizeEvent      size;      //!< Size event parameters (Event::Resized)
        KeyEvent       key;       //!< Key event parameters (Event::KeyPressed, Event::KeyReleased)
        TextEvent      text;      //!< Text event parameters (Event::TextEntered)
        MouseMoveEvent mouseMove; //!< Mouse move event parameters (Event::MouseMoved)
        MouseButtonEvent mouseButton; //!< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
        MouseWheelScrollEvent mouseWheelScroll; //!< Mouse wheel event parameters (Event::MouseWheelScrolled)
        JoystickMoveEvent     joystickMove;     //!< Joystick move event parameters (Event::JoystickMoved)
        JoystickButtonEvent joystickButton; //!< Joystick button event parameters (Event::JoystickButtonPressed, Event::JoystickButtonReleased)
        JoystickConnectEvent joystickConnect; //!< Joystick (dis)connect event parameters (Event::JoystickConnected, Event::JoystickDisconnected)
        TouchEvent  touch;  //!< Touch events parameters (Event::TouchBegan, Event::TouchMoved, Event::TouchEnded)
        SensorEvent sensor; //!< Sensor event parameters (Event::SensorChanged)
    };
};

}

//graphics files

#if defined(SFML_GRAPHICS_EXPORTS)

#define SFML_GRAPHICS_API SFML_API_EXPORT

#else

#define SFML_GRAPHICS_API SFML_API_IMPORT

#endif

namespace sf
{
class RenderTarget;
class RenderStates;

////////////////////////////////////////////////////////////
/// \brief Abstract base class for objects that can be drawn
///        to a render target
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API Drawable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Drawable() = default;

protected:
    friend class RenderTarget;

    ////////////////////////////////////////////////////////////
    /// \brief Draw the object to a render target
    ///
    /// This is a pure virtual function that has to be implemented
    /// by the derived class to define how the drawable should be
    /// drawn.
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    virtual void draw(RenderTarget& target, const RenderStates& states) const = 0;
};

}

namespace sf
{

////////////////////////////////////////////////////////////
/// \brief Blending modes for drawing
///
////////////////////////////////////////////////////////////
struct SFML_GRAPHICS_API BlendMode
{
    ////////////////////////////////////////////////////////
    /// \brief Enumeration of the blending factors
    ///
    /// The factors are mapped directly to their OpenGL equivalents,
    /// specified by glBlendFunc() or glBlendFuncSeparate().
    ////////////////////////////////////////////////////////
    enum Factor
    {
        Zero,             //!< (0, 0, 0, 0)
        One,              //!< (1, 1, 1, 1)
        SrcColor,         //!< (src.r, src.g, src.b, src.a)
        OneMinusSrcColor, //!< (1, 1, 1, 1) - (src.r, src.g, src.b, src.a)
        DstColor,         //!< (dst.r, dst.g, dst.b, dst.a)
        OneMinusDstColor, //!< (1, 1, 1, 1) - (dst.r, dst.g, dst.b, dst.a)
        SrcAlpha,         //!< (src.a, src.a, src.a, src.a)
        OneMinusSrcAlpha, //!< (1, 1, 1, 1) - (src.a, src.a, src.a, src.a)
        DstAlpha,         //!< (dst.a, dst.a, dst.a, dst.a)
        OneMinusDstAlpha  //!< (1, 1, 1, 1) - (dst.a, dst.a, dst.a, dst.a)
    };

    ////////////////////////////////////////////////////////
    /// \brief Enumeration of the blending equations
    ///
    /// The equations are mapped directly to their OpenGL equivalents,
    /// specified by glBlendEquation() or glBlendEquationSeparate().
    ////////////////////////////////////////////////////////
    enum Equation
    {
        Add,             //!< Pixel = Src * SrcFactor + Dst * DstFactor
        Subtract,        //!< Pixel = Src * SrcFactor - Dst * DstFactor
        ReverseSubtract, //!< Pixel = Dst * DstFactor - Src * SrcFactor
        Min,             //!< Pixel = min(Dst, Src)
        Max              //!< Pixel = max(Dst, Src)
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs a blending mode that does alpha blending.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the blend mode given the factors and equation.
    ///
    /// This constructor uses the same factors and equation for both
    /// color and alpha components. It also defaults to the Add equation.
    ///
    /// \param sourceFactor      Specifies how to compute the source factor for the color and alpha channels.
    /// \param destinationFactor Specifies how to compute the destination factor for the color and alpha channels.
    /// \param blendEquation     Specifies how to combine the source and destination colors and alpha.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode(Factor sourceFactor, Factor destinationFactor, Equation blendEquation = Add);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the blend mode given the factors and equation.
    ///
    /// \param colorSourceFactor      Specifies how to compute the source factor for the color channels.
    /// \param colorDestinationFactor Specifies how to compute the destination factor for the color channels.
    /// \param colorBlendEquation     Specifies how to combine the source and destination colors.
    /// \param alphaSourceFactor      Specifies how to compute the source factor.
    /// \param alphaDestinationFactor Specifies how to compute the destination factor.
    /// \param alphaBlendEquation     Specifies how to combine the source and destination alphas.
    ///
    ////////////////////////////////////////////////////////////
    BlendMode(Factor   colorSourceFactor,
              Factor   colorDestinationFactor,
              Equation colorBlendEquation,
              Factor   alphaSourceFactor,
              Factor   alphaDestinationFactor,
              Equation alphaBlendEquation);

    ////////////////////////////////////////////////////////////
    // Member Data
    ////////////////////////////////////////////////////////////
    Factor   colorSrcFactor{BlendMode::SrcAlpha};         //!< Source blending factor for the color channels
    Factor   colorDstFactor{BlendMode::OneMinusSrcAlpha}; //!< Destination blending factor for the color channels
    Equation colorEquation{BlendMode::Add};               //!< Blending equation for the color channels
    Factor   alphaSrcFactor{BlendMode::One};              //!< Source blending factor for the alpha channel
    Factor   alphaDstFactor{BlendMode::OneMinusSrcAlpha}; //!< Destination blending factor for the alpha channel
    Equation alphaEquation{BlendMode::Add};               //!< Blending equation for the alpha channel
};

////////////////////////////////////////////////////////////
/// \relates BlendMode
/// \brief Overload of the == operator
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if blending modes are equal, false if they are different
///
////////////////////////////////////////////////////////////
SFML_GRAPHICS_API bool operator==(const BlendMode& left, const BlendMode& right);

////////////////////////////////////////////////////////////
/// \relates BlendMode
/// \brief Overload of the != operator
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if blending modes are different, false if they are equal
///
////////////////////////////////////////////////////////////
SFML_GRAPHICS_API bool operator!=(const BlendMode& left, const BlendMode& right);

////////////////////////////////////////////////////////////
// Commonly used blending modes
////////////////////////////////////////////////////////////
// NOLINTBEGIN(readability-identifier-naming)
SFML_GRAPHICS_API extern const BlendMode BlendAlpha;    //!< Blend source and dest according to dest alpha
SFML_GRAPHICS_API extern const BlendMode BlendAdd;      //!< Add source to dest
SFML_GRAPHICS_API extern const BlendMode BlendMultiply; //!< Multiply source and dest
SFML_GRAPHICS_API extern const BlendMode BlendMin;      //!< Take minimum between source and dest
SFML_GRAPHICS_API extern const BlendMode BlendMax;      //!< Take maximum between source and dest
SFML_GRAPHICS_API extern const BlendMode BlendNone;     //!< Overwrite dest with source
// NOLINTEND(readability-identifier-naming)

} 

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating RGBA colors
///
////////////////////////////////////////////////////////////
class Color
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructs an opaque black color. It is equivalent to
    /// sf::Color(0, 0, 0, 255).
    ///
    ////////////////////////////////////////////////////////////
    constexpr Color();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the color from its 4 RGBA components
    ///
    /// \param red   Red component (in the range [0, 255])
    /// \param green Green component (in the range [0, 255])
    /// \param blue  Blue component (in the range [0, 255])
    /// \param alpha Alpha (opacity) component (in the range [0, 255])
    ///
    ////////////////////////////////////////////////////////////
    constexpr Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the color from 32-bit unsigned integer
    ///
    /// \param color Number containing the RGBA components (in that order)
    ///
    ////////////////////////////////////////////////////////////
    constexpr explicit Color(std::uint32_t color);

    ////////////////////////////////////////////////////////////
    /// \brief Retrieve the color as a 32-bit unsigned integer
    ///
    /// \return Color represented as a 32-bit unsigned integer
    ///
    ////////////////////////////////////////////////////////////
    constexpr std::uint32_t toInteger() const;

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTBEGIN(readability-identifier-naming)
    static const Color Black;       //!< Black predefined color
    static const Color White;       //!< White predefined color
    static const Color Red;         //!< Red predefined color
    static const Color Green;       //!< Green predefined color
    static const Color Blue;        //!< Blue predefined color
    static const Color Yellow;      //!< Yellow predefined color
    static const Color Magenta;     //!< Magenta predefined color
    static const Color Cyan;        //!< Cyan predefined color
    static const Color Transparent; //!< Transparent (black) predefined color
    // NOLINTEND(readability-identifier-naming)

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::uint8_t r{};    //!< Red component
    std::uint8_t g{};    //!< Green component
    std::uint8_t b{};    //!< Blue component
    std::uint8_t a{255}; //!< Alpha (opacity) component
};

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the == operator
///
/// This operator compares two colors and check if they are equal.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if colors are equal, false if they are different
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator==(const Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the != operator
///
/// This operator compares two colors and check if they are different.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return True if colors are different, false if they are equal
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator!=(const Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the binary + operator
///
/// This operator returns the component-wise sum of two colors.
/// Components that exceed 255 are clamped to 255.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Result of \a left + \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Color operator+(const Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the binary - operator
///
/// This operator returns the component-wise subtraction of two colors.
/// Components below 0 are clamped to 0.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Result of \a left - \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Color operator-(const Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the binary * operator
///
/// This operator returns the component-wise multiplication
/// (also called "modulation") of two colors.
/// Components are then divided by 255 so that the result is
/// still in the range [0, 255].
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Result of \a left * \a right
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr Color operator*(const Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the binary += operator
///
/// This operator computes the component-wise sum of two colors,
/// and assigns the result to the left operand.
/// Components that exceed 255 are clamped to 255.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
constexpr Color& operator+=(Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the binary -= operator
///
/// This operator computes the component-wise subtraction of two colors,
/// and assigns the result to the left operand.
/// Components below 0 are clamped to 0.
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
constexpr Color& operator-=(Color& left, const Color& right);

////////////////////////////////////////////////////////////
/// \relates Color
/// \brief Overload of the binary *= operator
///
/// This operator returns the component-wise multiplication
/// (also called "modulation") of two colors, and assigns
/// the result to the left operand.
/// Components are then divided by 255 so that the result is
/// still in the range [0, 255].
///
/// \param left  Left operand
/// \param right Right operand
///
/// \return Reference to \a left
///
////////////////////////////////////////////////////////////
constexpr Color& operator*=(Color& left, const Color& right);

constexpr Color::Color() = default;


////////////////////////////////////////////////////////////
constexpr Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) :
r(red),
g(green),
b(blue),
a(alpha)
{
}


////////////////////////////////////////////////////////////
constexpr Color::Color(std::uint32_t color) :
r(static_cast<std::uint8_t>((color & 0xff000000) >> 24)),
g(static_cast<std::uint8_t>((color & 0x00ff0000) >> 16)),
b(static_cast<std::uint8_t>((color & 0x0000ff00) >> 8)),
a(static_cast<std::uint8_t>(color & 0x000000ff))
{
}


////////////////////////////////////////////////////////////
constexpr std::uint32_t Color::toInteger() const
{
    return static_cast<std::uint32_t>((r << 24) | (g << 16) | (b << 8) | a);
}


////////////////////////////////////////////////////////////
constexpr bool operator==(const Color& left, const Color& right)
{
    return (left.r == right.r) && (left.g == right.g) && (left.b == right.b) && (left.a == right.a);
}


////////////////////////////////////////////////////////////
constexpr bool operator!=(const Color& left, const Color& right)
{
    return !(left == right);
}


////////////////////////////////////////////////////////////
constexpr Color operator+(const Color& left, const Color& right)
{
    const auto clampedAdd = [](std::uint8_t lhs, std::uint8_t rhs) -> std::uint8_t
    {
        const int intResult = int{lhs} + int{rhs};
        return static_cast<std::uint8_t>(intResult < 255 ? intResult : 255);
    };

    return Color(clampedAdd(left.r, right.r),
                 clampedAdd(left.g, right.g),
                 clampedAdd(left.b, right.b),
                 clampedAdd(left.a, right.a));
}


////////////////////////////////////////////////////////////
constexpr Color operator-(const Color& left, const Color& right)
{
    const auto clampedSub = [](std::uint8_t lhs, std::uint8_t rhs) -> std::uint8_t
    {
        const int intResult = int{lhs} - int{rhs};
        return static_cast<std::uint8_t>(intResult > 0 ? intResult : 0);
    };

    return Color(clampedSub(left.r, right.r),
                 clampedSub(left.g, right.g),
                 clampedSub(left.b, right.b),
                 clampedSub(left.a, right.a));
}


////////////////////////////////////////////////////////////
constexpr Color operator*(const Color& left, const Color& right)
{
    const auto scaledMul = [](std::uint8_t lhs, std::uint8_t rhs) -> std::uint8_t
    {
        const auto uint16Result = static_cast<std::uint16_t>(std::uint16_t{lhs} * std::uint16_t{rhs});
        return static_cast<std::uint8_t>(uint16Result / 255u);
    };

    return Color(scaledMul(left.r, right.r),
                 scaledMul(left.g, right.g),
                 scaledMul(left.b, right.b),
                 scaledMul(left.a, right.a));
}


////////////////////////////////////////////////////////////
constexpr Color& operator+=(Color& left, const Color& right)
{
    return left = left + right;
}


////////////////////////////////////////////////////////////
constexpr Color& operator-=(Color& left, const Color& right)
{
    return left = left - right;
}


////////////////////////////////////////////////////////////
constexpr Color& operator*=(Color& left, const Color& right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
// Static member data
////////////////////////////////////////////////////////////

// Note: the 'inline' keyword here is technically not required, but VS2019 fails
// to compile with a bogus "multiple definition" error if not explicitly used.
inline constexpr Color Color::Black(0, 0, 0);
inline constexpr Color Color::White(255, 255, 255);
inline constexpr Color Color::Red(255, 0, 0);
inline constexpr Color Color::Green(0, 255, 0);
inline constexpr Color Color::Blue(0, 0, 255);
inline constexpr Color Color::Yellow(255, 255, 0);
inline constexpr Color Color::Magenta(255, 0, 255);
inline constexpr Color Color::Cyan(0, 255, 255);
inline constexpr Color Color::Transparent(0, 0, 0, 0);
}

namespace sf
{
////////////////////////////////////////////////////////////
/// \ingroup graphics
/// \brief Types of primitives that a sf::VertexArray can render
///
/// Points and lines have no area, therefore their thickness
/// will always be 1 pixel, regardless the current transform
/// and view.
///
////////////////////////////////////////////////////////////
enum class PrimitiveType
{
    Points,        //!< List of individual points
    Lines,         //!< List of individual lines
    LineStrip,     //!< List of connected lines, a point uses the previous point to form a line
    Triangles,     //!< List of individual triangles
    TriangleStrip, //!< List of connected triangles, a point uses the two previous points to form a triangle
    TriangleFan //!< List of connected triangles, a point uses the common center and the previous point to form a triangle
};

}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating 2D axis aligned rectangles
///
////////////////////////////////////////////////////////////
template <typename T>
class Rect
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty rectangle (it is equivalent to calling
    /// Rect({0, 0}, {0, 0})).
    ///
    ////////////////////////////////////////////////////////////
    constexpr Rect();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the rectangle from position and size
    ///
    /// Be careful, the last parameter is the size,
    /// not the bottom-right corner!
    ///
    /// \param position Position of the top-left corner of the rectangle
    /// \param size     Size of the rectangle
    ///
    ////////////////////////////////////////////////////////////
    constexpr Rect(const Vector2<T>& position, const Vector2<T>& size);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the rectangle from another type of rectangle
    ///
    /// This constructor doesn't replace the copy constructor,
    /// it's called only when U != T.
    /// A call to this constructor will fail to compile if U
    /// is not convertible to T.
    ///
    /// \param rectangle Rectangle to convert
    ///
    ////////////////////////////////////////////////////////////
    template <typename U>
    constexpr explicit Rect(const Rect<U>& rectangle);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a point is inside the rectangle's area
    ///
    /// This check is non-inclusive. If the point lies on the
    /// edge of the rectangle, this function will return false.
    ///
    /// \param point Point to test
    ///
    /// \return True if the point is inside, false otherwise
    ///
    /// \see findIntersection
    ///
    ////////////////////////////////////////////////////////////
    constexpr bool contains(const Vector2<T>& point) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check the intersection between two rectangles
    ///
    /// \param rectangle Rectangle to test
    ///
    /// \return Intersection rectangle if intersecting, std::nullopt otherwise
    ///
    /// \see contains
    ///
    ////////////////////////////////////////////////////////////
    constexpr std::optional<Rect<T>> findIntersection(const Rect<T>& rectangle) const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the rectangle's top-left corner
    ///
    /// \return Position of rectangle
    ///
    /// \see getSize
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2<T> getPosition() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the rectangle
    ///
    /// \return Size of rectangle
    ///
    /// \see getPosition
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2<T> getSize() const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T left{};   //!< Left coordinate of the rectangle
    T top{};    //!< Top coordinate of the rectangle
    T width{};  //!< Width of the rectangle
    T height{}; //!< Height of the rectangle
};

////////////////////////////////////////////////////////////
/// \relates Rect
/// \brief Overload of binary operator ==
///
/// This operator compares strict equality between two rectangles.
///
/// \param left  Left operand (a rectangle)
/// \param right Right operand (a rectangle)
///
/// \return True if \a left is equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator==(const Rect<T>& left, const Rect<T>& right);

////////////////////////////////////////////////////////////
/// \relates Rect
/// \brief Overload of binary operator !=
///
/// This operator compares strict difference between two rectangles.
///
/// \param left  Left operand (a rectangle)
/// \param right Right operand (a rectangle)
///
/// \return True if \a left is not equal to \a right
///
////////////////////////////////////////////////////////////
template <typename T>
[[nodiscard]] constexpr bool operator!=(const Rect<T>& left, const Rect<T>& right);

template <typename T>
constexpr Rect<T>::Rect() = default;


////////////////////////////////////////////////////////////
template <typename T>
constexpr Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) :
left(position.x),
top(position.y),
width(size.x),
height(size.y)
{
}


////////////////////////////////////////////////////////////
template <typename T>
template <typename U>
constexpr Rect<T>::Rect(const Rect<U>& rectangle) :
left(static_cast<T>(rectangle.left)),
top(static_cast<T>(rectangle.top)),
width(static_cast<T>(rectangle.width)),
height(static_cast<T>(rectangle.height))
{
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool Rect<T>::contains(const Vector2<T>& point) const
{
    // Not using 'std::min' and 'std::max' to avoid depending on '<algorithm>'
    const auto min = [](T a, T b) { return (a < b) ? a : b; };
    const auto max = [](T a, T b) { return (a < b) ? b : a; };

    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the real min and max of the rectangle on both axes
    const T minX = min(left, static_cast<T>(left + width));
    const T maxX = max(left, static_cast<T>(left + width));
    const T minY = min(top, static_cast<T>(top + height));
    const T maxY = max(top, static_cast<T>(top + height));

    return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr std::optional<Rect<T>> Rect<T>::findIntersection(const Rect<T>& rectangle) const
{
    // Not using 'std::min' and 'std::max' to avoid depending on '<algorithm>'
    const auto min = [](T a, T b) { return (a < b) ? a : b; };
    const auto max = [](T a, T b) { return (a < b) ? b : a; };

    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the min and max of the first rectangle on both axes
    const T r1MinX = min(left, static_cast<T>(left + width));
    const T r1MaxX = max(left, static_cast<T>(left + width));
    const T r1MinY = min(top, static_cast<T>(top + height));
    const T r1MaxY = max(top, static_cast<T>(top + height));

    // Compute the min and max of the second rectangle on both axes
    const T r2MinX = min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    const T r2MaxX = max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    const T r2MinY = min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
    const T r2MaxY = max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

    // Compute the intersection boundaries
    const T interLeft   = max(r1MinX, r2MinX);
    const T interTop    = max(r1MinY, r2MinY);
    const T interRight  = min(r1MaxX, r2MaxX);
    const T interBottom = min(r1MaxY, r2MaxY);

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom))
    {
        return Rect<T>({interLeft, interTop}, {interRight - interLeft, interBottom - interTop});
    }
    else
    {
        return std::nullopt;
    }
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> Rect<T>::getPosition() const
{
    return Vector2<T>(left, top);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr Vector2<T> Rect<T>::getSize() const
{
    return Vector2<T>(width, height);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator==(const Rect<T>& left, const Rect<T>& right)
{
    return (left.left == right.left) && (left.width == right.width) && (left.top == right.top) &&
           (left.height == right.height);
}


////////////////////////////////////////////////////////////
template <typename T>
constexpr bool operator!=(const Rect<T>& left, const Rect<T>& right)
{
    return !(left == right);
}
// Create type aliases for the most common types
using IntRect   = Rect<int>;
using FloatRect = Rect<float>;

}

namespace sf
{
class Angle;

////////////////////////////////////////////////////////////
/// \brief Define a 3x3 transform matrix
///
////////////////////////////////////////////////////////////
class Transform
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an identity transform (a transform that does nothing).
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a transform from a 3x3 matrix
    ///
    /// \param a00 Element (0, 0) of the matrix
    /// \param a01 Element (0, 1) of the matrix
    /// \param a02 Element (0, 2) of the matrix
    /// \param a10 Element (1, 0) of the matrix
    /// \param a11 Element (1, 1) of the matrix
    /// \param a12 Element (1, 2) of the matrix
    /// \param a20 Element (2, 0) of the matrix
    /// \param a21 Element (2, 1) of the matrix
    /// \param a22 Element (2, 2) of the matrix
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);

    ////////////////////////////////////////////////////////////
    /// \brief Return the transform as a 4x4 matrix
    ///
    /// This function returns a pointer to an array of 16 floats
    /// containing the transform elements as a 4x4 matrix, which
    /// is directly compatible with OpenGL functions.
    ///
    /// \code
    /// sf::Transform transform = ...;
    /// glLoadMatrixf(transform.getMatrix());
    /// \endcode
    ///
    /// \return Pointer to a 4x4 matrix
    ///
    ////////////////////////////////////////////////////////////
    constexpr const float* getMatrix() const;

    ////////////////////////////////////////////////////////////
    /// \brief Return the inverse of the transform
    ///
    /// If the inverse cannot be computed, an identity transform
    /// is returned.
    ///
    /// \return A new transform which is the inverse of self
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform getInverse() const;

    ////////////////////////////////////////////////////////////
    /// \brief Transform a 2D point
    ///
    /// These two statements are equivalent:
    /// \code
    /// sf::Vector2f transformedPoint = matrix.transformPoint(point);
    /// sf::Vector2f transformedPoint = matrix * point;
    /// \endcode
    ///
    /// \param point Point to transform
    ///
    /// \return Transformed point
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vector2f transformPoint(const Vector2f& point) const;

    ////////////////////////////////////////////////////////////
    /// \brief Transform a rectangle
    ///
    /// Since SFML doesn't provide support for oriented rectangles,
    /// the result of this function is always an axis-aligned
    /// rectangle. Which means that if the transform contains a
    /// rotation, the bounding rectangle of the transformed rectangle
    /// is returned.
    ///
    /// \param rectangle Rectangle to transform
    ///
    /// \return Transformed rectangle
    ///
    ////////////////////////////////////////////////////////////
    constexpr FloatRect transformRect(const FloatRect& rectangle) const;

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with another one
    ///
    /// The result is a transform that is equivalent to applying
    /// \a transform followed by *this. Mathematically, it is
    /// equivalent to a matrix multiplication (*this) * transform.
    ///
    /// These two statements are equivalent:
    /// \code
    /// left.combine(right);
    /// left *= right;
    /// \endcode
    ///
    /// \param transform Transform to combine with this transform
    ///
    /// \return Reference to *this
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform& combine(const Transform& transform);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a translation
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform transform;
    /// transform.translate(sf::Vector2f(100, 200)).rotate(sf::degrees(45));
    /// \endcode
    ///
    /// \param offset Translation offset to apply
    ///
    /// \return Reference to *this
    ///
    /// \see rotate, scale
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform& translate(const Vector2f& offset);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a rotation
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform transform;
    /// transform.rotate(sf::degrees(90)).translate(50, 20);
    /// \endcode
    ///
    /// \param angle Rotation angle
    ///
    /// \return Reference to *this
    ///
    /// \see translate, scale
    ///
    ////////////////////////////////////////////////////////////
    SFML_GRAPHICS_API Transform& rotate(Angle angle);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a rotation
    ///
    /// The center of rotation is provided for convenience as a second
    /// argument, so that you can build rotations around arbitrary points
    /// more easily (and efficiently) than the usual
    /// translate(-center).rotate(angle).translate(center).
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform transform;
    /// transform.rotate(sf::degrees(90), sf::Vector2f(8, 3)).translate(sf::Vector2f(50, 20));
    /// \endcode
    ///
    /// \param angle Rotation angle
    /// \param center Center of rotation
    ///
    /// \return Reference to *this
    ///
    /// \see translate, scale
    ///
    ////////////////////////////////////////////////////////////
    SFML_GRAPHICS_API Transform& rotate(Angle angle, const Vector2f& center);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a scaling
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform transform;
    /// transform.scale(sf::Vector2f(2, 1)).rotate(sf::degrees(45));
    /// \endcode
    ///
    /// \param factors Scaling factors
    ///
    /// \return Reference to *this
    ///
    /// \see translate, rotate
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform& scale(const Vector2f& factors);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a scaling
    ///
    /// The center of scaling is provided for convenience as a second
    /// argument, so that you can build scaling around arbitrary points
    /// more easily (and efficiently) than the usual
    /// translate(-center).scale(factors).translate(center).
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform transform;
    /// transform.scale(sf::Vector2f(2, 1), sf::Vector2f(8, 3)).rotate(45);
    /// \endcode
    ///
    /// \param factors Scaling factors
    /// \param center Center of scaling
    ///
    /// \return Reference to *this
    ///
    /// \see translate, rotate
    ///
    ////////////////////////////////////////////////////////////
    constexpr Transform& scale(const Vector2f& factors, const Vector2f& center);

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTNEXTLINE(readability-identifier-naming)
    static const Transform Identity; //!< The identity transform (does nothing)

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    // clang-format off
    float m_matrix[16]{1.f, 0.f, 0.f, 0.f,
                       0.f, 1.f, 0.f, 0.f,
                       0.f, 0.f, 1.f, 0.f,
                       0.f, 0.f, 0.f, 1.f}; //!< 4x4 matrix defining the transformation
    // clang-format off
};

////////////////////////////////////////////////////////////
/// \relates sf::Transform
/// \brief Overload of binary operator * to combine two transforms
///
/// This call is equivalent to calling Transform(left).combine(right).
///
/// \param left Left operand (the first transform)
/// \param right Right operand (the second transform)
///
/// \return New combined transform
///
////////////////////////////////////////////////////////////
constexpr Transform operator*(const Transform& left, const Transform& right);

////////////////////////////////////////////////////////////
/// \relates sf::Transform
/// \brief Overload of binary operator *= to combine two transforms
///
/// This call is equivalent to calling left.combine(right).
///
/// \param left Left operand (the first transform)
/// \param right Right operand (the second transform)
///
/// \return The combined transform
///
////////////////////////////////////////////////////////////
constexpr Transform& operator*=(Transform& left, const Transform& right);

////////////////////////////////////////////////////////////
/// \relates sf::Transform
/// \brief Overload of binary operator * to transform a point
///
/// This call is equivalent to calling left.transformPoint(right).
///
/// \param left Left operand (the transform)
/// \param right Right operand (the point to transform)
///
/// \return New transformed point
///
////////////////////////////////////////////////////////////
constexpr Vector2f operator*(const Transform& left, const Vector2f& right);

////////////////////////////////////////////////////////////
/// \relates sf::Transform
/// \brief Overload of binary operator == to compare two transforms
///
/// Performs an element-wise comparison of the elements of the
/// left transform with the elements of the right transform.
///
/// \param left Left operand (the first transform)
/// \param right Right operand (the second transform)
///
/// \return true if the transforms are equal, false otherwise
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator==(const Transform& left, const Transform& right);

////////////////////////////////////////////////////////////
/// \relates sf::Transform
/// \brief Overload of binary operator != to compare two transforms
///
/// This call is equivalent to !(left == right).
///
/// \param left Left operand (the first transform)
/// \param right Right operand (the second transform)
///
/// \return true if the transforms are not equal, false otherwise
///
////////////////////////////////////////////////////////////
[[nodiscard]] constexpr bool operator!=(const Transform& left, const Transform& right);

constexpr Transform::Transform() = default;


////////////////////////////////////////////////////////////
// clang-format off
constexpr Transform::Transform(float a00, float a01, float a02,
                               float a10, float a11, float a12,
                               float a20, float a21, float a22)
    : m_matrix{a00, a10, 0.f, a20,
               a01, a11, 0.f, a21,
               0.f, 0.f, 1.f, 0.f,
               a02, a12, 0.f, a22}
{
}
// clang-format on


////////////////////////////////////////////////////////////
constexpr const float* Transform::getMatrix() const
{
    return m_matrix;
}


////////////////////////////////////////////////////////////
constexpr Transform Transform::getInverse() const
{
    // clang-format off
    // Compute the determinant
    const float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
                      m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
                      m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);
    // clang-format on

    // Compute the inverse if the determinant is not zero
    // (don't use an epsilon because the determinant may *really* be tiny)
    if (det != 0.f)
    {
        // clang-format off
        return Transform( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                         -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                          (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                         -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                          (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                         -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                          (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                         -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                          (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
        // clang-format on
    }
    else
    {
        return Identity;
    }
}


////////////////////////////////////////////////////////////
constexpr Vector2f Transform::transformPoint(const Vector2f& point) const
{
    return Vector2f(m_matrix[0] * point.x + m_matrix[4] * point.y + m_matrix[12],
                    m_matrix[1] * point.x + m_matrix[5] * point.y + m_matrix[13]);
}


////////////////////////////////////////////////////////////
constexpr FloatRect Transform::transformRect(const FloatRect& rectangle) const
{
    // Transform the 4 corners of the rectangle
    const Vector2f points[] = {transformPoint({rectangle.left, rectangle.top}),
                               transformPoint({rectangle.left, rectangle.top + rectangle.height}),
                               transformPoint({rectangle.left + rectangle.width, rectangle.top}),
                               transformPoint({rectangle.left + rectangle.width, rectangle.top + rectangle.height})};

    // Compute the bounding rectangle of the transformed points
    float left   = points[0].x;
    float top    = points[0].y;
    float right  = points[0].x;
    float bottom = points[0].y;

    for (int i = 1; i < 4; ++i)
    {
        // clang-format off
        if      (points[i].x < left)   left   = points[i].x;
        else if (points[i].x > right)  right  = points[i].x;

        if      (points[i].y < top)    top    = points[i].y;
        else if (points[i].y > bottom) bottom = points[i].y;
        // clang-format on
    }

    return FloatRect({left, top}, {right - left, bottom - top});
}


////////////////////////////////////////////////////////////
constexpr Transform& Transform::combine(const Transform& transform)
{
    const float* a = m_matrix;
    const float* b = transform.m_matrix;

    // clang-format off
    *this = Transform(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                      a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                      a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                      a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                      a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                      a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                      a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                      a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                      a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);
    // clang-format on

    return *this;
}


////////////////////////////////////////////////////////////
constexpr Transform& Transform::translate(const Vector2f& offset)
{
    // clang-format off
    const Transform translation(1, 0, offset.x,
                                0, 1, offset.y,
                                0, 0, 1);
    // clang-format on

    return combine(translation);
}


////////////////////////////////////////////////////////////
constexpr Transform& Transform::scale(const Vector2f& factors)
{
    // clang-format off
    const Transform scaling(factors.x, 0,         0,
                            0,         factors.y, 0,
                            0,         0,         1);
    // clang-format on

    return combine(scaling);
}


////////////////////////////////////////////////////////////
constexpr Transform& Transform::scale(const Vector2f& factors, const Vector2f& center)
{
    // clang-format off
    const Transform scaling(factors.x, 0,         center.x * (1 - factors.x),
                            0,         factors.y, center.y * (1 - factors.y),
                            0,         0,         1);
    // clang-format on

    return combine(scaling);
}


////////////////////////////////////////////////////////////
constexpr Transform operator*(const Transform& left, const Transform& right)
{
    return Transform(left).combine(right);
}


////////////////////////////////////////////////////////////
constexpr Transform& operator*=(Transform& left, const Transform& right)
{
    return left.combine(right);
}


////////////////////////////////////////////////////////////
constexpr Vector2f operator*(const Transform& left, const Vector2f& right)
{
    return left.transformPoint(right);
}


////////////////////////////////////////////////////////////
constexpr bool operator==(const Transform& left, const Transform& right)
{
    const float* a = left.getMatrix();
    const float* b = right.getMatrix();

    // clang-format off
    return ((a[0]  == b[0])  && (a[1]  == b[1])  && (a[3]  == b[3]) &&
            (a[4]  == b[4])  && (a[5]  == b[5])  && (a[7]  == b[7]) &&
            (a[12] == b[12]) && (a[13] == b[13]) && (a[15] == b[15]));
    // clang-format on
}


////////////////////////////////////////////////////////////
constexpr bool operator!=(const Transform& left, const Transform& right)
{
    return !(left == right);
}


////////////////////////////////////////////////////////////
// Static member data
////////////////////////////////////////////////////////////

// Note: the 'inline' keyword here is technically not required, but VS2019 fails
// to compile with a bogus "multiple definition" error if not explicitly used.
inline constexpr Transform Transform::Identity;
}

namespace sf
{
class Shader;
class Texture;

////////////////////////////////////////////////////////////
/// \brief Define the states used for drawing to a RenderTarget
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API RenderStates
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Constructing a default set of render states is equivalent
    /// to using sf::RenderStates::Default.
    /// The default set defines:
    /// \li the BlendAlpha blend mode
    /// \li the identity transform
    /// \li a null texture
    /// \li a null shader
    ///
    ////////////////////////////////////////////////////////////
    RenderStates();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom blend mode
    ///
    /// \param theBlendMode Blend mode to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const BlendMode& theBlendMode);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom transform
    ///
    /// \param theTransform Transform to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const Transform& theTransform);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom texture
    ///
    /// \param theTexture Texture to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const Texture* theTexture);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a default set of render states with a custom shader
    ///
    /// \param theShader Shader to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const Shader* theShader);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a set of render states with all its attributes
    ///
    /// \param theBlendMode Blend mode to use
    /// \param theTransform Transform to use
    /// \param theTexture   Texture to use
    /// \param theShader    Shader to use
    ///
    ////////////////////////////////////////////////////////////
    RenderStates(const BlendMode& theBlendMode, const Transform& theTransform, const Texture* theTexture, const Shader* theShader);

    ////////////////////////////////////////////////////////////
    // Static member data
    ////////////////////////////////////////////////////////////
    // NOLINTNEXTLINE(readability-identifier-naming)
    static const RenderStates Default; //!< Special instance holding the default render states

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    BlendMode      blendMode{BlendAlpha}; //!< Blending mode
    Transform      transform;             //!< Transform
    const Texture* texture{};             //!< Texture
    const Shader*  shader{};              //!< Shader
};

}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Define a point with color and texture coordinates
///
////////////////////////////////////////////////////////////
class Vertex
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vertex();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vertex from its position
    ///
    /// The vertex color is white and texture coordinates are (0, 0).
    ///
    /// \param thePosition Vertex position
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vertex(const Vector2f& thePosition);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vertex from its position and color
    ///
    /// The texture coordinates are (0, 0).
    ///
    /// \param thePosition Vertex position
    /// \param theColor    Vertex color
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vertex(const Vector2f& thePosition, const Color& theColor);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vertex from its position and texture coordinates
    ///
    /// The vertex color is white.
    ///
    /// \param thePosition  Vertex position
    /// \param theTexCoords Vertex texture coordinates
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vertex(const Vector2f& thePosition, const Vector2f& theTexCoords);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vertex from its position, color and texture coordinates
    ///
    /// \param thePosition  Vertex position
    /// \param theColor     Vertex color
    /// \param theTexCoords Vertex texture coordinates
    ///
    ////////////////////////////////////////////////////////////
    constexpr Vertex(const Vector2f& thePosition, const Color& theColor, const Vector2f& theTexCoords);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Vector2f position;            //!< 2D position of the vertex
    Color    color{Color::White}; //!< Color of the vertex
    Vector2f texCoords;           //!< Coordinates of the texture's pixel to map to the vertex
};

constexpr Vertex::Vertex() = default;


////////////////////////////////////////////////////////////
constexpr Vertex::Vertex(const Vector2f& thePosition) : position(thePosition)
{
}


////////////////////////////////////////////////////////////
constexpr Vertex::Vertex(const Vector2f& thePosition, const Color& theColor) : position(thePosition), color(theColor)
{
}


////////////////////////////////////////////////////////////
constexpr Vertex::Vertex(const Vector2f& thePosition, const Vector2f& theTexCoords) :
position(thePosition),
texCoords(theTexCoords)
{
}


////////////////////////////////////////////////////////////
constexpr Vertex::Vertex(const Vector2f& thePosition, const Color& theColor, const Vector2f& theTexCoords) :
position(thePosition),
color(theColor),
texCoords(theTexCoords)
{
}



}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief 2D camera that defines what region is shown on screen
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API View
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor creates a default view of (0, 0, 1000, 1000)
    ///
    ////////////////////////////////////////////////////////////
    View();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the view from a rectangle
    ///
    /// \param rectangle Rectangle defining the zone to display
    ///
    ////////////////////////////////////////////////////////////
    explicit View(const FloatRect& rectangle);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the view from its center and size
    ///
    /// \param center Center of the zone to display
    /// \param size   Size of zone to display
    ///
    ////////////////////////////////////////////////////////////
    View(const Vector2f& center, const Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// \brief Set the center of the view
    ///
    /// \param center New center
    ///
    /// \see setSize, getCenter
    ///
    ////////////////////////////////////////////////////////////
    void setCenter(const Vector2f& center);

    ////////////////////////////////////////////////////////////
    /// \brief Set the size of the view
    ///
    /// \param size New size
    ///
    /// \see setCenter, getCenter
    ///
    ////////////////////////////////////////////////////////////
    void setSize(const Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// \brief Set the orientation of the view
    ///
    /// The default rotation of a view is 0 degree.
    ///
    /// \param angle New angle
    ///
    /// \see getRotation
    ///
    ////////////////////////////////////////////////////////////
    void setRotation(Angle angle);

    ////////////////////////////////////////////////////////////
    /// \brief Set the target viewport
    ///
    /// The viewport is the rectangle into which the contents of the
    /// view are displayed, expressed as a factor (between 0 and 1)
    /// of the size of the RenderTarget to which the view is applied.
    /// For example, a view which takes the left side of the target would
    /// be defined with View.setViewport(sf::FloatRect({0.f, 0.f}, {0.5f, 1.f})).
    /// By default, a view has a viewport which covers the entire target.
    ///
    /// \param viewport New viewport rectangle
    ///
    /// \see getViewport
    ///
    ////////////////////////////////////////////////////////////
    void setViewport(const FloatRect& viewport);

    ////////////////////////////////////////////////////////////
    /// \brief Reset the view to the given rectangle
    ///
    /// Note that this function resets the rotation angle to 0.
    ///
    /// \param rectangle Rectangle defining the zone to display
    ///
    /// \see setCenter, setSize, setRotation
    ///
    ////////////////////////////////////////////////////////////
    void reset(const FloatRect& rectangle);

    ////////////////////////////////////////////////////////////
    /// \brief Get the center of the view
    ///
    /// \return Center of the view
    ///
    /// \see getSize, setCenter
    ///
    ////////////////////////////////////////////////////////////
    const Vector2f& getCenter() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the view
    ///
    /// \return Size of the view
    ///
    /// \see getCenter, setSize
    ///
    ////////////////////////////////////////////////////////////
    const Vector2f& getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the current orientation of the view
    ///
    /// \return Rotation angle of the view
    ///
    /// \see setRotation
    ///
    ////////////////////////////////////////////////////////////
    Angle getRotation() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the target viewport rectangle of the view
    ///
    /// \return Viewport rectangle, expressed as a factor of the target size
    ///
    /// \see setViewport
    ///
    ////////////////////////////////////////////////////////////
    const FloatRect& getViewport() const;

    ////////////////////////////////////////////////////////////
    /// \brief Move the view relatively to its current position
    ///
    /// \param offset Move offset
    ///
    /// \see setCenter, rotate, zoom
    ///
    ////////////////////////////////////////////////////////////
    void move(const Vector2f& offset);

    ////////////////////////////////////////////////////////////
    /// \brief Rotate the view relatively to its current orientation
    ///
    /// \param angle Angle to rotate
    ///
    /// \see setRotation, move, zoom
    ///
    ////////////////////////////////////////////////////////////
    void rotate(Angle angle);

    ////////////////////////////////////////////////////////////
    /// \brief Resize the view rectangle relatively to its current size
    ///
    /// Resizing the view simulates a zoom, as the zone displayed on
    /// screen grows or shrinks.
    /// \a factor is a multiplier:
    /// \li 1 keeps the size unchanged
    /// \li > 1 makes the view bigger (objects appear smaller)
    /// \li < 1 makes the view smaller (objects appear bigger)
    ///
    /// \param factor Zoom factor to apply
    ///
    /// \see setSize, move, rotate
    ///
    ////////////////////////////////////////////////////////////
    void zoom(float factor);

    ////////////////////////////////////////////////////////////
    /// \brief Get the projection transform of the view
    ///
    /// This function is meant for internal use only.
    ///
    /// \return Projection transform defining the view
    ///
    /// \see getInverseTransform
    ///
    ////////////////////////////////////////////////////////////
    const Transform& getTransform() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the inverse projection transform of the view
    ///
    /// This function is meant for internal use only.
    ///
    /// \return Inverse of the projection transform defining the view
    ///
    /// \see getTransform
    ///
    ////////////////////////////////////////////////////////////
    const Transform& getInverseTransform() const;

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Vector2f  m_center;                     //!< Center of the view, in scene coordinates
    Vector2f  m_size;                       //!< Size of the view, in scene coordinates
    Angle     m_rotation;                   //!< Angle of rotation of the view rectangle
    FloatRect m_viewport{{0, 0}, {1, 1}};   //!< Viewport rectangle, expressed as a factor of the render-target's size
    mutable Transform m_transform;          //!< Precomputed projection transform corresponding to the view
    mutable Transform m_inverseTransform;   //!< Precomputed inverse projection transform corresponding to the view
    mutable bool      m_transformUpdated{}; //!< Internal state telling if the transform needs to be updated
    mutable bool      m_invTransformUpdated{}; //!< Internal state telling if the inverse transform needs to be updated
};

}



namespace sf
{
class Drawable;
class VertexBuffer;
class Transform;

////////////////////////////////////////////////////////////
/// \brief Base class for all render targets (window, texture, ...)
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API RenderTarget
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~RenderTarget();

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy constructor
    ///
    ////////////////////////////////////////////////////////////
    RenderTarget(const RenderTarget&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Deleted copy assignment
    ///
    ////////////////////////////////////////////////////////////
    RenderTarget& operator=(const RenderTarget&) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Clear the entire target with a single color
    ///
    /// This function is usually called once every frame,
    /// to clear the previous contents of the target.
    ///
    /// \param color Fill color to use to clear the render target
    ///
    ////////////////////////////////////////////////////////////
    void clear(const Color& color = Color::Black);

    ////////////////////////////////////////////////////////////
    /// \brief Change the current active view
    ///
    /// The view is like a 2D camera, it controls which part of
    /// the 2D scene is visible, and how it is viewed in the
    /// render target.
    /// The new view will affect everything that is drawn, until
    /// another view is set.
    /// The render target keeps its own copy of the view object,
    /// so it is not necessary to keep the original one alive
    /// after calling this function.
    /// To restore the original view of the target, you can pass
    /// the result of getDefaultView() to this function.
    ///
    /// \param view New view to use
    ///
    /// \see getView, getDefaultView
    ///
    ////////////////////////////////////////////////////////////
    void setView(const View& view);

    ////////////////////////////////////////////////////////////
    /// \brief Get the view currently in use in the render target
    ///
    /// \return The view object that is currently used
    ///
    /// \see setView, getDefaultView
    ///
    ////////////////////////////////////////////////////////////
    const View& getView() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the default view of the render target
    ///
    /// The default view has the initial size of the render target,
    /// and never changes after the target has been created.
    ///
    /// \return The default view of the render target
    ///
    /// \see setView, getView
    ///
    ////////////////////////////////////////////////////////////
    const View& getDefaultView() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the viewport of a view, applied to this render target
    ///
    /// The viewport is defined in the view as a ratio, this function
    /// simply applies this ratio to the current dimensions of the
    /// render target to calculate the pixels rectangle that the viewport
    /// actually covers in the target.
    ///
    /// \param view The view for which we want to compute the viewport
    ///
    /// \return Viewport rectangle, expressed in pixels
    ///
    ////////////////////////////////////////////////////////////
    IntRect getViewport(const View& view) const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert a point from target coordinates to world
    ///        coordinates, using the current view
    ///
    /// This function is an overload of the mapPixelToCoords
    /// function that implicitly uses the current view.
    /// It is equivalent to:
    /// \code
    /// target.mapPixelToCoords(point, target.getView());
    /// \endcode
    ///
    /// \param point Pixel to convert
    ///
    /// \return The converted point, in "world" coordinates
    ///
    /// \see mapCoordsToPixel
    ///
    ////////////////////////////////////////////////////////////
    Vector2f mapPixelToCoords(const Vector2i& point) const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert a point from target coordinates to world coordinates
    ///
    /// This function finds the 2D position that matches the
    /// given pixel of the render target. In other words, it does
    /// the inverse of what the graphics card does, to find the
    /// initial position of a rendered pixel.
    ///
    /// Initially, both coordinate systems (world units and target pixels)
    /// match perfectly. But if you define a custom view or resize your
    /// render target, this assertion is not true anymore, i.e. a point
    /// located at (10, 50) in your render target may map to the point
    /// (150, 75) in your 2D world -- if the view is translated by (140, 25).
    ///
    /// For render-windows, this function is typically used to find
    /// which point (or object) is located below the mouse cursor.
    ///
    /// This version uses a custom view for calculations, see the other
    /// overload of the function if you want to use the current view of the
    /// render target.
    ///
    /// \param point Pixel to convert
    /// \param view The view to use for converting the point
    ///
    /// \return The converted point, in "world" units
    ///
    /// \see mapCoordsToPixel
    ///
    ////////////////////////////////////////////////////////////
    Vector2f mapPixelToCoords(const Vector2i& point, const View& view) const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert a point from world coordinates to target
    ///        coordinates, using the current view
    ///
    /// This function is an overload of the mapCoordsToPixel
    /// function that implicitly uses the current view.
    /// It is equivalent to:
    /// \code
    /// target.mapCoordsToPixel(point, target.getView());
    /// \endcode
    ///
    /// \param point Point to convert
    ///
    /// \return The converted point, in target coordinates (pixels)
    ///
    /// \see mapPixelToCoords
    ///
    ////////////////////////////////////////////////////////////
    Vector2i mapCoordsToPixel(const Vector2f& point) const;

    ////////////////////////////////////////////////////////////
    /// \brief Convert a point from world coordinates to target coordinates
    ///
    /// This function finds the pixel of the render target that matches
    /// the given 2D point. In other words, it goes through the same process
    /// as the graphics card, to compute the final position of a rendered point.
    ///
    /// Initially, both coordinate systems (world units and target pixels)
    /// match perfectly. But if you define a custom view or resize your
    /// render target, this assertion is not true anymore, i.e. a point
    /// located at (150, 75) in your 2D world may map to the pixel
    /// (10, 50) of your render target -- if the view is translated by (140, 25).
    ///
    /// This version uses a custom view for calculations, see the other
    /// overload of the function if you want to use the current view of the
    /// render target.
    ///
    /// \param point Point to convert
    /// \param view The view to use for converting the point
    ///
    /// \return The converted point, in target coordinates (pixels)
    ///
    /// \see mapPixelToCoords
    ///
    ////////////////////////////////////////////////////////////
    Vector2i mapCoordsToPixel(const Vector2f& point, const View& view) const;

    ////////////////////////////////////////////////////////////
    /// \brief Draw a drawable object to the render target
    ///
    /// \param drawable Object to draw
    /// \param states   Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(const Drawable& drawable, const RenderStates& states = RenderStates::Default);

    ////////////////////////////////////////////////////////////
    /// \brief Draw primitives defined by an array of vertices
    ///
    /// \param vertices    Pointer to the vertices
    /// \param vertexCount Number of vertices in the array
    /// \param type        Type of primitives to draw
    /// \param states      Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(const Vertex*       vertices,
              std::size_t         vertexCount,
              PrimitiveType       type,
              const RenderStates& states = RenderStates::Default);

    ////////////////////////////////////////////////////////////
    /// \brief Draw primitives defined by a vertex buffer
    ///
    /// \param vertexBuffer Vertex buffer
    /// \param states       Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(const VertexBuffer& vertexBuffer, const RenderStates& states = RenderStates::Default);

    ////////////////////////////////////////////////////////////
    /// \brief Draw primitives defined by a vertex buffer
    ///
    /// \param vertexBuffer Vertex buffer
    /// \param firstVertex  Index of the first vertex to render
    /// \param vertexCount  Number of vertices to render
    /// \param states       Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void draw(const VertexBuffer& vertexBuffer,
              std::size_t         firstVertex,
              std::size_t         vertexCount,
              const RenderStates& states = RenderStates::Default);

    ////////////////////////////////////////////////////////////
    /// \brief Return the size of the rendering region of the target
    ///
    /// \return Size in pixels
    ///
    ////////////////////////////////////////////////////////////
    virtual Vector2u getSize() const = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Tell if the render target will use sRGB encoding when drawing on it
    ///
    /// \return True if the render target use sRGB encoding, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    virtual bool isSrgb() const;

    ////////////////////////////////////////////////////////////
    /// \brief Activate or deactivate the render target for rendering
    ///
    /// This function makes the render target's context current for
    /// future OpenGL rendering operations (so you shouldn't care
    /// about it if you're not doing direct OpenGL stuff).
    /// A render target's context is active only on the current thread,
    /// if you want to make it active on another thread you have
    /// to deactivate it on the previous thread first if it was active.
    /// Only one context can be current in a thread, so if you
    /// want to draw OpenGL geometry to another render target
    /// don't forget to activate it again. Activating a render
    /// target will automatically deactivate the previously active
    /// context (if any).
    ///
    /// \param active True to activate, false to deactivate
    ///
    /// \return True if operation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] virtual bool setActive(bool active = true);

    ////////////////////////////////////////////////////////////
    /// \brief Save the current OpenGL render states and matrices
    ///
    /// This function can be used when you mix SFML drawing
    /// and direct OpenGL rendering. Combined with popGLStates,
    /// it ensures that:
    /// \li SFML's internal states are not messed up by your OpenGL code
    /// \li your OpenGL states are not modified by a call to a SFML function
    ///
    /// More specifically, it must be used around code that
    /// calls Draw functions. Example:
    /// \code
    /// // OpenGL code here...
    /// window.pushGLStates();
    /// window.draw(...);
    /// window.draw(...);
    /// window.popGLStates();
    /// // OpenGL code here...
    /// \endcode
    ///
    /// Note that this function is quite expensive: it saves all the
    /// possible OpenGL states and matrices, even the ones you
    /// don't care about. Therefore it should be used wisely.
    /// It is provided for convenience, but the best results will
    /// be achieved if you handle OpenGL states yourself (because
    /// you know which states have really changed, and need to be
    /// saved and restored). Take a look at the resetGLStates
    /// function if you do so.
    ///
    /// \see popGLStates
    ///
    ////////////////////////////////////////////////////////////
    void pushGLStates();

    ////////////////////////////////////////////////////////////
    /// \brief Restore the previously saved OpenGL render states and matrices
    ///
    /// See the description of pushGLStates to get a detailed
    /// description of these functions.
    ///
    /// \see pushGLStates
    ///
    ////////////////////////////////////////////////////////////
    void popGLStates();

    ////////////////////////////////////////////////////////////
    /// \brief Reset the internal OpenGL states so that the target is ready for drawing
    ///
    /// This function can be used when you mix SFML drawing
    /// and direct OpenGL rendering, if you choose not to use
    /// pushGLStates/popGLStates. It makes sure that all OpenGL
    /// states needed by SFML are set, so that subsequent draw()
    /// calls will work as expected.
    ///
    /// Example:
    /// \code
    /// // OpenGL code here...
    /// glPushAttrib(...);
    /// window.resetGLStates();
    /// window.draw(...);
    /// window.draw(...);
    /// glPopAttrib(...);
    /// // OpenGL code here...
    /// \endcode
    ///
    ////////////////////////////////////////////////////////////
    void resetGLStates();

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    RenderTarget();

    ////////////////////////////////////////////////////////////
    /// \brief Performs the common initialization step after creation
    ///
    /// The derived classes must call this function after the
    /// target is created and ready for drawing.
    ///
    ////////////////////////////////////////////////////////////
    void initialize();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Apply the current view
    ///
    ////////////////////////////////////////////////////////////
    void applyCurrentView();

    ////////////////////////////////////////////////////////////
    /// \brief Apply a new blending mode
    ///
    /// \param mode Blending mode to apply
    ///
    ////////////////////////////////////////////////////////////
    void applyBlendMode(const BlendMode& mode);

    ////////////////////////////////////////////////////////////
    /// \brief Apply a new transform
    ///
    /// \param transform Transform to apply
    ///
    ////////////////////////////////////////////////////////////
    void applyTransform(const Transform& transform);

    ////////////////////////////////////////////////////////////
    /// \brief Apply a new texture
    ///
    /// \param texture Texture to apply
    ///
    ////////////////////////////////////////////////////////////
    void applyTexture(const Texture* texture);

    ////////////////////////////////////////////////////////////
    /// \brief Apply a new shader
    ///
    /// \param shader Shader to apply
    ///
    ////////////////////////////////////////////////////////////
    void applyShader(const Shader* shader);

    ////////////////////////////////////////////////////////////
    /// \brief Setup environment for drawing
    ///
    /// \param useVertexCache Are we going to use the vertex cache?
    /// \param states         Render states to use for drawing
    ///
    ////////////////////////////////////////////////////////////
    void setupDraw(bool useVertexCache, const RenderStates& states);

    ////////////////////////////////////////////////////////////
    /// \brief Draw the primitives
    ///
    /// \param type        Type of primitives to draw
    /// \param firstVertex Index of the first vertex to use when drawing
    /// \param vertexCount Number of vertices to use when drawing
    ///
    ////////////////////////////////////////////////////////////
    void drawPrimitives(PrimitiveType type, std::size_t firstVertex, std::size_t vertexCount);

    ////////////////////////////////////////////////////////////
    /// \brief Clean up environment after drawing
    ///
    /// \param states Render states used for drawing
    ///
    ////////////////////////////////////////////////////////////
    void cleanupDraw(const RenderStates& states);

    ////////////////////////////////////////////////////////////
    /// \brief Render states cache
    ///
    ////////////////////////////////////////////////////////////
    struct StatesCache
    {
        static constexpr std::size_t VertexCacheSize{4}; // NOLINT(readability-identifier-naming)

        bool          enable;                       //!< Is the cache enabled?
        bool          glStatesSet{};                //!< Are our internal GL states set yet?
        bool          viewChanged;                  //!< Has the current view changed since last draw?
        BlendMode     lastBlendMode;                //!< Cached blending mode
        std::uint64_t lastTextureId;                //!< Cached texture
        bool          texCoordsArrayEnabled;        //!< Is GL_TEXTURE_COORD_ARRAY client state enabled?
        bool          useVertexCache;               //!< Did we previously use the vertex cache?
        Vertex        vertexCache[VertexCacheSize]; //!< Pre-transformed vertices cache
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    View          m_defaultView; //!< Default view
    View          m_view;        //!< Current view
    StatesCache   m_cache;       //!< Render states cache
    std::uint64_t m_id{};        //!< Unique number that identifies the RenderTarget
};

}


namespace sf
{
class Image;

////////////////////////////////////////////////////////////
/// \brief Window that can serve as a target for 2D drawing
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API RenderWindow : public Window, public RenderTarget
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor doesn't actually create the window,
    /// use the other constructors or call create() to do so.
    ///
    ////////////////////////////////////////////////////////////
    RenderWindow();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a new window
    ///
    /// This constructor creates the window with the size and pixel
    /// depth defined in \a mode. An optional style can be passed to
    /// customize the look and behavior of the window (borders,
    /// title bar, resizable, closable, ...).
    ///
    /// The fourth parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc. You shouldn't care about these
    /// parameters for a regular usage of the graphics module.
    ///
    /// \param mode     Video mode to use (defines the width, height and depth of the rendering area of the window)
    /// \param title    Title of the window
    /// \param style    %Window style, a bitwise OR combination of sf::Style enumerators
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    RenderWindow(VideoMode              mode,
                 const String&          title,
                 std::uint32_t          style    = Style::Default,
                 const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Construct the window from an existing control
    ///
    /// Use this constructor if you want to create an SFML
    /// rendering area into an already existing control.
    ///
    /// The second parameter is an optional structure specifying
    /// advanced OpenGL context settings such as antialiasing,
    /// depth-buffer bits, etc. You shouldn't care about these
    /// parameters for a regular usage of the graphics module.
    ///
    /// \param handle   Platform-specific handle of the control (\a HWND on
    ///                 Windows, \a %Window on Linux/FreeBSD, \a NSWindow on OS X)
    /// \param settings Additional settings for the underlying OpenGL context
    ///
    ////////////////////////////////////////////////////////////
    explicit RenderWindow(WindowHandle handle, const ContextSettings& settings = ContextSettings());

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Closes the window and frees all the resources attached to it.
    ///
    ////////////////////////////////////////////////////////////
    ~RenderWindow() override;

    ////////////////////////////////////////////////////////////
    /// \brief Get the size of the rendering region of the window
    ///
    /// The size doesn't include the titlebar and borders
    /// of the window.
    ///
    /// \return Size in pixels
    ///
    ////////////////////////////////////////////////////////////
    Vector2u getSize() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Change the window's icon
    ///
    /// The OS default icon is used by default.
    ///
    /// \param icon Image to use as the icon. The image is copied,
    ///             so you need not keep the source alive after
    ///             calling this function.
    ///
    ////////////////////////////////////////////////////////////
    void setIcon(const Image& icon);
    using Window::setIcon;

    ////////////////////////////////////////////////////////////
    /// \brief Tell if the window will use sRGB encoding when drawing on it
    ///
    /// You can request sRGB encoding for a window by having the sRgbCapable flag set in the ContextSettings
    ///
    /// \return True if the window use sRGB encoding, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool isSrgb() const override;

    ////////////////////////////////////////////////////////////
    /// \brief Activate or deactivate the window as the current target
    ///        for OpenGL rendering
    ///
    /// A window is active only on the current thread, if you want to
    /// make it active on another thread you have to deactivate it
    /// on the previous thread first if it was active.
    /// Only one window can be active on a thread at a time, thus
    /// the window previously active (if any) automatically gets deactivated.
    /// This is not to be confused with requestFocus().
    ///
    /// \param active True to activate, false to deactivate
    ///
    /// \return True if operation was successful, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool setActive(bool active = true) override;

protected:
    ////////////////////////////////////////////////////////////
    /// \brief Function called after the window has been created
    ///
    /// This function is called so that derived classes can
    /// perform their own specific initialization as soon as
    /// the window is created.
    ///
    ////////////////////////////////////////////////////////////
    void onCreate() override;

    ////////////////////////////////////////////////////////////
    /// \brief Function called after the window has been resized
    ///
    /// This function is called so that derived classes can
    /// perform custom actions when the size of the window changes.
    ///
    ////////////////////////////////////////////////////////////
    void onResize() override;

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int m_defaultFrameBuffer{}; //!< Framebuffer to bind when targeting this window
};

}

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Decomposed transform defined by a position, a rotation and a scale
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API Transformable
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Transformable();

    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Transformable();

    ////////////////////////////////////////////////////////////
    /// \brief set the position of the object
    ///
    /// This function completely overwrites the previous position.
    /// See the move function to apply an offset based on the previous position instead.
    /// The default position of a transformable object is (0, 0).
    ///
    /// \param position New position
    ///
    /// \see move, getPosition
    ///
    ////////////////////////////////////////////////////////////
    void setPosition(const Vector2f& position);

    ////////////////////////////////////////////////////////////
    /// \brief set the orientation of the object
    ///
    /// This function completely overwrites the previous rotation.
    /// See the rotate function to add an angle based on the previous rotation instead.
    /// The default rotation of a transformable object is 0.
    ///
    /// \param angle New rotation
    ///
    /// \see rotate, getRotation
    ///
    ////////////////////////////////////////////////////////////
    void setRotation(Angle angle);

    ////////////////////////////////////////////////////////////
    /// \brief set the scale factors of the object
    ///
    /// This function completely overwrites the previous scale.
    /// See the scale function to add a factor based on the previous scale instead.
    /// The default scale of a transformable object is (1, 1).
    ///
    /// \param factors New scale factors
    ///
    /// \see scale, getScale
    ///
    ////////////////////////////////////////////////////////////
    void setScale(const Vector2f& factors);

    ////////////////////////////////////////////////////////////
    /// \brief set the local origin of the object
    ///
    /// The origin of an object defines the center point for
    /// all transformations (position, scale, rotation).
    /// The coordinates of this point must be relative to the
    /// top-left corner of the object, and ignore all
    /// transformations (position, scale, rotation).
    /// The default origin of a transformable object is (0, 0).
    ///
    /// \param origin New origin
    ///
    /// \see getOrigin
    ///
    ////////////////////////////////////////////////////////////
    void setOrigin(const Vector2f& origin);

    ////////////////////////////////////////////////////////////
    /// \brief get the position of the object
    ///
    /// \return Current position
    ///
    /// \see setPosition
    ///
    ////////////////////////////////////////////////////////////
    const Vector2f& getPosition() const;

    ////////////////////////////////////////////////////////////
    /// \brief get the orientation of the object
    ///
    /// The rotation is always in the range [0, 360].
    ///
    /// \return Current rotation
    ///
    /// \see setRotation
    ///
    ////////////////////////////////////////////////////////////
    Angle getRotation() const;

    ////////////////////////////////////////////////////////////
    /// \brief get the current scale of the object
    ///
    /// \return Current scale factors
    ///
    /// \see setScale
    ///
    ////////////////////////////////////////////////////////////
    const Vector2f& getScale() const;

    ////////////////////////////////////////////////////////////
    /// \brief get the local origin of the object
    ///
    /// \return Current origin
    ///
    /// \see setOrigin
    ///
    ////////////////////////////////////////////////////////////
    const Vector2f& getOrigin() const;

    ////////////////////////////////////////////////////////////
    /// \brief Move the object by a given offset
    ///
    /// This function adds to the current position of the object,
    /// unlike setPosition which overwrites it.
    /// Thus, it is equivalent to the following code:
    /// \code
    /// object.setPosition(object.getPosition() + offset);
    /// \endcode
    ///
    /// \param offset Offset
    ///
    /// \see setPosition
    ///
    ////////////////////////////////////////////////////////////
    void move(const Vector2f& offset);

    ////////////////////////////////////////////////////////////
    /// \brief Rotate the object
    ///
    /// This function adds to the current rotation of the object,
    /// unlike setRotation which overwrites it.
    /// Thus, it is equivalent to the following code:
    /// \code
    /// object.setRotation(object.getRotation() + angle);
    /// \endcode
    ///
    /// \param angle Angle of rotation
    ///
    ////////////////////////////////////////////////////////////
    void rotate(Angle angle);

    ////////////////////////////////////////////////////////////
    /// \brief Scale the object
    ///
    /// This function multiplies the current scale of the object,
    /// unlike setScale which overwrites it.
    /// Thus, it is equivalent to the following code:
    /// \code
    /// sf::Vector2f scale = object.getScale();
    /// object.setScale(scale.x * factor.x, scale.y * factor.y);
    /// \endcode
    ///
    /// \param factor Scale factors
    ///
    /// \see setScale
    ///
    ////////////////////////////////////////////////////////////
    void scale(const Vector2f& factor);

    ////////////////////////////////////////////////////////////
    /// \brief get the combined transform of the object
    ///
    /// \return Transform combining the position/rotation/scale/origin of the object
    ///
    /// \see getInverseTransform
    ///
    ////////////////////////////////////////////////////////////
    const Transform& getTransform() const;

    ////////////////////////////////////////////////////////////
    /// \brief get the inverse of the combined transform of the object
    ///
    /// \return Inverse of the combined transformations applied to the object
    ///
    /// \see getTransform
    ///
    ////////////////////////////////////////////////////////////
    const Transform& getInverseTransform() const;

private:
    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Vector2f          m_origin;                           //!< Origin of translation/rotation/scaling of the object
    Vector2f          m_position;                         //!< Position of the object in the 2D world
    Angle             m_rotation;                         //!< Orientation of the object
    Vector2f          m_scale{1, 1};                      //!< Scale of the object
    mutable Transform m_transform;                        //!< Combined transformation of the object
    mutable Transform m_inverseTransform;                 //!< Combined transformation of the object
    mutable bool      m_transformNeedUpdate{true};        //!< Does the transform need to be recomputed?
    mutable bool      m_inverseTransformNeedUpdate{true}; //!< Does the transform need to be recomputed?
};

}

#ifndef SFML_SPRITE_HPP
#define SFML_SPRITE_HPP
namespace sf
{
class Texture;

////////////////////////////////////////////////////////////
/// \brief Drawable representation of a texture, with its
///        own transformations, color, etc.
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API Sprite : public Drawable, public Transformable
{
public:

Sprite();
    ////////////////////////////////////////////////////////////
    /// \brief Construct the sprite from a source texture
    ///
    /// \param texture Source texture
    ///
    /// \see setTexture
    ///
    ////////////////////////////////////////////////////////////
    explicit Sprite(const Texture& texture);

    ////////////////////////////////////////////////////////////
    /// \brief Disallow construction from a temporary texture
    ///
    ////////////////////////////////////////////////////////////
    explicit Sprite(Texture&& texture) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Construct the sprite from a sub-rectangle of a source texture
    ///
    /// \param texture   Source texture
    /// \param rectangle Sub-rectangle of the texture to assign to the sprite
    ///
    /// \see setTexture, setTextureRect
    ///
    ////////////////////////////////////////////////////////////
    Sprite(const Texture& texture, const IntRect& rectangle);

    ////////////////////////////////////////////////////////////
    /// \brief Disallow construction from a temporary texture
    ///
    ////////////////////////////////////////////////////////////
    Sprite(Texture&& texture, const IntRect& rectangle) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Change the source texture of the sprite
    ///
    /// The \a texture argument refers to a texture that must
    /// exist as long as the sprite uses it. Indeed, the sprite
    /// doesn't store its own copy of the texture, but rather keeps
    /// a pointer to the one that you passed to this function.
    /// If the source texture is destroyed and the sprite tries to
    /// use it, the behavior is undefined.
    /// If \a resetRect is true, the TextureRect property of
    /// the sprite is automatically adjusted to the size of the new
    /// texture. If it is false, the texture rect is left unchanged.
    ///
    /// \param texture   New texture
    /// \param resetRect Should the texture rect be reset to the size of the new texture?
    ///
    /// \see getTexture, setTextureRect
    ///
    ////////////////////////////////////////////////////////////
    void setTexture(const Texture& texture, bool resetRect = false);

    ////////////////////////////////////////////////////////////
    /// \brief Disallow setting from a temporary texture
    ///
    ////////////////////////////////////////////////////////////
    void setTexture(Texture&& texture, bool resetRect = false) = delete;

    ////////////////////////////////////////////////////////////
    /// \brief Set the sub-rectangle of the texture that the sprite will display
    ///
    /// The texture rect is useful when you don't want to display
    /// the whole texture, but rather a part of it.
    /// By default, the texture rect covers the entire texture.
    ///
    /// \param rectangle Rectangle defining the region of the texture to display
    ///
    /// \see getTextureRect, setTexture
    ///
    ////////////////////////////////////////////////////////////
    void setTextureRect(const IntRect& rectangle);

    ////////////////////////////////////////////////////////////
    /// \brief Set the global color of the sprite
    ///
    /// This color is modulated (multiplied) with the sprite's
    /// texture. It can be used to colorize the sprite, or change
    /// its global opacity.
    /// By default, the sprite's color is opaque white.
    ///
    /// \param color New color of the sprite
    ///
    /// \see getColor
    ///
    ////////////////////////////////////////////////////////////
    void setColor(const Color& color);

    ////////////////////////////////////////////////////////////
    /// \brief Get the source texture of the sprite
    ///
    /// The returned reference is const, which means that you can't
    /// modify the texture when you retrieve it with this function.
    ///
    /// \return Reference to the sprite's texture
    ///
    /// \see setTexture
    ///
    ////////////////////////////////////////////////////////////
    const Texture& getTexture() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the sub-rectangle of the texture displayed by the sprite
    ///
    /// \return Texture rectangle of the sprite
    ///
    /// \see setTextureRect
    ///
    ////////////////////////////////////////////////////////////
    const IntRect& getTextureRect() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global color of the sprite
    ///
    /// \return Global color of the sprite
    ///
    /// \see setColor
    ///
    ////////////////////////////////////////////////////////////
    const Color& getColor() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the local bounding rectangle of the entity
    ///
    /// The returned rectangle is in local coordinates, which means
    /// that it ignores the transformations (translation, rotation,
    /// scale, ...) that are applied to the entity.
    /// In other words, this function returns the bounds of the
    /// entity in the entity's coordinate system.
    ///
    /// \return Local bounding rectangle of the entity
    ///
    ////////////////////////////////////////////////////////////
    FloatRect getLocalBounds() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the global bounding rectangle of the entity
    ///
    /// The returned rectangle is in global coordinates, which means
    /// that it takes into account the transformations (translation,
    /// rotation, scale, ...) that are applied to the entity.
    /// In other words, this function returns the bounds of the
    /// sprite in the global 2D world's coordinate system.
    ///
    /// \return Global bounding rectangle of the entity
    ///
    ////////////////////////////////////////////////////////////
    FloatRect getGlobalBounds() const;

private:
    ////////////////////////////////////////////////////////////
    /// \brief Draw the sprite to a render target
    ///
    /// \param target Render target to draw to
    /// \param states Current render states
    ///
    ////////////////////////////////////////////////////////////
    void draw(RenderTarget& target, const RenderStates& states) const override;

    ////////////////////////////////////////////////////////////
    /// \brief Update the vertices' positions
    ///
    ////////////////////////////////////////////////////////////
    void updatePositions();

    ////////////////////////////////////////////////////////////
    /// \brief Update the vertices' texture coordinates
    ///
    ////////////////////////////////////////////////////////////
    void updateTexCoords();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Vertex         m_vertices[4]; //!< Vertices defining the sprite's geometry
    const Texture* m_texture{};   //!< Texture of the sprite
    IntRect        m_textureRect; //!< Rectangle defining the area of the source texture to display
};

}

#endif


namespace sf
{
class InputStream;
class RenderTarget;
class RenderTexture;
class Text;
class Window;
class Image;

////////////////////////////////////////////////////////////
/// \brief Image living on the graphics card that can be used for drawing
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API Texture : GlResource
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Types of texture coordinates that can be used for rendering
    ///
    ////////////////////////////////////////////////////////////
    enum CoordinateType
    {
        Normalized, //!< Texture coordinates in range [0 .. 1]
        Pixels      //!< Texture coordinates in range [0 .. size]
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty texture.
    ///
    ////////////////////////////////////////////////////////////
    Texture();

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Texture();

    ////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    /// \param copy instance to copy
    ///
    ////////////////////////////////////////////////////////////
    Texture(const Texture& copy);

    ////////////////////////////////////////////////////////////
    /// \brief Copy assignment operator
    ///
    ////////////////////////////////////////////////////////////
    Texture& operator=(const Texture&);

    ////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ////////////////////////////////////////////////////////////
    Texture(Texture&&) noexcept;

    ////////////////////////////////////////////////////////////
    /// \brief Move assignment operator
    ///
    ////////////////////////////////////////////////////////////
    Texture& operator=(Texture&&) noexcept;

    ////////////////////////////////////////////////////////////
    /// \brief Create the texture
    ///
    /// If this function fails, the texture is left unchanged.
    ///
    /// \param size Width and height of the texture
    ///
    /// \return True if creation was successful
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool create(const Vector2u& size);

    ////////////////////////////////////////////////////////////
    /// \brief Load the texture from a file on disk
    ///
    /// This function is a shortcut for the following code:
    /// \code
    /// sf::Image image;
    /// image.loadFromFile(filename);
    /// texture.loadFromImage(image, area);
    /// \endcode
    ///
    /// The \a area argument can be used to load only a sub-rectangle
    /// of the whole image. If you want the entire image then leave
    /// the default value (which is an empty IntRect).
    /// If the \a area rectangle crosses the bounds of the image, it
    /// is adjusted to fit the image size.
    ///
    /// The maximum size for a texture depends on the graphics
    /// driver and can be retrieved with the getMaximumSize function.
    ///
    /// If this function fails, the texture is left unchanged.
    ///
    /// \param filename Path of the image file to load
    /// \param area     Area of the image to load
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromMemory, loadFromStream, loadFromImage
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool loadFromFile(const std::filesystem::path& filename, const IntRect& area = IntRect());

    ////////////////////////////////////////////////////////////
    /// \brief Load the texture from a file in memory
    ///
    /// This function is a shortcut for the following code:
    /// \code
    /// sf::Image image;
    /// image.loadFromMemory(data, size);
    /// texture.loadFromImage(image, area);
    /// \endcode
    ///
    /// The \a area argument can be used to load only a sub-rectangle
    /// of the whole image. If you want the entire image then leave
    /// the default value (which is an empty IntRect).
    /// If the \a area rectangle crosses the bounds of the image, it
    /// is adjusted to fit the image size.
    ///
    /// The maximum size for a texture depends on the graphics
    /// driver and can be retrieved with the getMaximumSize function.
    ///
    /// If this function fails, the texture is left unchanged.
    ///
    /// \param data Pointer to the file data in memory
    /// \param size Size of the data to load, in bytes
    /// \param area Area of the image to load
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromFile, loadFromStream, loadFromImage
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool loadFromMemory(const void* data, std::size_t size, const IntRect& area = IntRect());

    ////////////////////////////////////////////////////////////
    /// \brief Load the texture from a custom stream
    ///
    /// This function is a shortcut for the following code:
    /// \code
    /// sf::Image image;
    /// image.loadFromStream(stream);
    /// texture.loadFromImage(image, area);
    /// \endcode
    ///
    /// The \a area argument can be used to load only a sub-rectangle
    /// of the whole image. If you want the entire image then leave
    /// the default value (which is an empty IntRect).
    /// If the \a area rectangle crosses the bounds of the image, it
    /// is adjusted to fit the image size.
    ///
    /// The maximum size for a texture depends on the graphics
    /// driver and can be retrieved with the getMaximumSize function.
    ///
    /// If this function fails, the texture is left unchanged.
    ///
    /// \param stream Source stream to read from
    /// \param area   Area of the image to load
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromFile, loadFromMemory, loadFromImage
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool loadFromStream(InputStream& stream, const IntRect& area = IntRect());

    ////////////////////////////////////////////////////////////
    /// \brief Load the texture from an image
    ///
    /// The \a area argument can be used to load only a sub-rectangle
    /// of the whole image. If you want the entire image then leave
    /// the default value (which is an empty IntRect).
    /// If the \a area rectangle crosses the bounds of the image, it
    /// is adjusted to fit the image size.
    ///
    /// The maximum size for a texture depends on the graphics
    /// driver and can be retrieved with the getMaximumSize function.
    ///
    /// If this function fails, the texture is left unchanged.
    ///
    /// \param image Image to load into the texture
    /// \param area  Area of the image to load
    ///
    /// \return True if loading was successful
    ///
    /// \see loadFromFile, loadFromMemory
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool loadFromImage(const Image& image, const IntRect& area = IntRect());

    ////////////////////////////////////////////////////////////
    /// \brief Return the size of the texture
    ///
    /// \return Size in pixels
    ///
    ////////////////////////////////////////////////////////////
    Vector2u getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Copy the texture pixels to an image
    ///
    /// This function performs a slow operation that downloads
    /// the texture's pixels from the graphics card and copies
    /// them to a new image, potentially applying transformations
    /// to pixels if necessary (texture may be padded or flipped).
    ///
    /// \return Image containing the texture's pixels
    ///
    /// \see loadFromImage
    ///
    ////////////////////////////////////////////////////////////
    Image copyToImage() const;

    ////////////////////////////////////////////////////////////
    /// \brief Update the whole texture from an array of pixels
    ///
    /// The \a pixel array is assumed to have the same size as
    /// the \a area rectangle, and to contain 32-bits RGBA pixels.
    ///
    /// No additional check is performed on the size of the pixel
    /// array, passing invalid arguments will lead to an undefined
    /// behavior.
    ///
    /// This function does nothing if \a pixels is null or if the
    /// texture was not previously created.
    ///
    /// \param pixels Array of pixels to copy to the texture
    ///
    ////////////////////////////////////////////////////////////
    void update(const std::uint8_t* pixels);

    ////////////////////////////////////////////////////////////
    /// \brief Update a part of the texture from an array of pixels
    ///
    /// The size of the \a pixel array must match the \a width and
    /// \a height arguments, and it must contain 32-bits RGBA pixels.
    ///
    /// No additional check is performed on the size of the pixel
    /// array or the bounds of the area to update, passing invalid
    /// arguments will lead to an undefined behavior.
    ///
    /// This function does nothing if \a pixels is null or if the
    /// texture was not previously created.
    ///
    /// \param pixels Array of pixels to copy to the texture
    /// \param size   Width and height of the pixel region contained in \a pixels
    /// \param dest   Coordinates of the destination position
    ///
    ////////////////////////////////////////////////////////////
    void update(const std::uint8_t* pixels, const Vector2u& size, const Vector2u& dest);

    ////////////////////////////////////////////////////////////
    /// \brief Update a part of this texture from another texture
    ///
    /// Although the source texture can be smaller than this texture,
    /// this function is usually used for updating the whole texture.
    /// The other overload, which has (x, y) additional arguments,
    /// is more convenient for updating a sub-area of this texture.
    ///
    /// No additional check is performed on the size of the passed
    /// texture, passing a texture bigger than this texture
    /// will lead to an undefined behavior.
    ///
    /// This function does nothing if either texture was not
    /// previously created.
    ///
    /// \param texture Source texture to copy to this texture
    ///
    ////////////////////////////////////////////////////////////
    void update(const Texture& texture);

    ////////////////////////////////////////////////////////////
    /// \brief Update a part of this texture from another texture
    ///
    /// No additional check is performed on the size of the texture,
    /// passing an invalid combination of texture size and destination
    /// will lead to an undefined behavior.
    ///
    /// This function does nothing if either texture was not
    /// previously created.
    ///
    /// \param texture Source texture to copy to this texture
    /// \param dest    Coordinates of the destination position
    ///
    ////////////////////////////////////////////////////////////
    void update(const Texture& texture, const Vector2u& dest);

    ////////////////////////////////////////////////////////////
    /// \brief Update the texture from an image
    ///
    /// Although the source image can be smaller than the texture,
    /// this function is usually used for updating the whole texture.
    /// The other overload, which has (x, y) additional arguments,
    /// is more convenient for updating a sub-area of the texture.
    ///
    /// No additional check is performed on the size of the image,
    /// passing an image bigger than the texture will lead to an
    /// undefined behavior.
    ///
    /// This function does nothing if the texture was not
    /// previously created.
    ///
    /// \param image Image to copy to the texture
    ///
    ////////////////////////////////////////////////////////////
    void update(const Image& image);

    ////////////////////////////////////////////////////////////
    /// \brief Update a part of the texture from an image
    ///
    /// No additional check is performed on the size of the image,
    /// passing an invalid combination of image size and destination
    /// will lead to an undefined behavior.
    ///
    /// This function does nothing if the texture was not
    /// previously created.
    ///
    /// \param image Image to copy to the texture
    /// \param dest  Coordinates of the destination position
    ///
    ////////////////////////////////////////////////////////////
    void update(const Image& image, const Vector2u& dest);

    ////////////////////////////////////////////////////////////
    /// \brief Update the texture from the contents of a window
    ///
    /// Although the source window can be smaller than the texture,
    /// this function is usually used for updating the whole texture.
    /// The other overload, which has (x, y) additional arguments,
    /// is more convenient for updating a sub-area of the texture.
    ///
    /// No additional check is performed on the size of the window,
    /// passing a window bigger than the texture will lead to an
    /// undefined behavior.
    ///
    /// This function does nothing if either the texture or the window
    /// was not previously created.
    ///
    /// \param window Window to copy to the texture
    ///
    ////////////////////////////////////////////////////////////
    void update(const Window& window);

    ////////////////////////////////////////////////////////////
    /// \brief Update a part of the texture from the contents of a window
    ///
    /// No additional check is performed on the size of the window,
    /// passing an invalid combination of window size and destination
    /// will lead to an undefined behavior.
    ///
    /// This function does nothing if either the texture or the window
    /// was not previously created.
    ///
    /// \param window Window to copy to the texture
    /// \param dest   Coordinates of the destination position
    ///
    ////////////////////////////////////////////////////////////
    void update(const Window& window, const Vector2u& dest);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable the smooth filter
    ///
    /// When the filter is activated, the texture appears smoother
    /// so that pixels are less noticeable. However if you want
    /// the texture to look exactly the same as its source file,
    /// you should leave it disabled.
    /// The smooth filter is disabled by default.
    ///
    /// \param smooth True to enable smoothing, false to disable it
    ///
    /// \see isSmooth
    ///
    ////////////////////////////////////////////////////////////
    void setSmooth(bool smooth);

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether the smooth filter is enabled or not
    ///
    /// \return True if smoothing is enabled, false if it is disabled
    ///
    /// \see setSmooth
    ///
    ////////////////////////////////////////////////////////////
    bool isSmooth() const;

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable conversion from sRGB
    ///
    /// When providing texture data from an image file or memory, it can
    /// either be stored in a linear color space or an sRGB color space.
    /// Most digital images account for gamma correction already, so they
    /// would need to be "uncorrected" back to linear color space before
    /// being processed by the hardware. The hardware can automatically
    /// convert it from the sRGB color space to a linear color space when
    /// it gets sampled. When the rendered image gets output to the final
    /// framebuffer, it gets converted back to sRGB.
    ///
    /// After enabling or disabling sRGB conversion, make sure to reload
    /// the texture data in order for the setting to take effect.
    ///
    /// This option is only useful in conjunction with an sRGB capable
    /// framebuffer. This can be requested during window creation.
    ///
    /// \param sRgb True to enable sRGB conversion, false to disable it
    ///
    /// \see isSrgb
    ///
    ////////////////////////////////////////////////////////////
    void setSrgb(bool sRgb);

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether the texture source is converted from sRGB or not
    ///
    /// \return True if the texture source is converted from sRGB, false if not
    ///
    /// \see setSrgb
    ///
    ////////////////////////////////////////////////////////////
    bool isSrgb() const;

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable repeating
    ///
    /// Repeating is involved when using texture coordinates
    /// outside the texture rectangle [0, 0, width, height].
    /// In this case, if repeat mode is enabled, the whole texture
    /// will be repeated as many times as needed to reach the
    /// coordinate (for example, if the X texture coordinate is
    /// 3 * width, the texture will be repeated 3 times).
    /// If repeat mode is disabled, the "extra space" will instead
    /// be filled with border pixels.
    /// Warning: on very old graphics cards, white pixels may appear
    /// when the texture is repeated. With such cards, repeat mode
    /// can be used reliably only if the texture has power-of-two
    /// dimensions (such as 256x128).
    /// Repeating is disabled by default.
    ///
    /// \param repeated True to repeat the texture, false to disable repeating
    ///
    /// \see isRepeated
    ///
    ////////////////////////////////////////////////////////////
    void setRepeated(bool repeated);

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether the texture is repeated or not
    ///
    /// \return True if repeat mode is enabled, false if it is disabled
    ///
    /// \see setRepeated
    ///
    ////////////////////////////////////////////////////////////
    bool isRepeated() const;

    ////////////////////////////////////////////////////////////
    /// \brief Generate a mipmap using the current texture data
    ///
    /// Mipmaps are pre-computed chains of optimized textures. Each
    /// level of texture in a mipmap is generated by halving each of
    /// the previous level's dimensions. This is done until the final
    /// level has the size of 1x1. The textures generated in this process may
    /// make use of more advanced filters which might improve the visual quality
    /// of textures when they are applied to objects much smaller than they are.
    /// This is known as minification. Because fewer texels (texture elements)
    /// have to be sampled from when heavily minified, usage of mipmaps
    /// can also improve rendering performance in certain scenarios.
    ///
    /// Mipmap generation relies on the necessary OpenGL extension being
    /// available. If it is unavailable or generation fails due to another
    /// reason, this function will return false. Mipmap data is only valid from
    /// the time it is generated until the next time the base level image is
    /// modified, at which point this function will have to be called again to
    /// regenerate it.
    ///
    /// \return True if mipmap generation was successful, false if unsuccessful
    ///
    ////////////////////////////////////////////////////////////
    [[nodiscard]] bool generateMipmap();

    ////////////////////////////////////////////////////////////
    /// \brief Swap the contents of this texture with those of another
    ///
    /// \param right Instance to swap with
    ///
    ////////////////////////////////////////////////////////////
    void swap(Texture& right) noexcept;

    ////////////////////////////////////////////////////////////
    /// \brief Get the underlying OpenGL handle of the texture.
    ///
    /// You shouldn't need to use this function, unless you have
    /// very specific stuff to implement that SFML doesn't support,
    /// or implement a temporary workaround until a bug is fixed.
    ///
    /// \return OpenGL handle of the texture or 0 if not yet created
    ///
    ////////////////////////////////////////////////////////////
    unsigned int getNativeHandle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Bind a texture for rendering
    ///
    /// This function is not part of the graphics API, it mustn't be
    /// used when drawing SFML entities. It must be used only if you
    /// mix sf::Texture with OpenGL code.
    ///
    /// \code
    /// sf::Texture t1, t2;
    /// ...
    /// sf::Texture::bind(&t1);
    /// // draw OpenGL stuff that use t1...
    /// sf::Texture::bind(&t2);
    /// // draw OpenGL stuff that use t2...
    /// sf::Texture::bind(nullptr);
    /// // draw OpenGL stuff that use no texture...
    /// \endcode
    ///
    /// The \a coordinateType argument controls how texture
    /// coordinates will be interpreted. If Normalized (the default), they
    /// must be in range [0 .. 1], which is the default way of handling
    /// texture coordinates with OpenGL. If Pixels, they must be given
    /// in pixels (range [0 .. size]). This mode is used internally by
    /// the graphics classes of SFML, it makes the definition of texture
    /// coordinates more intuitive for the high-level API, users don't need
    /// to compute normalized values.
    ///
    /// \param texture Pointer to the texture to bind, can be null to use no texture
    /// \param coordinateType Type of texture coordinates to use
    ///
    ////////////////////////////////////////////////////////////
    static void bind(const Texture* texture, CoordinateType coordinateType = Normalized);

    ////////////////////////////////////////////////////////////
    /// \brief Get the maximum texture size allowed
    ///
    /// This maximum size is defined by the graphics driver.
    /// You can expect a value of 512 pixels for low-end graphics
    /// card, and up to 8192 pixels or more for newer hardware.
    ///
    /// \return Maximum size allowed for textures, in pixels
    ///
    ////////////////////////////////////////////////////////////
    static unsigned int getMaximumSize();

private:
    friend class Text;
    friend class RenderTexture;
    friend class RenderTarget;

    ////////////////////////////////////////////////////////////
    /// \brief Get a valid image size according to hardware support
    ///
    /// This function checks whether the graphics driver supports
    /// non power of two sizes or not, and adjusts the size
    /// accordingly.
    /// The returned size is greater than or equal to the original size.
    ///
    /// \param size size to convert
    ///
    /// \return Valid nearest size (greater than or equal to specified size)
    ///
    ////////////////////////////////////////////////////////////
    static unsigned int getValidSize(unsigned int size);

    ////////////////////////////////////////////////////////////
    /// \brief Invalidate the mipmap if one exists
    ///
    /// This also resets the texture's minifying function.
    /// This function is mainly for internal use by RenderTexture.
    ///
    ////////////////////////////////////////////////////////////
    void invalidateMipmap();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Vector2u      m_size;            //!< Public texture size
    Vector2u      m_actualSize;      //!< Actual texture size (can be greater than public size because of padding)
    unsigned int  m_texture{};       //!< Internal texture identifier
    bool          m_isSmooth{};      //!< Status of the smooth filter
    bool          m_sRgb{};          //!< Should the texture source be converted from sRGB?
    bool          m_isRepeated{};    //!< Is the texture in repeat mode?
    mutable bool  m_pixelsFlipped{}; //!< To work around the inconsistency in Y orientation
    bool          m_fboAttachment{}; //!< Is this texture owned by a framebuffer object?
    bool          m_hasMipmap{};     //!< Has the mipmap been generated?
    std::uint64_t m_cacheId;         //!< Unique number that identifies the texture to the render target's cache
};

////////////////////////////////////////////////////////////
/// \brief Swap the contents of one texture with those of another
///
/// \param left First instance to swap
/// \param right Second instance to swap
///
////////////////////////////////////////////////////////////
SFML_GRAPHICS_API void swap(Texture& left, Texture& right) noexcept;

}

