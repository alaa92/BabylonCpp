#include <babylon/engine/node.h>

#include <babylon/animations/animation.h>
#include <babylon/animations/animation_range.h>
#include <babylon/babylon_stl_util.h>
#include <babylon/behaviors/behavior.h>
#include <babylon/cameras/camera.h>
#include <babylon/core/json.h>
#include <babylon/engine/engine.h>
#include <babylon/engine/scene.h>
#include <babylon/lights/light.h>
#include <babylon/math/matrix.h>
#include <babylon/mesh/abstract_mesh.h>
#include <babylon/tools/tools.h>

namespace BABYLON {

Node::Node(const string_t& iName, Scene* scene)
    : name{iName}
    , id{iName}
    , doNotSerialize{false}
    , _currentRenderId{-1}
    , _isEnabled{true}
    , _isReady{true}
    , _parentRenderId{-1}
    , _parentNode{nullptr}
    , _worldMatrix{::std::make_unique<Matrix>(Matrix::Identity())}
    , _onDisposeObserver{nullptr}
{
  state    = "";
  _scene   = scene ? scene : Engine::LastCreatedScene();
  uniqueId = _scene->getUniqueId();
  _initCache();
}

Node::~Node()
{
}

IReflect::Type Node::type() const
{
  return IReflect::Type::NODE;
}

void Node::setParent(Node* parent)
{
  if (_parentNode == parent) {
    return;
  }

  // Remove self from list of children of parent
  if (_parentNode && !_parentNode->_children.empty()) {
    _parentNode->_children.erase(::std::remove(_parentNode->_children.begin(),
                                               _parentNode->_children.end(),
                                               this),
                                 _parentNode->_children.end());
  }

  // Store new parent
  _parentNode = parent;

  // Add as child to new parent
  if (_parentNode) {
    _parentNode->_children.emplace_back(this);
  }
}

Node* Node::parent() const
{
  return _parentNode;
}

const char* Node::getClassName() const
{
  return "Node";
}

void Node::setOnDispose(
  const ::std::function<void(Node* node, EventState& es)>& callback)
{
  if (_onDisposeObserver) {
    onDisposeObservable.remove(_onDisposeObserver);
  }
  _onDisposeObserver = onDisposeObservable.add(callback);
}

Scene* Node::getScene()
{
  return _scene;
}

Engine* Node::getEngine()
{
  return _scene->getEngine();
}

Node& Node::addBehavior(Behavior<Node>* behavior)
{
  auto it = ::std::find(_behaviors.begin(), _behaviors.end(), behavior);

  if (it != _behaviors.end()) {
    return *this;
  }

  behavior->init();
  if (_scene->isLoading()) {
    // We defer the attach when the scene will be loaded
  }
  else {
    behavior->attach(this);
  }
  _behaviors.emplace_back(behavior);

  return *this;
}

Node& Node::removeBehavior(Behavior<Node>* behavior)
{
  auto it = ::std::find(_behaviors.begin(), _behaviors.end(), behavior);

  if (it == _behaviors.end()) {
    return *this;
  }

  (*it)->detach();
  _behaviors.erase(it);

  return *this;
}

vector_t<Behavior<Node>*>& Node::behaviors()
{
  return _behaviors;
}

const vector_t<Behavior<Node>*>& Node::behaviors() const
{
  return _behaviors;
}

Behavior<Node>* Node::getBehaviorByName(const string_t& iName)
{
  auto it = ::std::find_if(_behaviors.begin(), _behaviors.end(),
                           [&iName](const Behavior<Node>* behavior) {
                             return behavior->name == iName;
                           });

  return (it != _behaviors.end() ? *it : nullptr);
}

Matrix* Node::getWorldMatrix()
{
  return _worldMatrix.get();
}

void Node::_initCache()
{
  _cache.parent = nullptr;
}

void Node::updateCache(bool force)
{
  if (!force && isSynchronized()) {
    return;
  }

  _cache.parent = parent();

  _updateCache();
}

void Node::_updateCache(bool /*ignoreParentClass*/)
{
}

bool Node::_isSynchronized()
{
  return true;
}

void Node::_markSyncedWithParent()
{
  if (parent()) {
    _parentRenderId = parent()->_currentRenderId;
  }
}

bool Node::isSynchronizedWithParent()
{
  if (!parent()) {
    return true;
  }

  if (_parentRenderId != _parentNode->_currentRenderId) {
    return false;
  }

  return parent()->isSynchronized();
}

bool Node::isSynchronized(bool iUpdateCache)
{
  bool check = hasNewParent();

  check = check ? check : !isSynchronizedWithParent();

  check = check ? check : !_isSynchronized();

  if (iUpdateCache) {
    updateCache(true);
  }

  return !check;
}

bool Node::hasNewParent(bool update)
{
  if (_cache.parent == parent()) {
    return false;
  }

  if (update) {
    _cache.parent = parent();
  }

  return true;
}

bool Node::isReady() const
{
  return _isReady;
}

bool Node::isEnabled(bool checkAncestors)
{
  if (checkAncestors == false) {
    return _isEnabled;
  }

  if (_isEnabled == false) {
    return false;
  }

  if (parent()) {
    return parent()->isEnabled(checkAncestors);
  }

  return true;
}

void Node::setEnabled(bool value)
{
  _isEnabled = value;
}

bool Node::isDescendantOf(const Node* ancestor)
{
  if (parent()) {
    if (parent() == ancestor) {
      return true;
    }

    return parent()->isDescendantOf(ancestor);
  }
  return false;
}

void Node::_getDescendants(vector_t<Node*>& results, bool directDescendantsOnly,
                           const ::std::function<bool(Node* node)>& predicate)
{
  if (_children.empty()) {
    return;
  }

  for (auto& item : _children) {
    if (!predicate || predicate(item)) {
      results.emplace_back(item);
    }

    if (!directDescendantsOnly) {
      item->_getDescendants(results, false, predicate);
    }
  }
}

void Node::_getDescendants(vector_t<AbstractMesh*>& results,
                           bool directDescendantsOnly,
                           const ::std::function<bool(Node* node)>& predicate)
{
  if (_children.empty()) {
    return;
  }

  for (auto& item : _children) {
    if (!predicate || predicate(item)) {
      if (auto m = dynamic_cast<AbstractMesh*>(item)) {
        results.emplace_back(m);
      }
    }

    if (!directDescendantsOnly) {
      item->_getDescendants(results, false, predicate);
    }
  }
}

void Node::_getDescendants(vector_t<TransformNode*>& results,
                           bool directDescendantsOnly,
                           const ::std::function<bool(Node* node)>& predicate)
{
  if (_children.empty()) {
    return;
  }

  for (auto& item : _children) {
    if (!predicate || predicate(item)) {
      if (auto m = dynamic_cast<TransformNode*>(item)) {
        results.emplace_back(m);
      }
    }

    if (!directDescendantsOnly) {
      item->_getDescendants(results, false, predicate);
    }
  }
}

vector_t<Node*>
Node::getDescendants(bool directDescendantsOnly,
                     const ::std::function<bool(Node* node)>& predicate)
{
  vector_t<Node*> results;
  _getDescendants(results, directDescendantsOnly, predicate);

  return results;
}

vector_t<AbstractMesh*>
Node::getChildMeshes(bool directDescendantsOnly,
                     const ::std::function<bool(Node* node)>& predicate)
{
  vector_t<AbstractMesh*> results;
  _getDescendants(results, directDescendantsOnly, [&predicate](Node* node) {
    return ((!predicate || predicate(node))
            && (dynamic_cast<AbstractMesh*>(node)));
  });
  return results;
}

vector_t<TransformNode*>
Node::getChildTransformNodes(bool directDescendantsOnly,
                             const ::std::function<bool(Node* node)>& predicate)
{
  vector_t<TransformNode*> results;
  _getDescendants(results, directDescendantsOnly, [&predicate](Node* node) {
    return ((!predicate || predicate(node))
            && (dynamic_cast<TransformNode*>(node)));
  });
  return results;
}

vector_t<Node*>
Node::getChildren(const ::std::function<bool(Node* node)>& predicate)
{
  return getDescendants(true, predicate);
}

void Node::_setReady(bool iState)
{
  if (iState == _isReady) {
    return;
  }

  if (!iState) {
    _isReady = false;
    return;
  }

  _isReady = true;
  if (onReady) {
    onReady(this);
  }
}

vector_t<Animation*> Node::getAnimations()
{
  return animations;
}

Animation* Node::getAnimationByName(const string_t& iName)
{
  auto it = ::std::find_if(
    animations.begin(), animations.end(),
    [&iName](Animation* animation) { return animation->name == iName; });

  return (it != animations.end() ? *it : nullptr);
}

void Node::createAnimationRange(const string_t& iName, float from, float to)
{
  // check name not already in use
  if (!stl_util::contains(_ranges, iName)) {
    _ranges[iName] = ::std::make_unique<AnimationRange>(iName, from, to);
    for (auto& animation : animations) {
      if (animation) {
        animation->createRange(iName, from, to);
      }
    }
  }
}

void Node::deleteAnimationRange(const string_t& iName, bool deleteFrames)
{
  for (auto& animation : animations) {
    if (animation) {
      animation->deleteRange(iName, deleteFrames);
    }
  }

  _ranges.erase(iName);
}

AnimationRange* Node::getAnimationRange(const string_t& iName)
{
  if (stl_util::contains(_ranges, iName)) {
    return _ranges[iName].get();
  }

  return nullptr;
}

Animatable* Node::beginAnimation(const string_t& iName, bool loop,
                                 float speedRatio,
                                 ::std::function<void()> onAnimationEnd)
{
  auto range = getAnimationRange(iName);

  if (!range) {
    return nullptr;
  }

  return _scene->beginAnimation(this, static_cast<int>(range->from),
                                static_cast<int>(range->to), loop, speedRatio,
                                onAnimationEnd);
}

vector_t<AnimationRange> Node::serializeAnimationRanges()
{
  vector_t<AnimationRange> serializationRanges;
  for (auto& item : _ranges) {
    serializationRanges.emplace_back(
      AnimationRange(item.first, item.second->from, item.second->to));
  }

  return serializationRanges;
}

Matrix& Node::computeWorldMatrix(bool /*force*/)
{
  return *_worldMatrix;
}

void Node::dispose(bool /*doNotRecurse*/)
{
  setParent(nullptr);

  // Callback
  onDisposeObservable.notifyObservers(this);
  onDisposeObservable.clear();

  // Behaviors
  for (auto& behavior : _behaviors) {
    behavior->detach();
  }

  _behaviors.clear();
}

void Node::ParseAnimationRanges(Node* node, const Json::value& parsedNode,
                                Scene* /*scene*/)
{
  if (parsedNode.contains("ranges")) {
    for (auto& range : Json::GetArray(parsedNode, "ranges")) {
      node->createAnimationRange(Json::GetString(range, "name"),
                                 Json::GetNumber<float>(range, "from", 0),
                                 Json::GetNumber<float>(range, "to", 0));
    }
  }
}

} // end of namespace BABYLON
