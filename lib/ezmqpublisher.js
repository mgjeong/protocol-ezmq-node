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
var ezmqpub = require('../build/Release/ezmq.node'),
    ezmqEvent = require('./ezmqevent.js'),
    ezmqByteData = require('./ezmqbytedata.js');

//Expose bindings as the module.
exports = module.exports = ezmqpub;

var nezmqPub;
/**
 * @class This class represent EZMQPublisher. It contains APIs to
 *              start/stop publisher and to publish data. <br><br>
 *
 * <b>ProtoType of startCB</b> :- function startCB(erroCode) {} <br>
 * <b>ProtoType of stopCB</b> :- function stopCB(erroCode){}  <br>
 * <b>ProtoType of errorCB</b> :- function errorCB(erroCode){} <br><br>
 *
 * <b>Note:</b> As of now callbacks are not being used. <br>
 *
 * @constructor
 * @param {number} port -Port number.
 * @param {callback} startCB -Start callback.
 * @param {callback} stopCB -Stop callback.
 * @param {callback} errorCB -Error callback.
 */
var EZMQPublisher = (exports.EZMQPublisher = function(
    port,
    startCB,
    stopCB,
    errorCB
) {
    this.nezmqPub = new ezmqpub.NEZMQPublisher(port, startCB, stopCB, errorCB);
});

/**
 * Starts PUB instance.
 *
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQPublisher.prototype.start = function() {
    return this.nezmqPub.start();
};

/**
 * Publish data on the socket for subscribers with/without topic.
 * Data can be EZMQEvent or EZMQByteData.
 *
 * @param {EZMQEvent/EZMQByteData} message -Message to be published.
 * @param {string} topic -Topic on which data needs to be published.
 *
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQPublisher.prototype.publish = function(message, topic) {
    if (typeof topic === 'undefined') {
        if (message instanceof ezmqEvent.EZMQEvent) {
            return this.nezmqPub.publish(message.getAddonObj());
        } else if (message instanceof ezmqByteData.EZMQByteData) {
            return this.nezmqPub.publishByteData(message.getAddonObj());
        }
    }

    if (typeof topic === 'string') {
        if (message instanceof ezmqEvent.EZMQEvent) {
            return this.nezmqPub.publishOnTopic(topic, message.getAddonObj());
        } else if (message instanceof ezmqByteData.EZMQByteData) {
            return this.nezmqPub.publishByteDataOnTopic(
                topic,
                message.getAddonObj()
            );
        }
    } else {
        if (message instanceof ezmqEvent.EZMQEvent) {
            return this.nezmqPub.publishOnTopicList(
                topic,
                message.getAddonObj()
            );
        } else if (message instanceof ezmqByteData.EZMQByteData) {
            return this.nezmqPub.publishByteDataOnList(
                topic,
                message.getAddonObj()
            );
        }
    }
};

/**
 * Get the port of the publisher.
 *
 * @return {number} Port number.
 */
EZMQPublisher.prototype.getPort = function() {
    return this.nezmqPub.getPort();
};

/**
 * Stops PUB instance.
 *
 * @return {EZMQErrorCode} EZMQ_OK on success, otherwise appropriate error code.
 */
EZMQPublisher.prototype.stop = function() {
    return this.nezmqPub.stop();
};
