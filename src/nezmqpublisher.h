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

#ifndef NEZMQ_PUBLISHER_H
#define NEZMQ_PUBLISHER_H

#include <nan.h>

#include "EZMQPublisher.h"

using namespace Nan;
using namespace ezmq;

namespace nezmq
{
    class NEZMQPublisher: public Nan::ObjectWrap
    {
        public:
            static NAN_MODULE_INIT(Init);
            static v8::Local<v8::Object> NewInstance();

            //callback functions
            static void startCallback(EZMQErrorCode code, NEZMQPublisher *pointer);
            static void stopCallback(EZMQErrorCode code, NEZMQPublisher *pointer);
            static void errorCallback(EZMQErrorCode code, NEZMQPublisher *pointer);

        private:
            NEZMQPublisher(int port);
            ~NEZMQPublisher();

            static NAN_METHOD(New);
            static NAN_METHOD(SetServerPrivateKey);
            static NAN_METHOD(Start);
            static NAN_METHOD(Publish);
            static NAN_METHOD(PublishOnTopic);
            static NAN_METHOD(PublishOnTopicList);
            static NAN_METHOD(PublishByteData);
            static NAN_METHOD(PublishByteDataOnTopic);
            static NAN_METHOD(PublishByteDataOnList);
            static NAN_METHOD(Stop);
            static NAN_METHOD(GetPort);

            static inline Nan::Persistent<v8::Function> & constructor()
            {
                static Nan::Persistent<v8::Function> constructor;
                return constructor;
            }

            ezmq::EZMQPublisher *nativeHandle;
    };
}
#endif  //NEZMQ_PUBLISHER_H


