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

//Module dependencies.
var ezmqErrorCodes = require('../build/Release/ezmq.node');

//Expose bindings as the module.
exports = module.exports = ezmqErrorCodes;

/**
 * Represents EZMQ stack error codes.
 */
var EZMQErrorCode = (exports.EZMQErrorCode = {
    /**  Success case */
    EZMQ_OK: 0,
    /**  ERROR */
    EZMQ_ERROR: 1,
    /**  INVALID TOPIC */
    EZMQ_INVALID_TOPIC: 2,
    /** INVALID CONTENT_TYPE */
    EZMQ_INVALID_CONTENT_TYPE: 3,
});

var ezmqStatusCodes = require('../build/Release/ezmq.node');
exports = module.exports = ezmqStatusCodes;

/**
 * Represents EZMQ stack Status codes.
 */
var EZMQStatusCode = (exports.EZMQStatusCode = {
    /** UNKNOWN Status */
    EZMQ_UNKNOWN: 0,
    /** CONSTRUCTED */
    EZMQ_CONSTRUCTED: 1,
    /**  INITAILIZED */
    EZMQ_INITAILIZED: 2,
    /** TERMINATED */
    EZMQ_TERMINATED: 3,
});

var ezmqContentType = require('../build/Release/ezmq.node');
exports = module.exports = ezmqContentType;

/**
 * Represents EZMQ message's content types.
 */
var EZMQContentType = (exports.EZMQContentType = {
    /** PROTOBUF */
    EZMQ_CONTENT_TYPE_PROTOBUF: 0,
    /** BYTEDATA */
    EZMQ_CONTENT_TYPE_BYTEDATA: 1,
    /** AML */
    EZMQ_CONTENT_TYPE_AML: 2,
    /** JSON */
    EZMQ_CONTENT_TYPE_JSON: 3,
});
