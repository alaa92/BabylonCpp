#include <imgui_utils/icons_font_awesome_5.h>
#include <babylon/babylon_imgui/run_scene_with_inspector.h>
#include <imgui_utils/app_runner/imgui_runner.h>
#include <babylon/GL/framebuffer_canvas.h>

#include <babylon/core/logging.h>
#include <babylon/samples/samples_index.h>

#ifdef _WIN32
#include <windows.h>
#endif

namespace
{
  template<typename EnumType>
  bool ShowTabBarEnum(const std::map<EnumType, std::string> & enumNames, EnumType * value)
  {
    bool changed = false;
    for (const auto & kv : enumNames)
    {
      bool selected = (*value == kv.first);
      if (selected)
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.6f, 1.f));

      if (ImGui::Button(kv.second.c_str()))
      {
        if (*value != kv.first)
        {
          *value = kv.first;
          changed = true;
        }
      }
      if (selected)
        ImGui::PopStyleColor();
      ImGui::SameLine();
    }
    //ImGui::NewLine();
    //ImGui::Separator();
    return changed;
  }

}


namespace BABYLON
{
namespace impl
{
const int INSPECTOR_WIDTH = 400;

class BabylonInspectorApp {
public:

  BabylonInspectorApp() {}
  void RunApp(
    std::shared_ptr<BABYLON::IRenderableScene> initialScene,
    const SceneWithInspectorOptions & options
  )
  {
    _appContext._options = options;

    std::function<bool(void)> showGuiLambda = [this]() -> bool {
      return this->render();
    };
    auto initSceneLambda = [&]() {
      this->initScene();
      this->setRenderableScene(initialScene);
    };
    ImGuiUtils::ImGuiRunner::RunGui(showGuiLambda, _appContext._options._appWindowParams, initSceneLambda);
  }


private:
  enum class ViewState
  {
    Scene3d,
    CodeEditor,
    SampleBrowser,
  };
  static std::map<BabylonInspectorApp::ViewState, std::string> ViewStateLabels;

  void initScene()
  {
    _appContext._sampleListComponent.OnNewRenderableScene = [&](std::shared_ptr<IRenderableScene> scene) {
      this->setRenderableScene(scene);
    };
    _appContext._sampleListComponent.OnEditFiles = [&](const std::vector<std::string> & files) {
      _codeEditor.setFiles(files);
      _appContext._viewState = ViewState::CodeEditor;
    };
    _appContext._sampleListComponent.OnLoopSamples = [&](const std::vector<std::string> & samples) {
      _appContext._loopSamples.flagLoop = true;
      _appContext._loopSamples.samplesToLoop = samples;
      _appContext._loopSamples.currentIdx = 0;
      _appContext._viewState = ViewState::Scene3d;
    };

    _appContext._sceneWidget = std::make_unique<BABYLON::ImGuiSceneWidget>(getSceneSize());
    _appContext._sceneWidget->OnBeforeResize.push_back(
      [this]() {
        _appContext._inspector.release();
    }
    );
  }

  ImVec2 getSceneSize()
  {
    ImVec2 sceneSize = ImGui::GetIO().DisplaySize;
    sceneSize.x -= INSPECTOR_WIDTH;
    sceneSize.y -= 60;
    return sceneSize;
  }

  void createInspectorIfNeeded()
  {
    auto currentScene = _appContext._sceneWidget->getScene();
    if ((! _appContext._inspector) || (_appContext._inspector->scene() != currentScene))
    {
      _appContext._inspector = std::make_unique<BABYLON::Inspector>(nullptr, _appContext._sceneWidget->getScene());
      _appContext._inspector->setScene(currentScene);
    }
  }

  bool render() // renders the GUI. Returns true when exit required
  {

    bool shallExit = false;
    createInspectorIfNeeded();
    _appContext._inspector->render(false, INSPECTOR_WIDTH);
    ImGui::SameLine();

    ImGui::BeginGroup();
    ImGui::Text("%s", _appContext._sceneWidget->getRenderableScene()->getName());
    ImGui::SameLine(0., 100.);

    ShowTabBarEnum(ViewStateLabels, &_appContext._viewState);

    ImGui::SameLine(0.f, 150.f);
    if (ImGui::Button(ICON_FA_DOOR_OPEN  "Exit"))
      shallExit = true;

    ImGui::Separator();

    if (_appContext._viewState == ViewState::Scene3d)
      _appContext._sceneWidget->render(getSceneSize());
    if (_appContext._viewState == ViewState::CodeEditor)
      _codeEditor.render();
    else if (_appContext._viewState == ViewState::SampleBrowser)
      _appContext._sampleListComponent.render();


    ImGui::EndGroup();

    handleLoopSamples();

    if (_appContext._options._flagScreenshotOneSampleAndExit)
      return saveScreenshot();
    else
      return shallExit;
  }

  void setRenderableScene(std::shared_ptr<BABYLON::IRenderableScene> scene)
  {
    if (_appContext._inspector)
      _appContext._inspector->setScene(nullptr);
    _appContext._sceneWidget->setRenderableScene(scene);
    if (_appContext._inspector)
      _appContext._inspector->setScene(_appContext._sceneWidget->getScene());
    _appContext._viewState = ViewState::Scene3d;
  }

  // Saves a screenshot after  few frames (eeturns true when done)
  bool saveScreenshot()
  {
    _appContext._frameCounter++;
    if (_appContext._frameCounter < 30)
      return false;
    int imageWidth = 200;
    int jpgQuality = 75;
    this->_appContext._sceneWidget->getCanvas()->saveScreenshotJpg((_appContext._options._sceneName + ".jpg").c_str(),
      jpgQuality, imageWidth);
    return true;
  }


private:
  void handleLoopSamples()
  {
    static BABYLON::Samples::SamplesIndex samplesIndex;
    if (!_appContext._loopSamples.flagLoop)
      return;

    static int frame_counter = 0;
    const int max_frames = 60;

    if (frame_counter > max_frames)
    {
      std::string sampleName = _appContext._loopSamples.samplesToLoop[_appContext._loopSamples.currentIdx];
      BABYLON_LOG_ERROR("LoopSample", sampleName);
      auto scene = samplesIndex.createRenderableScene(sampleName, nullptr);
      this->setRenderableScene(scene);

      if (_appContext._loopSamples.currentIdx < _appContext._loopSamples.samplesToLoop.size() - 2)
        _appContext._loopSamples.currentIdx++;
      else
        _appContext._loopSamples.flagLoop = false;

      frame_counter = 0;
    }
    else
      frame_counter++;
  }


  struct AppContext
  {
    std::unique_ptr<BABYLON::ImGuiSceneWidget> _sceneWidget;
    std::unique_ptr< BABYLON::Inspector> _inspector;
    BABYLON::SamplesBrowser _sampleListComponent;
    ViewState _viewState = ViewState::Scene3d;
    int _frameCounter = 0;
    SceneWithInspectorOptions _options;

    struct
    {
      bool flagLoop = false;
      size_t currentIdx = 0;
      std::vector<std::string> samplesToLoop;
    } _loopSamples;
  };

  AppContext _appContext;
  ImGuiUtils::CodeEditor _codeEditor;
}; // end of class BabylonInspectorApp


std::map<BabylonInspectorApp::ViewState, std::string> BabylonInspectorApp::ViewStateLabels = {
{ BabylonInspectorApp::ViewState::Scene3d, ICON_FA_CUBE " 3D Scene"},
{ BabylonInspectorApp::ViewState::CodeEditor, ICON_FA_EDIT " Code Editor"},
{ BabylonInspectorApp::ViewState::SampleBrowser, ICON_FA_PALETTE " Browse samples"},
};


} // namespace impl

// public API
void runSceneWithInspector(
  std::shared_ptr<BABYLON::IRenderableScene> scene,
  SceneWithInspectorOptions options /* = SceneWithInspectorOptions() */
)
{
  BABYLON::impl::BabylonInspectorApp app;
  app.RunApp(scene, options);
}

} // namespace BABYLON