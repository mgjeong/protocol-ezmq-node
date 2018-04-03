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

#ifndef NEZQ_READING_H
#define NEZQ_READING_H

#include <nan.h>

#include "Event.pb.h"

#include "nezmqevent.h"

using namespace Nan;
using namespace ezmq;
using namespace v8;

namespace nezmq
{
    class NEZMQReading : public ObjectWrap
    {
         public:
            friend class NEZMQEvent;

            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance(int argc, v8::Local<v8::Value> argv[]);

         private:
           explicit NEZMQReading(NEZMQEvent *eventObj);
              ~NEZMQReading();

            static NAN_METHOD(New);
            static NAN_METHOD(GetID);
            static NAN_METHOD(GetCreated);
            static NAN_METHOD(GetModified);
            static NAN_METHOD(GetOrigin);
            static NAN_METHOD(GetPushed);
            static NAN_METHOD(GetName);
            static NAN_METHOD(GetValue);
            static NAN_METHOD(GetDevice);
            static NAN_METHOD(SetID);
            static NAN_METHOD(SetCreated);
            static NAN_METHOD(SetModified);
            static NAN_METHOD(SetOrigin);
            static NAN_METHOD(SetPushed);
            static NAN_METHOD(SetName);
            static NAN_METHOD(SetValue);
            static NAN_METHOD(SetDevice);

            static inline Nan::Persistent<v8::Function> & constructor1()
            {
                static Nan::Persistent<v8::Function> constructor1;
                return constructor1;
            }

            ezmq::Reading *nativeHandle;

    };
}

#endif  //NEZQ_READING_H
