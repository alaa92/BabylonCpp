﻿#ifndef BABYLON_POSTPROCESSES_RENDERPIPELINE_POST_PROCESS_RENDER_PIPELINE_H
#define BABYLON_POSTPROCESSES_RENDERPIPELINE_POST_PROCESS_RENDER_PIPELINE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>
#include <babylon/babylon_fwd.h>
#include <babylon/interfaces/idisposable.h>
#include <babylon/misc/iinspectable.h>

namespace BABYLON {

class Engine;
FWD_CLASS_SPTR(Camera)
FWD_CLASS_SPTR(PostProcessRenderEffect)
FWD_CLASS_SPTR(PostProcessRenderPipeline)
FWD_CLASS_SPTR(PrePassRenderer)

/**
 * @brief PostProcessRenderPipeline
 * @see https://doc.babylonjs.com/how_to/how_to_use_postprocessrenderpipeline
 */
class BABYLON_SHARED_EXPORT PostProcessRenderPipeline : public IDisposable {

public:
  template <typename... Ts>
  static PostProcessRenderPipelinePtr New(Ts&&... args)
  {
    return std::shared_ptr<PostProcessRenderPipeline>(
      new PostProcessRenderPipeline(std::forward<Ts>(args)...));
  }
  ~PostProcessRenderPipeline() override; // = default

  /**
   * @brief Gets the class name.
   * @returns "PostProcessRenderPipeline"
   */
  virtual std::string getClassName() const;

  /**
   * @brief Adds an effect to the pipeline.
   * @param renderEffect the effect to add
   */
  void addEffect(const PostProcessRenderEffectPtr& renderEffect);

  /**
   * @brief Hidden
   */
  virtual void _rebuild();

  /**
   * @brief Hidden
   */
  void _enableEffect(const std::string& renderEffectName, const std::vector<CameraPtr>& cameras);

  /**
   * @brief Hidden
   */
  void _disableEffect(const std::string& renderEffectName, const std::vector<CameraPtr>& cameras);

  /**
   * @brief Hidden
   */
  void _attachCameras(const std::vector<CameraPtr>& cameras, bool unique);

  /**
   * @brief Hidden
   */
  void _detachCameras(const std::vector<CameraPtr>& cameras);

  /**
   * @brief Hidden
   */
  void _update();

  /**
   * @brief Hidden
   */
  void _reset();

  /**
   * @brief Sets the required values to the prepass renderer.
   * @param prePassRenderer defines the prepass renderer to setup.
   * @returns true if the pre pass is needed.
   */
  virtual bool setPrePassRenderer(const PrePassRendererPtr& prePassRenderer);

  /**
   * @brief Disposes of the pipeline.
   */
  void dispose(bool doNotRecurse = false, bool disposeMaterialAndTextures = false) override;

protected:
  /**
   * @brief Initializes a PostProcessRenderPipeline.
   * @param engine engine to add the pipeline to
   * @param name name of the pipeline
   */
  PostProcessRenderPipeline(Engine* engine, const std::string& name);

  /**
   * @brief Gets pipeline name.
   */
  std::string get_name() const;

  /**
   * @brief Gets the list of attached cameras.
   */
  std::vector<CameraPtr>& get_cameras();

  /**
   * @brief If all the render effects in the pipeline are supported.
   */
  bool get_isSupported() const;

  /**
   * @brief Hidden
   */
  bool _enableMSAAOnFirstPostProcess(unsigned int sampleCount);

public:
  /**
   * List of inspectable custom properties (used by the Inspector)
   * @see https://doc.babylonjs.com/how_to/debug_layer#extensibility
   */
  std::vector<IInspectable> inspectableCustomProperties;

  /**
   * Hidden
   */
  std::string _name;

  /**
   * Gets pipeline name
   */
  ReadOnlyProperty<PostProcessRenderPipeline, std::string> name;

  /**
   * Gets the list of attached cameras
   */
  ReadOnlyProperty<PostProcessRenderPipeline, std::vector<CameraPtr>> cameras;

  /**
   * If all the render effects in the pipeline are supported
   */
  ReadOnlyProperty<PostProcessRenderPipeline, bool> isSupported;

protected:
  /**
   * The list of attached cameras
   */
  std::vector<CameraPtr> _cameras;

private:
  Engine* engine;
  std::unordered_map<std::string, PostProcessRenderEffectPtr> _renderEffects;
  std::unordered_map<std::string, PostProcessRenderEffectPtr> _renderEffectsForIsolatedPass;

}; // end of class PostProcessRenderPipeline

} // end of namespace BABYLON

#endif // end of
       // BABYLON_POSTPROCESSES_RENDERPIPELINE_POST_PROCESS_RENDER_PIPELINE_H
