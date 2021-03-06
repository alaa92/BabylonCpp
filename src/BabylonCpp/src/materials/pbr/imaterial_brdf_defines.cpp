#include <babylon/materials/pbr/imaterial_brdf_defines.h>

#include <sstream>

namespace BABYLON {

IMaterialBRDFDefines::IMaterialBRDFDefines()
{
  boolDef = {
    {"BRDF_V_HEIGHT_CORRELATED", false},                //
    {"MS_BRDF_ENERGY_CONSERVATION", false},             //
    {"SPHERICAL_HARMONICS", false},                     //
    {"SPECULAR_GLOSSINESS_ENERGY_CONSERVATION", false}, //
  };
}

IMaterialBRDFDefines::~IMaterialBRDFDefines() = default;

std::string IMaterialBRDFDefines::toString() const
{
  std::ostringstream oss;
  oss << MaterialDefines::toString();

  return oss.str();
}

} // end of namespace BABYLON
