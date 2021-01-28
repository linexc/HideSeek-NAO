// Generated by gencpp from file detect_darkness/move_directionRequest.msg
// DO NOT EDIT!


#ifndef DETECT_DARKNESS_MESSAGE_MOVE_DIRECTIONREQUEST_H
#define DETECT_DARKNESS_MESSAGE_MOVE_DIRECTIONREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace detect_darkness
{
template <class ContainerAllocator>
struct move_directionRequest_
{
  typedef move_directionRequest_<ContainerAllocator> Type;

  move_directionRequest_()
    : x()
    , y()
    , angle()  {
    }
  move_directionRequest_(const ContainerAllocator& _alloc)
    : x(_alloc)
    , y(_alloc)
    , angle(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _x_type;
  _x_type x;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _y_type;
  _y_type y;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _angle_type;
  _angle_type angle;





  typedef boost::shared_ptr< ::detect_darkness::move_directionRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::detect_darkness::move_directionRequest_<ContainerAllocator> const> ConstPtr;

}; // struct move_directionRequest_

typedef ::detect_darkness::move_directionRequest_<std::allocator<void> > move_directionRequest;

typedef boost::shared_ptr< ::detect_darkness::move_directionRequest > move_directionRequestPtr;
typedef boost::shared_ptr< ::detect_darkness::move_directionRequest const> move_directionRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::detect_darkness::move_directionRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::detect_darkness::move_directionRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace detect_darkness

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::detect_darkness::move_directionRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::detect_darkness::move_directionRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::detect_darkness::move_directionRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a0956ac46d729f8f73f5b2aba7230f66";
  }

  static const char* value(const ::detect_darkness::move_directionRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa0956ac46d729f8fULL;
  static const uint64_t static_value2 = 0x73f5b2aba7230f66ULL;
};

template<class ContainerAllocator>
struct DataType< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "detect_darkness/move_directionRequest";
  }

  static const char* value(const ::detect_darkness::move_directionRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
float64[] x\n\
float64[] y\n\
float64[] angle\n\
\n\
";
  }

  static const char* value(const ::detect_darkness::move_directionRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.angle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct move_directionRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::detect_darkness::move_directionRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::detect_darkness::move_directionRequest_<ContainerAllocator>& v)
  {
    s << indent << "x[]" << std::endl;
    for (size_t i = 0; i < v.x.size(); ++i)
    {
      s << indent << "  x[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.x[i]);
    }
    s << indent << "y[]" << std::endl;
    for (size_t i = 0; i < v.y.size(); ++i)
    {
      s << indent << "  y[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.y[i]);
    }
    s << indent << "angle[]" << std::endl;
    for (size_t i = 0; i < v.angle.size(); ++i)
    {
      s << indent << "  angle[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.angle[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // DETECT_DARKNESS_MESSAGE_MOVE_DIRECTIONREQUEST_H
