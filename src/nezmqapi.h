/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#ifndef NEZMQ_API_H
#define NEZMQ_API_H

#include <nan.h>

#include "EZMQAPI.h"

using namespace Nan;
using namespace ezmq;

namespace nezmq
{
    class NEZMQAPI : public Nan::ObjectWrap
    {
        public:
            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance();

        private:
            NEZMQAPI();
            ~NEZMQAPI();

            static NAN_METHOD(New);
            static NAN_METHOD(Initialize);
            static NAN_METHOD(Terminate);
            static NAN_METHOD(GetStatus);

            static inline Persistent<v8::Function> & constructor()
            {
                static Persistent<v8::Function> constructor;
                return constructor;
            }

           EZMQAPI *nativeHandle;
    };
}
#endif  //NEZMQ_API_H


