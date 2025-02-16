//
// Created by Marc Rousavy on 20.02.24.
//

#pragma once

#include "RNFFilamentProxy.h"
#include "java-bindings/RNFJFilamentProxy.h"
#include <fbjni/fbjni.h>
#include <jni.h>

namespace margelo {

using namespace facebook;

/**
 * Implementation for the abstract class FilamentProxy, which uses the JNI
 * Hybrid Class "JFilamentProxy" underneath.
 */
class AndroidFilamentProxy : public FilamentProxy {
public:
  explicit AndroidFilamentProxy(jni::alias_ref<JFilamentProxy::javaobject> filamentProxy, std::shared_ptr<Dispatcher> jsDispatcher);
  ~AndroidFilamentProxy();

private:
  std::shared_ptr<FilamentBuffer> loadAsset(const std::string& path) override;
  std::shared_ptr<FilamentView> findFilamentView(int id) override;
  std::shared_ptr<Choreographer> createChoreographer() override;
  std::shared_ptr<FilamentRecorder> createRecorder(int width, int height, int fps, double bitRate) override;
  std::shared_ptr<Dispatcher> getJSDispatcher() override;
  std::shared_ptr<Dispatcher> getRenderThreadDispatcher() override;
  std::shared_ptr<Dispatcher> getUIDispatcher() override;
  std::shared_ptr<Dispatcher> getBackgroundDispatcher() override;
  float getDisplayRefreshRate() override;
  float getDensityPixelRatio() override;

public:
  jsi::Runtime& getMainJSRuntime() override;

private:
  jni::global_ref<JFilamentProxy::javaobject> _proxy;
  std::shared_ptr<Dispatcher> _jsDispatcher;
};

} // namespace margelo
