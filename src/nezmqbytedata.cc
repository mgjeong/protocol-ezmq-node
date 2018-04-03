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

#include "nezmqbytedata.h"

#include <iostream>
#include <node.h>
#include "v8.h"

using namespace Nan;
using namespace v8;
using namespace std;

namespace nezmq
{
    NAN_MODULE_INIT(NEZMQByteData::Init)
    {
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NEZMQByteData").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "getContentType", GetContentType);
        Nan::SetPrototypeMethod(tpl, "getLength", GetLength);
        Nan::SetPrototypeMethod(tpl, "getByteData", GetByteData);
        Nan::SetPrototypeMethod(tpl, "setByteData", SetByteData);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NEZMQByteData").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NEZMQByteData::NewInstance(int argc, v8::Local<v8::Value> argv[])
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons, argc, argv).ToLocalChecked();
    }

    NEZMQByteData::NEZMQByteData(const uint8_t *data,  size_t dataLength) : Nan::ObjectWrap()
    {
        nativeHandle =  new EZMQByteData(data, dataLength);
        if (!nativeHandle)
        {
            Nan::ThrowError("Byte data creation failed");
        }
    }

    NEZMQByteData::~NEZMQByteData()
    {

    }

    NAN_METHOD(NEZMQByteData::New)
    {
        if (info.IsConstructCall())
        {
            NEZMQByteData* obj;
            Local<Object> bufferObj;
            size_t dataLength = 0 ;
            uint8_t* data = NULL;
            if(info.Length() > 0)
            {
                bufferObj = info[0]->ToObject();
                dataLength = info[1]->Uint32Value();
                data = (uint8_t*)node::Buffer::Data(bufferObj);
            }

            obj = new NEZMQByteData(data, dataLength);
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
        }
    }

    NAN_METHOD(NEZMQByteData::GetContentType)
    {
        NEZMQByteData* obj = ObjectWrap::Unwrap<NEZMQByteData>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->getContentType()));
    }

     NAN_METHOD(NEZMQByteData::GetLength)
     {
        NEZMQByteData* obj = ObjectWrap::Unwrap<NEZMQByteData>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->getLength()));
     }

     NAN_METHOD(NEZMQByteData::GetByteData)
     {
        NEZMQByteData* obj = ObjectWrap::Unwrap<NEZMQByteData>(info.Holder());
        const uint8_t* data = (obj->nativeHandle)->getByteData();
        info.GetReturnValue().Set(Nan::CopyBuffer((char *)data, (obj->nativeHandle)->getLength()).ToLocalChecked());
     }

     NAN_METHOD(NEZMQByteData::SetByteData)
     {
        NEZMQByteData* obj = ObjectWrap::Unwrap<NEZMQByteData>(info.Holder());
        Local<Object> bufferObj = info[0]->ToObject();
        size_t dataLength = info[1]->Uint32Value();
        const uint8_t* data= (const uint8_t*)node::Buffer::Data(bufferObj);
        info.GetReturnValue().Set(Nan::New<Number>((obj->nativeHandle)->setByteData(data, dataLength)));
     }
}


