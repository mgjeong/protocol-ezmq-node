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
var ezmqByteData = require('../build/Release/ezmq.node');

//Expose bindings as the module.
exports = module.exports = ezmqByteData;

var nezmqByteData;

/**
 * @class This class represent one of the supported messsage format
 *              of EZMQ library i.e. Byte data. It contains APIs for creating
 *              byte data and getting/setting its fields.
 *
 * @constructor
 * @param {Uint8Array} data -Byte data.
 * @param {number} length -Data length.
 */
var EZMQByteData = (exports.EZMQByteData = function(data, length) {
    if (0 === length) {
        return;
    }
    this.nezmqByteData = new ezmqByteData.NEZMQByteData(data, length);
});

/**
 * Get content-type of EZMQByteData.
 *
 * @return {EZMQContentType} content type.
 */
EZMQByteData.prototype.getContentType = function() {
    return this.nezmqByteData.getContentType();
};

/**
 * Get length of data.
 *
 * @return {number} Length of data.
 */
EZMQByteData.prototype.getLength = function() {
    return this.nezmqByteData.getLength();
};

/**
 * Get message's byte data.
 *
 * @return {Uint8Array} Byte data.
 */
EZMQByteData.prototype.getByteData = function() {
    return this.nezmqByteData.getByteData();
};

/**
 * Set byte data.
 * This method can be used to update data
 * of already created EZMQByteData object.
 *
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQByteData.prototype.setByteData = function(data, length) {
    return this.nezmqByteData.setByteData(data, length);
};

//This methods are being used internally by ezmq-js layer
EZMQByteData.prototype.getAddonObj = function() {
    return this.nezmqByteData;
};

EZMQByteData.prototype.setAddonObj = function(byteDataObj) {
    this.nezmqByteData = byteDataObj;
};
