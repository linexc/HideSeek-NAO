// Generated by gencpp from file detectDarkness/move_directionResponse.msg
// DO NOT EDIT!


#ifndef DETECTDARKNESS_MESSAGE_MOVE_DIRECTIONRESPONSE_H
#define DETECTDARKNESS_MESSAGE_MOVE_DIRECTIONRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace detectDarkness
{
template <class ContainerAllocator>
struct move_directionResponse_
{
  typedef move_directionResponse_<ContainerAllocator> Type;

  move_directionResponse_()
    : reply(false)  {
    }
  move_directionResponse_(const ContainerAllocator& _alloc)
    : reply(false)  {
  (void)_alloc;
    }



   typedef uint8_t _reply_type;
  _reply_type reply;





  typedef boost::shared_ptr< ::detectDarkness::move_directionResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::detectDarkness::move_directionResponse_<ContainerAllocator> const> ConstPtr;

}; // struct move_directionResponse_

typedef ::detectDarkness::move_directionResponse_<std::allocator<void> > move_directionResponse;

typedef boost::shared_ptr< ::detectDarkness::move_directionResponse > move_directionResponsePtr;
typedef boost::shared_ptr< ::detectDarkness::move_directionResponse const> move_directionResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::detectDarkness::move_directionResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::detectDarkness::move_directionResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace detectDarkness

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::detectDarkness::move_directionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::detectDarkness::move_directionResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::detectDarkness::move_directionResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "06d4f276c51f7469624c6fbcbf0e7869";
  }

  static const char* value(const ::detectDarkness::move_directionResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x06d4f276c51f7469ULL;
  static const uint64_t static_value2 = 0x624c6fbcbf0e7869ULL;
};

template<class ContainerAllocator>
struct DataType< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "detectDarkness/move_directionResponse";
  }

  static const char* value(const ::detectDarkness::move_directionResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
bool reply\n\
\n\
";
  }

  static const char* value(const ::detectDarkness::move_directionResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.reply);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct move_directionResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::detectDarkness::move_directionResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::detectDarkness::move_directionResponse_<ContainerAllocator>& v)
  {
    s << indent << "reply: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.reply);
  }
};

} // namespace message_operations
} // namespace ros

#endif // DETECTDARKNESS_MESSAGE_MOVE_DIRECTIONRESPONSE_H
