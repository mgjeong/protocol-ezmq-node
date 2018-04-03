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

#ifndef NEZMQ_BYTEDATA_H_
#define NEZMQ_BYTEDATA_H_

#include <nan.h>

#include "EZMQByteData.h"

using namespace Nan;
using namespace ezmq;

namespace nezmq
{
    class NEZMQByteData  : public ObjectWrap
    {
        public:
            friend class NEZMQReading;
            friend class NEZMQPublisher;
            friend class NEZMQSubscriber;

            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance(int argc, v8::Local<v8::Value> argv[]);

        private:
            NEZMQByteData(const uint8_t *data,  size_t dataLength);
            ~NEZMQByteData();

            static NAN_METHOD(New);
            static NAN_METHOD(GetContentType);
            static NAN_METHOD(GetLength);
            static NAN_METHOD(GetByteData);
            static NAN_METHOD(SetByteData);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }

            ezmq::EZMQByteData *nativeHandle;
    };
}

#endif // NEZMQ_BYTEDATA_H_


