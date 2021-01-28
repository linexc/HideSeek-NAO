;; Auto-generated. Do not edit!


(when (boundp 'detectDarkness::move_direction)
  (if (not (find-package "DETECTDARKNESS"))
    (make-package "DETECTDARKNESS"))
  (shadow 'move_direction (find-package "DETECTDARKNESS")))
(unless (find-package "DETECTDARKNESS::MOVE_DIRECTION")
  (make-package "DETECTDARKNESS::MOVE_DIRECTION"))
(unless (find-package "DETECTDARKNESS::MOVE_DIRECTIONREQUEST")
  (make-package "DETECTDARKNESS::MOVE_DIRECTIONREQUEST"))
(unless (find-package "DETECTDARKNESS::MOVE_DIRECTIONRESPONSE")
  (make-package "DETECTDARKNESS::MOVE_DIRECTIONRESPONSE"))

(in-package "ROS")





(defclass detectDarkness::move_directionRequest
  :super ros::object
  :slots (_x _y _angle ))

(defmethod detectDarkness::move_directionRequest
  (:init
   (&key
    ((:x __x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y __y) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:angle __angle) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _x __x)
   (setq _y __y)
   (setq _angle __angle)
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; float64[] _x
    (* 8    (length _x)) 4
    ;; float64[] _y
    (* 8    (length _y)) 4
    ;; float64[] _angle
    (* 8    (length _angle)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64[] _x
     (write-long (length _x) s)
     (dotimes (i (length _x))
       (sys::poke (elt _x i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _y
     (write-long (length _y) s)
     (dotimes (i (length _y))
       (sys::poke (elt _y i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _angle
     (write-long (length _angle) s)
     (dotimes (i (length _angle))
       (sys::poke (elt _angle i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64[] _x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _angle
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _angle (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _angle i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass detectDarkness::move_directionResponse
  :super ros::object
  :slots (_reply ))

(defmethod detectDarkness::move_directionResponse
  (:init
   (&key
    ((:reply __reply) nil)
    )
   (send-super :init)
   (setq _reply __reply)
   self)
  (:reply
   (&optional __reply)
   (if __reply (setq _reply __reply)) _reply)
  (:serialization-length
   ()
   (+
    ;; bool _reply
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _reply
       (if _reply (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _reply
     (setq _reply (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass detectDarkness::move_direction
  :super ros::object
  :slots ())

(setf (get detectDarkness::move_direction :md5sum-) "f2e70ef85308fdb83273380a5ba777c1")
(setf (get detectDarkness::move_direction :datatype-) "detectDarkness/move_direction")
(setf (get detectDarkness::move_direction :request) detectDarkness::move_directionRequest)
(setf (get detectDarkness::move_direction :response) detectDarkness::move_directionResponse)

(defmethod detectDarkness::move_directionRequest
  (:response () (instance detectDarkness::move_directionResponse :init)))

(setf (get detectDarkness::move_directionRequest :md5sum-) "f2e70ef85308fdb83273380a5ba777c1")
(setf (get detectDarkness::move_directionRequest :datatype-) "detectDarkness/move_directionRequest")
(setf (get detectDarkness::move_directionRequest :definition-)
      "

float64[] x
float64[] y
float64[] angle

---

bool reply

")

(setf (get detectDarkness::move_directionResponse :md5sum-) "f2e70ef85308fdb83273380a5ba777c1")
(setf (get detectDarkness::move_directionResponse :datatype-) "detectDarkness/move_directionResponse")
(setf (get detectDarkness::move_directionResponse :definition-)
      "

float64[] x
float64[] y
float64[] angle

---

bool reply

")



(provide :detectDarkness/move_direction "f2e70ef85308fdb83273380a5ba777c1")


