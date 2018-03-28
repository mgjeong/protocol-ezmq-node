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

#include "nezmqapi.h"
#include <iostream>
using namespace Nan;
using namespace v8;

namespace nezmq
{
    NAN_MODULE_INIT(NEZMQAPI::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NEZMQAPI").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "initialize", Initialize);
        Nan::SetPrototypeMethod(tpl, "terminate", Terminate);
        Nan::SetPrototypeMethod(tpl, "getStatus", GetStatus);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NEZMQAPI").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NEZMQAPI::NewInstance()
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons).ToLocalChecked();
    }

    NEZMQAPI::NEZMQAPI(): Nan::ObjectWrap()
    {
        nativeHandle =  ezmq::EZMQAPI::getInstance();
        if (!nativeHandle)
        {
            Nan::ThrowError("EZMQAPI - Native handle is null");
        }
    }

    NEZMQAPI::~NEZMQAPI()
    {

    }

    NAN_METHOD(NEZMQAPI::New)
    {
        if (info.IsConstructCall())
        {
            // Invoked as constructor: `new NEZMQAPI(...)`
            NEZMQAPI* obj = new NEZMQAPI();
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
        else
        {
        }
    }

    NAN_METHOD(NEZMQAPI::Initialize)
    {
        NEZMQAPI* obj = ObjectWrap::Unwrap<NEZMQAPI>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->initialize()));
    }

    NAN_METHOD(NEZMQAPI::Terminate)
    {
        NEZMQAPI* obj = ObjectWrap::Unwrap<NEZMQAPI>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->terminate()));
    }

    NAN_METHOD(NEZMQAPI::GetStatus)
    {
        NEZMQAPI* obj = ObjectWrap::Unwrap<NEZMQAPI>(info.Holder());
        info.GetReturnValue().Set(Nan::New<Integer>((obj->nativeHandle)->getStatus()));
    }
}

