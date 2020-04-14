#pragma once

#include "OscDataElemStruct.h"


/// Base class to receive OSC messages.
struct PLAYBACKCTRL_API IPlaybackCtrlInterface
{
    virtual ~IPlaybackCtrlInterface()  {}
    virtual const FString & GetDepartmentFilter() const = 0;
    virtual const FString & GetBuildFilter() const = 0;
    virtual void SendEvent(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp) = 0;
};


/// Forward calls to an impl object.
template <class T>
struct PLAYBACKCTRL_API BasicCueReceiver : IPlaybackCtrlInterface
{
    T * const _impl;

    BasicCueReceiver(T * impl) : _impl(impl)
    {
    }

    const FString & GetDepartmentFilter() const final
    {
        return _impl->GetDepartmentFilter();
    }
    
    const FString & GetBuildFilter() const final
       {
           return _impl->GetBuildFilter();
       }

   void SendEvent(const FName & Address, const TArray<FOscDataElemStruct> & Data, const FString & SenderIp) final
   {
       _impl->SendEvent(Address, Data, SenderIp);
   }
};
