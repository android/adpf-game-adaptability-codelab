/*
 * Copyright 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NDKHelper.h"
#include "native_engine.h"

extern "C" {
void android_main(struct android_app *app);
}

// Register classes to Java.
jint JNI_OnLoad(JavaVM *vm, void * /* reserved */) {
  JNIEnv *env;
  if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }

  return JNI_VERSION_1_6;
}

/*
    android_main (not main) is our game entry function, it is called from
    the native app glue utility code as part of the onCreate handler.
*/

void android_main(struct android_app *app) {
  std::shared_ptr<NativeEngine> engine(new NativeEngine(app));

  ndk_helper::JNIHelper::Init(app);

  engine->GameLoop();
}
