#ifndef BABYLON_INSPECTOR_COMPONENTS_ACTION_TABS_TABS_PROPERTY_GRIDS_MATERIALS_MULTI_MATERIAL_PROPERTY_GRID_COMPONENT_H
#define BABYLON_INSPECTOR_COMPONENTS_ACTION_TABS_TABS_PROPERTY_GRIDS_MATERIALS_MULTI_MATERIAL_PROPERTY_GRID_COMPONENT_H

#include <memory>

#include <babylon/babylon_api.h>
#include <babylon/core/string.h>
#include <babylon/inspector/components/actiontabs/lines/text_line_component.h>
#include <babylon/inspector/components/actiontabs/tabs/propertygrids/materials/common_material_property_grid_component.h>
#include <babylon/materials/multi_material.h>

namespace BABYLON {

class MultiMaterial;
using MultiMaterialPtr = std::shared_ptr<MultiMaterial>;

struct BABYLON_SHARED_EXPORT MultiMaterialPropertyGridComponent {

  static void renderChildMaterial(const MultiMaterialPtr& material)
  {
    // --- CHILDREN ---
    static auto childrenContainerOpened = true;
    ImGui::SetNextTreeNodeOpen(childrenContainerOpened, ImGuiCond_Always);
    if (ImGui::CollapsingHeader("CHILDREN")) {
      int i = 0;
      for (const auto& mat : material->subMaterials()) {
        if (mat) {
          TextLineComponent::render(String::printf("Material #%d", i).c_str(),
                                    mat->name);
        }
        ++i;
      }
      childrenContainerOpened = true;
    }
    else {
      childrenContainerOpened = false;
    }
  }

  static void render(const MultiMaterialPtr& material)
  {
    CommonMaterialPropertyGridComponent::render(material);
    renderChildMaterial(material);
  }

}; // end of struct MultiMaterialPropertyGridComponent

} // end of namespace BABYLON

#endif // end of
       // BABYLON_INSPECTOR_COMPONENTS_ACTION_TABS_TABS_PROPERTY_GRIDS_MATERIALS_MULTI_MATERIAL_PROPERTY_GRID_COMPONENT_H