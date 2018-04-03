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

#ifndef NEZQ_EVENT_H
#define NEZQ_EVENT_H

#include <nan.h>
#include "Event.pb.h"

using namespace Nan;
using namespace ezmq;
using namespace v8;

namespace nezmq
{
    class NEZMQEvent : public ObjectWrap
    {
         public:
            friend class NEZMQReading;
            friend class NEZMQPublisher;
            friend class NEZMQSubscriber;

            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance();

         private:
            explicit NEZMQEvent();
            ~NEZMQEvent();
            v8::Local<v8::Object> createReadingInstance(Reading *reading);

            static NAN_METHOD(New);
            static NAN_METHOD(GetContentType);
            static NAN_METHOD(GetID);
            static NAN_METHOD(GetCreated);
            static NAN_METHOD(GetModified);
            static NAN_METHOD(GetOrigin);
            static NAN_METHOD(GetPushed);
            static NAN_METHOD(GetDevice);
            static NAN_METHOD(GetReadingCount);
            static NAN_METHOD(GetReading);
            static NAN_METHOD(SetID);
            static NAN_METHOD(SetCreated);
            static NAN_METHOD(SetModified);
            static NAN_METHOD(SetOrigin);
            static NAN_METHOD(SetPushed);
            static NAN_METHOD(SetDevice);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }

            ezmq::Event *nativeHandle;
    };
}
#endif  //NEZQ_EVENT_H

