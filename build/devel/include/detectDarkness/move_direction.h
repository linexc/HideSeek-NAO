// Generated by gencpp from file detectDarkness/move_direction.msg
// DO NOT EDIT!


#ifndef DETECTDARKNESS_MESSAGE_MOVE_DIRECTION_H
#define DETECTDARKNESS_MESSAGE_MOVE_DIRECTION_H

#include <ros/service_traits.h>


#include <detectDarkness/move_directionRequest.h>
#include <detectDarkness/move_directionResponse.h>


namespace detectDarkness
{

struct move_direction
{

typedef move_directionRequest Request;
typedef move_directionResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct move_direction
} // namespace detectDarkness


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::detectDarkness::move_direction > {
  static const char* value()
  {
    return "f2e70ef85308fdb83273380a5ba777c1";
  }

  static const char* value(const ::detectDarkness::move_direction&) { return value(); }
};

template<>
struct DataType< ::detectDarkness::move_direction > {
  static const char* value()
  {
    return "detectDarkness/move_direction";
  }

  static const char* value(const ::detectDarkness::move_direction&) { return value(); }
};


// service_traits::MD5Sum< ::detectDarkness::move_directionRequest> should match 
// service_traits::MD5Sum< ::detectDarkness::move_direction > 
template<>
struct MD5Sum< ::detectDarkness::move_directionRequest>
{
  static const char* value()
  {
    return MD5Sum< ::detectDarkness::move_direction >::value();
  }
  static const char* value(const ::detectDarkness::move_directionRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::detectDarkness::move_directionRequest> should match 
// service_traits::DataType< ::detectDarkness::move_direction > 
template<>
struct DataType< ::detectDarkness::move_directionRequest>
{
  static const char* value()
  {
    return DataType< ::detectDarkness::move_direction >::value();
  }
  static const char* value(const ::detectDarkness::move_directionRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::detectDarkness::move_directionResponse> should match 
// service_traits::MD5Sum< ::detectDarkness::move_direction > 
template<>
struct MD5Sum< ::detectDarkness::move_directionResponse>
{
  static const char* value()
  {
    return MD5Sum< ::detectDarkness::move_direction >::value();
  }
  static const char* value(const ::detectDarkness::move_directionResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::detectDarkness::move_directionResponse> should match 
// service_traits::DataType< ::detectDarkness::move_direction > 
template<>
struct DataType< ::detectDarkness::move_directionResponse>
{
  static const char* value()
  {
    return DataType< ::detectDarkness::move_direction >::value();
  }
  static const char* value(const ::detectDarkness::move_directionResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // DETECTDARKNESS_MESSAGE_MOVE_DIRECTION_H