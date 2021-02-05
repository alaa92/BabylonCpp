#ifndef BABYLON_POSTPROCESSES_SUB_SURFACE_SCATTERING_POST_PROCESS_H
#define BABYLON_POSTPROCESSES_SUB_SURFACE_SCATTERING_POST_PROCESS_H

#include <babylon/babylon_api.h>
#include <babylon/babylon_fwd.h>
#include <babylon/postprocesses/post_process.h>

namespace BABYLON {

FWD_CLASS_SPTR(SubSurfaceScatteringPostProcess)

/**
 * @brief Sub surface scattering post process.
 */
class BABYLON_SHARED_EXPORT SubSurfaceScatteringPostProcess : public PostProcess {

public:
  template <typename... Ts>
  static SubSurfaceScatteringPostProcessPtr New(Ts&&... args)
  {
    auto postProcess = std::shared_ptr<SubSurfaceScatteringPostProcess>(
      new SubSurfaceScatteringPostProcess(std::forward<Ts>(args)...));
    postProcess->add(postProcess);

    return postProcess;
  }
  ~SubSurfaceScatteringPostProcess() override; // = default

  /**
   * @brief Gets a string identifying the name of the class.
   * @returns "SubSurfaceScatteringPostProcess" string
   */
  std::string getClassName() const override;

protected:
  /**
   * @brief Creates a sub surface scattering post process.
   */
  SubSurfaceScatteringPostProcess(const std::string& name, Scene* scene,
                                  const std::variant<float, PostProcessOptions>& options,
                                  const CameraPtr& camera                         = nullptr,
                                  const std::optional<unsigned int>& samplingMode = std::nullopt,
                                  Engine* engine = nullptr, bool reusable = false,
                                  unsigned int textureType = Constants::TEXTURETYPE_UNSIGNED_INT);

}; // end of class SubSurfaceScatteringPostProcess

} // end of namespace BABYLON

#endif // end of BABYLON_POSTPROCESSES_SUB_SURFACE_SCATTERING_POST_PROCESS_H
