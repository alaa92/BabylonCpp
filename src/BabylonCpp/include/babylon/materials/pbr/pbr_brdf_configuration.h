#ifndef BABYLON_MATERIALS_PBR_PBR_BRDF_CONFIGURATION_H
#define BABYLON_MATERIALS_PBR_PBR_BRDF_CONFIGURATION_H

#include <functional>

#include <nlohmann/json_fwd.hpp>

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>

using json = nlohmann::json;

namespace BABYLON {

struct MaterialDefines;
class Scene;

/**
 * @brief Define the code related to the BRDF parameters of the pbr material.
 */
class BABYLON_SHARED_EXPORT PBRBRDFConfiguration {

public:
  /**
   * Default value used for the energy conservation.
   * This should only be changed to adapt to the type of texture in scene.environmentBRDFTexture.
   */
  static bool DEFAULT_USE_ENERGY_CONSERVATION;

  /**
   * Default value used for the Smith Visibility Height Correlated mode.
   * This should only be changed to adapt to the type of texture in scene.environmentBRDFTexture.
   */
  static bool DEFAULT_USE_SMITH_VISIBILITY_HEIGHT_CORRELATED;

  /**
   * Default value used for the IBL diffuse part.
   * This can help switching back to the polynomials mode globally which is a tiny bit
   * less GPU intensive at the drawback of a lower quality.
   */
  static bool DEFAULT_USE_SPHERICAL_HARMONICS;

  /**
   * Default value used for activating energy conservation for the specular workflow.
   * If activated, the albedo color is multiplied with (1. - maxChannel(specular color)).
   * If deactivated, a material is only physically plausible, when (albedo color + specular color)
   * < 1.
   */
  static bool DEFAULT_USE_SPECULAR_GLOSSINESS_INPUT_ENERGY_CONSERVATION;

public:
  /**
   * @brief Instantiate a new instance of clear coat configuration.
   * @param markAllSubMeshesAsMiscDirty Callback to flag the material to dirty
   */
  PBRBRDFConfiguration(const std::function<void()>& markAllSubMeshesAsMiscDirty);
  ~PBRBRDFConfiguration(); // = default

  /**
   * @brief Hidden
   */
  void _markAllSubMeshesAsMiscDirty();

  /**
   * @brief Checks to see if a texture is used in the material.
   * @param defines the list of "defines" to update.
   */
  void prepareDefines(MaterialDefines& defines);

  /**
   * @brief Get the current class name of the texture useful for serialization
   * or dynamic coding.
   * @returns "PBRClearCoatConfiguration"
   */
  [[nodiscard]] std::string getClassName() const;

  /**
   * @brief Makes a duplicate of the current configuration into another one.
   * @param brdfConfiguration define the config where to copy the info
   */
  void copyTo(PBRBRDFConfiguration& brdfConfiguration);

  /**
   * @brief Serializes this BRDF configuration.
   * @returns - An object with the serialized config.
   */
  [[nodiscard]] json serialize() const;

  /**
   * @brief Parses a BRDF Configuration from a serialized object.
   * @param source - Serialized object.
   * @param scene Defines the scene we are parsing for
   * @param rootUrl Defines the rootUrl to load from
   */
  void parse(const json& source, Scene* scene, const std::string& rootUrl);

protected:
  [[nodiscard]] bool get_useEnergyConservation() const;
  void set_useEnergyConservation(bool value);
  [[nodiscard]] bool get_useSmithVisibilityHeightCorrelated() const;
  void set_useSmithVisibilityHeightCorrelated(bool value);
  [[nodiscard]] bool get_useSphericalHarmonics() const;
  void set_useSphericalHarmonics(bool value);
  [[nodiscard]] bool get_useSpecularGlossinessInputEnergyConservation() const;
  void set_useSpecularGlossinessInputEnergyConservation(bool value);

public:
  /**
   * Defines if the material uses energy conservation.
   */
  Property<PBRBRDFConfiguration, bool> useEnergyConservation;

  /**
   * LEGACY Mode set to false
   * Defines if the material uses height smith correlated visibility term.
   * If you intent to not use our default BRDF, you need to load a separate BRDF
   * Texture for the PBR You can either load
   * https://assets.babylonjs.com/environments/uncorrelatedBRDF.png or
   * https://assets.babylonjs.com/environments/uncorrelatedBRDF.dds to have more
   * precision Not relying on height correlated will also disable energy
   * conservation.
   */
  Property<PBRBRDFConfiguration, bool> useSmithVisibilityHeightCorrelated;

  /**
   * LEGACY Mode set to false
   * Defines if the material uses spherical harmonics vs spherical polynomials
   * for the diffuse part of the IBL. The harmonics despite a tiny bigger cost
   * has been proven to provide closer results to the ground truth.
   */
  Property<PBRBRDFConfiguration, bool> useSphericalHarmonics;

  /**
   * Defines if the material uses energy conservation, when the specular workflow is active.
   * If activated, the albedo color is multiplied with (1. - maxChannel(specular color)).
   * If deactivated, a material is only physically plausible, when (albedo color + specular color)
   * < 1. In the deactivated case, the material author has to ensure energy conservation, for a
   * physically plausible rendering.
   */
  Property<PBRBRDFConfiguration, bool> useSpecularGlossinessInputEnergyConservation;

private:
  bool _useEnergyConservation;
  bool _useSmithVisibilityHeightCorrelated;
  bool _useSphericalHarmonics;
  bool _useSpecularGlossinessInputEnergyConservation;
  /** Hidden */
  std::function<void()> _internalMarkAllSubMeshesAsMiscDirty;

}; // end of class PBRBRDFConfiguration

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_PBR_PBR_BRDF_CONFIGURATION_H
