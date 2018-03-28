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

#include "nezmqpublisher.h"
#include "nezmqevent.h"
#include "nezmqbytedata.h"

using namespace v8;

namespace nezmq
{
    NAN_MODULE_INIT(NEZMQPublisher::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NEZMQPublisher").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "start", Start);
        Nan::SetPrototypeMethod(tpl, "publish", Publish);
        Nan::SetPrototypeMethod(tpl, "publishOnTopic", PublishOnTopic);
        Nan::SetPrototypeMethod(tpl, "publishOnTopicList", PublishOnTopicList);
        Nan::SetPrototypeMethod(tpl, "publishByteData", PublishByteData);
        Nan::SetPrototypeMethod(tpl, "publishByteDataOnTopic", PublishByteDataOnTopic);
        Nan::SetPrototypeMethod(tpl, "publishByteDataOnList", PublishByteDataOnList);
        Nan::SetPrototypeMethod(tpl, "stop", Stop);
        Nan::SetPrototypeMethod(tpl, "getPort", GetPort);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NEZMQPublisher").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NEZMQPublisher::NewInstance()
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons).ToLocalChecked();
    }

    NEZMQPublisher::NEZMQPublisher(int port) : Nan::ObjectWrap()
    {
        nativeHandle =  new ezmq::EZMQPublisher(port, std::bind(NEZMQPublisher::startCallback, std::placeholders::_1, this),
                                                                                                 std::bind(NEZMQPublisher::stopCallback, std::placeholders::_1, this),
                                                                                                 std::bind(NEZMQPublisher::errorCallback, std::placeholders::_1, this));
        if (!nativeHandle)
        {
            Nan::ThrowError("Native handle is NULL");
        }
    }

    NEZMQPublisher::~NEZMQPublisher()
    {

    }

    void NEZMQPublisher::startCallback(EZMQErrorCode code, NEZMQPublisher *pointer)
    {
    }

    void NEZMQPublisher::stopCallback(EZMQErrorCode code, NEZMQPublisher *pointer)
    {
    }

    void NEZMQPublisher::errorCallback(EZMQErrorCode code, NEZMQPublisher *pointer)
    {
    }

    NAN_METHOD(NEZMQPublisher::New)
    {
        if (info.IsConstructCall())
        {
            // Invoked as constructor: `new NEZMQPublisher(...)`
            int port = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
            //args[1], args[2], args[3] will be application callback [Not being used now]
            NEZMQPublisher* obj = new NEZMQPublisher(port);
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
        }
    }

    NAN_METHOD(NEZMQPublisher::Start)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->start()));
    }

    NAN_METHOD(NEZMQPublisher::Publish)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        NEZMQEvent* eventObj = Nan::ObjectWrap::Unwrap<NEZMQEvent>(info[0].As<Object>());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->publish(*(eventObj->nativeHandle))));
    }

        NAN_METHOD(NEZMQPublisher::PublishOnTopic)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        Local<String> topic = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(topic);
        NEZMQEvent* eventObj = Nan::ObjectWrap::Unwrap<NEZMQEvent>(info[1].As<Object>());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->publish(*utfValue, *(eventObj->nativeHandle))));
    }

    NAN_METHOD(NEZMQPublisher::PublishOnTopicList)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        Local<Array> topicList = Local<Array>::Cast(info[0]);
        unsigned int length = topicList->Length();
        std::list<std::string> nativeList;
        for (unsigned int i = 0; i < length; i++)
        {
            Local<String> str = Local<String>::Cast(topicList->Get(i));
            String::Utf8Value utfValue(str);
            nativeList.push_back(*utfValue);
        }
        NEZMQEvent* eventObj = Nan::ObjectWrap::Unwrap<NEZMQEvent>(info[1].As<Object>());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->publish(nativeList, *(eventObj->nativeHandle))));
    }

    NAN_METHOD(NEZMQPublisher::PublishByteData)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        NEZMQByteData* byteDataObj = Nan::ObjectWrap::Unwrap<NEZMQByteData>(info[0].As<Object>());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->publish(*(byteDataObj->nativeHandle))));
    }

    NAN_METHOD(NEZMQPublisher::PublishByteDataOnTopic)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        Local<String> topic = Local<String>::Cast(info[0]);
        String::Utf8Value utfValue(topic);
        NEZMQByteData* byteDataObj = Nan::ObjectWrap::Unwrap<NEZMQByteData>(info[1].As<Object>());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->publish(*utfValue, *(byteDataObj->nativeHandle))));
    }

    NAN_METHOD(NEZMQPublisher::PublishByteDataOnList)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        Local<Array> topicList = Local<Array>::Cast(info[0]);
        unsigned int length = topicList->Length();
        std::list<std::string> nativeList;
        for (unsigned int i = 0; i < length; i++)
        {
            Local<String> str = Local<String>::Cast(topicList->Get(i));
            String::Utf8Value utfValue(str);
            nativeList.push_back(*utfValue);
        }
        NEZMQByteData* byteDataObj = Nan::ObjectWrap::Unwrap<NEZMQByteData>(info[1].As<Object>());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->publish(nativeList, *(byteDataObj->nativeHandle))));
    }

    NAN_METHOD(NEZMQPublisher::Stop)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->stop()));
    }

    NAN_METHOD(NEZMQPublisher::GetPort)
    {
        NEZMQPublisher* obj = ObjectWrap::Unwrap<NEZMQPublisher>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->getPort()));
    }
}

