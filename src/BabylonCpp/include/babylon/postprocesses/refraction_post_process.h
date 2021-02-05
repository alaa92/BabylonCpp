#ifndef BABYLON_POSTPROCESSES_REFRACTION_POST_PROCESS_H
#define BABYLON_POSTPROCESSES_REFRACTION_POST_PROCESS_H

#include <babylon/babylon_api.h>
#include <babylon/babylon_fwd.h>
#include <babylon/maths/color3.h>
#include <babylon/postprocesses/post_process.h>

namespace BABYLON {

FWD_CLASS_SPTR(RefractionPostProcess)
FWD_CLASS_SPTR(Texture)

/**
 * @brief Post process which applies a refraction texture.
 * @see https://doc.babylonjs.com/how_to/how_to_use_postprocesses#refraction
 */
class BABYLON_SHARED_EXPORT RefractionPostProcess : public PostProcess {

public:
  /**
   * @brief Initializes the RefractionPostProcess.
   * @see https://doc.babylonjs.com/how_to/how_to_use_postprocesses#refraction
   * @param name The name of the effect.
   * @param refractionTextureUrl Url of the refraction texture to use
   * @param color the base color of the refraction (used to taint the rendering)
   * @param depth simulated refraction depth
   * @param colorLevel the coefficient of the base color (0 to remove base color tainting)
   * @param camera The camera to apply the render pass to.
   * @param options The required width/height ratio to downsize to before computing the render pass.
   * @param samplingMode The sampling mode to be used when computing the pass. (default: 0)
   * @param engine The engine which the post process will be applied. (default: current engine)
   * @param reusable If the post process can be reused on the same frame. (default: false)
   */
  RefractionPostProcess(const std::string& name, const std::string& refractionTextureUrl,
                        const Color3& color, float depth, int colorLevel, float ratio,
                        const CameraPtr& camera,
                        const std::optional<unsigned int>& samplingMode = std::nullopt,
                        Engine* engine = nullptr, bool reusable = false);
  ~RefractionPostProcess() override; // = default

  /**
   * @brief Gets a string identifying the name of the class.
   * @returns "RefractionPostProcess" string
   */
  std::string getClassName() const override;

  /**
   * @brief Disposes of the post process.
   * @param camera Camera to dispose post process on
   */
  void dispose(Camera* camera = nullptr) override;

  /**
   * @brief Hidden
   */
  static RefractionPostProcessPtr _Parse(const json& parsedPostProcess,
                                         const CameraPtr& targetCamera, Scene* scene,
                                         const std::string& rootUrl);

private:
  /**
   * @brief Gets the refraction texture.
   * Please note that you are responsible for disposing the texture if you set it manually
   */
  TexturePtr& get_refractionTexture();

  /**
   * @brief Sets the refraction texture.
   * Please note that you are responsible for disposing the texture if you set it manually
   */
  void set_refractionTexture(const TexturePtr& value);

public:
  /**
   * The base color of the refraction (used to taint the rendering)
   */
  Color3 color;

  /**
   * Simulated refraction depth
   */
  float depth;

  /**
   * The coefficient of the base color (0 to remove base color tainting)
   */
  int colorLevel;

  /**
   * Gets the url used to load the refraction texture
   */
  std::string refractionTextureUrl;

  /**
   * Gets or sets the refraction texture
   * Please note that you are responsible for disposing the texture if you set it manually
   */
  Property<RefractionPostProcess, TexturePtr> refractionTexture;

private:
  TexturePtr _refTexture;
  bool _ownRefractionTexture;

}; // end of class RefractionPostProcess

} // end of namespace BABYLON

#endif // end of BABYLON_POSTPROCESSES_REFRACTION_POST_PROCESS_H
