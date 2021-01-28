
(cl:in-package :asdf)

(defsystem "detect_darkness-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "move_direction" :depends-on ("_package_move_direction"))
    (:file "_package_move_direction" :depends-on ("_package"))
  ))