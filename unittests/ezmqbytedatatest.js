var assert = require('assert');
var ezmq = require('../');

var array = new Uint8Array(4);
array[0] = 0x81;
array[1] = 0x01;
array[2] = 0x10;
array[3] = 0x11;
var ezmqByteData = new ezmq.EZMQByteData(array, 4);

describe('#getContentType()', function() {
    it('should return byte data as type', function() {
        assert.equal(
            ezmqByteData.getContentType(),
            ezmq.EZMQContentType.EZMQ_CONTENT_TYPE_BYTEDATA
        );
    });
});

describe('#getLength()', function() {
    it('should return length of byte data', function() {
        assert.equal(ezmqByteData.getLength(), 4);
    });
});

describe('#getByteData()', function() {
    it('should return byte data', function() {
        assert.equal(ezmqByteData.getByteData()[0], array[0]);
    });
});

describe('#setByteData()', function() {
    it('should return right byte data', function() {
        var newArray = new Uint8Array(1);
        newArray[0] = 0x20;
        assert.equal(
            ezmqByteData.setByteData(newArray, 1),
            ezmq.EZMQErrorCode.EZMQ_OK
        );
        assert.equal(ezmqByteData.getLength(), 1);
        assert.equal(ezmqByteData.getByteData()[0], newArray[0]);
    });
});

describe('#invalidLength()', function() {
    it('should return undefined', function() {
        var byteDataObj = new ezmq.EZMQByteData(array, 0);
    });
});