#ifndef BABYLON_POSTPROCESSES_CHROMATIC_ABERRATION_POST_PROCESS_H
#define BABYLON_POSTPROCESSES_CHROMATIC_ABERRATION_POST_PROCESS_H

#include <babylon/babylon_api.h>
#include <babylon/babylon_fwd.h>
#include <babylon/engines/constants.h>
#include <babylon/postprocesses/post_process.h>

namespace BABYLON {

FWD_CLASS_SPTR(ChromaticAberrationPostProcess)

/**
 * @brief The ChromaticAberrationPostProcess separates the rgb channels in an image to produce
 * chromatic distortion around the edges of the screen
 */
class BABYLON_SHARED_EXPORT ChromaticAberrationPostProcess : public PostProcess {

public:
  template <typename... Ts>
  static ChromaticAberrationPostProcessPtr New(Ts&&... args)
  {
    auto postProcess = std::shared_ptr<ChromaticAberrationPostProcess>(
      new ChromaticAberrationPostProcess(std::forward<Ts>(args)...));
    postProcess->add(postProcess);

    return postProcess;
  }
  ~ChromaticAberrationPostProcess() override; // = default

  /**
   * @brief Gets a string identifying the name of the class.
   * @returns "ChromaticAberrationPostProcess" string
   */
  std::string getClassName() const override;

  /**
   * @brief Hidden
   */
  static ChromaticAberrationPostProcessPtr _Parse(const json& parsedPostProcess,
                                                  const CameraPtr& targetCamera, Scene* scene,
                                                  const std::string& rootUrl);

protected:
  /**
   * @brief Creates a new instance ChromaticAberrationPostProcess.
   * @param name The name of the effect.
   * @param screenWidth The width of the screen to apply the effect on.
   * @param screenHeight The height of the screen to apply the effect on.
   * @param options The required width/height ratio to downsize to before computing the render pass.
   * @param camera The camera to apply the render pass to.
   * @param samplingMode The sampling mode to be used when computing the pass. (default: 0)
   * @param engine The engine which the post process will be applied. (default: current engine)
   * @param reusable If the post process can be reused on the same frame. (default: false)
   * @param textureType Type of textures used when performing the post process. (default: 0)
   * @param blockCompilation If compilation of the shader should not be done in the constructor. The
   * updateEffect method can be used to compile the shader at a later time. (default: false)
   */
  ChromaticAberrationPostProcess(const std::string& name, int screenWidth, int screenHeight,
                                 const std::variant<float, PostProcessOptions>& options,
                                 const CameraPtr& camera,
                                 const std::optional<unsigned int>& samplingMode = std::nullopt,
                                 Engine* engine = nullptr, bool reusable = false,
                                 unsigned int textureType = Constants::TEXTURETYPE_UNSIGNED_INT,
                                 bool blockCompilation    = false);

public:
  /**
   * The amount of separation of rgb channels (default: 30)
   */
  float aberrationAmount;

  /**
   * The amount the effect will increase for pixels closer to the edge of the screen. (default: 0)
   */
  float radialIntensity;

  /**
   * The normalized direction in which the rgb channels should be separated. If set to 0,0 radial
   * direction will be used. (default: Vector2(0.707,0.707))
   */
  Vector2 direction;

  /**
   * The center position where the radialIntensity should be around. [0.5,0.5 is center of screen,
   * 1,1 is top right corner] (default: Vector2(0.5 ,0.5))
   */
  Vector2 centerPosition;

  /**
   * The width of the screen to apply the effect on
   */
  float screenWidth;

  /**
   * The height of the screen to apply the effect on
   */
  float screenHeight;

}; // end of class ChromaticAberrationPostProcess

} // end of namespace BABYLON

#endif // end of BABYLON_POSTPROCESSES_CHROMATIC_ABERRATION_POST_PROCESS_H
