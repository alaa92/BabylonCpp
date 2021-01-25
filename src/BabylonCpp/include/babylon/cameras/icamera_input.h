#ifndef BABYLON_CAMERAS_ICAMERA_INPUT_H
#define BABYLON_CAMERAS_ICAMERA_INPUT_H

#include <string>

#include <babylon/babylon_api.h>

namespace BABYLON {

class ICanvas;

/**
 * @brief This is the contract to implement in order to create a new input class.
 * Inputs are dealing with listening to user actions and moving the camera accordingly.
 */
template <class TCamera>
struct BABYLON_SHARED_EXPORT ICameraInput {
  virtual ~ICameraInput() = default;
  /**
   * Defines the camera the input is attached to.
   */
  TCamera* camera = nullptr;

  /**
   * Hidden
   */
  bool hasCheckInputs = true;

  /**
   * @brief Gets the class name of the current input.
   * @returns the class name
   */
  [[nodiscard]] virtual std::string getClassName() const = 0;

  /**
   * @brief Get the friendly name associated with the input class.
   * @returns the input friendly name
   */
  [[nodiscard]] virtual std::string getSimpleName() const = 0;

  /**
   * @brief Attach the input controls to a specific dom element to get the input from.
   * @param noPreventDefault Defines whether event caught by the controls should call
   * preventdefault()
   * (https://developer.mozilla.org/en-US/docs/Web/API/Event/preventDefault)
   */
  virtual void attachControl(bool noPreventDefault = false) = 0;

  /**
   * @brief Detach the current controls from the specified dom element.
   * @param ignored defines an ignored parameter kept for backward compatibility. If you want to
   * define the source input element, you can set engine.inputElement before calling
   * camera.attachControl
   */
  virtual void detachControl(ICanvas* ignored = nullptr) = 0;

  /**
   * @brief Update the current camera state depending on the inputs that have
   * been used this frame. This is a dynamically created lambda to avoid the
   * performance penalty of looping for inputs in the render loop.
   */
  virtual void checkInputs() = 0;

}; // end of class ICameraInput<TCamera>

} // end of namespace BABYLON

#endif // end of BABYLON_CAMERAS_ICAMERA_INPUT_H
