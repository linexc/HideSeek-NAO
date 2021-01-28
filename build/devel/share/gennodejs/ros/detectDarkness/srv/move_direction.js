// Auto-generated. Do not edit!

// (in-package detectDarkness.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class move_directionRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.x = null;
      this.y = null;
      this.angle = null;
    }
    else {
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = [];
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = [];
      }
      if (initObj.hasOwnProperty('angle')) {
        this.angle = initObj.angle
      }
      else {
        this.angle = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type move_directionRequest
    // Serialize message field [x]
    bufferOffset = _arraySerializer.float64(obj.x, buffer, bufferOffset, null);
    // Serialize message field [y]
    bufferOffset = _arraySerializer.float64(obj.y, buffer, bufferOffset, null);
    // Serialize message field [angle]
    bufferOffset = _arraySerializer.float64(obj.angle, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type move_directionRequest
    let len;
    let data = new move_directionRequest(null);
    // Deserialize message field [x]
    data.x = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [y]
    data.y = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [angle]
    data.angle = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.x.length;
    length += 8 * object.y.length;
    length += 8 * object.angle.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'detectDarkness/move_directionRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a0956ac46d729f8f73f5b2aba7230f66';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    float64[] x
    float64[] y
    float64[] angle
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new move_directionRequest(null);
    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = []
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = []
    }

    if (msg.angle !== undefined) {
      resolved.angle = msg.angle;
    }
    else {
      resolved.angle = []
    }

    return resolved;
    }
};

class move_directionResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.reply = null;
    }
    else {
      if (initObj.hasOwnProperty('reply')) {
        this.reply = initObj.reply
      }
      else {
        this.reply = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type move_directionResponse
    // Serialize message field [reply]
    bufferOffset = _serializer.bool(obj.reply, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type move_directionResponse
    let len;
    let data = new move_directionResponse(null);
    // Deserialize message field [reply]
    data.reply = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'detectDarkness/move_directionResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '06d4f276c51f7469624c6fbcbf0e7869';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    bool reply
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new move_directionResponse(null);
    if (msg.reply !== undefined) {
      resolved.reply = msg.reply;
    }
    else {
      resolved.reply = false
    }

    return resolved;
    }
};

module.exports = {
  Request: move_directionRequest,
  Response: move_directionResponse,
  md5sum() { return 'f2e70ef85308fdb83273380a5ba777c1'; },
  datatype() { return 'detectDarkness/move_direction'; }
};
