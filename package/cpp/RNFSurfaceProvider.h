//
// Created by Marc Rousavy on 20.02.24.
//

#pragma once

#include "RNFListener.h"
#include "RNFListenerManager.h"
#include "RNFSurface.h"
#include "jsi/RNFHybridObject.h"
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace margelo {

class SurfaceProvider : public HybridObject {
public:
  using TOnCreate = std::function<void(std::shared_ptr<Surface> surface)>;
  using TOnResize = std::function<void(std::shared_ptr<Surface> surface, int width, int height)>;
  using TOnDestroy = std::function<void(std::shared_ptr<Surface>)>;

  struct Callbacks {
    std::optional<TOnCreate> onSurfaceCreated;
    std::optional<TOnResize> onSurfaceSizeChanged;
    std::optional<TOnDestroy> onSurfaceDestroyed;
  };

public:
  explicit SurfaceProvider() : HybridObject("SurfaceProvider") {}

public:
  std::shared_ptr<Listener> addOnSurfaceChangedListener(Callbacks&& callbacks);
  std::shared_ptr<Listener> addOnSurfaceCreatedListener(TOnCreate callback, std::shared_ptr<Dispatcher> dispatcher);
  std::shared_ptr<Listener> addOnSurfaceDestroyedListener(TOnDestroy callback, std::shared_ptr<Dispatcher> dispatcher);

  virtual std::shared_ptr<Surface> getSurfaceOrNull() = 0;
  std::optional<std::shared_ptr<Surface>> getSurface();

  void loadHybridMethods() override;

protected:
  void onSurfaceCreated(std::shared_ptr<Surface> callbacks);
  void onSurfaceChanged(std::shared_ptr<Surface> surface, int width, int height);
  void onSurfaceDestroyed(std::shared_ptr<Surface> surface);

private:
  std::shared_ptr<ListenerManager<Callbacks>> _listeners = ListenerManager<Callbacks>::create();
  std::mutex _mutex;

private:
  static constexpr auto TAG = "SurfaceProvider";
};

} // namespace margelo
