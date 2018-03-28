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
var ezmqEvent = require('../build/Release/ezmq.node'),
    ezmqReading = require('./ezmqreading.js');

// Expose bindings as the module.
exports = module.exports = ezmqEvent;

var nezmqEvent;

/**
 * @class This class represent one of the supported messsage format
 *              of EZMQ library i.e. Protobuf data. It contains APIs for creating
 *              ezmq event and getting/setting event fields.
 * @constructor
 */
var EZMQEvent = (exports.EZMQEvent = function() {
    this.nezmqEvent = new ezmqEvent.NEZMQEvent();
});

/**
 * Get content-type of EZMQEvent.
 *
 * @return {EZMQContentType} content type.
 */
EZMQEvent.prototype.getContentType = function() {
    return this.nezmqEvent.getContentType();
};

/**
 * Get ID field of event.
 *
 * @return {string} Id field.
 */
EZMQEvent.prototype.getID = function() {
    return this.nezmqEvent.getID();
};

/**
 * Get created field of event.
 *
 * @return {number} Created field.
 */
EZMQEvent.prototype.getCreated = function() {
    return this.nezmqEvent.getCreated();
};

/**
 * Get modified field of event.
 *
 * @return {number} Modified field.
 */
EZMQEvent.prototype.getModified = function() {
    return this.nezmqEvent.getModified();
};

/**
 * Get origin field of event.
 *
 * @return {number} Origin field.
 */
EZMQEvent.prototype.getOrigin = function() {
    return this.nezmqEvent.getOrigin();
};

/**
 * Get pushed field of event.
 *
 * @return {number} Pushed field.
 */
EZMQEvent.prototype.getPushed = function() {
    return this.nezmqEvent.getPushed();
};

/**
 * Get device field of event.
 *
 * @return {string} Device field.
 */
EZMQEvent.prototype.getDevice = function() {
    return this.nezmqEvent.getDevice();
};

/**
 * Get reading count of event.
 *
 * @return {number} Number of readings in event.
 */
EZMQEvent.prototype.getReadingCount = function() {
    return this.nezmqEvent.getReadingCount();
};

/**
 * Get reading in event at given index.
 *
 * @return {EZMQReading} Reading object.
 */
EZMQEvent.prototype.getReading = function(index) {
    if (0 == this.nezmqEvent.getReadingCount()) {
        return undefined;
    }
    var reading = this.nezmqEvent.getReading(index);
    var readingObj = new ezmqEvent.EZMQReading(null);
    readingObj.setAddonObj(reading);
    return readingObj;
};

/**
 * Set ID field of event.
 *
 * @param {string} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQEvent.prototype.setID = function(value) {
    return this.nezmqEvent.setID(value);
};

/**
 * Set created field of event.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQEvent.prototype.setCreated = function(value) {
    return this.nezmqEvent.setCreated(value);
};

/**
 * Set modified field of event.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQEvent.prototype.setModified = function(value) {
    return this.nezmqEvent.setModified(value);
};

/**
 * Set origin field of event.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQEvent.prototype.setOrigin = function(value) {
    return this.nezmqEvent.setOrigin(value);
};

/**
 * Set pushed field of event.
 *
 * @param {number} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQEvent.prototype.setPushed = function(value) {
    return this.nezmqEvent.setPushed(value);
};

/**
 * Set device field of event.
 *
 * @param {string} data -Value to be set.
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQEvent.prototype.setDevice = function(value) {
    return this.nezmqEvent.setDevice(value);
};

//This methods are being used internally by ezmq-js layer
EZMQEvent.prototype.getAddonObj = function() {
    return this.nezmqEvent;
};

EZMQEvent.prototype.setAddonObj = function(eventObj) {
    this.nezmqEvent = eventObj;
};
