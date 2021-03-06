#include <babylon/materials/pbr/pbr_brdf_configuration.h>

#include <babylon/core/json_util.h>
#include <babylon/materials/pbr/imaterial_brdf_defines.h>

namespace BABYLON {

bool PBRBRDFConfiguration::DEFAULT_USE_ENERGY_CONSERVATION                           = true;
bool PBRBRDFConfiguration::DEFAULT_USE_SMITH_VISIBILITY_HEIGHT_CORRELATED            = true;
bool PBRBRDFConfiguration::DEFAULT_USE_SPHERICAL_HARMONICS                           = true;
bool PBRBRDFConfiguration::DEFAULT_USE_SPECULAR_GLOSSINESS_INPUT_ENERGY_CONSERVATION = true;

PBRBRDFConfiguration::PBRBRDFConfiguration(const std::function<void()>& markAllSubMeshesAsMiscDirty)
    : useEnergyConservation{this, &PBRBRDFConfiguration::get_useEnergyConservation,
                            &PBRBRDFConfiguration::set_useEnergyConservation}
    , useSmithVisibilityHeightCorrelated{this,
                                         &PBRBRDFConfiguration::
                                           get_useSmithVisibilityHeightCorrelated,
                                         &PBRBRDFConfiguration::
                                           set_useSmithVisibilityHeightCorrelated}
    , useSphericalHarmonics{this, &PBRBRDFConfiguration::get_useSphericalHarmonics,
                            &PBRBRDFConfiguration::set_useSphericalHarmonics}
    , useSpecularGlossinessInputEnergyConservation{this,
                                                   &PBRBRDFConfiguration::
                                                     get_useSpecularGlossinessInputEnergyConservation,
                                                   &PBRBRDFConfiguration::
                                                     set_useSpecularGlossinessInputEnergyConservation}
    , _useEnergyConservation{PBRBRDFConfiguration::DEFAULT_USE_ENERGY_CONSERVATION}
    , _useSmithVisibilityHeightCorrelated{PBRBRDFConfiguration::
                                            DEFAULT_USE_SMITH_VISIBILITY_HEIGHT_CORRELATED}
    , _useSphericalHarmonics{PBRBRDFConfiguration::DEFAULT_USE_SPHERICAL_HARMONICS}
    , _useSpecularGlossinessInputEnergyConservation{PBRBRDFConfiguration::
                                                      DEFAULT_USE_SPECULAR_GLOSSINESS_INPUT_ENERGY_CONSERVATION}
    , _internalMarkAllSubMeshesAsMiscDirty{markAllSubMeshesAsMiscDirty}
{
  useEnergyConservation = PBRBRDFConfiguration::DEFAULT_USE_ENERGY_CONSERVATION;
  useSmithVisibilityHeightCorrelated
    = PBRBRDFConfiguration::DEFAULT_USE_SMITH_VISIBILITY_HEIGHT_CORRELATED;
  useSphericalHarmonics = PBRBRDFConfiguration::DEFAULT_USE_SPHERICAL_HARMONICS;
  useSpecularGlossinessInputEnergyConservation
    = PBRBRDFConfiguration::DEFAULT_USE_SPECULAR_GLOSSINESS_INPUT_ENERGY_CONSERVATION;
}

PBRBRDFConfiguration::~PBRBRDFConfiguration() = default;

bool PBRBRDFConfiguration::get_useEnergyConservation() const
{
  return _useEnergyConservation;
}

void PBRBRDFConfiguration::set_useEnergyConservation(bool value)
{
  if (_useEnergyConservation == value) {
    return;
  }

  _markAllSubMeshesAsMiscDirty();
  _useEnergyConservation = value;
}

bool PBRBRDFConfiguration::get_useSmithVisibilityHeightCorrelated() const
{
  return _useSmithVisibilityHeightCorrelated;
}

void PBRBRDFConfiguration::set_useSmithVisibilityHeightCorrelated(bool value)
{
  if (_useSmithVisibilityHeightCorrelated == value) {
    return;
  }

  _useSmithVisibilityHeightCorrelated = value;
  _markAllSubMeshesAsMiscDirty();
}

bool PBRBRDFConfiguration::get_useSphericalHarmonics() const
{
  return _useSphericalHarmonics;
}

void PBRBRDFConfiguration::set_useSphericalHarmonics(bool value)
{
  if (_useSphericalHarmonics == value) {
    return;
  }

  _useSphericalHarmonics = value;
  _markAllSubMeshesAsMiscDirty();
}

bool PBRBRDFConfiguration::get_useSpecularGlossinessInputEnergyConservation() const
{
  return _useSpecularGlossinessInputEnergyConservation;
}

void PBRBRDFConfiguration::set_useSpecularGlossinessInputEnergyConservation(bool value)
{
  if (_useSpecularGlossinessInputEnergyConservation == value) {
    return;
  }

  _useSpecularGlossinessInputEnergyConservation = value;
  _markAllSubMeshesAsMiscDirty();
}

void PBRBRDFConfiguration::_markAllSubMeshesAsMiscDirty()
{
  _internalMarkAllSubMeshesAsMiscDirty();
}

void PBRBRDFConfiguration::prepareDefines(MaterialDefines& defines)
{
  defines.boolDef["BRDF_V_HEIGHT_CORRELATED"] = _useSmithVisibilityHeightCorrelated;
  defines.boolDef["MS_BRDF_ENERGY_CONSERVATION"]
    = _useEnergyConservation && _useSmithVisibilityHeightCorrelated;
  defines.boolDef["SPHERICAL_HARMONICS"] = _useSphericalHarmonics;
  defines.boolDef["SPECULAR_GLOSSINESS_ENERGY_CONSERVATION"]
    = _useSpecularGlossinessInputEnergyConservation;
}

std::string PBRBRDFConfiguration::getClassName() const
{
  return "PBRBRDFConfiguration";
}

void PBRBRDFConfiguration::copyTo(PBRBRDFConfiguration& /*anisotropicConfiguration*/)
{
}

json PBRBRDFConfiguration::serialize() const
{
  return nullptr;
}

void PBRBRDFConfiguration::parse(const json& /*source*/, Scene* /*scene*/,
                                 const std::string& /*rootUrl*/)
{
}

} // end of namespace BABYLON
