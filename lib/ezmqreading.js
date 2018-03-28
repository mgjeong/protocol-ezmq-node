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
var ezmqReading = require('../build/Release/ezmq.node');

//Expose bindings as the module.
exports = module.exports = ezmqReading;

var nezmqReading;
/**
 * @class This class represent reading of EZMQEvent.
 *              It contains APIs for creating reading and
 *              getting/setting reading fields.
 * @constructor
 */
var EZMQReading = (exports.EZMQReading = function(eventObj) {
    if (null === eventObj) {
        return;
    }
    this.nezmqReading = new ezmqReading.NEZMQReading(eventObj.getAddonObj());
});

/**
 * Get ID field of reading.
 *
 * @return {string} Id field.
 */
EZMQReading.prototype.getID = function() {
    return this.nezmqReading.getID();
};

/**
 * Get created field of reading.
 *
 * @return {number} Created field.
 */
EZMQReading.prototype.getCreated = function() {
    return this.nezmqReading.getCreated();
};

/**
 * Get modified field of reading.
 *
 * @return {number} Modified field.
 */
EZMQReading.prototype.getModified = function() {
    return this.nezmqReading.getModified();
};

/**
 * Get origin field of reading.
 *
 * @return {number} Origin field.
 */
EZMQReading.prototype.getOrigin = function() {
    return this.nezmqReading.getOrigin();
};

/**
 * Get pushed field of reading.
 *
 * @return {number} Pushed field.
 */
EZMQReading.prototype.getPushed = function() {
    return this.nezmqReading.getPushed();
};

/**
 * Get name field of reading.
 *
 * @return {string} Device field.
 */
EZMQReading.prototype.getName = function() {
    return this.nezmqReading.getName();
};

/**
 * Get value field of reading.
 *
 * @return {string} Device field.
 */
EZMQReading.prototype.getValue = function() {
    return this.nezmqReading.getValue();
};

/**
 * Get device field of reading.
 *
 * @return {string} Device field.
 */
EZMQReading.prototype.getDevice = function() {
    return this.nezmqReading.getDevice();
};

/**
 * Set ID field of reading.
 *
 * @param {string} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setID = function(value) {
    return this.nezmqReading.setID(value);
};

EZMQReading.prototype.setCreated = function(value) {
    return this.nezmqReading.setCreated(value);
};

/**
 * Set modified field of reading.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setModified = function(value) {
    return this.nezmqReading.setModified(value);
};

/**
 * Set origin field of reading.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setOrigin = function(value) {
    return this.nezmqReading.setOrigin(value);
};

/**
 * Set pushed field of reading.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setPushed = function(value) {
    return this.nezmqReading.setPushed(value);
};

/**
 * Set name field of reading.
 *
 * @param {string} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setName = function(value) {
    return this.nezmqReading.setName(value);
};

/**
 * Set value field of reading.
 *
 * @param {string} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setValue = function(value) {
    return this.nezmqReading.setValue(value);
};

/**
 * Set device field of reading.
 *
 * @param {string} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQReading.prototype.setDevice = function(value) {
    return this.nezmqReading.setDevice(value);
};

//This methods are being used internally by ezmq-js layer
EZMQReading.prototype.setAddonObj = function(reading) {
    this.nezmqReading = reading;
};
