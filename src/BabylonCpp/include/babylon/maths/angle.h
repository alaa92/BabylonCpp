#ifndef BABYLON_MATHS_ANGLE_H
#define BABYLON_MATHS_ANGLE_H

#include <memory>

#include <babylon/babylon_api.h>

namespace BABYLON {

class Vector2;

/**
 * @brief Defines angle representation.
 */
class BABYLON_SHARED_EXPORT Angle {

public:
  /**
   * @brief Creates an Angle object of "radians" radians (float).
   * @param radians the angle in radians
   */
  Angle();
  Angle(float radians);
  Angle(const Angle& otherAngle);
  Angle(Angle&& otherAngle);
  Angle& operator=(const Angle& otherAngle);
  Angle& operator=(Angle&& otherAngle);
  ~Angle(); // = default
  [[nodiscard]] Angle copy() const;
  [[nodiscard]] std::unique_ptr<Angle> clone() const;
  friend std::ostream& operator<<(std::ostream& os, const Angle& angle);
  friend bool operator==(const Angle& lhs, const Angle& rhs);
  friend bool operator!=(const Angle& lhs, const Angle& rhs);

  /**
   * @brief Get value in degrees.
   * @returns the Angle value in degrees (float)
   */
  [[nodiscard]] float degrees() const;

  /**
   * @brief Get value in radians.
   * @returns the Angle value in radians (float)
   */
  [[nodiscard]] float radians() const;

  /** Statics **/

  /**
   * @brief Gets a new Angle object valued with the gradient angle, in radians, of the line joining
   * two points
   * @param a defines first point as the origin
   * @param b defines point
   * @returns a new Angle
   */
  static Angle BetweenTwoPoints(const Vector2& a, const Vector2& b);

  /**
   * @brief Gets a new Angle object from the given float in radians.
   * @param radians defines the angle value in radians
   * @returns a new Angle
   */
  static Angle FromRadians(float radians);

  /**
   * @brief Gets a new Angle object from the given float in degrees.
   * @param degrees defines the angle value in degrees
   * @returns a new Angle
   */
  static Angle FromDegrees(float degrees);

private:
  float _radians;

}; // end of class Angle

std::ostream& operator<<(std::ostream& os, const Angle& angle);
bool operator==(const Angle& lhs, const Angle& rhs);
bool operator!=(const Angle& lhs, const Angle& rhs);

} // end of namespace BABYLON

#endif // end of BABYLON_MATHS_ANGLE_H
