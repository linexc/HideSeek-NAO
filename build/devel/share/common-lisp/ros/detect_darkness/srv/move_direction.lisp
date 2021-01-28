; Auto-generated. Do not edit!


(cl:in-package detect_darkness-srv)


;//! \htmlinclude move_direction-request.msg.html

(cl:defclass <move_direction-request> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (y
    :reader y
    :initarg :y
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (angle
    :reader angle
    :initarg :angle
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass move_direction-request (<move_direction-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <move_direction-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'move_direction-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name detect_darkness-srv:<move_direction-request> is deprecated: use detect_darkness-srv:move_direction-request instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <move_direction-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader detect_darkness-srv:x-val is deprecated.  Use detect_darkness-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <move_direction-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader detect_darkness-srv:y-val is deprecated.  Use detect_darkness-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <move_direction-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader detect_darkness-srv:angle-val is deprecated.  Use detect_darkness-srv:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <move_direction-request>) ostream)
  "Serializes a message object of type '<move_direction-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'x))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'y))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'angle))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <move_direction-request>) istream)
  "Deserializes a message object of type '<move_direction-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'x) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'x)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'y) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'y)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'angle) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'angle)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<move_direction-request>)))
  "Returns string type for a service object of type '<move_direction-request>"
  "detect_darkness/move_directionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'move_direction-request)))
  "Returns string type for a service object of type 'move_direction-request"
  "detect_darkness/move_directionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<move_direction-request>)))
  "Returns md5sum for a message object of type '<move_direction-request>"
  "f2e70ef85308fdb83273380a5ba777c1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'move_direction-request)))
  "Returns md5sum for a message object of type 'move_direction-request"
  "f2e70ef85308fdb83273380a5ba777c1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<move_direction-request>)))
  "Returns full string definition for message of type '<move_direction-request>"
  (cl:format cl:nil "~%~%float64[] x~%float64[] y~%float64[] angle~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'move_direction-request)))
  "Returns full string definition for message of type 'move_direction-request"
  (cl:format cl:nil "~%~%float64[] x~%float64[] y~%float64[] angle~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <move_direction-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'angle) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <move_direction-request>))
  "Converts a ROS message object to a list"
  (cl:list 'move_direction-request
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':angle (angle msg))
))
;//! \htmlinclude move_direction-response.msg.html

(cl:defclass <move_direction-response> (roslisp-msg-protocol:ros-message)
  ((reply
    :reader reply
    :initarg :reply
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass move_direction-response (<move_direction-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <move_direction-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'move_direction-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name detect_darkness-srv:<move_direction-response> is deprecated: use detect_darkness-srv:move_direction-response instead.")))

(cl:ensure-generic-function 'reply-val :lambda-list '(m))
(cl:defmethod reply-val ((m <move_direction-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader detect_darkness-srv:reply-val is deprecated.  Use detect_darkness-srv:reply instead.")
  (reply m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <move_direction-response>) ostream)
  "Serializes a message object of type '<move_direction-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'reply) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <move_direction-response>) istream)
  "Deserializes a message object of type '<move_direction-response>"
    (cl:setf (cl:slot-value msg 'reply) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<move_direction-response>)))
  "Returns string type for a service object of type '<move_direction-response>"
  "detect_darkness/move_directionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'move_direction-response)))
  "Returns string type for a service object of type 'move_direction-response"
  "detect_darkness/move_directionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<move_direction-response>)))
  "Returns md5sum for a message object of type '<move_direction-response>"
  "f2e70ef85308fdb83273380a5ba777c1")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'move_direction-response)))
  "Returns md5sum for a message object of type 'move_direction-response"
  "f2e70ef85308fdb83273380a5ba777c1")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<move_direction-response>)))
  "Returns full string definition for message of type '<move_direction-response>"
  (cl:format cl:nil "~%bool reply~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'move_direction-response)))
  "Returns full string definition for message of type 'move_direction-response"
  (cl:format cl:nil "~%bool reply~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <move_direction-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <move_direction-response>))
  "Converts a ROS message object to a list"
  (cl:list 'move_direction-response
    (cl:cons ':reply (reply msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'move_direction)))
  'move_direction-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'move_direction)))
  'move_direction-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'move_direction)))
  "Returns string type for a service object of type '<move_direction>"
  "detect_darkness/move_direction")