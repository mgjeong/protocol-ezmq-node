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
var ezmqApi = require('../build/Release/ezmq.node');

//Expose bindings as the module.
exports = module.exports = ezmqApi;

var nezmqAPI;

/**
 *  @class This class Contains APIs related to initialization, termination
 *               of EZMQ stack.
 *  @constructor
 */
var EZMQAPI = (exports.EZMQAPI = function() {
    this.nezmqAPI = new ezmqApi.NEZMQAPI();
});

/**
 * Initialize required EZMQ components.
 * This API should be called first, before using any EZMQ APIs.
 *
 * @return  {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQAPI.prototype.initialize = function() {
    return this.nezmqAPI.initialize();
};

/**
 * Perform cleanup of EZMQ components.
 *
 * @return  {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQAPI.prototype.terminate = function() {
    return this.nezmqAPI.terminate();
};

/**
 * Get status of EZMQ service.
 *
 * @return {EZMQStatusCode} Current status of EZMQ Service.
 */
EZMQAPI.prototype.getStatus = function() {
    return this.nezmqAPI.getStatus();
};
